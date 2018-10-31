#ifndef DEVICESMODBUSRTU_H
#define DEVICESMODBUSRTU_H

//#include "modbusmemory.h"
//#include "modbuscommon.h"
#include "device.h"

#include <QVector>
#include <QObject>

class ModbusMemory;

class DevicesModbusRTU : public Device
{
    Q_OBJECT
public:
    DevicesModbusRTU();
    virtual ~DevicesModbusRTU();

    void TouchAddress( int slave, int address );
    virtual bool ReadWords( int startAddress, int count, QVector<quint16> &readValues );
    virtual bool ReadBits( int startAddress, int count, QVector<bool> &readValues );
    virtual void WriteWords( int startAddress, QVector<quint16> values );
    virtual void WriteBits( int startAddress, QVector<bool> values );
    virtual void Finish();


private:
    QVector<ModbusMemory*> m_Memories;
  //  ModbusCommon *m_pModbusCommon;


    void UpdateWords();
    void UpdateBits();
    virtual void UpdateMemory();

};

#endif // DEVICESMODBUSRTU_H
