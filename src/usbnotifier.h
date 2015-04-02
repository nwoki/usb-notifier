#ifndef USBNOTIFIER_H
#define USBNOTIFIER_H

#include <QtCore/QThread>

class libusb_device;


namespace UsbNotifier {

class UsbDevice;
class UsbNotifierPrivate;


/**
 * @class UsbNotifier
 * @brief Usb notification class
 *
 * This class notifies when a usb device is pluggin in or detached from the current system
 *
 * @author Francesco Nwokeka <francesco.nwokeka@gmail.com>
 */

class UsbNotifier : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for UsbNotifier.
     *
     * Creates a notifier class that looks out for attach and detach events of libusb.
     * If a vendor and/or product id is/are given, ONLY events regarding those devices will
     * be notified.
     *
     * If nor vendor or product are specified, then ALL devices are subject to attach/detach notification
     *
     * @param vendor id of the vendor to be notified about.
     * @param product id of the product to be notified about.
     */
    UsbNotifier(int vendor = 0, int product = 0, QObject *parent = 0);
    ~UsbNotifier();

    UsbDevice* extractUsbDevice(libusb_device *device);

Q_SIGNALS:
    /**
     * emitted when a device has beed attached to the system
     * @param device pointer to the UsbNotifier::UsbDevice object created on the event
     */
    void deviceAttached(UsbDevice *device);

    /**
     * emitted when a device has been detached
     * @param deviceAddress address of the device detached from the machine
     */
    void deviceDetached(int deviceAddress);

protected:
    void run();

private:
    UsbNotifierPrivate * const d;
};

}

#endif  // USBNOTIFIER_H
