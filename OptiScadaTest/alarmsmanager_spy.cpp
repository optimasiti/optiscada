#include "alarmsmanager_spy.h"

QList<Alarm*> *AlarmsManager_Spy::get_Alarms()
{
    return m_pAlarms;
}

AlarmsManager_Spy::AlarmsManager_Spy(AlarmsManager *pAlarmsManager ):
    m_Finish( pAlarmsManager->m_Finish),
    m_Finished( pAlarmsManager->m_Finished),
    m_pAlarms( pAlarmsManager->m_pAlarms)
{  
}
