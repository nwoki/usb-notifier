#ifndef USBDEVICE_H
#define USBDEVICE_H

#include <QtCore/QObject>

class libusb_device;

namespace UsbNotifier {

class UsbDevicePrivate;


class UsbDevice : public QObject
{
    Q_OBJECT

public:
    UsbDevice(const UsbDevice &dev);
    UsbDevice(libusb_device *device = 0, QObject *parent = 0);
    virtual ~UsbDevice();

private:
    UsbDevicePrivate * const d;
};

};

#endif  // USBDEVICE_H
