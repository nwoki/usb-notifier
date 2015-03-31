#include "usbdevice.h"
#include "usbdevice_p.h"

#include <libusb-1.0/libusb.h>


namespace UsbNotifier {

UsbDevice::UsbDevice(const UsbDevice &dev)
    : QObject(dev.parent())
    , d(new UsbDevicePrivate)
{
}

UsbDevice::UsbDevice(int address
                , int vendorId
                , int productId
                , char *manufacturer
                , char *product
                , libusb_device *device
                , QObject *parent)
    : QObject(parent)
    , d(new UsbDevicePrivate)
{
    d->address = address;
    d->vendorId = vendorId;
    d->productId = productId;
    d->manufacturer = QString(manufacturer);
    d->product = QString(product);
    d->libusbDevice = device;
}

UsbDevice::UsbDevice(QObject *parent)
    : QObject(parent)
    , d(new UsbDevicePrivate)
{
    d->address = 0;
    d->vendorId = 0;
    d->productId = 0;
    d->libusbDevice = nullptr;
}


UsbDevice::~UsbDevice()
{
    // TODO delete libusbdevice (close it first if open)
    delete d;
}

QString UsbDevice::manufacturer() const
{
    return d->manufacturer;
}

}
