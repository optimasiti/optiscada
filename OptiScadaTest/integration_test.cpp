#include "integration_test.h"
#include "scadabuilder.h"
#include "modbusserver.h"
#include "tagscada.h"
#include "alarmsmanager.h"

#include <QThread>
/*TODO
void Integration_Test::Integration_RefreshTags()
{
    // [Preparation]

    QString fileName = QDir::currentPath()+"/../OptiScadaTest/test_files/Integration_RefreshTags";

    int port = 502;
    int deviceNumber = 1;

    ModbusServer *pServer1 = new ModbusServer();
    if( !pServer1->Start( port, deviceNumber ))
    {
        QFAIL( "Cannot start Server");
        return;
    }

    port = 503;
    deviceNumber = 2;

    ModbusServer *pServer2 = new ModbusServer();
    if( !pServer2->Start( port, deviceNumber ))
    {
        QFAIL( "Cannot start Server");
        return;
    }

    bool built = ScadaBuilder::BuildScada( fileName );

    if( !built )
    {
        QFAIL( "Unexpected error building scada");
        return;
    }

    pServer1->SetRegisterValue(40065, 100 );
    pServer2->SetRegisterValue(40065, 50 );

    // [Execution]

    QDateTime e = QDateTime::currentDateTime().addMSecs(5000);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    double value1;
    double value2;
    bool value1Ok = ScadaBuilder::get_Tags()->first()->GetValue(value1);
    bool value2Ok = ScadaBuilder::get_Tags()->last()->GetValue(value2);

    // [Comparation]

    QCOMPARE( value1Ok, true );
    QCOMPARE( value1, 10.0 );
    QCOMPARE( value2Ok, true );
    QCOMPARE( value2, 5.0 );


    // [Ending]

    ScadaBuilder::ShutdownScada();

    delete pServer1;
    delete pServer2;

}
*/

void Integration_Test::Integration_RaiseAlarms()
{
    // [Preparation]

    QString fileName = QDir::currentPath()+"/../OptiScadaTest/test_files/Integration_RaiseAlarms";

    int port = 502;
    int deviceNumber = 1;

    ModbusServer *pServer1 = new ModbusServer();
    if( !pServer1->Start( port, deviceNumber ))
    {
        QFAIL( "Cannot start Server");
        return;
    }

    port = 503;
    deviceNumber = 2;

    ModbusServer *pServer2 = new ModbusServer();
    if( !pServer2->Start( port, deviceNumber ))
    {
        QFAIL( "Cannot start Server");
        return;
    }

    pServer1->SetRegisterValue(40065, 100 );
    pServer1->SetRegisterValue(40066, 50);
    pServer2->SetRegisterValue(40065, 50 );
    pServer2->SetRegisterValue(40066, 49 );

    bool built = ScadaBuilder::BuildScada( fileName );

    if( !built )
    {
        QFAIL( "Unexpected error building scada");
        return;
    }

    // [Execution]

    QDateTime e = QDateTime::currentDateTime().addMSecs(5000);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    QList<QString> alarms = ScadaBuilder::get_AlarmsManager()->GetOnAlarms();

    // [Comparation]

    QCOMPARE( alarms.size(), 1 );


    // [Ending]

    ScadaBuilder::ShutdownScada();

    delete pServer1;
    delete pServer2;

}

