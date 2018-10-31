#ifndef SCADACORE_H
#define SCADACORE_H

#include <QList>
#include <QObject>

class TagScada;
class Device;

class ScadaCore : public QObject
{
    Q_OBJECT
public:
    QList<TagScada*> &get_Tags();

    ScadaCore();
    bool Start();
private:
    QList<TagScada*> m_Tags;
    QList<Device*> m_Devices;
};

#endif // SCADACORE_H
