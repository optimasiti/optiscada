#include "filestream.h"
#include <QFile>
#include <QTextStream>

int FileStream::get_Id()
{
    return m_Id;
}

QFile *FileStream::get_pFile()
{
    return m_pFile;
}

QTextStream *FileStream::get_pStream()
{
    return m_pStream;
}


FileStream::FileStream( int id, QFile *pFile, QTextStream *pStream ):
    m_Id( id ),
    m_pFile( pFile ),
    m_pStream (pStream )
{
}
