#ifndef DEVICE_H
#define DEVICE_H

//#include <QtGlobal>
#include <QObject>

class Device : public QObject
{
    Q_OBJECT
public:
    int get_Id();
    int get_TimeOutMs();

    Device( int deviceId, int timeOutMs );

    virtual bool ReadWords( int startAddress, int count, QVector<quint16> &readValues ) = 0;
    virtual bool ReadBits( int startAddress, int count, QVector<bool> &readValues ) = 0;
    virtual void WriteWords( int startAddress, QVector<quint16> values ) = 0;
    virtual void WriteBits( int startAddress, QVector<bool> values ) = 0;
    virtual void Finish() = 0;

public slots:
    void update();

protected:
    int m_Id;
    QString m_Type;
    int m_TimeOutMs;

    virtual void UpdateMemory() = 0;
};

#endif // DEVICE_H
