#include "writecommand.h"

QVector<quint16>& WriteCommand::get_Values()
{
    return m_Values;
}

int WriteCommand::get_DeviceNumber()
{
    return m_DeviceNumber;
}

int WriteCommand::get_StartAddress()
{
    return m_StartAddress;
}

WriteCommand::WriteCommand( int deviceNumber, int startAddress, const QVector<quint16> &values):
    m_DeviceNumber( deviceNumber ),
    m_StartAddress( startAddress ),
    m_Values( values )
{

}


