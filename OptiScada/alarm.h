#ifndef ALARM_H
#define ALARM_H

#include <QString>


class Alarm
{
public:
    QString get_Name();
    bool get_IsOn();

    Alarm( QString name );

    virtual void Evaluate() = 0;

private:
    QString m_Name;
    bool m_IsOn;

};

#endif // ALARM_H
