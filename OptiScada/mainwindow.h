#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

class QTimer;
class TagScada;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QList<TagScada*> &tags, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QTimer *m_pTimer;
    QList<TagScada*> m_Tags;

private slots:
    void update();
    void on_m_pSP_returnPressed();
};

#endif // MAINWINDOW_H
