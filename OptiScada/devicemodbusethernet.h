#ifndef DEVICEMODBUSETHERNET_H
#define DEVICEMODBUSETHERNET_H

#include <QObject>
#include <QUrl>
#include <QList>
#include <QMutex>

class QModbusTcpClient;
class ModbusMemory;
class WriteCommand;

class DeviceModbusEthernet : public QObject
{
    Q_OBJECT

public:
    int get_Id();
    int get_TimeOutMs();
    QUrl get_ServerUrl();
    int get_DeviceNumber();

    DeviceModbusEthernet( int deviceId, QUrl serverUrl, int timeOutMs );
    virtual ~DeviceModbusEthernet();

    void TouchAddress( int address );
    bool ReadWords( int startAddress, int count, QVector<quint16> &readValues );
    bool ReadBits( int startAddress, int count, QVector<bool> &readValues );
    void WriteWords( int startAddress, QVector<quint16> values );
    void WriteBits( int startAddress, QVector<bool> values );
    void Finish();

public slots:
    void update();


private:
    static const int NumberOfRetries;
    static const int MaxReadCount;

    int m_Id;
    int m_TimeOutMs;
    ModbusMemory *m_pMemory;
    QModbusTcpClient *m_pModbusClient;
    QUrl m_ServerUrl;
    QList<int> m_RefreshBlocks;
    QList<WriteCommand*> m_Writes;
    QMutex m_WritesMutex;
    bool m_Finish;

    bool Connect();
    virtual void UpdateMemory();
};

#endif // DEVICEMODBUSETHERNET_H
