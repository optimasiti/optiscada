#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QMutex>

class Log
{
public:
    enum Severity {
            Info,
            Warning,
            Error,
            Critical
        };

    static void AddLog( Severity severity, QString message );

private:
    static QMutex m_Mutex;
    static QString SeverityToString( Severity severity );
};

#endif // LOG_H
