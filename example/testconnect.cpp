#include "testconnect.h"

#include <UsbNotifier/UsbDevice>
#include <UsbNotifier/UsbNotifier>

#include <libusb-1.0/libusb.h>

TestConnect::TestConnect(QObject *parent)
    : QObject(parent)
    , m_usb(new UsbNotifier::UsbNotifier(0, 0, this))
{
    m_usb->start();

    connect(m_usb, &UsbNotifier::UsbNotifier::deviceAttached, [] (UsbNotifier::UsbDevice *dev) {
        qDebug("[TestConnect::TestConnect] GOT A DEVICE");
    });
}

TestConnect::~TestConnect()
{
    delete m_usb;
}
