#ifndef INTEGRATION_TEST_H
#define INTEGRATION_TEST_H

#include <QtTest/QTest>
#include <QObject>

class Integration_Test : public QObject
{
    Q_OBJECT

private slots:
    void Integration_RefreshTags();
    void Integration_RaiseAlarms();
};

#endif // INTEGRATION_TEST_H
//TODO Tag repetido TEst
