#include "alarm.h"

bool Alarm::get_IsOn()
{
    return m_IsOn;
}

Alarm::Alarm( QString name ):
    m_Name( name ),
    m_IsOn( false )
{
}


