#include "device.h"

int Device::get_Id()
{
    return m_Id;
}

int Device::get_TimeOutMs()
{
    return m_TimeOutMs;
}

Device::Device( int deviceId, int timeOutMs ):
    m_Id( deviceId ),
    m_TimeOutMs( timeOutMs )
{
}

void Device::update()
{
    UpdateMemory();
}
