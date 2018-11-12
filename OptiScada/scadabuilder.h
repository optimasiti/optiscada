#ifndef SCADABUILDER_H
#define SCADABUILDER_H

#include <QList>
#include <QJsonObject>

class Device;

class ScadaBuilder
{
public:
    static QList<Device*> *LoadDevices( QString fileName );

private:
    static const QString NotFoundString;

    static Device* LoadModbusEthernetDevice( QJsonObject device );
};

#endif // SCADABUILDER_H
