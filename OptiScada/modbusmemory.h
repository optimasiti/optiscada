#ifndef MODBUSMEMORY_H
#define MODBUSMEMORY_H

#include <QtGlobal>
#include <QVector>
#include <QDateTime>

class ModbusMemory
{
public:
    static const int ExpirationSecs;

    ModbusMemory( int deviceNumber );

    int get_DeviceNumber();

    void SetValues( int startAddress, const QVector<quint16> &values );
    bool GetValues( int startAddress, int count, QVector<quint16> &values );

private:
    bool m_IsValid;
    int m_DeviceNumber;

    quint16 m_InputBits[10000];
    quint16 m_Coils[10000];
    quint16 m_InputRegisters[10000];
    quint16 m_HoldingRegisters[10000];

    QDateTime m_LastTsInputBits;
    QDateTime m_LastTsCoils;
    QDateTime m_LastTsInputRegisters;
    QDateTime m_LastTsHoldingRegisters;

};

#endif // MODBUSMEMORY_H
