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

    Historical( QList<TagHistorical*> *pTagsHistorical );
    void Finish();

public slots:
    void execBody();

private:
    static const int FlushPeriodSecs;

    QList<TagHistorical*> *m_pTagsHistorical;
    bool m_Finish;
    bool m_Finished;
    QList<FileStream*> m_Files;

    void TrateSaveToDatabase( TagHistorical *pTag );
    bool SaveToDatabase( TagHistorical *pTag );
    void CreateFiles();
    void CloseFiles();
};

#endif // HISTORICAL_H
