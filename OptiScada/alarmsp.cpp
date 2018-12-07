#include "alarmsp.h"
#include "tagscada.h"
#include "math.h"


AlarmSP::AlarmSP( QString name, TagScada *pTagSP, TagScada *pTagPV, double tolerance ):
    Alarm( name ),
    m_pTagSP( pTagSP ),
    m_pTagPV( pTagPV ),
    m_Tolerance( tolerance )
{
}

AlarmSP::~AlarmSP()
{

}

void AlarmSP::Evaluate()
{
    double sp;
    double pv;

    if( !m_pTagSP->GetValue( sp ))
        return;

    if( !m_pTagPV->GetValue( pv ))
        return;

    double diff = fabs(sp - pv);
    double margin = fabs(sp * m_Tolerance/100);

    if( diff > margin )
        this->SetOn();
    else
        this->SetOff();
}
