#ifndef DEVICEMODBUS_H
#define DEVICEMODBUS_H

#include <QVector>

class QModbusClient;
class ModbusMemory;

class ModbusCommon
{
public:
    static void ModbusReadData( QModbusClient *pModbusClient, int deviceNumber, int startAddress, int count, ModbusMemory *pMemory );
    static void ModbusWriteData(QModbusClient *pModbusClient, int deviceNumber, int startAddress, QVector<quint16> & values, ModbusMemory *pMemory );

private:
    static void ModbusWriteWords(QModbusClient *pModbusClient, int deviceNumber, int startAddress, QVector<quint16> & values, ModbusMemory *pMemory );
    static void ModbusWriteBits( QModbusClient *pModbusClient, int deviceNumber, int startAddress, QVector<bool> & values, ModbusMemory *pMemory );
};

#endif // DEVICEMODBUS_H
