#include "historical.h"

bool Historical::get_Finished()
{
    return m_Finished;
}

Historical::Historical()
{
    m_Finish = false;
    m_Finished = false;
}

void Historical::Finish()
{
    m_Finish = true;
}

void Historical::execBody()
{
    while( !m_Finish )
    {

    }

    m_Finished = true;
}
