#include "usbdevice.h"

namespace UsbNotifier {

class UsbNotifierPrivate
{
public:
    UsbNotifierPrivate()
        : vendor(0)
        , product(0)
        , supportsHotplug(false)
        , end(false)
    {}

    int vendor;
    int product;
    bool supportsHotplug;
    bool end;
};

}
