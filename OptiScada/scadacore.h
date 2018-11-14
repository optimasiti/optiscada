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
    ~ScadaCore();

    bool Start();

private:
    static const QString ConfigFolder;
};

#endif // SCADACORE_H
