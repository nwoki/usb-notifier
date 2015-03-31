#ifndef TESTCONNECT_H
#define TESTCONNECT_H

#include <QtCore/QObject>

namespace UsbNotifier {
    class UsbNotifier;
};


class TestConnect : public QObject
{
    Q_OBJECT

public:
    TestConnect(QObject *parent = 0);
    ~TestConnect();

private:
    UsbNotifier::UsbNotifier *m_usb;
};

#endif  // TESTCONNECT_H
