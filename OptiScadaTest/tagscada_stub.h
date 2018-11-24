#ifndef TAGSCADA_STUB_H
#define TAGSCADA_STUB_H

#include "tagscada.h"

class TagScada_Stub : public TagScada
{
public:
    TagScada_Stub( int id, QString name, int address, DeviceModbusEthernet *pDevice );

    bool GetValue( double &value );
    void SetValue( double value );
};

#endif // TAGSCADA_STUB_H
