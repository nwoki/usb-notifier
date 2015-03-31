#include "usbdevice.h"
#include "usbnotifier.h"
#include "usbnotifier_p.h"

#include <libusb-1.0/libusb.h>

#include <QtCore/QDebug>

namespace UsbNotifier {

static UsbNotifier *s_me = 0;


int deviceInsertCallback(libusb_context *ctx, libusb_device *device, libusb_hotplug_event event, void *user_data)
{
    Q_EMIT s_me->deviceAttached(new UsbDevice(device));
    return 0;
}

UsbNotifier::UsbNotifier(int vendor, int product, QObject *parent)
    : QThread(parent)
    , d(new UsbNotifierPrivate)
{
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

    qDebug() << "CALLBACK BIND RESULT: " << result;
}

UsbNotifier::~UsbNotifier()
{
    delete d;
}

void UsbNotifier::run()
{
    while (1) {
        libusb_handle_events(NULL);
    }
}

}

