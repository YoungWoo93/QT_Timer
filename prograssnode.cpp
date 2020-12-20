#include "prograssnode.h"

#include <random>

prograssNode::prograssNode(int no, QWidget * parent)
{
    mTime = 180;
    nodeNo = no;
    mName = "이름";
    mAnnouncement = "멘트를 넣어주세요";
    mMemo = "메모";

    mIsSelect = false;

    mNameLabel = new QLabel(mName);
    mTimeLabel = new QLabel(timeParse(mTime));

    this->setFixedWidth(105);
    this->setFixedHeight(105);

    mBox = new QRect(0,0,100, 100);
    mBox->moveCenter(QPoint(width()/2,height()/2));

    QVBoxLayout * vBoxLayout = new QVBoxLayout(this);

    vBoxLayout->addWidget(mNameLabel);
    vBoxLayout->addWidget(mTimeLabel);

 }


void prograssNode::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPen pen(Qt::black, 2);
    QPainter p(this);
    p.setPen(pen);

    if(mIsSelect)
    {
        p.setBrush(QColor(211,118,120));
        p.drawRect(*mBox);
    }
    else
    {
        p.setBrush(QColor(192,250,158));
        p.drawRect(*mBox);
    }
}


QString prograssNode::timeParse(int time)
{
    unsigned int h = time / 3600;
    unsigned int m = (time / 60) - (h * 60);
    unsigned int s = time - (m * 60) - (h * 3600);

    QString ret = QString("%1:%2:%3")
            .arg(h,  2, 10, QChar('0'))
            .arg(m,  2, 10, QChar('0'))
            .arg(s,  2, 10, QChar('0'));

    return ret;
}

void prograssNode::click()
{
    mIsSelect = !mIsSelect;
    update();
}





void prograssNode::setName(QString name)
{
    mName = name;
    mNameLabel->setText(name);
    update();
}
QString prograssNode::getName()
{
    return mName;
}

void prograssNode::setTime(int time)
{
    mTime = time;
    mTimeLabel->setText(timeParse(time));
    update();
}
int prograssNode::getTime()
{
    return mTime;
}

void prograssNode::setAnnouncement(QString announce)
{
    mAnnouncement = announce;
}
QString prograssNode::getAnnouncement()
{
    return mAnnouncement;
}

void prograssNode::setMemo(QString memo)
{
    mMemo = memo;
}
QString prograssNode::getMemo()
{
    return mMemo;
}



int prograssNode::getNodeNumber()
{
    return nodeNo;
}
