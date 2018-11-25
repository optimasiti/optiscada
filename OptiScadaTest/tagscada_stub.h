#ifndef TAGSCADA_STUB_H
#define TAGSCADA_STUB_H

#include "tagscada.h"

class TagScada_Stub : public TagScada
{
public:
    TagScada_Stub( int id, QString name, int address, DeviceModbusEthernet *pDevice );
    virtual ~TagScada_Stub();

    virtual bool GetValue( double &value );
    virtual void SetValue( double value );

private:
    double m_TestValue;
};

#endif // TAGSCADA_STUB_H
