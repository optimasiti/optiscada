#include <QCoreApplication>
#include <QTest>

#include "devicemodbusethernet_test.h"
#include "scadabuilder_test.h"
#include "alarmsp_test.h"
#include "alarmsmanager_test.h"
#include "integration_test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DeviceModbusEthernet_Test deviceModbusEthernetTest;
    ScadaBuilder_Test scadaBuilderTest;
    AlarmSP_Test alarmSPTest;
    AlarmsManager_Test alarmsManagerTest;
    Integration_Test integrationTest;

    QTest::qExec(&deviceModbusEthernetTest);
    QTest::qExec(&scadaBuilderTest);
    QTest::qExec(&alarmSPTest);
    QTest::qExec(&alarmsManagerTest);
    QTest::qExec(&integrationTest);
}
