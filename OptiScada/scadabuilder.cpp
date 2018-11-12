#include "scadabuilder.h"
#include "device.h"
#include "devicemodbusethernet.h"
#include "log.h"
#include "tagscada.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>

const QString ScadaBuilder::NotFoundString = "NOT_FOUND";
const int ScadaBuilder::DefaultTimeOutMs = 2000;
const int ScadaBuilder::DefaultPort = 502;



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
    {
        Log::AddLog( Log::Critical, QString("No devices found in config file ") + fileName );
        return NULL;
    }

    foreach( device, devices )
    {
        QString deviceType = device.toObject().value("type").toString( NotFoundString );

        if( deviceType == NotFoundString )
        {
            Log::AddLog( Log::Critical, QString("No device type found in config file ") + fileName );
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
            Log::AddLog( Log::Critical, QString("Unsupported device type %1 ").arg(deviceType) + QString(" in config file ") + fileName );
            return NULL;
        }
    }

    return pDevices;
}

QList<TagScada*> *ScadaBuilder::LoadTags( QString fileName )
{

    QList<TagScada*> *pTags = new QList<TagScada*>();

    QString fileContent;
    QFile file;
    file.setFileName( fileName );
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileContent = file.readAll();
    file.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson( fileContent.toUtf8() );
    QJsonArray tags = jsonDocument.object().value("tags").toArray();
    QJsonValue tag;

    if( tags.count() == 0)
    {
        Log::AddLog( Log::Critical, QString("No devices found in config file ") + fileName );
        return NULL; //TODO destruir. Tambien pasa en Devices.
    }

    foreach( tag, tags )
    {
        QString deviceType = device.toObject().value("type").toString( NotFoundString );

        if( deviceType == NotFoundString )
        {
            Log::AddLog( Log::Critical, QString("No device type found in config file ") + fileName );
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
            Log::AddLog( Log::Critical, QString("Unsupported device type %1 ").arg(deviceType) + QString(" in config file ") + fileName );
            return NULL;
        }
    }

    return pDevices;*/
    return nullptr;
}


Device* ScadaBuilder::LoadModbusEthernetDevice( QJsonObject device )
{
    int deviceNumber = device.value("id").toInt(-1);
    if( deviceNumber == -1 )
    {
        Log::AddLog( Log::Critical, QString( "Device number not found") );
        return NULL;
    }

    QString server = device.value("server").toString(NotFoundString);
    if( server == NotFoundString)
    {
        Log::AddLog( Log::Critical, QString( "Server not found") );
        return NULL;
    }

    int port = device.value("port").toInt(DefaultPort);

    QUrl serverUrl = QUrl::fromUserInput( QString("%1:%2").arg(server).arg(port) );

    int timeOutMs = device.value("time_out_ms").toInt(DefaultTimeOutMs);

    return new DeviceModbusEthernet( deviceNumber, serverUrl, timeOutMs);
}

TagScada* ScadaBuilder::LoadTag( QJsonObject tag )
{
    /*
    int deviceNumber = device.value("id").toInt(-1);
    if( deviceNumber == -1 )
    {
        Log::AddLog( Log::Critical, QString( "Device number not found") );
        return NULL;
    }

    QString server = device.value("server").toString(NotFoundString);
    if( server == NotFoundString)
    {
        Log::AddLog( Log::Critical, QString( "Server not found") );
        return NULL;
    }

    int port = device.value("port").toInt(DefaultPort);

    QUrl serverUrl = QUrl::fromUserInput( QString("%1:%2").arg(server).arg(port) );

    int timeOutMs = device.value("time_out_ms").toInt(DefaultTimeOutMs);

    return new DeviceModbusEthernet( deviceNumber, serverUrl, timeOutMs);
    */
    return nullptr;
}
