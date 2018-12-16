#ifndef HISTORICAL_H
#define HISTORICAL_H

#include <QObject>

class Historical : public QObject
{
    Q_OBJECT

public:
    bool get_Finished();

    Historical();
    void Finish();

public slots:
    void execBody();

private:
    bool m_Finish;
    bool m_Finished;
};

#endif // HISTORICAL_H
