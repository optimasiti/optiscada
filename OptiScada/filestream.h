#ifndef FILESTREAM_H
#define FILESTREAM_H

class QFile;
class QTextStream;

class FileStream
{
public:
    int get_Id();
    QFile *get_pFile();
    QTextStream *get_pStream();

    FileStream( int id, QFile *pFile, QTextStream *pStream );

private:
    int m_Id;
    QFile *m_pFile;
    QTextStream *m_pStream;
};

#endif // FILESTREAM_H
