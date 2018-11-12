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
    QList<TagScada*> *get_Tags();

    ScadaCore();
    bool Start();
private:
    static const QString DeviceFileName;
    static const QString TagsFileName;

    QList<TagScada*> *m_pTags;
    QList<Device*> *m_pDevices;
};

#endif // SCADACORE_H
