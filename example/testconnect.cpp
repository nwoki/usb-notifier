#include "inherit.h"
#include "testconnect.h"

#include <UsbNotifier/UsbDevice>
#include <UsbNotifier/UsbNotifier>

#include <QtCore/QDebug>

#include <libusb-1.0/libusb.h>

TestConnect::TestConnect(QObject *parent)
    : QObject(parent)
    , m_usb(new UsbNotifier::UsbNotifier(0, 0, this))
{
    connect(m_usb, &UsbNotifier::UsbNotifier::deviceAttached, [] (UsbNotifier::UsbDevice *dev) {
        qDebug("[TestConnect::TestConnect] GOT A DEVICE");

        qDebug() << "MANUFACTURER: " << dev->manufacturer();
        qDebug() << "PRODUCT: " << dev->product();

        // create inhereted obj to test
        Inherit *in = new Inherit(dev);
        delete in;
    });

    m_usb->start();
}

TestConnect::~TestConnect()
{
    delete m_usb;
}
