#include "devicemodbusethernet_test.h"
#include "devicemodbusethernet.h"
#include "modbusserver.h"
#include "tagscada.h"

#include <QThread>
#include <QUrl>
#include <QVector>

void DeviceModbusEthernet_Test::ReadHoldingRegisters_Ok()
{
    // [Preparation]

    int port = 502;
    int deviceNumber = 1;
    int timeOutMs = 2000;
    int tagAddress = 40010;
    quint16 tagValue = 123;
    QUrl url = QUrl::fromUserInput( QString("localhost:%1").arg(port));

    ModbusServer *pServer = new ModbusServer();
    if( !pServer->Start( port, deviceNumber ))
    {
        QFAIL( "Cannot start Server");
        return;
    }

    DeviceModbusEthernet *pDevice = new DeviceModbusEthernet( deviceNumber, url, timeOutMs );
    pDevice->TouchAddress( tagAddress );

    QThread *pThreadDevice = new QThread();
    connect(pThreadDevice, SIGNAL(finished()), pDevice, SLOT(deleteLater()));
    pDevice->moveToThread(pThreadDevice);
    QObject::connect(pThreadDevice, SIGNAL (started()), pDevice, SLOT (update()));
    pThreadDevice->start();

    // [Execution]

    pServer->SetRegisterValue( tagAddress, tagValue );

    QDateTime e = QDateTime::currentDateTime().addMSecs(timeOutMs*2);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    // [Comparation]
    int count = 1;
    QVector<quint16> readValues;

    pDevice->ReadWords( tagAddress, count, readValues );

    QCOMPARE( tagValue, readValues.first() );

    // [Ending]

    pDevice->Finish();

    e = QDateTime::currentDateTime().addMSecs(timeOutMs*2);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    pThreadDevice->exit();

    while(!pThreadDevice->isFinished())
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    delete pServer;
}

void DeviceModbusEthernet_Test::ReadInputRegisters_Ok()
{
    // [Preparation]

    int port = 502;
    int deviceNumber = 1;
    int timeOutMs = 2000;
    int tagAddress = 30010;
    quint16 tagValue = 123;
    QUrl url = QUrl::fromUserInput( QString("localhost:%1").arg(port));

    ModbusServer *pServer = new ModbusServer();
    if( !pServer->Start( port, deviceNumber ))
    {
        QFAIL( "Cannot start Server");
        return;
    }

    DeviceModbusEthernet *pDevice = new DeviceModbusEthernet( deviceNumber, url, timeOutMs );
    pDevice->TouchAddress( tagAddress );

    QThread *pThreadDevice = new QThread();
    connect(pThreadDevice, SIGNAL(finished()), pDevice, SLOT(deleteLater()));
    pDevice->moveToThread(pThreadDevice);
    QObject::connect(pThreadDevice, SIGNAL (started()), pDevice, SLOT (update()));
    pThreadDevice->start();

    // [Execution]

    pServer->SetRegisterValue( tagAddress, tagValue );

    QDateTime e = QDateTime::currentDateTime().addMSecs(timeOutMs*2);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    // [Comparation]
    int count = 1;
    QVector<quint16> readValues;

    pDevice->ReadWords( tagAddress, count, readValues );

    QCOMPARE( tagValue, readValues.first() );

    // [Ending]

    pDevice->Finish();

    e = QDateTime::currentDateTime().addMSecs(timeOutMs*2);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    pThreadDevice->exit();

    while(!pThreadDevice->isFinished())
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    delete pServer;

}

void DeviceModbusEthernet_Test::ReadDiscreteInputs_Ok()
{
    // [Preparation]

    int port = 502;
    int deviceNumber = 1;
    int timeOutMs = 2000;
    int tagAddress = 10010;
    quint16 tagValue = 1;
    QUrl url = QUrl::fromUserInput( QString("localhost:%1").arg(port));

    ModbusServer *pServer = new ModbusServer();
    if( !pServer->Start( port, deviceNumber ))
    {
        QFAIL( "Cannot start Server");
        return;
    }

    DeviceModbusEthernet *pDevice = new DeviceModbusEthernet( deviceNumber, url, timeOutMs );
    pDevice->TouchAddress( tagAddress );

    QThread *pThreadDevice = new QThread();
    connect(pThreadDevice, SIGNAL(finished()), pDevice, SLOT(deleteLater()));
    pDevice->moveToThread(pThreadDevice);
    QObject::connect(pThreadDevice, SIGNAL (started()), pDevice, SLOT (update()));
    pThreadDevice->start();

    // [Execution]

    pServer->SetRegisterValue( tagAddress, tagValue );

    QDateTime e = QDateTime::currentDateTime().addMSecs(timeOutMs*2);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    // [Comparation]
    int count = 1;
    QVector<bool> readValues;

    pDevice->ReadBits( tagAddress, count, readValues );

    QCOMPARE( tagValue, readValues.first() );

    // [Ending]

    pDevice->Finish();

    e = QDateTime::currentDateTime().addMSecs(timeOutMs*2);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    pThreadDevice->exit();

    while(!pThreadDevice->isFinished())
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    delete pServer;

}

