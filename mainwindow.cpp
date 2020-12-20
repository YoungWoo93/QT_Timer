#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    mTimer.setmTimeLimit(time);



    QGridLayout * gridLayout = new QGridLayout(this);

    gridLayout->addWidget(&mTimer,  0, 0, 2, 1);
    gridLayout->addWidget(&mList,   1, 0, 1, 1);


    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

