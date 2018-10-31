#include <QCoreApplication>
#include <QTest>

#include "modbusserver.h"
#include "devicemodbusethernet_test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DeviceModbusEthernet_Test deviceModbusEthernetTest;

    QTest::qExec(&deviceModbusEthernetTest);

}
