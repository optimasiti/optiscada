#include "scadabuilder.h"
#include "device.h"
#include "devicemodbusethernet.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>

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

    return pDevices;
}

Device* ScadaBuilder::LoadModbusEthernetDevice( QJsonObject device )
{
    int deviceNumber = device.value("id").toInt(-1);
    if( deviceNumber == -1 )
    {
        //TODO qCritical()<<"Missing id for one serial device";
        return NULL;
    }

    QString address = device.value("server").toString();
    //TODO CHECK

    int port = device.value("port").toInt();
    //TODO CHECK

    int slave = device.value("slave").toInt(1);

    if( slave == 0 )
    {
        //TODOqCritical()<<"Missing server address for device "<<deviceId<<" in config file";
        return NULL;
    }

    int timeOutMs = device.value("time_out_ms").toInt(2000);//TODO a K

    return new DeviceModbusEthernet( deviceNumber, QString("%1:%2").arg(slave).arg(port), timeOutMs);
}
