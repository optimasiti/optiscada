#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tagscada.h"
#include "scadacore.h"
#include "alarmsmanager.h"

MainWindow::MainWindow(QList<TagScada*> &tags, AlarmsManager *pAlarmsManager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle( "OptiScada v0.3");

    for( int i = 0; i < tags.size(); i++ )
        m_Tags.append(( tags.at(i)));

    ui->m_pSPName->setText( m_Tags.at(0)->get_Name());
    ui->m_pPVName->setText( m_Tags.at(1)->get_Name());

    m_pTimerUpdateTags = new QTimer( this );
    connect( m_pTimerUpdateTags, SIGNAL( timeout()), this, SLOT(updateTags()));
    m_pTimerUpdateTags->start( 5000 );

    m_AlarmIndex = 0;
    m_pAlarmsManager = pAlarmsManager;

    m_pTimerUpdateAlarms = new QTimer( this );
    connect( m_pTimerUpdateAlarms, SIGNAL( timeout()), this, SLOT(updateAlarms()));
    m_pTimerUpdateAlarms->start( 10000 );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTags()
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

void MainWindow::updateAlarms()
{
    QList<QString> alarms = m_pAlarmsManager->GetOnAlarms();

    if( alarms.size() == 0)
    {
        ui->m_pAlarm->setText("");
        return;
    }

    if( m_AlarmIndex>=alarms.count())
        m_AlarmIndex = 0;

    ui->m_pAlarm->setText( alarms.at(m_AlarmIndex));

    m_AlarmIndex++;
}

void MainWindow::on_m_pSP_returnPressed()
{
    bool ok;

    double value = ui->m_pSP->text().toDouble(&ok);

    if( !ok )
        return;

    m_Tags.at(0)->SetValue( value );
}
