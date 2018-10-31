#ifndef WRITECOMMAND_H
#define WRITECOMMAND_H

#include <QVector>
#include <QtGlobal>

class WriteCommand
{
public:
    WriteCommand( int deviceNumber, int startAddress, const QVector<quint16> &values);

    int get_DeviceNumber();
    int get_StartAddress();
    QVector<quint16>& get_Values();

private:
    int m_DeviceNumber;
    int m_StartAddress;
    QVector<quint16> m_Values;

};

#endif // WRITECOMMAND_H
