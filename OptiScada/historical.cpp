#include "historical.h"
#include "tagscada.h"

#include <QDateTime>
#include <QThread>
#include <QCoreApplication>
#include <QSqlQuery>

const int Historical::SavePeriodSecs = 60;

bool Historical::get_Finished()
{
    return m_Finished;
}

Historical::Historical( QList<TagScada*> *pTags )
{
    m_pTags = pTags;
    m_Finish = false;
    m_Finished = false;
}

void Historical::Finish()
{
    m_Finish = true;
}

void Historical::execBody()
{
    int i = 0;

    while( !m_Finish )
    {
        QDateTime e = QDateTime::currentDateTime().addSecs( SavePeriodSecs );
        while( QDateTime::currentDateTime() < e )
        {
            QThread::usleep(50000);
            QCoreApplication::processEvents();
        }

        for( int i = 0; i < m_pTags->size(); i++ )
            SaveToDatabase( m_pTags->at(i) );
    }

    m_Finished = true;
}

void Historical::SaveToDatabase( TagScada *pTag )
{
    QSqlQuery query;
        query.prepare("INSERT INTO person (id, forename, surname) "
                      "VALUES (:id, :forename, :surname)");
        query.bindValue(0, 1001);
        query.bindValue(1, "Bart");
        query.bindValue(2, "Simpson");
        query.exec();
}
