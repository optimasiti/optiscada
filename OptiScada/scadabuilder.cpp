#include "scadabuilder.h"
#include "device.h"
#include "devicemodbusethernet.h"
#include "log.h"
#include "tagscada.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QThread>
#include <QDateTime>
#include <QCoreApplication>

const QString ScadaBuilder::NotFoundString = "";
const int ScadaBuilder::DefaultTimeOutMs = 2000;
const int ScadaBuilder::DefaultPort = 502;
const QString ScadaBuilder::DeviceFileName = "devices.txt";
const QString ScadaBuilder::TagsFileName = "tags.txt";

QList<Device*> *ScadaBuilder::m_pDevices = new QList<Device*>();
QList<TagScada*> *ScadaBuilder::m_pTags = new QList<TagScada*>();

QList<Device*> *ScadaBuilder::get_Devices()
{
    return m_pDevices;
}

QList<TagScada*> *ScadaBuilder::get_Tags()
{
    return m_pTags;
}

bool ScadaBuilder::BuildScada( QString configPath )
{
    if( LoadDevices( configPath + "/" + DeviceFileName ))
    {
        if( LoadTags( configPath + "/" + TagsFileName ) )
        {
            StartRefreshDevices();
            return true;
        }
    }

    return false;
}

void ScadaBuilder::ShutdownScada()
{
    for( int i = 0; i < m_pTags->size(); i++)
        delete m_pTags->at(i);

    delete m_pTags;

    for( int i = 0; i < m_pDevices->size(); i++ )
    {
        m_pDevices->at(i)->Finish();

        QDateTime ts = QDateTime::currentDateTime().addMSecs( m_pDevices->at(i)->get_TimeOutMs()*2);

        while(QDateTime::currentDateTime() < ts )
        {
            QThread::usleep(50000);
            QCoreApplication::processEvents();
        }
    }

    delete m_pDevices;
}

bool ScadaBuilder::LoadDevices( QString fileName )
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
        return false;
    }

    foreach( device, devices )
    {
        QString deviceType = device.toObject().value("type").toString( NotFoundString );

        if( deviceType == NotFoundString )
        {
            Log::AddLog( Log::Critical, QString("No device type found in config file ") + fileName );
            return false;
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
            return false;
        }
    }

    return true;
}

bool ScadaBuilder::LoadTags( QString fileName )
{
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
        return false;
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
            return false;
        }

        if( rawMin != 0 && rawMax != 0 && engMin != 0.0 && engMax != 0.0 )
        {
            pTag = new TagScada( id, description, address, rawMin, rawMax, engMin, engMax, pDevice);
        }
        else
        {
            pTag = new TagScada( id, description, address, pDevice );
        }

        if( QString( pDevice->metaObject()->className() ) == "DeviceModbusEthernet" )
        {
            static_cast<DeviceModbusEthernet*>(pDevice)->TouchAddress(address);
        }
        else
        {
            Log::AddLog( Log::Critical, QString( "%1  not implemented").arg(pDevice->metaObject()->className()));
            return false;
        }

        m_pTags->append( pTag );
    }

    return true;
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

void ScadaBuilder::StartRefreshDevices()
{
    for( int i = 0; i < m_pDevices->count(); i++ )
    {
        QThread *pThread = new QThread();
        m_pDevices->at(i)->moveToThread(pThread);
        QObject::connect(pThread, SIGNAL (started()), m_pDevices->at(i), SLOT (update()));
        pThread->start();
    }
}

Device* ScadaBuilder::FindDevice( int deviceId )
{
    for( int i = 0; i < m_pDevices->size(); i++ )
        if( m_pDevices->at(i)->get_Id() == deviceId )
            return m_pDevices->at(i);

    return nullptr;
}
