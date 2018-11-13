#ifndef SCADABUILDER_H
#define SCADABUILDER_H

#include <QList>
#include <QJsonObject>

class Device;
class TagScada;

class ScadaBuilder
{
public:
    static bool BuildScada( QString configPath );

private:
    static const QString NotFoundString;
    static const int DefaultTimeOutMs;
    static const int DefaultPort;
    static QList<Device*> *m_pDevices;
    static QList<TagScada*> *m_pTags;

    static QList<Device*> *LoadDevices( QString fileName );
    static QList<TagScada*> *LoadTags( QString fileName );
    static Device* LoadModbusEthernetDevice( QJsonObject device );
    static TagScada* LoadTag( QJsonObject tag );
    static Device* FindDevice( int deviceId );
};

#endif // SCADABUILDER_H
