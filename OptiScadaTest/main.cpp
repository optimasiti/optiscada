#include <QCoreApplication>
#include <QTest>

#include "modbusserver.h"
#include "devicemodbusethernet_test.h"
#include "scadabuilder_test.h"
#include "scadabuilder.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DeviceModbusEthernet_Test deviceModbusEthernetTest;
    ScadaBuilder_Test scadaBuilderTest;

    QTest::qExec(&deviceModbusEthernetTest);
    QTest::qExec(&scadaBuilderTest);

}
