#include <QThread>

#include "scadacore.h"
#include "devicemodbusethernet.h"
#include "tagscada.h"

QList<TagScada*>& ScadaCore::get_Tags()
{
    return m_Tags;
}

ScadaCore::ScadaCore()
{

}

bool ScadaCore::Start()
{
    int deviceNumber = 1;
    //QUrl serverUrl = QUrl::fromUserInput("bocamina.hopto.org:502");
    QUrl serverUrl = QUrl::fromUserInput("localhost:502");
    int timeOutMs = 2000;

    DeviceModbusEthernet *pDevice = new DeviceModbusEthernet( deviceNumber, serverUrl, timeOutMs);

    m_Devices.append( pDevice );

    int address = 40065;
    TagScada *pTag = new TagScada( "Consigna", address, pDevice );
    pDevice->TouchAddress( address );
    m_Tags.append( pTag );

    address = 40066;
    pTag = new TagScada( "Caudal", address, pDevice );
    pDevice->TouchAddress( address );
    m_Tags.append( pTag );

    for( int i = 0; i < m_Devices.count(); i++ )
    {
        QThread *pThread = new QThread();
        m_Devices.at(i)->moveToThread(pThread);
        QObject::connect(pThread, SIGNAL (started()), m_Devices.at(i), SLOT (update()));
        pThread->start();
    }

    return true;
}
