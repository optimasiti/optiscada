#include <QThread>
#include <QDir>

#include "scadacore.h"
#include "devicemodbusethernet.h"
#include "tagscada.h"
#include "scadabuilder.h"

const QString ScadaCore::ConfigFolder = "/../config";

QList<TagScada*>* ScadaCore::get_Tags()
{
    return ScadaBuilder::get_Tags();
}

ScadaCore::ScadaCore()
{
}

ScadaCore::~ScadaCore()
{
    ScadaBuilder::ShutdownScada();
}

bool ScadaCore::Start()
{
    QString fileName = QDir::currentPath() + ConfigFolder;

    return ScadaBuilder::BuildScada( fileName );
}


