#ifndef ALARM_H
#define ALARM_H

#include <QString>
#include <QDateTime>


class Alarm
{
public:
    QString get_Name();
    bool get_IsOn();
    QDateTime get_OnTs();

    Alarm( QString name );
    void SetOn();
    void SetOff();

    virtual void Evaluate() = 0;

protected:
    QString m_Name;
    QDateTime m_OnTs;

private:
    bool m_IsOn;

};

#endif // ALARM_H
