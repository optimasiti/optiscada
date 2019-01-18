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

AlarmsManager *ScadaCore::get_AlarmsManager()
{
    return ScadaBuilder::get_AlarmsManager();
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
    QString configFolder = QDir::currentPath() + ConfigFolder;

    return ScadaBuilder::BuildScada( configFolder );
}


