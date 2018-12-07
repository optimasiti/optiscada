#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

class QTimer;
class TagScada;
class AlarmsManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QList<TagScada*> &tags, AlarmsManager *pAlarmsManager, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *m_pTimerUpdateTags;
    QTimer *m_pTimerUpdateAlarms;
    QList<TagScada*> m_Tags;
    int m_AlarmIndex;
    AlarmsManager *m_pAlarmsManager;

private slots:
    void updateTags();
    void updateAlarms();
    void on_m_pSP_returnPressed();
};

#endif // MAINWINDOW_H
