#include "tagscada.h"
#include "devicemodbusethernet.h"

int TagScada::get_Id()
{
    return m_Id;
}

QString TagScada::get_Name()
{
    return m_Name;
}

DeviceModbusEthernet *TagScada::get_Device()
{
    return m_pDevice;
}

int TagScada::get_RawMin()
{
    return m_RawMin;
}

int TagScada::get_RawMax()
{
    return m_RawMax;
}

double TagScada::get_EngMin()
{
    return m_EngMin;
}

double TagScada::get_EngMax()
{
    return m_EngMax;
}


TagScada::TagScada( int id, QString name, int address, DeviceModbusEthernet *pDevice ):
    m_Id( id ),
    m_Name( name ),
    m_Address( address ),
    m_RawEng( false ),
    m_pDevice(pDevice )
{
}


TagScada::TagScada( int id, QString name, int address, quint16 rawMin, quint16 rawMax, double engMin, double engMax, DeviceModbusEthernet *pDevice ):
    m_Id( id ),
    m_Name( name ),
    m_Address( address ),
    m_RawEng( true ),
    m_pDevice( pDevice ),
    m_RawMin( rawMin ),
    m_RawMax( rawMax ),
    m_EngMin( engMin ),
    m_EngMax( engMax )
{
}

TagScada::~TagScada()
{
}

bool TagScada::GetValue( bool &value)
{
    bool isValid;
    static const int count = 1;
    QVector<bool> readValues;

    isValid = m_pDevice->ReadBits( m_Address, count, readValues );

    if( readValues.count() > 0 )
    {
        value = readValues.first();
    }
    else
    {
        isValid = false;
    }

    return isValid;
}

void TagScada::SetValue( bool value )
{
    QVector<bool> values;

    values.append( value );

    m_pDevice->WriteBits( m_Address, values );
}

bool TagScada::GetValue( double &value )
{
    bool isValid;
    static const int count = 1;
    QVector<quint16> readValues;

    isValid = m_pDevice->ReadWords( m_Address, count, readValues );

    if( isValid )
    {
        value = readValues.first();
        if( m_RawEng )
        {
            double factor = (m_EngMax - m_EngMin)/(m_RawMax-m_RawMin);
            value = (value - m_RawMin) * factor + m_EngMin;
        }
    }

    return isValid;
}

void TagScada::SetValue( double value )
{
    QVector<quint16> values;

    if( m_RawEng )
    {
        double factor = (m_RawMax-m_RawMin)/(m_EngMax - m_EngMin);
        value = (value - m_EngMin) * factor + m_RawMin;
    }

    values.append( static_cast<quint16>(value) );

    m_pDevice->WriteWords( m_Address, values );
}
