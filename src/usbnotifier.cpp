#include "usbdevice.h"
#include "usbnotifier.h"
#include "usbnotifier_p.h"

#include <libusb-1.0/libusb.h>

#include <QtCore/QDebug>

namespace UsbNotifier {

static UsbNotifier *s_me = 0;

int deviceDetachCallback(libusb_context *ctx, libusb_device *device, libusb_hotplug_event event, void *user_data)
{
    Q_EMIT s_me->deviceDetached(libusb_get_device_address(device));

    // TODO remove the device from the cache
    return 0;
}

int deviceInsertCallback(libusb_context *ctx, libusb_device *device, libusb_hotplug_event event, void *user_data)
{
    Q_UNUSED(user_data)

    UsbDevice *attachedDevice = s_me->extractUsbDevice(device);

    if (attachedDevice) {
        Q_EMIT s_me->deviceAttached(attachedDevice);
    }

    return 0;
}

UsbNotifier::UsbNotifier(int vendor, int product, QObject *parent)
    : QThread(parent)
    , d(new UsbNotifierPrivate)
{
    // register to the QMetaSystem so Qt knows how to pass arount the object
    qRegisterMetaType<UsbDevice>("UsbDevice");

    if (!s_me) {
        s_me = this;
    }

    d->vendor = vendor;
    d->product = product;

    libusb_hotplug_callback_handle attachHandle;
    libusb_hotplug_callback_handle detachHandle;
    libusb_init(NULL);

    if (libusb_has_capability(LIBUSB_CAP_HAS_HOTPLUG)) {
        // TODO setup hotplug callbacks
        qDebug("This device correctly supports callback");
    } else {
        // TODO use thread with manual update
    }

    int result = libusb_hotplug_register_callback(NULL
                                                , LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED
                                                , LIBUSB_HOTPLUG_ENUMERATE
                                                , d->vendor == 0 ? LIBUSB_HOTPLUG_MATCH_ANY : d->vendor
                                                , d->product == 0 ? LIBUSB_HOTPLUG_MATCH_ANY : d->product
                                                , LIBUSB_HOTPLUG_MATCH_ANY
                                                , &deviceInsertCallback
                                                , NULL
                                                , &attachHandle);

    // TODO handle callback registration fail
    qDebug() << "CALLBACK BIND RESULT: " << result;

    result = libusb_hotplug_register_callback(NULL
                                            , LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT
                                            , LIBUSB_HOTPLUG_ENUMERATE
                                            , d->vendor == 0 ? LIBUSB_HOTPLUG_MATCH_ANY : d->vendor
                                            , d->product == 0 ? LIBUSB_HOTPLUG_MATCH_ANY : d->product
                                            , LIBUSB_HOTPLUG_MATCH_ANY
                                            , &deviceDetachCallback
                                            , NULL
                                            , &detachHandle);

    // TODO handle callback registration fail
    qDebug() << "CALLBACK BIND RESULT: " << result;
}

UsbNotifier::~UsbNotifier()
{
    libusb_exit(NULL);
    delete d;
}

UsbDevice* UsbNotifier::extractUsbDevice(libusb_device *device)
{
    struct libusb_device_descriptor descriptor;
    struct libusb_device_handle *myHandle = nullptr;
    int operationResult = 0;

    if (libusb_get_device_descriptor(device, &descriptor) < 0) {
        qDebug("COMPLETE FAIL");
        return nullptr;
    }

    // I need to open the device to get more information about the usb
    operationResult = libusb_open(device, &myHandle);

    if (operationResult < 0) {
        qDebug() << "UsbNotifier::deviceInsertCallback - Can't open usb device @ " << libusb_get_device_address(device) << " ERROR NO: " << operationResult;
        return nullptr;
    }

    char manufacturer[256];
    char product[256];

    operationResult = libusb_get_string_descriptor_ascii(myHandle
    , descriptor.iManufacturer
    , (unsigned char*)manufacturer
    , sizeof(manufacturer));

    if (operationResult < 0) {
        qDebug() << "UsbNotifier::deviceInsertCallback - something went wrong while extracting the manufacturer";
        return nullptr;
    }

    operationResult = libusb_get_string_descriptor_ascii(myHandle
    , descriptor.iProduct
    , (unsigned char*)product
    , sizeof(product));

    if (operationResult < 0) {
        qDebug() << "UsbNotifier::deviceInsertCallback - something went wrong while extracting the product";
        return nullptr;
    }

    libusb_close(myHandle);

    return new UsbDevice(libusb_get_device_address(device)
                        , descriptor.idVendor
                        , descriptor.idProduct
                        , manufacturer
                        , product
                        , device);
}


void UsbNotifier::run()
{
    // do a quick check for already plugged in usb devices
    int result = 0;
    libusb_device **deviceList;

    result = libusb_get_device_list(NULL, &deviceList);

    if (result < 0) {
        // TODO handle error
        qDebug() << "[UsbNotifier::run] result value: " << result;
        qDebug() << "UsbNotifier::run] ERROR: " << libusb_error_name(result);
    } else {
        libusb_device_handle *handle = nullptr;

        for (int i = 0; i < result; ++i) {
            // test if the device is usable. There might be some usb device which we don't have permission
            // to operate on. This test is done by a simple libusb_open/close test.
            if (libusb_open(deviceList[i], &handle) == LIBUSB_SUCCESS) {
                libusb_close(handle);

                UsbDevice *usbDevice = extractUsbDevice(deviceList[i]);

                if (usbDevice && (d->product == 0 || d->vendor == 0)) {
                    Q_EMIT deviceAttached(usbDevice);
                } else {
                    if (usbDevice
                        && (usbDevice->productId() == d->product && usbDevice->vendorId() == d->vendor)) {
                        Q_EMIT deviceAttached(usbDevice);
                    }
                }
            }
        }

        libusb_free_device_list(deviceList, 1);
    }

    // and now start watching for events
    while (1) {
        libusb_handle_events(NULL);
    }
}

}

