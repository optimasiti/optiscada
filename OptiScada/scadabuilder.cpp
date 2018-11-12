#include "scadabuilder.h"
#include "device.h"
#include "devicemodbusethernet.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

const QString ScadaBuilder::NotFoundString = "NOT_FOUND";

QList<Device*> *ScadaBuilder::LoadDevices( QString fileName )
{
    QList<Device*> *pDevices = new QList<Device*>();

    QString fileContent;
    QFile file;
    file.setFileName( fileName );
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileContent = file.readAll();
    file.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson( fileContent.toUtf8() );
    QJsonArray devices = jsonDocument.object().value("devices").toArray();
    QJsonValue device;

    if( devices.count() == 0)
    { //TODO
        return NULL;
    }

    foreach( device, devices )
    {
        QString deviceType = device.toObject().value("type").toString( NotFoundString );

        if( deviceType == NotFoundString )
        {//TODO
            return NULL;
        }

        if( deviceType == "modbus_tcp" )
        {
            Device *pDevice = ScadaBuilder::LoadModbusEthernetDevice(device.toObject());
            if( pDevice )
                pDevices->append( pDevice );

        }
        else
        {
            return NULL; //TODO
        }
    }
}

Device* ScadaBuilder::LoadModbusEthernetDevice( QJsonObject device )
{
//    DeviceModbusEthernet *pDevice = new DeviceModbusEthernet( deviceNumber, serverUrl, timeOutMs);
/*
    {
        int deviceId = device.value("id").toInt(NotFoundNumeric);
        if( deviceId == NotFoundNumeric )
        {
            qCritical()<<"Missing id for one serial device";
            return false;
        }

        int busId = device.value("primary_bus").toInt(NotFoundNumeric);

        if( busId == NotFoundNumeric)
        {
            qCritical()<<"Missing primary_bus value for device "<<deviceId;
            return false;
        }

        QString address = device.value("address").toString();

        int wordsMemoryStartAddress = device.value("words_memory_start_address").toInt(-1);
        int wordsMemoryLength = device.value("words_memory_length").toInt(-1);
        int bitsMemoryStartAddress = device.value("bits_memory_start_address").toInt(-1);
        int bitsMemoryLength = device.value("bits_memory_length").toInt(-1);
    //    int slaveAddress = device.value("slave").toInt();
        QString name = device.value("name").toString(NotFoundString);

        if( address.split(":").length() != 3 )
        {
            qCritical()<<QString("Invalid address for device %1. Expected IP:PORT:SLAVE").arg(deviceId);
            return false;
        }
        int slaveAddress = address.split(":").at(2).toInt();
        address = QString("%1:%2").arg(address.split(":").at(0)).arg(address.split(":").at(1));

        if( wordsMemoryStartAddress == -1 || wordsMemoryLength == -1 ||
            bitsMemoryStartAddress == -1  || bitsMemoryLength == -1 || name == NotFoundString )
        {
            qCritical()<<"Missing memory configuration or name for device "<<deviceId<<" in config file";
            return false;
        }

        if( slaveAddress == 0 )
        {
            qCritical()<<"Missing server address for device "<<deviceId<<" in config file";
            return false;
        }

        DeviceTcp *pDevice = new DeviceTcp( deviceId, slaveAddress, name, wordsMemoryStartAddress, wordsMemoryLength, bitsMemoryStartAddress,
                                            bitsMemoryLength, QUrl::fromUserInput( address));
    //    m_ModbusServers.append( new ModbusServer( pDevice ) );

        m_Devices.append( pDevice );

        QThread *pThread = new QThread();
        pDevice->moveToThread(pThread);
        QObject::connect(pThread, SIGNAL (started()), pDevice, SLOT (process()));
        QObject::connect(pDevice, SIGNAL (finished()), pThread, SLOT (quit()));
        QObject::connect(pDevice, SIGNAL (finished()), pDevice, SLOT (deleteLater()));
        QObject::connect(pThread, SIGNAL (finished()), pThread, SLOT (deleteLater()));
        pThread->start();




    //    pDevice->Start();

        return true;
    }
    */

}
