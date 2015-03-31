#include <QtCore/QCoreApplication>

#include "testconnect.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TestConnect test;

    return a.exec();
}
