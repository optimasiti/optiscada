#ifndef HISTORICAL_H
#define HISTORICAL_H

#include "filestream.h"

#include <QObject>
#include <QList>
#include <QFile>


class TagHistorical;


class Historical : public QObject
{
    Q_OBJECT

public:
    bool get_Finished();

    Historical( QList<TagHistorical*> *pTagsHistorical, QString path );
    void Finish();

public slots:
    void execBody();

private:
    static const int FlushPeriodSecs;

    QList<TagHistorical*> *m_pTagsHistorical;
    bool m_Finish;
    bool m_Finished;
    QList<FileStream*> m_Files;
    QString m_Path;

    void TrateSave( TagHistorical *pTag );
    void SaveToInfluxDB( double value );
    void SaveToCSV( double value, int tagId );
    void CreateFiles();
    void CloseFiles();
};

#endif // HISTORICAL_H
