#include "alarm.h"

bool Alarm::get_IsOn()
{
    return m_IsOn;
}

QString Alarm::get_Name()
{
    return m_Name;
}

QDateTime Alarm::get_OnTs()
{
    return m_OnTs;
}

Alarm::Alarm( QString name ):
    m_Name( name ),
    m_IsOn( false )
{
}

Alarm::~Alarm()
{

}

void Alarm::SetOn()
{
    m_IsOn = true;
    m_OnTs = QDateTime::currentDateTime();
}

void Alarm::SetOff()
{
    m_IsOn = false;
    m_OnTs = QDateTime();
}


