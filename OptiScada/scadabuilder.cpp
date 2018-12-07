#include "scadabuilder.h"
#include "devicemodbusethernet.h"
#include "devicemodbusethernet.h"
#include "log.h"
#include "tagscada.h"
#include "alarmsmanager.h"
#include "alarmsp.h"

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
const QString ScadaBuilder::AlarmsFileName = "alarms.txt";

QList<DeviceModbusEthernet*> *ScadaBuilder::m_pDevices = nullptr;
QList<TagScada*> *ScadaBuilder::m_pTags = nullptr;
QList<Alarm*> *ScadaBuilder::m_pAlarms = nullptr;
AlarmsManager* ScadaBuilder::m_pAlarmsManager = nullptr;


QList<DeviceModbusEthernet*> *ScadaBuilder::get_Devices()
{
    return m_pDevices;
}

QList<TagScada*> *ScadaBuilder::get_Tags()
{
    return m_pTags;
}

AlarmsManager *ScadaBuilder::get_AlarmsManager()
{
    return m_pAlarmsManager;
}

bool ScadaBuilder::BuildScada( QString configPath )
{
    if( m_pDevices || m_pTags )
        return false;

    if( LoadDevices( configPath + "/" + DeviceFileName ))
    {
        if( LoadTags( configPath + "/" + TagsFileName ) )
        {
            if( LoadAlarms( configPath + "/" + AlarmsFileName ))
            {
                StartRefreshDevices();
                StartAlarmsManager();
                return true;
            }
        }
    }

    return false;
}

void ScadaBuilder::ShutdownScada()
{
    if( m_pAlarmsManager )
    {
        m_pAlarmsManager->Finish();

        while( !m_pAlarmsManager->get_Finished())
        {
            QThread::usleep(50000);
            QCoreApplication::processEvents();
        }

        delete m_pAlarmsManager;
        m_pAlarmsManager = nullptr;
    }

    if( m_pAlarms != nullptr )
    {
        for( int i = 0; i < m_pAlarms->size(); i++ )
            delete m_pAlarms->at(i);

        delete m_pAlarms;
        m_pAlarms = nullptr;
    }

    if( m_pTags )
    {
        for( int i = 0; i < m_pTags->size(); i++)
            delete m_pTags->at(i);

        delete m_pTags;
        m_pTags = nullptr;
    }

    if( m_pDevices )
    {
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
        m_pDevices = nullptr;
    }

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

    m_pDevices = new QList<DeviceModbusEthernet*>();

    foreach( device, devices )
    {
        DeviceModbusEthernet *pDevice = ScadaBuilder::LoadModbusEthernetDevice(device.toObject());

        if( pDevice )
            m_pDevices->append( pDevice );
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

    m_pTags = new QList<TagScada*>();

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

        if( FindTag( id ) )
        {
            Log::AddLog( Log::Critical, QString( "Tag id %1 already defined").arg(id));
            return false;
        }

        TagScada *pTag;
        DeviceModbusEthernet *pDevice = FindDevice( deviceId );

        if( pDevice == nullptr)
        {
            Log::AddLog( Log::Critical, QString( "Device %1 not found in config file %2").arg( deviceId ).arg( fileName ));
            return false;
        }

        if( rawMin == 0 && rawMax == 0 && engMin == 0.0 && engMax == 0.0 )
        {
            pTag = new TagScada( id, description, address, pDevice );
        }
        else
        {
            pTag = new TagScada( id, description, address, rawMin, rawMax, engMin, engMax, pDevice);
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

bool ScadaBuilder::LoadAlarms( QString fileName )
{
    QString fileContent;
    QFile file;
    file.setFileName( fileName );
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileContent = file.readAll();
    file.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson( fileContent.toUtf8() );
    QJsonArray alarms = jsonDocument.object().value("alarms").toArray();
    QJsonValue alarm;

    if( alarms.count() == 0)
    {
        Log::AddLog( Log::Critical, QString("No Alarms found in config file ") + fileName );
        return true;
    }

    m_pAlarms = new QList<Alarm*>();

    foreach( alarm, alarms )
    {
        QString name = alarm.toObject().value("name").toString(NotFoundString);
        if( name == NotFoundString )
        {
            Log::AddLog( Log::Critical, "Alarm name not found");
            return false;
        }

        int tagIdSP = alarm.toObject().value("tag_sp").toInt(-1);
        int tagIdPV = alarm.toObject().value("tag_pv").toInt(-1);

        TagScada* pTagSP = FindTag( tagIdSP );
        TagScada* pTagPV = FindTag( tagIdPV );

        if( pTagSP == nullptr )
        {
            Log::AddLog( Log::Critical, QString("Tag for SP in alarm %1 not found").arg(name ));
            return false;
        }

        if( pTagPV == nullptr )
        {
            Log::AddLog( Log::Critical, QString("Tag for PV in alarm %1 not found").arg(name));
            return false;
        }

        double tolerance = alarm.toObject().value("tolerance_percentage").toDouble();

        AlarmSP *pAlarm = new AlarmSP( name, pTagSP, pTagPV, tolerance );

        m_pAlarms->append( pAlarm );
    }

    m_pAlarmsManager = new AlarmsManager( m_pAlarms );



    return true;
}


DeviceModbusEthernet* ScadaBuilder::LoadModbusEthernetDevice( QJsonObject device )
{
    int deviceNumber = device.value("id").toInt(-1);
    if( deviceNumber == -1 )
    {
        Log::AddLog( Log::Critical, QString( "Device number not found") );
        return nullptr;
    }

    QString server = device.value("server").toString(NotFoundString);
    if( server == NotFoundString)
    {
        Log::AddLog( Log::Critical, QString( "Server not found") );
        return nullptr;
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

void ScadaBuilder::StartAlarmsManager()
{
    if( !m_pAlarmsManager )
        return;

    QThread *pThread = new QThread();
    m_pAlarmsManager->moveToThread( pThread );
    QObject::connect(pThread, SIGNAL (started()), m_pAlarmsManager, SLOT (evaluatePool()));
    pThread->start();
}

DeviceModbusEthernet* ScadaBuilder::FindDevice( int deviceId )
{
    for( int i = 0; i < m_pDevices->size(); i++ )
        if( m_pDevices->at(i)->get_Id() == deviceId )
            return m_pDevices->at(i);

    return nullptr;
}

TagScada* ScadaBuilder::FindTag( int tagId )
{
    for( int i = 0; i < m_pTags->size(); i++ )
        if( m_pTags->at(i)->get_Id() == tagId )
            return m_pTags->at(i);

    return nullptr;
}
