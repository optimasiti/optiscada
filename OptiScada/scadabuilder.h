#ifndef SCADABUILDER_H
#define SCADABUILDER_H

#include "alarm.h"


#include <QList>
#include <QJsonObject>

class DeviceModbusEthernet;
class TagScada;
class AlarmsManager;

class ScadaBuilder
{
public:
    static QList<DeviceModbusEthernet*> *get_Devices();
    static QList<TagScada*> *get_Tags();
    static AlarmsManager *get_AlarmsManager();

    static bool BuildScada( QString configPath );
    static void ShutdownScada();

private:
    static const QString NotFoundString;
    static const int DefaultTimeOutMs;
    static const int DefaultPort;
    static QList<DeviceModbusEthernet*> *m_pDevices;
    static QList<TagScada*> *m_pTags;
    static QList<Alarm*> *m_pAlarms;
    static AlarmsManager *m_pAlarmsManager;
    static const QString DeviceFileName;
    static const QString TagsFileName;
    static const QString AlarmsFileName;

    static bool LoadDevices( QString fileName );
    static bool LoadTags( QString fileName );
    static bool LoadAlarms( QString fileName );
    static DeviceModbusEthernet* LoadModbusEthernetDevice( QJsonObject device );
    static DeviceModbusEthernet* FindDevice( int deviceId );
    static TagScada* FindTag( int tagId );
    static void StartRefreshDevices();

};

#endif // SCADABUILDER_H
