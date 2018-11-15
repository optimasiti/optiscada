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

    TagScada *pTag = ScadaBuilder::get_Tags()->first();
    QCOMPARE( pTag->get_Id(), 1);
    QCOMPARE( pTag->get_Name(), "Consigna" );
    QCOMPARE( pTag->get_Device()->get_Id(), 1 );
    QCOMPARE( pTag->get_RawMin(), 10 );
    QCOMPARE( pTag->get_RawMax(), 1000 );
    QCOMPARE( pTag->get_EngMin(), 5.0 );
    QCOMPARE( pTag->get_EngMax(), 100.0 );

    pTag = ScadaBuilder::get_Tags()->last();
    QCOMPARE( pTag->get_Id(), 2);
    QCOMPARE( pTag->get_Name(), "Caudal" );
    QCOMPARE( pTag->get_Device()->get_Id(), 2 );
    QCOMPARE( pTag->get_RawMin(), 0 );
    QCOMPARE( pTag->get_RawMax(), 1000 );
    QCOMPARE( pTag->get_EngMin(), 0.0 );
    QCOMPARE( pTag->get_EngMax(), 100.0 );

    // [Ending]

    ScadaBuilder::ShutdownScada();
}

void ScadaBuilder_Test::BuildScada_ErrorByDevices()
{
    // [Preparation]

    QString fileName = QDir::currentPath()+"/../OptiScadaTest/test_files/BuildScada_ErrorByDevices";

    // [Execution]

    bool built = ScadaBuilder::BuildScada( fileName );

    // [Comparation]

    QCOMPARE( built, false );

    // [Ending]

    ScadaBuilder::ShutdownScada();
}

void ScadaBuilder_Test::BuildScada_ErrorUnknownDevice()
{
    // [Preparation]

    QString fileName = QDir::currentPath()+"/../OptiScadaTest/test_files/BuildScada_ErrorUnknownDevice";

    // [Execution]

    bool built = ScadaBuilder::BuildScada( fileName );

    // [Comparation]

    QCOMPARE( built, false );

    // [Ending]

    ScadaBuilder::ShutdownScada();
}

