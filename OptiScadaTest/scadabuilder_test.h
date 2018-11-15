#ifndef SCADABUILDER_TEST_H
#define SCADABUILDER_TEST_H

#include <QtTest/QTest>
#include <QObject>

class ScadaBuilder_Test : public QObject
{
    Q_OBJECT

private slots:
    virtual void BuildScada_Ok();
    virtual void BuildScada_ErrorByDevices();
    virtual void BuildScada_ErrorUnknownDevice();

};

#endif // SCADABUILDER_TEST_H

//TEST Tags info
