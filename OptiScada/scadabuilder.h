#ifndef SCADABUILDER_H
#define SCADABUILDER_H

#include "alarm.h"


#include <QList>
#include <QJsonObject>

class DeviceModbusEthernet;
class TagScada;
class TagHistorical;
class AlarmsManager;
class Historical;

class ScadaBuilder
{
public:
    static QList<DeviceModbusEthernet*> *get_Devices();
    static QList<TagScada*> *get_Tags();
    static AlarmsManager *get_AlarmsManager();
    static Historical *get_Historical();

    static bool BuildScada( QString configPath );
    static void ShutdownScada();

private:
    static const QString NotFoundString;
    static const int DefaultTimeOutMs;
    static const int DefaultPort;
    static QList<DeviceModbusEthernet*> *m_pDevices;
    static QList<TagScada*> *m_pTags;
    static QList<TagHistorical*> *m_pTagsHistorical;
    static QList<Alarm*> *m_pAlarms;
    static AlarmsManager *m_pAlarmsManager;
    static const QString DeviceFileName;
    static const QString TagsFileName;
    static const QString AlarmsFileName;
    static Historical *m_pHistorical;
    static const QString HistoricalPath;

    static bool LoadDevices( QString fileName );
    static bool LoadTags( QString fileName );
    static bool LoadAlarms( QString fileName );
    static bool LoadHistoricalPath( QString fileName );
    static DeviceModbusEthernet* LoadModbusEthernetDevice( QJsonObject device );
    static DeviceModbusEthernet* FindDevice( int deviceId );
    static TagScada* FindTag( int tagId );
    static void StartRefreshDevices();
    static void StartAlarmsManager();
    static bool StartHistorical();

};

#endif // SCADABUILDER_H
