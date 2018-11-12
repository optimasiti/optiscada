#include "device.h"

QString Device::get_Type()
{
    return m_Type;
}

void Device::update()
{
    UpdateMemory();
}
