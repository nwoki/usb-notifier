class libusb_device;

class UsbDevicePrivate
{
public:
    UsbDevicePrivate()
        : libusbDevice(nullptr)
    {}

    libusb_device *libusbDevice;
};
