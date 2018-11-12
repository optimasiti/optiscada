#ifndef DEVICE_H
#define DEVICE_H

//#include <QtGlobal>
#include <QObject>

class Device : public QObject
{
    Q_OBJECT
public:
    QString get_Type();

    virtual bool ReadWords( int startAddress, int count, QVector<quint16> &readValues ) = 0;
    virtual bool ReadBits( int startAddress, int count, QVector<bool> &readValues ) = 0;
    virtual void WriteWords( int startAddress, QVector<quint16> values ) = 0;
    virtual void WriteBits( int startAddress, QVector<bool> values ) = 0;
    virtual void Finish() = 0;

public slots:
    void update();

protected:
    QString m_Type;

    virtual void UpdateMemory() = 0;
};

#endif // DEVICE_H
