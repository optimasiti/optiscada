#include "tagscada_stub.h"

TagScada_Stub::TagScada_Stub( int id, QString name, int address, DeviceModbusEthernet *pDevice ):
    TagScada( id, name, address, pDevice )
{

}

TagScada_Stub::~TagScada_Stub()
{

}

bool TagScada_Stub::GetValue( double &value )
{
    value = m_TestValue;
    return true;
}

void TagScada_Stub::SetValue( double value )
{
    m_TestValue = value;
}
