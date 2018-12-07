#ifndef ALARMSMANAGER_TEST_H
#define ALARMSMANAGER_TEST_H


#include <QtTest/QTest>
#include <QObject>

class AlarmsManager_Test : public QObject
{
public:
    Q_OBJECT

private slots:
    virtual void EvaluatePool_Alarm();
    virtual void EvaluatePool_NoAlarm();
};

#endif // ALARMSMANAGER_TEST_H
