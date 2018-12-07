#include "alarmsmanager.h"
#include "alarm.h"
#include "log.h"


bool AlarmsManager::get_Finished()
{
    return m_Finished;
}

QList<Alarm*>* AlarmsManager::get_Alarms()
{
    return m_pAlarms;
}

AlarmsManager::AlarmsManager( QList<Alarm*> *pAlarms ):
    m_pAlarms( pAlarms )
{
    m_Finish = false;
    m_Finished = true;
}

AlarmsManager::~AlarmsManager()
{
}

QList<QString> AlarmsManager::GetOnAlarms()
{
    QList<QString> onAlarms;

    for( int i = 0; i < m_pAlarms->size(); i++ )
    {
        if( m_pAlarms->at(i)->get_IsOn())
        {
            onAlarms.append( m_pAlarms->at(i)->get_OnTs().toString("dd-MM-yyyy HH:mm:ss ") + m_pAlarms->at(i)->get_Name() );
        }
    }

    return onAlarms;
}

void AlarmsManager::Finish()
{
    m_Finish = true;
}

void AlarmsManager::evaluatePool()
{
    if( m_pAlarms->size() == 0 )
    {
        Log::AddLog( Log::Info, "No alarms in AlarmsManager");
        return;
    }

    m_Finished = false;
    int i = 0;

    while( !m_Finish )
    {
        m_pAlarms->at(i)->Evaluate();

        i++;
        if( i == m_pAlarms->size() )
            i = 0;
    }

    m_Finished = true;
}
