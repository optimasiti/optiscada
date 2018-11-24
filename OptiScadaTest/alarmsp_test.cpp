#include "alarmsp_test.h"
#include "alarmsp.h"
#include "tagscada_stub.h".h"

//TODO

void AlarmSP_Test::Evaluate_Alarm()
{
    // [Preparation]
    TagScada_Stub *pTagSP = new TagScada_Stub( 1, "TAG_SP", 0, nullptr);
    TagScada_Stub *pTagPV = new TagScada_Stub( 2, "TAG_PS", 1, nullptr);
    double tolerance = 1;

    double pv = 100;
    double sp = 100;

    pTagPV->SetValue(pv); //TODO Si que hay que hacer stub.
    pTagSP->SetValue(sp);

    AlarmSP *pAlarm = new AlarmSP( "Name", pTagSP, pTagPV, tolerance );

    // [Execution]

    pAlarm->Evaluate();

    // [Comparation]

    bool isOn = pAlarm->get_IsOn();

    QCOMPARE( isOn, true );

    // [Ending]

    delete pAlarm;
    delete pTagSP;
    delete pTagPV;
}
