#include "device.h"

int Device::get_Id()
{
    return m_Id;
}

QString Device::get_Type()
{
    return m_Type;
}

void Device::update()
{
    UpdateMemory();
}
