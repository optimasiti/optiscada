#include <QModbusTcpClient>
#include <QDateTime>
#include <QThread>
#include <QCoreApplication>
#include <QVariant>
#include <QMutexLocker>

#include "writecommand.h"
#include "devicemodbusethernet.h"
#include "modbuscommon.h"
#include "modbusmemory.h"
#include "log.h"

const int DeviceModbusEthernet::NumberOfRetries = 0;
const int DeviceModbusEthernet::MaxReadCount = 20;

QUrl DeviceModbusEthernet::get_ServerUrl()
{
    return m_ServerUrl;
}

int DeviceModbusEthernet::get_TimeOutMs()
{
    return m_TimeOutMs;
}

int DeviceModbusEthernet::get_DeviceNumber()
{
    return m_pMemory->get_DeviceNumber();
}


DeviceModbusEthernet::DeviceModbusEthernet( int deviceId, QUrl serverUrl, int timeOutMs ):
    m_ServerUrl( serverUrl ),
    m_TimeOutMs( timeOutMs )
{
    m_Id = deviceId;
    m_pMemory = new ModbusMemory( deviceId );
    m_pModbusClient = nullptr;
    m_Finish = false;
    m_Type = "modbus_tcp";
}

DeviceModbusEthernet::~DeviceModbusEthernet()
{
}

void DeviceModbusEthernet::Finish()
{
    m_Finish = true;
}

void DeviceModbusEthernet::TouchAddress( int address )
{
    for( int i = 0; i < m_RefreshBlocks.size(); i++ )
    {
        if( address >= m_RefreshBlocks.at(i) && address < ( m_RefreshBlocks.at(i) + MaxReadCount ) )
            return;
    }

    m_RefreshBlocks.append( address );
}

bool DeviceModbusEthernet::ReadWords( int startAddress, int count, QVector<quint16> &readValues )
{
    return m_pMemory->GetValues( startAddress, count, readValues );

}

bool DeviceModbusEthernet::ReadBits( int startAddress, int count, QVector<bool> &readValues )
{
    QVector<quint16> rawValues;


    if( !m_pMemory->GetValues( startAddress, count, rawValues ))
        return false;

    for( int i = 0; i < count; i++ )
        readValues.append( rawValues.at(i) > 0 );

    return true;
}

void DeviceModbusEthernet::WriteWords( int startAddress, QVector<quint16> values )
{
    QMutexLocker locker( &m_WritesMutex);

    m_Writes.append( new WriteCommand( m_pMemory->get_DeviceNumber(), startAddress, values ) );
}

void DeviceModbusEthernet::WriteBits( int startAddress, QVector<bool> values )
{
    QMutexLocker locker( &m_WritesMutex);

    QVector<quint16> rawValues;
    for( int i = 0; i < values.size(); i++ )
        rawValues.append( values.at( i ));

    m_Writes.append( new WriteCommand( m_pMemory->get_DeviceNumber(), startAddress, rawValues ) );
}

void DeviceModbusEthernet::UpdateMemory()
{
    if( m_RefreshBlocks.size() == 0 )
    {
        Log::AddLog( Log::Error, QString( "DeviceModbusEthernet::UpdateMemory No tags to Refresh for device %1").arg(m_ServerUrl.url()));
        return;
    }

    while( !m_Finish )
    {
        for( int i = 0; i < m_RefreshBlocks.size(); i++ )
        {
            WriteCommand *pWriteCommand = nullptr;

            m_WritesMutex.lock();
            if( m_Writes.size() > 0 )
            {
                pWriteCommand = m_Writes.first();
                m_Writes.removeFirst();
            }
            m_WritesMutex.unlock();

            if( !Connect())
            {
                {
                    QDateTime e = QDateTime::currentDateTime().addMSecs(m_TimeOutMs);
                    while(QDateTime::currentDateTime()<e)
                    {
                        QThread::usleep(50000);
                        QCoreApplication::processEvents();
                    }
                    continue;
                }
            }

            if( pWriteCommand )
            {
                ModbusCommon::ModbusWriteData( m_pModbusClient, pWriteCommand->get_DeviceNumber(), pWriteCommand->get_StartAddress(), pWriteCommand->get_Values(), m_pMemory );
                delete pWriteCommand;
            }
            else
            {
                ModbusCommon::ModbusReadData( m_pModbusClient, m_pMemory->get_DeviceNumber(), m_RefreshBlocks.at(i), MaxReadCount, m_pMemory );
            }
        }
    }
}

bool DeviceModbusEthernet::Connect()
{
    if( !m_pModbusClient )
        m_pModbusClient = new QModbusTcpClient(this);

    if( m_pModbusClient->state() == QModbusDevice::ConnectedState )
        return true;

    m_pModbusClient->setConnectionParameter(QModbusDevice::NetworkPortParameter, m_ServerUrl.port() );
    m_pModbusClient->setConnectionParameter(QModbusDevice::NetworkAddressParameter, m_ServerUrl.host());
    m_pModbusClient->setTimeout(m_TimeOutMs);
    m_pModbusClient->setNumberOfRetries(NumberOfRetries);

    if( !m_pModbusClient->connectDevice() )
    {
        Log::AddLog( Log::Warning, QString("DeviceModbusEthernet::Connect Cannot connect to device Host=%1 Port=%2").arg(m_ServerUrl.host()).arg(m_ServerUrl.port()));
        return false;
    }

    QDateTime e = QDateTime::currentDateTime().addMSecs(m_pModbusClient->timeout());
    while(QDateTime::currentDateTime()<e)
    {
        QThread::usleep(50000);
        QCoreApplication::processEvents();
        if( m_pModbusClient->state() == QModbusDevice::ConnectedState )
        {
            break;
        }
    }

    if( m_pModbusClient->state() != QModbusDevice::ConnectedState)
    {
        Log::AddLog( Log::Warning, QString("DeviceModbusEthernet::Connect Cannot connect to device Host=%1 Port=%2").arg(m_ServerUrl.host()).arg(m_ServerUrl.port()));
        return false;
    }

    Log::AddLog( Log::Info, QString("DeviceModbusEthernet::Connect Connection status to device Host=%1 Port=%2 Status=%3").arg(m_ServerUrl.host()).arg(m_ServerUrl.port()).arg(m_pModbusClient->state() == QModbusDevice::ConnectedState));

    return m_pModbusClient->state() == QModbusDevice::ConnectedState;
}


