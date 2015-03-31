class libusb_device;

namespace UsbNotifier {

class UsbDevicePrivate
{
public:
    UsbDevicePrivate()
        : libusbDevice(nullptr)
    {}

    libusb_device *libusbDevice;
};

}
