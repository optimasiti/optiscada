#ifndef DEVICEMODBUSETHERNET_TEST_H
#define DEVICEMODBUSETHERNET_TEST_H

#include <QtTest/QTest>
#include <QObject>

#include "devicemodbusethernet.h"

class DeviceModbusEthernet_Test : public QObject
{
public:
    Q_OBJECT

private slots:

    virtual void ReadHoldingRegisters_Ok();
    virtual void ReadInputRegisters_Ok();
    virtual void ReadDiscreteInputs_Ok();
    virtual void ReadCoils_Ok();
    virtual void WriteHoldingRegisters_Ok();
    virtual void WriteCoils_Ok();
};

#endif // DEVICEMODBUSETHERNET_TEST_H
