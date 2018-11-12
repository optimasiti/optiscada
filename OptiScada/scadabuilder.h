#ifndef SCADABUILDER_H
#define SCADABUILDER_H

#include <QList>
#include <QJsonObject>

class Device;
class TagScada;

class ScadaBuilder
{
public:
    static QList<Device*> *LoadDevices( QString fileName );
    static QList<TagScada*> *LoadTags( QString fileName );

private:
    static const QString NotFoundString;
    static const int DefaultTimeOutMs;
    static const int DefaultPort;

    static Device* LoadModbusEthernetDevice( QJsonObject device );
    static TagScada* LoadTag( QJsonObject tag );
};

#endif // SCADABUILDER_H
