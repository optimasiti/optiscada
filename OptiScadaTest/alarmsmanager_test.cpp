#include "alarmsmanager_test.h"
#include "alarmsmanager.h"
#include "tagscada_stub.h"
#include "alarmsp.h"

#include <QThread>

void AlarmsManager_Test::EvaluatePool_Alarm()
{
    // [Preparation]

    TagScada_Stub *pTagSP = new TagScada_Stub( 1, "TAG_SP", 0, nullptr);
    TagScada_Stub *pTagPV = new TagScada_Stub( 2, "TAG_PS", 1, nullptr);
    double tolerance = 1;

    double pv = 50;
    double sp = 100;

    pTagPV->SetValue(pv);
    pTagSP->SetValue(sp);

    AlarmSP *pAlarm = new AlarmSP( "Name", pTagSP, pTagPV, tolerance );
    QList<Alarm*> *pAlarms = new QList<Alarm*>();
    pAlarms->append( pAlarm );

    AlarmsManager *pAlarmsManager = new AlarmsManager( pAlarms );

    // [Execution]

    QThread *pThread = new QThread();
    connect(pThread, SIGNAL(finished()), pAlarmsManager, SLOT(deleteLater()));
    pAlarmsManager->moveToThread(pThread);
    QObject::connect(pThread, SIGNAL (started()), pAlarmsManager, SLOT (evaluatePool()));
    pThread->start();

    QDateTime e = QDateTime::currentDateTime().addMSecs(1000);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    // [Comparation]

    QList<QString> onAlarms = pAlarmsManager->GetOnAlarms();

    QCOMPARE( onAlarms.size(), 1 );

    QString name = onAlarms.first();

    QCOMPARE( onAlarms.first().mid(20,4), "Name");

    QString tsString = onAlarms.first();
    QDateTime ts = QDateTime(QDate(tsString.mid(6,4).toInt(), tsString.mid(3,2).toInt(), tsString.mid(0,2).toInt()), QTime(tsString.mid(11,2).toInt(), tsString.mid(14,2).toInt(),tsString.mid(17,2).toInt()));
    int diff = ts.secsTo(QDateTime::currentDateTime());
    QVERIFY( diff <= 2 );

    // [Ending]

   pAlarmsManager->Finish();
   while( !pAlarmsManager->get_Finished())
   {
       QThread::usleep(50000);
       QCoreApplication::processEvents();
   }
   delete pAlarmsManager;
   delete pAlarm;
   delete pAlarms;
}

void AlarmsManager_Test::EvaluatePool_NoAlarm()
{
    // [Preparation]

    TagScada_Stub *pTagSP = new TagScada_Stub( 1, "TAG_SP", 0, nullptr);
    TagScada_Stub *pTagPV = new TagScada_Stub( 2, "TAG_PS", 1, nullptr);
    double tolerance = 1;

    double pv = 99;
    double sp = 100;

    pTagPV->SetValue(pv);
    pTagSP->SetValue(sp);

    AlarmSP *pAlarm = new AlarmSP( "Name", pTagSP, pTagPV, tolerance );
    QList<Alarm*> *pAlarms = new QList<Alarm*>();
    pAlarms->append( pAlarm );

    AlarmsManager *pAlarmsManager = new AlarmsManager( pAlarms );

    // [Execution]

    QThread *pThread = new QThread();
    connect(pThread, SIGNAL(finished()), pAlarmsManager, SLOT(deleteLater()));
    pAlarmsManager->moveToThread(pThread);
    QObject::connect(pThread, SIGNAL (started()), pAlarmsManager, SLOT (evaluatePool()));
    pThread->start();

    QDateTime e = QDateTime::currentDateTime().addMSecs(1000);
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
    }

    // [Comparation]

    QList<QString> onAlarms = pAlarmsManager->GetOnAlarms();

    QCOMPARE( onAlarms.size(), 0 );

    // [Ending]

   pAlarmsManager->Finish();
   while( !pAlarmsManager->get_Finished())
   {
       QThread::usleep(50000);
       QCoreApplication::processEvents();
   }
   delete pAlarmsManager;
   delete pAlarm;
   delete pAlarms;
}
