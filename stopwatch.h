#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QDateTime>
#include <QTimerEvent>
#include <QProgressBar>

#include <iostream>
#include "sapi.h"

class StopWatch : public QWidget
{
    Q_OBJECT
public:
    explicit StopWatch(QWidget * parent = 0, qint64 timeLimit = 60000, QString ment = "시작");
    void setmTimeLimit(qint64 time);

public slots:
    void start(void);
    void pause(void);
    void stop(void);
    void setTimeSlot(int);
    void setMentSlot(QString ment);

protected:
    void timerEvent(QTimerEvent *);
    QString getTimeStr(qint64 time);
    qint64 getmTimeLimit();

    void speak(std::string str);
    void speak(std::wstring str);
    void speak(QString str);

private:
    bool        mRunning;
    QDateTime   mStartTime;
    qint64      mSessionTime;
    QLabel *    mLabel;

    qint64      mTimeLimit;

    QPushButton * mStart;
    QPushButton * mPause;
    QPushButton * mStop;
    QProgressBar* mProgressBar;

    QString mAnnouncement;

    void resizeEvent(QResizeEvent*);
};

#endif // STOPWATCH_H
