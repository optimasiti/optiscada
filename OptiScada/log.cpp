#include <QDateTime>
#include <QMutexLocker>
#include <QDebug>

#include "log.h"

QMutex Log::m_Mutex;

void Log::AddLog( Severity severity, QString message)
{
    QMutexLocker lock(&m_Mutex);

    qDebug()<<SeverityToString( severity )<<" "<<QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")<<"->"<<message;
}

QString Log::SeverityToString( Severity severity )
{
    switch( severity )
    {
        case Info: return "INFO    ";
        case Warning: return "WARNING ";
        case Error: return "ERROR   ";
        case Critical: return "CRITICAL";
    }
}

