#include "scadabuilder_test.h"
#include "scadabuilder.h"
#include "devicemodbusethernet.h"
#include "tagscada.h"




void ScadaBuilder_Test::BuildScada_Ok()
{
    // [Preparation]

    QString fileName = QDir::currentPath()+"/../OptiScadaTest/test_files/BuildScada_Ok";

    // [Execution]

    bool built = ScadaBuilder::BuildScada( fileName );

    // [Comparation]

    QCOMPARE( built, true );

    QCOMPARE( ScadaBuilder::get_Devices()->size(), 2 );

    DeviceModbusEthernet *pDeviceEthernet = (DeviceModbusEthernet*)ScadaBuilder::get_Devices()->at(0);
    QCOMPARE( pDeviceEthernet->get_DeviceNumber(), 1);
    QCOMPARE( pDeviceEthernet->metaObject()->className(), "DeviceModbusEthernet" );
    QCOMPARE( pDeviceEthernet->get_ServerUrl().host(), "localhost" );
    QCOMPARE( pDeviceEthernet->get_TimeOutMs(), 2000 );

    pDeviceEthernet = (DeviceModbusEthernet*)ScadaBuilder::get_Devices()->at(1);
    QCOMPARE( pDeviceEthernet->metaObject()->className(), "DeviceModbusEthernet" );
    QCOMPARE( pDeviceEthernet->get_DeviceNumber(), 2);
    QCOMPARE( pDeviceEthernet->get_ServerUrl().host(), "localhost2");
    QCOMPARE( pDeviceEthernet->get_TimeOutMs(), 2500);

    // [Ending]

    ScadaBuilder::ShutdownScada();
}

void ScadaBuilder_Test::BuildScada_ErrorByDevices()
{
    // [Preparation]

    QString fileName = QDir::currentPath()+"/../OptiScadaTest/test_files/BuildScada _ErrorByDevices";

    // [Execution]

    bool built = ScadaBuilder::BuildScada( fileName );

    // [Comparation]

    QCOMPARE( built, false );

    // [Ending]

    ScadaBuilder::ShutdownScada();
}

