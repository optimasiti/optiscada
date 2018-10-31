#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tagscada.h"

MainWindow::MainWindow(QList<TagScada*> &tags, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle( "OptiScada v0.1");

    for( int i = 0; i < tags.size(); i++ )
        m_Tags.append(( tags.at(i)));

    ui->m_pSPName->setText( m_Tags.at(0)->get_Name());
    ui->m_pPVName->setText( m_Tags.at(1)->get_Name());

    m_pTimer = new QTimer( this );
    connect( m_pTimer, SIGNAL( timeout()), this, SLOT(update()));
    m_pTimer->start( 10000 );

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::update()
{
    double value;

    if( m_Tags.at(0)->GetValue(value))
        ui->m_pSP->setText( QString("%1").arg( value ));
    else
        ui->m_pSP->setText("---");

    if( m_Tags.at(1)->GetValue(value))
        ui->m_pPV->setText( QString("%1").arg( value ));
    else
        ui->m_pPV->setText("---");
}

void MainWindow::on_m_pSP_returnPressed()
{
    bool ok;

    double value = ui->m_pSP->text().toDouble(&ok);

    if( !ok )
        return;

    m_Tags.at(0)->SetValue( value );
}
