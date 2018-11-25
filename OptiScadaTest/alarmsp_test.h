#ifndef ALARMSP_TEST_H
#define ALARMSP_TEST_H

#include <QtTest/QTest>
#include <QObject>

class AlarmSP_Test : public QObject
{
public:
    Q_OBJECT

private slots:

    virtual void Evaluate_Alarm();
    virtual void Evaluate_NoAlarm();
    virtual void Evaluate_NoAlarmByTolerance();

};

#endif // ALARMSP_TEST_H
