#include "mainwidget.h"



mainWidget::mainWidget()
{
    this->resize(750, 500);
    mTimer = new StopWatch(this, 60);
    mTimer->setMinimumWidth(500);
    mList = new prograssList(this);
    mList->setMaximumHeight(145);
    mList->setMinimumHeight(145);

    QGridLayout * gridLayout = new QGridLayout(this);

    gridLayout->addWidget(mTimer,  0, 0, 2, 1);
    gridLayout->addWidget(mList,   3, 0, 1, 1);

    connect(mList, SIGNAL(timeLimitSignal(int)), mTimer, SLOT(setTimeSlot(int)));
    connect(mList, SIGNAL(mentSettingSignal(QString)), mTimer, SLOT(setMentSlot(QString)));
}
