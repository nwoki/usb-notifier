#include "usbdevice.h"
#include "usbdevice_p.h"

#include <libusb-1.0/libusb.h>


namespace UsbNotifier {

UsbDevice::UsbDevice(const UsbDevice &dev)
    : QObject(dev.parent())
    , d(dev.d)
{
}

UsbDevice::UsbDevice(int address
                , int busNumber
                , int vendorId
                , int portNumber
                , int productId
                , char *manufacturer
                , char *product
                , libusb_device *device
                , QObject *parent)
    : QObject(parent)
    , d(new UsbDevicePrivate)
{
    d->address = address;
    d->busNumber = busNumber;
    d->vendorId = vendorId;
    d->productId = productId;
    d->manufacturer = QString(manufacturer);
    d->portNumber = portNumber;
    d->product = QString(product);
    d->libusbDevice = device;
}

UsbDevice::UsbDevice(QObject *parent)
    : QObject(parent)
    , d(new UsbDevicePrivate)
{
}


UsbDevice::~UsbDevice()
{
    // TODO delete libusbdevice (close it first if open)
    qDebug("[UsbDevice::~UsbDevice]");
}

int UsbDevice::address() const
{
    return d->address;
}

int UsbDevice::busNumber() const
{
    return d->busNumber;
}

QString UsbDevice::manufacturer() const
{
    return d->manufacturer;
}

int UsbDevice::portNumber() const
{
    return d->portNumber;
}

QString UsbDevice::product() const
{
    return d->product;
}

int UsbDevice::productId() const
{
    return d->productId;
}

int UsbDevice::vendorId() const
{
    return d->vendorId;
}

}
