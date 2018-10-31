#include <QModbusTcpServer>
#include <QModbusDataUnit>
#include <QUrl>

#include "modbusserver.h"


bool ModbusServer::Start( int port, int deviceNumber )
{
    m_pServer = new QModbusTcpServer( this );

    QUrl url = QUrl::fromUserInput(QString("localhost:%1").arg(port));
    m_pServer->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
    m_pServer->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());
    m_pServer->setServerAddress(deviceNumber);

    QModbusDataUnitMap memory;
    memory.insert(QModbusDataUnit::HoldingRegisters, { QModbusDataUnit::HoldingRegisters, 0, 10000});
    memory.insert(QModbusDataUnit::InputRegisters, { QModbusDataUnit::InputRegisters, 0, 10000});
    memory.insert(QModbusDataUnit::DiscreteInputs, { QModbusDataUnit::DiscreteInputs, 0, 10000});
    memory.insert(QModbusDataUnit::Coils, { QModbusDataUnit::Coils, 0, 10000});
    m_pServer->setMap( memory );

    return m_pServer->connectDevice();
}

void ModbusServer::SetRegisterValue( int address, quint16 value )
{
    if( address >= 40001 )
        m_pServer->setData( QModbusDataUnit::HoldingRegisters, static_cast<quint16>(address) - 40000, value );
    else if( address >= 30001 )
        m_pServer->setData( QModbusDataUnit::InputRegisters, static_cast<quint16>(address) - 30000, value );
    else if( address >= 10001 && address <= 20000 )
        m_pServer->setData( QModbusDataUnit::DiscreteInputs, static_cast<quint16>(address) - 10000, value );
    else if( address >= 1 && address <= 10000)
        m_pServer->setData( QModbusDataUnit::Coils, static_cast<quint16>(address), value );
}


quint16 ModbusServer::GetRegisterValue( int address )
{
    int count = 1;

    QModbusDataUnit *pData = nullptr;
    bool res = false;

    if( address >= 40001 )
        pData = new QModbusDataUnit(QModbusDataUnit::HoldingRegisters, static_cast<quint16>(address) - 40000, count);
    else if( address >= 30001 )
        pData = new QModbusDataUnit(QModbusDataUnit::InputRegisters, static_cast<quint16>(address) - 30000, count);
    else if( address >= 10001 && address <= 20000 )
        pData = new QModbusDataUnit(QModbusDataUnit::DiscreteInputs, static_cast<quint16>(address) - 10000, count);
    else if( address >= 1 && address <= 10000)
        pData = new QModbusDataUnit(QModbusDataUnit::Coils, static_cast<quint16>(address), count);

    m_pServer->data( pData );

    return pData->value(0);
}
