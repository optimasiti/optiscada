#ifndef SCADABUILDER_TEST_H
#define SCADABUILDER_TEST_H

#include <QtTest/QTest>
#include <QObject>

class ScadaBuilder_Test : public QObject
{
    Q_OBJECT

private slots:

    virtual void LoadDevices_Ok();
    virtual void LoadDevices_Error();
    virtual void LoadTags_Ok();
};

#endif // SCADABUILDER_TEST_H
