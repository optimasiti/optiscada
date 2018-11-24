#include <QCoreApplication>
#include <QTest>

#include "modbusserver.h" //TODO
#include "devicemodbusethernet_test.h"
#include "scadabuilder_test.h"
#include "alarmsp_test.h"
#include "scadabuilder.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //TODO
    //DeviceModbusEthernet_Test deviceModbusEthernetTest;
    //ScadaBuilder_Test scadaBuilderTest;

    AlarmSP_Test alarmSPTest;

//    QTest::qExec(&deviceModbusEthernetTest);
//    QTest::qExec(&scadaBuilderTest);
    QTest::qExec(&alarmSPTest);

}
