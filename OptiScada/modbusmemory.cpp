#include "modbusmemory.h"
#include "log.h"

const int ModbusMemory::ExpirationSecs = 30;

int ModbusMemory::get_DeviceNumber()
{
    return m_DeviceNumber;
}

ModbusMemory::ModbusMemory( int deviceNumber ):
    m_DeviceNumber( deviceNumber )
{
    m_LastTsInputBits = QDateTime::currentDateTime().addSecs( - ExpirationSecs+1);
    m_LastTsCoils = QDateTime::currentDateTime().addSecs( - ExpirationSecs+1);
    m_LastTsInputRegisters = QDateTime::currentDateTime().addSecs( - ExpirationSecs+1);
    m_LastTsHoldingRegisters = QDateTime::currentDateTime().addSecs( - ExpirationSecs+1);
}

void ModbusMemory::SetValues( int startAddress, const QVector<quint16> &values )
{
    if( (startAddress / 10000) != ((startAddress+values.size())/10000))
    {
        Log::AddLog( Log::Critical, QString("ModbusMemory::SetValues Address %1 and count %2 out of range").arg( startAddress).arg( values.size()));
        return;
    }

    quint16 *pMemory;

    if( startAddress >= 40000 )
    {
        pMemory = m_HoldingRegisters;
        m_LastTsHoldingRegisters = QDateTime::currentDateTime();
    }
    else if( startAddress >= 30000 )
    {
        pMemory = m_InputRegisters;
        m_LastTsInputRegisters = QDateTime::currentDateTime();
    }
    else if( startAddress >= 10000 && startAddress < 20000 )
    {
        pMemory = m_InputBits;
        m_LastTsInputBits = QDateTime::currentDateTime();
    }
    else if( startAddress >= 0 && startAddress < 10000 )
    {
        pMemory = m_Coils;
        m_LastTsCoils = QDateTime::currentDateTime();
    }
    else
    {
        Log::AddLog( Log::Critical, QString("ModbusMemory::SetValues Address %1 out of range").arg( startAddress));
        return;
    }

    startAddress -= ((startAddress / 10000)*10000);

    for( int i = startAddress ; i < startAddress + values.size(); i++ )
    {
        pMemory[i] = values.at(i-startAddress);
        //Log::AddLog( Log::Info, QString("[%1]:%2").arg(i).arg(values.at(i-startAddress)));
    }
}

bool ModbusMemory::GetValues( int startAddress, int count, QVector<quint16> &values )
{
    quint16 *pMemory;

    if( startAddress >= 40000 )
    {
        if( m_LastTsHoldingRegisters.secsTo( QDateTime::currentDateTime()) > ExpirationSecs )
            return false;

        pMemory = m_HoldingRegisters;
    }
    else if( startAddress >= 30000 )
    {
        if( m_LastTsInputRegisters.secsTo( QDateTime::currentDateTime()) > ExpirationSecs )
            return false;

        pMemory = m_InputRegisters;
    }
    else if( startAddress >= 10000 && startAddress < 20000 )
    {
        if( m_LastTsInputBits.secsTo( QDateTime::currentDateTime()) > ExpirationSecs )
            return false;

        pMemory = m_InputBits;
    }
    else if( startAddress >= 0 && startAddress < 10000 )
    {
        if( m_LastTsCoils.secsTo( QDateTime::currentDateTime()) > ExpirationSecs )
            return false;

        pMemory = m_Coils;
    }
    else
    {
        Log::AddLog( Log::Critical, QString("ModbusMemory::SetValues Address %1 out of range").arg( startAddress));
        return false;
    }

    if( (startAddress / 10000) != ((startAddress+values.size())/10000))
    {
        Log::AddLog( Log::Critical, QString("ModbusMemory::SetValues Address %1 and count %2 out of range").arg( startAddress).arg( values.size()));
        return false;
    }

    startAddress -= ((startAddress / 10000)*10000);

    for( int i = startAddress; i < startAddress + count; i++ )
    {
        values.append(pMemory[i]);
    }

    return true;
}
