#ifndef PROGRASSNODE_H
#define PROGRASSNODE_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

#include <QPainter>
#include <QColor>
#include <QPen>
#include <QBrush>

#include <QMouseEvent>

class prograssNode : public QWidget
{
    Q_OBJECT
public:
    prograssNode(int no, QWidget * parent = 0);
    QString timeParse(int time);
    void click();

    void setName(QString name);
    QString getName();

    void setTime(int time);
    int getTime();

    void setAnnouncement(QString announce);
    QString getAnnouncement();

    void setMemo(QString memo);
    QString getMemo();

    int getNodeNumber();

private :
    int         nodeNo;
    int         mTime;
    bool        mIsSelect;

    QString     mName;
    QString     mAnnouncement;
    QString     mMemo;

    QLabel *    mNameLabel;
    QLabel *    mTimeLabel;
    QRect *     mBox;


    virtual void paintEvent(QPaintEvent *event);
};

#endif // PROGRASSNODE_H
