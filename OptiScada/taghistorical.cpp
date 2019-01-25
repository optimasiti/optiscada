#include "taghistorical.h"
#include "tagscada.h"

int TagHistorical::get_FrequencySecs()
{
    return m_FrequencySecs;
}

TagScada *TagHistorical::get_TagScada()
{
    return m_pTagScada;
}

QDateTime TagHistorical::get_LastSave()
{
    return m_LastSave;
}

TagHistorical::TagHistorical( TagScada *pTagScada, int frequencySecs ) :
    m_pTagScada( pTagScada ),
    m_FrequencySecs( frequencySecs )
{
}

void TagHistorical::SetLastSave()
{
    m_LastSave = QDateTime::currentDateTime();
}
