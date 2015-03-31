#ifndef INHERIT_H
#define INHERIT_H

#include <UsbNotifier/UsbDevice>

class Inherit : public UsbNotifier::UsbDevice
{
    Q_OBJECT

public:
    Inherit(UsbNotifier::UsbDevice *device);
    virtual ~Inherit();
};

#endif  // INHERIT_H
