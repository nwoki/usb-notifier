#include <QtCore/QSharedData>

class libusb_device;

namespace UsbNotifier {

class UsbDevicePrivate : public QSharedData
{
public:
    UsbDevicePrivate(const UsbDevicePrivate &other)
        : QSharedData(other)
        , libusbDevice(other.libusbDevice)
        , address(other.address)
        , busNumber(other.busNumber)
        , portNumber(other.portNumber)
        , productId(other.productId)
        , vendorId(other.vendorId)
        , manufacturer(other.manufacturer)
        , product(other.product)
    {}

    UsbDevicePrivate()
        : libusbDevice(nullptr)
        , address(0)
        , busNumber(0)
        , portNumber(0)
        , productId(0)
        , vendorId(0)
    {}

    libusb_device *libusbDevice;
    quint8 address;
    quint8 busNumber;
    quint8 portNumber;
    quint16 productId;
    quint16 vendorId;
    QString manufacturer;
    QString product;
};

}
