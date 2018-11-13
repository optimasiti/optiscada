#include "scadabuilder_test.h"
#include "scadabuilder.h"
#include "devicemodbusethernet.h"
#include "tagscada.h"

void ScadaBuilder_Test::BuildScada_Ok()
{

}

/*
void ScadaBuilder_Test::LoadDevices_Ok()
{
    // [Preparation]

    QString fileName = QDir::currentPath()+"/../OptiScadaTest/test_files/LoadDevices_Ok";

    // [Execution]

    bool built = ScadaBuilder::BuildScada( fileName );

    // [Comparation]

    QCOMPARE( pDevices->count(), 2 );
    QCOMPARE( pDevices->at(0)->get_Type(), "modbus_tcp");

    DeviceModbusEthernet *pDeviceEthernet = (DeviceModbusEthernet*)pDevices->at(0);
    QCOMPARE( pDeviceEthernet->get_DeviceNumber(), 1);
    QCOMPARE( pDeviceEthernet->get_ServerUrl().host(), "localhost" );
    QCOMPARE( pDeviceEthernet->get_TimeOutMs(), 2000 );

    pDeviceEthernet = (DeviceModbusEthernet*)pDevices->at(1);
    QCOMPARE( pDeviceEthernet->get_Type(), "modbus_tcp");
    QCOMPARE( pDeviceEthernet->get_DeviceNumber(), 2);
    QCOMPARE( pDeviceEthernet->get_ServerUrl().host(), "localhost2");
    QCOMPARE( pDeviceEthernet->get_TimeOutMs(), 2500);

    // [Ending]

    for( int i = 0; i < pDevices->size(); i++ )
        delete pDevices->at(i);

    delete pDevices;

}

void ScadaBuilder_Test::LoadDevices_Error()
{
    // [Preparation]

    QString fileName = QDir::currentPath()+"/../OptiScadaTest/test_files/devices_LoadDevices_Error.txt";

    // [Execution]

    QList<Device*> *pDevices = ScadaBuilder::LoadDevices( fileName );

    // [Comparation]

    QVERIFY( pDevices == NULL );

    // [Ending]

}
void ScadaBuilder_Test::LoadTags_Ok()
{
    // [Preparation]

    QString fileName = QDir::currentPath()+"/../OptiScadaTest/test_files/tags_LoadTags_Ok.txt";

    // [Execution]

    QList<TagScada*>* pTags = ScadaBuilder::LoadTags( fileName );

    // [Comparation]

}
*/
