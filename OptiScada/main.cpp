#include "mainwindow.h"
#include "scadacore.h"

#include <QApplication>
#include <QList>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ScadaCore scadaCore;

    if( !scadaCore.Start() )
        return 0;

    QList<TagScada*> tags;

    for( int i = 0; i < scadaCore.get_Tags()->size(); i++ )
        tags.append( scadaCore.get_Tags()->at(i));

    MainWindow w( tags, scadaCore.get_AlarmsManager() );
    w.show();

    return a.exec();
}
