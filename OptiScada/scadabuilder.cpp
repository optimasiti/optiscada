#include "scadabuilder.h"
#include "device.h"
#include "devicemodbusethernet.h"
#include "log.h"
#include "tagscada.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>

const QString ScadaBuilder::NotFoundString = "";
const int ScadaBuilder::DefaultTimeOutMs = 2000;
const int ScadaBuilder::DefaultPort = 502;

QList<Device*> *ScadaBuilder::m_pDevices = new QList<Device*>();
QList<TagScada*> *ScadaBuilder::m_pTags = new QList<TagScada*>();



bool ScadaBuilder::BuildScada( QString configPath )
{
    LoadDevices( configPath + "/devices.txt" );
    LoadTags( configPath + "/tags.txt" );

    return false; //TODO
}

QList<Device*> *ScadaBuilder::LoadDevices( QString fileName )
{
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
        return nullptr;
    }

    foreach( device, devices )
    {
        QString deviceType = device.toObject().value("type").toString( NotFoundString );

        if( deviceType == NotFoundString )
        {
            Log::AddLog( Log::Critical, QString("No device type found in config file ") + fileName );
            return nullptr;
        }

        if( deviceType == "modbus_tcp" )
        {
            Device *pDevice = ScadaBuilder::LoadModbusEthernetDevice(device.toObject());

            if( pDevice )
                m_pDevices->append( pDevice );

        }
        else
        {
            Log::AddLog( Log::Critical, QString("Unsupported device type %1 ").arg(deviceType) + QString(" in config file ") + fileName );
            return nullptr;
        }
    }

    return m_pDevices; //TODO
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
        Log::AddLog( Log::Critical, QString("No tags found in config file ") + fileName );
        return NULL; //TODO destruir. Tambien pasa en Devices.
    }

    foreach( tag, tags )
    {
        int id = tag.toObject().value("id").toInt(-1);
        int deviceId = tag.toObject().value("device_id").toInt(-1);
        int address = tag.toObject().value("address").toInt(-1);
        QString description = tag.toObject().value("description").toString(NotFoundString);
        quint16 rawMin = tag.toObject().value("raw_min").toInt();
        quint16 rawMax = tag.toObject().value("raw_max").toInt();
        double engMin = tag.toObject().value("eng_min").toDouble();
        double engMax = tag.toObject().value("eng_max").toDouble();

        TagScada *pTag;
        Device *pDevice = FindDevice( deviceId );

        if( pDevice == nullptr)
        {
            Log::AddLog( Log::Critical, QString( "Device %1 not found in config file %2").arg( deviceId ).arg( fileName ));
            return nullptr; //TODO
        }

        if( rawMin != 0 && rawMax != 0 && engMin != 0.0 && engMax != 0.0 )
        {
            pTag = new TagScada( id, description, address, rawMin, rawMax, engMin, engMax, pDevice);
        }
        else
        {
            pTag = new TagScada( id, description, address, pDevice );
        }

        if( QString( pDevice->metaObject()->className() ) == "DevicesModbusEthernet" )
        {
            static_cast<DeviceModbusEthernet*>(pDevice)->TouchAddress(address);
        }
        else
        {
            Q_ASSERT( false ); //TODO
        }

        m_pTags->append( pTag );
    }

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

Device* ScadaBuilder::FindDevice( int deviceId )
{
    for( int i = 0; i < m_pDevices->size(); i++ )
        if( m_pDevices->at(i)->get_Id() == deviceId )
            return m_pDevices->at(i);

    return nullptr;
}
