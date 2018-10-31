#ifndef MODBUSSERVER_H
#define MODBUSSERVER_H

#include <QObject>

class QModbusTcpServer;

class ModbusServer : public QObject
{
    Q_OBJECT
public:
    bool Start( int port, int deviceNumber);
    void SetRegisterValue( int address, quint16 value );
    quint16 GetRegisterValue( int address );

private:
    QModbusTcpServer *m_pServer;
};

#endif // MODBUSSERVER_H
