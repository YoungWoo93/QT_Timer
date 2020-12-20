#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "stopwatch.h"
#include "prograssnode.h"
#include "prograsslist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int time;
    prograssList mList;
    StopWatch mTimer;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
