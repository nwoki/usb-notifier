#include "usbdevice.h"
#include "usbdevice_p.h"

#include <libusb-1.0/libusb.h>


UsbDevice::UsbDevice(const UsbDevice &dev)
    : QObject(dev.parent())
    , d(new UsbDevicePrivate)
{
}

UsbDevice::UsbDevice(libusb_device* device, QObject* parent)
    : QObject(parent)
    , d(new UsbDevicePrivate)
{
    d->libusbDevice = device;
}

UsbDevice::~UsbDevice()
{
    // TODO delete libusbdevice (close it first if open)
    delete d;
}
