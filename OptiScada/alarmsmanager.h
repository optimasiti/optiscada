#ifndef ALARMSMANAGER_H
#define ALARMSMANAGER_H

#include <QList>
#include <QObject>

class Alarm;

class AlarmsManager : public QObject
{
    Q_OBJECT

public:
    bool get_Finished();
    QList<Alarm*>* get_Alarms();

    AlarmsManager(QList<Alarm*>*pAlarms);
    virtual ~AlarmsManager();
    QList<QString> GetOnAlarms();

    void Finish();

public slots:
    void evaluatePool();


protected:
    bool m_Finish;
    bool m_Finished;
    QList<Alarm*> *m_pAlarms;

};

#endif // ALARMSMANAGER_H