void DeviceModbusEthernet_Test::ReadCoils_Ok()
{
    // [Preparation]

    int port = 502;
    int deviceNumber = 1;
    int timeOutMs = 2000;
    int tagAddress = 10;
    quint16 tagValue = 1;
    QUrl url = QUrl::fromUserInput( QString("localhost:%1").arg(port));

    ModbusServer *pServer = new ModbusServer();
    if( !pServer->Start( port, deviceNumber ))
    {
        QFAIL( "Cannot start Server");
        return;
    }

    DeviceModbusEthernet *pDevice = new DeviceModbusEthernet( deviceNumber, url, timeOutMs );
    pDevice->TouchAddress( tagAddress );

    QThread *pThreadDevice = new QThread();
    connect(pThreadDevice, SIGNAL(finished()), pDevice, SLOT(deleteLater()));
    pDevice->moveToThread(pThreadDevice);
    QObject::connect(pThreadDevice, SIGNAL (started()), pDevice, SLOT (update()));
    pThreadDevice->start();

    // [Execution]

    pServer->SetRegisterValue( tagAddress, tagValue );

    QDateTime e = QDateTime::currentDateTime().addMSecs(timeOutMs*2);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    // [Comparation]
    int count = 1;
    QVector<bool> readValues;

    pDevice->ReadBits( tagAddress, count, readValues );

    QCOMPARE( tagValue, readValues.first() );

    // [Ending]

    pDevice->Finish();

    e = QDateTime::currentDateTime().addMSecs(timeOutMs*2);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    pThreadDevice->exit();

    while(!pThreadDevice->isFinished())
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    delete pServer;

}

void DeviceModbusEthernet_Test::WriteHoldingRegisters_Ok()
{
    // [Preparation]

    int port = 502;
    int deviceNumber = 1;
    int timeOutMs = 2000;
    int tagAddress = 40010;
    quint16 tagValue = 123;
    QUrl url = QUrl::fromUserInput( QString("localhost:%1").arg(port));

    ModbusServer *pServer = new ModbusServer();
    if( !pServer->Start( port, deviceNumber ))
    {
        QFAIL( "Cannot start Server");
        return;
    }

    DeviceModbusEthernet *pDevice = new DeviceModbusEthernet( deviceNumber, url, timeOutMs );
    pDevice->TouchAddress( tagAddress );

    QThread *pThreadDevice = new QThread();
    connect(pThreadDevice, SIGNAL(finished()), pDevice, SLOT(deleteLater()));
    pDevice->moveToThread(pThreadDevice);
    QObject::connect(pThreadDevice, SIGNAL (started()), pDevice, SLOT (update()));
    pThreadDevice->start();

    // [Execution]

    QVector<quint16> values;
    values.append( tagValue );
    pDevice->WriteWords( tagAddress, values );

    QDateTime e = QDateTime::currentDateTime().addMSecs(timeOutMs*2);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    // [Comparation]

    quint16 readValues = pServer->GetRegisterValue( tagAddress );

    QCOMPARE( tagValue, readValues );

    // [Ending]

    pDevice->Finish();

    e = QDateTime::currentDateTime().addMSecs(timeOutMs*2);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    pThreadDevice->exit();

    while(!pThreadDevice->isFinished())
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    delete pServer;
}

void DeviceModbusEthernet_Test::WriteCoils_Ok()
{
    // [Preparation]

    int port = 502;
    int deviceNumber = 1;
    int timeOutMs = 2000;
    int tagAddress = 10;
    quint16 tagValue = 1;
    QUrl url = QUrl::fromUserInput( QString("localhost:%1").arg(port));

    ModbusServer *pServer = new ModbusServer();
    if( !pServer->Start( port, deviceNumber ))
    {
        QFAIL( "Cannot start Server");
        return;
    }

    DeviceModbusEthernet *pDevice = new DeviceModbusEthernet( deviceNumber, url, timeOutMs );
    pDevice->TouchAddress( tagAddress );

    QThread *pThreadDevice = new QThread();
    connect(pThreadDevice, SIGNAL(finished()), pDevice, SLOT(deleteLater()));
    pDevice->moveToThread(pThreadDevice);
    QObject::connect(pThreadDevice, SIGNAL (started()), pDevice, SLOT (update()));
    pThreadDevice->start();

    // [Execution]

    QVector<bool> values;
    values.append( tagValue );
    pDevice->WriteBits( tagAddress, values );

    QDateTime e = QDateTime::currentDateTime().addMSecs(timeOutMs*2);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    // [Comparation]

    bool readValues = pServer->GetRegisterValue( tagAddress );

    QCOMPARE( tagValue, readValues );

    // [Ending]

    pDevice->Finish();

    e = QDateTime::currentDateTime().addMSecs(timeOutMs*2);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    pThreadDevice->exit();

    while(!pThreadDevice->isFinished())
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    delete pServer;
}

