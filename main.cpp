//#include "mainwindow.h"
#include "mainwidget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    mainWidget MW;
    MW.show();

    return app.exec();
}
