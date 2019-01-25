#include "historical.h"
#include "tagscada.h"
#include "taghistorical.h"
#include "log.h"

#include <QDateTime>
#include <QThread>
#include <QCoreApplication>
#include <QSqlQuery>
#include <QTextStream>
#include <QDir>

const int Historical::FlushPeriodSecs = 5;

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
    if( m_Files.length() == 0 )
    {
        m_Finished = true;
        return;
    }

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

        QThread::usleep(50000);
        QCoreApplication::processEvents();

        for( int i = 0; i < m_pTagsHistorical->size(); i++ )
            TrateSave( m_pTagsHistorical->at(i) );
    }

    CloseFiles();

    m_Finished = true;
}

bool Historical::CreateFiles()
{
    if( !QDir(m_Path).exists() )
        QDir().mkdir( m_Path );

    for( int i = 0; i < m_pTagsHistorical->length(); i++ )
    {
        QString fileName = m_Path + QString("/%1_%2.txt").arg(m_pTagsHistorical->at(i)->get_TagScada()->get_Name()).arg(QDateTime::currentDateTime().toString("yyyy-MM-ddThhmmss"));
        QFile *pFile = new QFile( fileName );

        if( !pFile->open( QIODevice::ReadWrite | QIODevice::Text ) )
        {
            Log::AddLog( Log::Critical, QString( "Error creating historical file %1").arg( fileName ));
            return false;
        }

        QTextStream *pStream = new QTextStream( pFile );
        m_Files.append( new FileStream( m_pTagsHistorical->at(i)->get_TagScada()->get_Id(), pFile, pStream ) );
    }

    return true;
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

void Historical::TrateSave( TagHistorical *pTagHistorical )
{
    if( !pTagHistorical->get_LastSave().isValid() || pTagHistorical->get_LastSave().secsTo( QDateTime::currentDateTime()) >= pTagHistorical->get_FrequencySecs() )
    {
        double value;

        if( pTagHistorical->get_TagScada()->GetValue( value ) )
        {
            int i;

            for( i = 0; i < m_Files.length(); i++ )
                if( m_Files.at(i)->get_Id() == m_pTagsHistorical->at(i)->get_TagScada()->get_Id())
                    break;

            if( m_pTagsHistorical->at(i)->get_TagScada()->GetValue( value ) )
            {
                SaveToCSV( value, m_Files.at(i)->get_pStream() );
                pTagHistorical->SetLastSave();
            }
        }
    }
}


void Historical::SaveToCSV( double value, QTextStream *pTextStream )
{
    *(pTextStream)<<QString("%1;%2").arg( QDateTime::currentDateTime().toString("yyyy-mm-ddThh:mm:ss")).arg(value )<<endl;
}
