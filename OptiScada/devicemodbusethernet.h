#ifndef DEVICEMODBUSETHERNET_H
#define DEVICEMODBUSETHERNET_H

#include <QObject>
#include <QUrl>
#include <QList>
#include <QMutex>

#include "device.h"

class QModbusTcpClient;
class ModbusMemory;
class WriteCommand;

class DeviceModbusEthernet : public Device
{
    Q_OBJECT

public:
    DeviceModbusEthernet( int deviceNumber, QUrl serverUrl, int timeOutMs );
    virtual ~DeviceModbusEthernet();

    void TouchAddress( int address );
    virtual bool ReadWords( int startAddress, int count, QVector<quint16> &readValues );
    virtual bool ReadBits( int startAddress, int count, QVector<bool> &readValues );
    virtual void WriteWords( int startAddress, QVector<quint16> values );
    virtual void WriteBits( int startAddress, QVector<bool> values );
    virtual void Finish();



private:
    static const int NumberOfRetries;
    static const int MaxReadCount;

    ModbusMemory *m_pMemory;
    QModbusTcpClient *m_pModbusClient;
    QUrl m_ServerUrl;
    int m_TimeOutMs;
    QList<int> m_RefreshBlocks;
    QList<WriteCommand*> m_Writes;
    QMutex m_WritesMutex;
    bool m_Finish;

    bool Connect();
    virtual void UpdateMemory();
};

#endif // DEVICEMODBUSETHERNET_H
