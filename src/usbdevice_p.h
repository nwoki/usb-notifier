class libusb_device;

namespace UsbNotifier {

class UsbDevicePrivate
{
public:
    UsbDevicePrivate()
        : libusbDevice(nullptr)
        , address(0)
        , productId(0)
        , vendorId(0)
    {}

    libusb_device *libusbDevice;
    quint8 address;
    quint16 productId;
    quint16 vendorId;
    QString manufacturer;
    QString product;
};

}
