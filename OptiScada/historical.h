#ifndef HISTORICAL_H
#define HISTORICAL_H

#include <QObject>
#include <QList>

class TagScada;

class Historical : public QObject
{
    Q_OBJECT

public:
    bool get_Finished();

    Historical( QList<TagScada*> *pTags );
    void Finish();

public slots:
    void execBody();

private:
    static const int SavePeriodSecs;

    QList<TagScada*> *m_pTags;
    bool m_Finish;
    bool m_Finished;

    void SaveToDatabase( TagScada *pTag );
};

#endif // HISTORICAL_H
