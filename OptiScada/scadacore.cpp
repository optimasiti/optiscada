#include <QThread>
#include <QDir>

#include "scadacore.h"
#include "devicemodbusethernet.h"
#include "tagscada.h"
#include "scadabuilder.h"

//const QString ScadaCore::DeviceFileName = "devices.txt";
//const QString ScadaCore::TagsFileName = "tags.txt";

QList<TagScada*>* ScadaCore::get_Tags()
{
    return m_pTags;
}

ScadaCore::ScadaCore()
{

}

bool ScadaCore::Start() //TODO Destructor
{
    QString fileName = QDir::currentPath() + "/config/";

    if( !ScadaBuilder::BuildScada( fileName ) )
    {
        return false;
    }

    /*
    int deviceNumber = 1;
    QUrl serverUrl = QUrl::fromUserInput("localhost:502");
    int timeOutMs = 2000;

    DeviceModbusEthernet *pDevice = new DeviceModbusEthernet( deviceNumber, serverUrl, timeOutMs);

    m_Devices.append( pDevice );
*/
    /*
    int address = 40065;
    TagScada *pTag = new TagScada( "Consigna", address, pDevice );
    pDevice->TouchAddress( address );
    m_Tags.append( pTag );

    address = 40066;
    pTag = new TagScada( "Caudal", address, pDevice );
    pDevice->TouchAddress( address );
    m_pTags->append( pTag );

    for( int i = 0; i < m_Devices.count(); i++ )
    {
        QThread *pThread = new QThread();
        m_pDevices->at(i)->moveToThread(pThread);
        QObject::connect(pThread, SIGNAL (started()), m_pDevices->at(i), SLOT (update()));
        pThread->start();
    }
*/
    return true;
}
