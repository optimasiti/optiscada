#include "tagscada_stub.h"

TagScada_Stub::TagScada_Stub( int id, QString name, int address, DeviceModbusEthernet *pDevice ):
    TagScada( id, name, address, pDevice )
{

}

bool TagScada_Stub::GetValue( double &value )
{
    //TODO
    int i = 0;
}

void TagScada_Stub::SetValue( double value )
{
    //TODO
    int i = 0;
}
