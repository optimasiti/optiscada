#include "alarmsp.h"
#include "tagscada.h"

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

}
