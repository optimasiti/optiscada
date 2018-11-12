#include "scadabuilder_test.h"
#include "scadabuilder.h"
#include "devicemodbusethernet.h"

void ScadaBuilder_Test::LoadDevices_Ok()
{
    // [Preparation]

    QString fileName = "D:\\Projects\\Optiscada\\optiscada\\config\\devices.txt";

    // [Execution]

    QList<Device*> *pDevices = ScadaBuilder::LoadDevices( fileName );

    // [Comparation]

    //TODO
    QCOMPARE( 2, pDevices->count());
    QCOMPARE( "modbus_tcp", pDevices->at(0)->get_Type());

    DeviceModbusEthernet *pDeviceEthernet = (DeviceModbusEthernet*)pDevices->at(0);
    QCOMPARE( 1, pDeviceEthernet->get_DeviceNumber());
    QCOMPARE( "localhost", pDeviceEthernet->get_ServerUrl().host());
    QCOMPARE( 2000, pDeviceEthernet->get_TimeOutMs());

    pDeviceEthernet = (DeviceModbusEthernet*)pDevices->at(0);
    QCOMPARE( "modbus_tcp", pDeviceEthernet->get_Type());
    QCOMPARE( 2, pDeviceEthernet->get_DeviceNumber());
    QCOMPARE( "localhost2", pDeviceEthernet->get_ServerUrl().host());
    QCOMPARE( 2500, pDeviceEthernet->get_TimeOutMs());

    // [Ending]

    for( int i = 0; i < pDevices->size(); i++ )
        delete pDevices->at(i);

    delete pDevices;
}
