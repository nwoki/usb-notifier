#include "usbdevice.h"
#include "usbnotifier.h"
#include "usbnotifier_p.h"

#include <libusb-1.0/libusb.h>

#include <QtCore/QDebug>

namespace UsbNotifier {

static UsbNotifier *s_me = 0;


int deviceInsertCallback(libusb_context *ctx, libusb_device *device, libusb_hotplug_event event, void *user_data)
{
    struct libusb_device_descriptor descriptor;
    struct libusb_device_handle *myHandle = nullptr;
    int operationResult = 0;

    if (libusb_get_device_descriptor(device, &descriptor) < 0) {
        qDebug("COMPLETE FAIL");
        return -1;
    }

    // I need to open the device to get more information about the usb
    operationResult = libusb_open(device, &myHandle);

    if (operationResult < 0) {
        qDebug() << "UsbNotifier::deviceInsertCallback - Can't open usb device @ " << libusb_get_device_address(device) << " ERROR NO: " << operationResult;
        return -1;
    }

    char manufacturer[256];
    char product[256];

    operationResult = libusb_get_string_descriptor_ascii(myHandle
                                                        , descriptor.iManufacturer
                                                        , (unsigned char*)manufacturer
                                                        , sizeof(manufacturer));

    if (operationResult < 0) {
        qDebug() << "UsbNotifier::deviceInsertCallback - something went wrong while extracting the manufacturer";
    }

    operationResult = libusb_get_string_descriptor_ascii(myHandle
                                                        , descriptor.iProduct
                                                        , (unsigned char*)product
                                                        , sizeof(product));

    if (operationResult < 0) {
        qDebug() << "UsbNotifier::deviceInsertCallback - something went wrong while extracting the product";
    }

    libusb_close(myHandle);

    Q_EMIT s_me->deviceAttached(new UsbDevice(libusb_get_device_address(device)
                                            , descriptor.idVendor
                                            , descriptor.idProduct
                                            , manufacturer
                                            , product
                                            , device));

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

    libusb_hotplug_callback_handle handle;
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
                                                , &handle);

    // TODO handle callback registration fail
    qDebug() << "CALLBACK BIND RESULT: " << result;
}

UsbNotifier::~UsbNotifier()
{
    libusb_exit(NULL);

    delete d;
}

void UsbNotifier::run()
{
    while (1) {
        libusb_handle_events(NULL);
    }
}

}

