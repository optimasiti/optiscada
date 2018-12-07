#include <QModbusDataUnit>
#include <QModbusReply>
#include <QModbusClient>
#include <QDateTime>
#include <QThread>
#include <QCoreApplication>
#include <QModbusDataUnit>
#include <QModbusClient>

#include "modbuscommon.h"
#include "modbusmemory.h"
#include "log.h"

void ModbusCommon::ModbusReadData( QModbusClient *pModbusClient, int deviceNumber, int startAddress, int count, ModbusMemory *pMemory )
{
    QModbusDataUnit::RegisterType registerType;

    if( startAddress >= 40000 )
        registerType = QModbusDataUnit::HoldingRegisters;
    else if( startAddress >= 30000 )
        registerType = QModbusDataUnit::InputRegisters;
    else if( startAddress >= 10000 && startAddress < 20000 )
        registerType = QModbusDataUnit::DiscreteInputs;
    else if( startAddress >= 0 && startAddress < 10000)
        registerType = QModbusDataUnit::Coils;
    else
    {
        Log::AddLog( Log::Critical, QString( "ModbusCommon::ModbusReadData Device %1 Address %3 out of range").arg( deviceNumber ).arg( startAddress ));
        return;
    }

    if( QModbusReply *pReply = pModbusClient->sendReadRequest( QModbusDataUnit( registerType, startAddress - (startAddress/10000)*10000,
                                                                                static_cast<quint16>(count)), deviceNumber ) )
    {
        QDateTime endTime = QDateTime::currentDateTime().addMSecs(pModbusClient->timeout());

        while(QDateTime::currentDateTime() < endTime)
        {
            QThread::usleep(50000);
            QCoreApplication::processEvents();
            if( pReply->isFinished())
                break;
        }

        if( pReply->isFinished() && pReply->error() == QModbusDevice::NoError)
        {
            const QModbusDataUnit unit = pReply->result();
            pMemory->SetValues( startAddress, unit.values() );

            delete pReply;
            return;
        }
        else
        {
            Log::AddLog( Log::Warning, QString("ModbusCommon::ModbusReadData Modbus Error %1 Device: %2 Address: %3 ").arg( pReply->errorString()).arg( deviceNumber ).arg( startAddress));
            delete pReply;
            return;
        }
    }
}

void ModbusCommon::ModbusWriteData(QModbusClient *pModbusClient, int deviceNumber, int startAddress, QVector<quint16> &values, ModbusMemory *pMemory )
{
    if( startAddress >= 40000 )
        ModbusWriteWords( pModbusClient, deviceNumber, startAddress, values, pMemory );
    else if (startAddress >= 0 && startAddress < 10000 )
    {
        QVector<bool> bitsValues;
        for( int i = 0; i < values.size(); i++ )
            bitsValues.append( values.at(i));

        ModbusWriteBits(  pModbusClient, deviceNumber, startAddress, bitsValues, pMemory );
    }
    else
        Log::AddLog( Log::Critical, "ModbusCommon::ModbusWriteData Attempting to write read only data");
}


void ModbusCommon::ModbusWriteWords(QModbusClient *pModbusClient, int deviceNumber, int startAddress, QVector<quint16> & values, ModbusMemory *pMemory )
{
    QModbusDataUnit writeDataUnit = QModbusDataUnit( QModbusDataUnit::RegisterType::HoldingRegisters, startAddress - (startAddress/10000)*10000, values.size());

    for( int i = 0; i < values.size(); i++ )
        writeDataUnit.setValue( i, values.at(i));

    if( QModbusReply *pReply = pModbusClient->sendWriteRequest( writeDataUnit, deviceNumber ) )
    {
        QDateTime e = QDateTime::currentDateTime().addMSecs(pModbusClient->timeout());
        while(QDateTime::currentDateTime()<e)
        {
            QThread::usleep(50000);
            QCoreApplication::processEvents();
            if( pReply->isFinished())
                break;
        }

        if( pReply->isFinished() && pReply->error() == QModbusDevice::NoError)
        {
            pMemory->SetValues( startAddress, values );
        }
        else
        {
            Log::AddLog( Log::Warning, QString("ModbusCommon::ModbusWriteWords Modbus Error %1 Device: %2 Address: %3 ").arg( pReply->errorString()).arg( deviceNumber ).arg( startAddress));
        }
    }
}

void ModbusCommon::ModbusWriteBits( QModbusClient *pModbusClient, int deviceNumber, int startAddress, QVector<bool> & values, ModbusMemory *pMemory )
{
    QModbusDataUnit writeDataUnit = QModbusDataUnit( QModbusDataUnit::RegisterType::Coils, startAddress, static_cast<quint16>(values.size()));

    for( int i = 0; i < values.size(); i++ )
        writeDataUnit.setValue( i, values.at(i) > 0);

    if( QModbusReply *pModbusReply = pModbusClient->sendWriteRequest( writeDataUnit, deviceNumber ) )
    {
        QDateTime e = QDateTime::currentDateTime().addMSecs(pModbusClient->timeout());
        while(QDateTime::currentDateTime()<e)
        {
            QThread::usleep(50000);
            QCoreApplication::processEvents();
            if( pModbusReply->isFinished())
                break;
        }

        if( pModbusReply->isFinished() && pModbusReply->error() == QModbusDevice::NoError)
        {
            QVector<quint16> rawValues;
            for( int i = 0; i < values.size(); i++ )
                rawValues.append( values.at(i) > 0 );

            pMemory->SetValues( startAddress, rawValues );
        }
    }
}
