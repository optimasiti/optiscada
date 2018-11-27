#ifndef TAGSCADA_H
#define TAGSCADA_H

#include <QVector>
#include <QString>

class DeviceModbusEthernet;

class TagScada
{
public:
    int get_Id();
    QString get_Name();
    DeviceModbusEthernet *get_Device();
    int get_RawMin();
    int get_RawMax();
    double get_EngMin();
    double get_EngMax();

    TagScada( int id, QString name, int address, DeviceModbusEthernet *pDevice );
    TagScada( int id, QString name, int address, quint16 rawMin, quint16 rawMax, double engMin, double engMax, DeviceModbusEthernet *pDevice );

    //bool GetValue( quint16 &value );
    //void SetValue( quint16 value );
    bool GetValue( bool &value );
    void SetValue( bool value );
    virtual bool GetValue( double &value );
    virtual void SetValue( double value );

protected:
    int m_Id;
    QString m_Name;
    int m_Address;
    bool m_RawEng;
    DeviceModbusEthernet *m_pDevice;
    quint16 m_RawMin;
    quint16 m_RawMax;
    double m_EngMin;
    double m_EngMax;

};

#endif // TAGSCADA_H
