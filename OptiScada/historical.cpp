#include "historical.h"
#include "tagscada.h"
#include "taghistorical.h"

#include <QDateTime>
#include <QThread>
#include <QCoreApplication>
#include <QSqlQuery>

#include <QDebug> //TODO

const int Historical::FlushPeriodSecs = 2;

bool Historical::get_Finished()
{
    return m_Finished;
}

Historical::Historical( QList<TagHistorical*> *pTagsHistorical, QString path )
{
    m_pTagsHistorical = pTagsHistorical;
    m_Finish = false;
    m_Finished = false;
    m_Path = path;
}

void Historical::Finish()
{
    m_Finish = true;
}

void Historical::execBody()
{
    CreateFiles();

    int i = 0;

    QDateTime nextFlush = QDateTime::currentDateTime().addSecs( FlushPeriodSecs );

    while( !m_Finish )
    {
        if( QDateTime::currentDateTime() > nextFlush )
        {
            for( int i = 0; i < m_Files.size(); i++ )
            {
                m_Files.at(i)->get_pStream()->flush();
                m_Files.at(i)->get_pFile()->flush();
            }

            nextFlush = QDateTime::currentDateTime().addSecs( FlushPeriodSecs );
        }

//        while( QDateTime::currentDateTime() < e )
        {
            QThread::usleep(50000);
            QCoreApplication::processEvents();
        }

        for( int i = 0; i < m_pTagsHistorical->size(); i++ )
            TrateSaveToDatabase( m_pTagsHistorical->at(i) );
    }

    CloseFiles();

    m_Finished = true;
}

void Historical::CreateFiles()
{
    for( int i = 0; i < m_pTagsHistorical->length(); i++ )
    {
        QFile *pFile = new QFile( m_Path + QString("/%1_%2.txt").arg(m_pTagsHistorical->at(i)->get_TagScada()->get_Name()).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd")));
        pFile->open( QIODevice::ReadWrite | QIODevice::Text );
        QTextStream *pStream = new QTextStream( pFile );
        m_Files.append( new FileStream( m_pTagsHistorical->at(i)->get_TagScada()->get_Id(), pFile, pStream ) );
    }
}

void Historical::CloseFiles()
{
    for( int i = 0; i < m_Files.length(); i++ )
    {
        m_Files.at(i)->get_pFile()->close();
        delete m_Files.at(i)->get_pStream();
        delete m_Files.at(i)->get_pFile();
    }
}

void Historical::TrateSaveToDatabase( TagHistorical *pTagHistorical )
{
    if( !pTagHistorical->get_LastSave().isValid() || pTagHistorical->get_LastSave().secsTo( QDateTime::currentDateTime()) >= pTagHistorical->get_FrequencySecs() )
    {
        if(SaveToDatabase( pTagHistorical ))
            pTagHistorical->SetLastSave();
    }

    return;
}

bool Historical::SaveToDatabase( TagHistorical *pTag )
{
    double value;

    if( !pTag->get_TagScada()->GetValue( value ) )
        return false;

    int i;

    for( i = 0; i < m_Files.length(); i++ )
        if( m_Files.at(i)->get_Id() == m_pTagsHistorical->at(i)->get_TagScada()->get_Id())
            break;

    *(m_Files.at(i)->get_pStream())<<QString("%1;%2").arg( QDateTime::currentDateTime().toString("yyyy-mm-ddThh:mm:ss")).arg(value )<<endl;

    return true;
}
