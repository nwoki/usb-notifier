#include "inherit.h"

#include <QtCore/QDebug>

Inherit::Inherit(UsbNotifier::UsbDevice *device)
    : UsbDevice(*device)
{
    qDebug() << "My Prod inherretind: " << product();
    qDebug() << "My MANUFAC INHERITIED: " << manufacturer();
}

Inherit::~Inherit()
{
    qDebug("[Inherit::~Inherit]");
}
