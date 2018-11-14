#include "devicesmodbusrtu.h"
#include "modbusmemory.h"

DevicesModbusRTU::DevicesModbusRTU():Device( 0, 0 ) //Not implemented
{

}

DevicesModbusRTU::~DevicesModbusRTU()
{
}

void DevicesModbusRTU::TouchAddress( int,  int  )
{
}

bool DevicesModbusRTU::ReadWords( int, int, QVector<quint16> & )
{
    return false;
}

bool DevicesModbusRTU::ReadBits( int, int, QVector<bool> & )
{
    return false;
}

void DevicesModbusRTU::WriteWords( int, QVector<quint16> )
{
}

void DevicesModbusRTU::WriteBits( int, QVector<bool> )
{
}


void DevicesModbusRTU::UpdateMemory()
{

}

void DevicesModbusRTU::Finish()
{

}
