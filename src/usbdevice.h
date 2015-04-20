#ifndef USBDEVICE_H
#define USBDEVICE_H

#include <QtCore/QObject>
#include <QtCore/QSharedDataPointer>

class libusb_device;

namespace UsbNotifier {

class UsbDevicePrivate;


/**
 * @class UsbDevice
 * @brief rappresentation of a UsbDevice
 *
 * A class used to rappresent a usb device detected by libusb
 *
 * @author Francesco Nwokeka <francesco.nwokeka@gmail.com>
 */

class UsbDevice : public QObject
{
    Q_OBJECT

public:
    UsbDevice(const UsbDevice &dev);
    UsbDevice(int address
            , int busNumber
            , int vendorId
            , int portNumber
            , int productId
            , char *manufacturer
            , char *product
            , libusb_device *device
            , QObject *parent = 0);
    UsbDevice(QObject* parent = 0);

    virtual ~UsbDevice();

    /** @return the usb address for the device */
    int address() const;

    /** @return the usb bus number of the device */
    int busNumber() const;

    /** @return the manufacturer of the device */
    QString manufacturer() const;

    /** @return the usb port number */
    int portNumber() const;

    /** @return the device product name */
    QString product() const;

    /** @return the device product id */
    int productId() const;

    /** @return the device vendor id */
    int vendorId() const;


private:
    QSharedDataPointer<UsbDevicePrivate> d;
};

};

#endif  // USBDEVICE_H
