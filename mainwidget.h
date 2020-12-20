#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "stopwatch.h"
#include "prograssnode.h"
#include "prograsslist.h"

class mainWidget : public QWidget
{
public:
    mainWidget();
    void setTimer(int times);
private:
    int time;
    prograssList*   mList;
    StopWatch*      mTimer;
};

#endif // MAINWIDGET_H
