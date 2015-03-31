#ifndef USBNOTIFIER_H
#define USBNOTIFIER_H

#include <QtCore/QThread>

class UsbNotifierPrivate;

class UsbNotifier : public QThread
{
    Q_OBJECT

public:
    UsbNotifier(int vendor = 0, int product = 0, QObject *parent = 0);
    ~UsbNotifier();

Q_SIGNALS:
    void deviceAttached();

protected:
    void run();

private:
    UsbNotifierPrivate * const d;
};


#endif  // USBNOTIFIER_H
