#include "stopwatch.h"


StopWatch :: StopWatch(QWidget * parent, qint64 timeLimit, QString ment)
    : QWidget(parent)
    , mRunning(false)
    , mStartTime()
    , mLabel(new QLabel("00:00:00"))
    , mStart(new QPushButton("시작"))
    , mPause(new QPushButton("일시정지"))
    , mStop(new QPushButton("정지"))
    , mProgressBar(new QProgressBar())
{
    mTimeLimit = timeLimit;
    mAnnouncement = ment;

    QGridLayout * gridLayout = new QGridLayout(this);

    gridLayout->addWidget(mLabel,   0, 0, 1, 3);
    gridLayout->addWidget(mProgressBar,   1, 0, 1, 3);
    gridLayout->addWidget(mStart,   2, 0, 1, 1);
    gridLayout->addWidget(mPause,   2, 1, 1, 1);
    gridLayout->addWidget(mStop,    2, 2, 1, 1);

    connect(mStart, SIGNAL(clicked()), SLOT(start()));
    connect(mPause, SIGNAL(clicked()), SLOT(pause()));
    connect(mStop, SIGNAL(clicked()), SLOT(stop()));

    QFont font("Arial", 50, QFont::Bold);


    QPalette palette = mLabel->palette();
    palette.setColor(QPalette::WindowText, Qt::black);
    mLabel->setPalette(palette);
    mLabel->setFont(font);
    mLabel->setText(getTimeStr(timeLimit));
    gridLayout->setAlignment(mLabel, Qt::AlignCenter);

    mStart->setMaximumHeight(100);
//    mStart->setMaximumWidth(200);
    mPause->setMaximumHeight(100);
//    mPause->setMaximumWidth(200);
    mStop->setMaximumHeight(100);
//    mStop->setMaximumWidth(200);

    mStart->setEnabled(true);
    mPause->setEnabled(false);
    mStop->setEnabled(false);
    mProgressBar->setTextVisible(false);
    mProgressBar->setMinimum(0);
    mProgressBar->setMaximum(mTimeLimit * 1000);

    startTimer(0);
}

void StopWatch :: start(void)
{
    speak(mAnnouncement);

    mStartTime = QDateTime::currentDateTime();
    mRunning = true;
    mStart->setEnabled(false);
    mPause->setEnabled(true);
    mStop->setEnabled(true);
}

void StopWatch :: pause(void)
{
    mStart->setEnabled(true);
    mPause->setEnabled(false);
    mStop->setEnabled(true);
    timerEvent(new QTimerEvent(0));
    mRunning = false;

    QString t = "일시정지";
    speak(t);
}

void StopWatch :: stop(void)
{
    int usedTime = mProgressBar->value();

    mStart->setEnabled(true);
    mPause->setEnabled(false);
    mStop->setEnabled(false);
    mLabel->setText(QString("[%1 sec used]")
            .arg(usedTime / 1000));
    mRunning = false;
    mProgressBar->setValue(0);


}

QString StopWatch :: getTimeStr(qint64 time)
{
    time = mTimeLimit - time;

    unsigned int h = time / 3600;
    unsigned int m = (time / 60) - (h * 60);
    unsigned int s = time - (m * 60) - (h * 3600);

    QString ret = QString("%1:%2:%3")
            .arg(h,  2, 10, QChar('0'))
            .arg(m,  2, 10, QChar('0'))
            .arg(s,  2, 10, QChar('0'));

    return ret;
}

void StopWatch ::timerEvent(QTimerEvent *)
{
    if(mRunning)
    {
        mSessionTime = mStartTime.msecsTo(QDateTime::currentDateTime());
        mStartTime = QDateTime::currentDateTime();

        QString diff;
        mProgressBar->setValue(mProgressBar->value() + mSessionTime);

        if(mProgressBar->value() / 1000 >= mTimeLimit)
        {
            diff = QString("시간 종료");
            mRunning = false;
            mLabel->setText(diff);

            QString t = "시간이 종료 되었습니다.";
            speak(t);
        }
        else
        {
            diff = getTimeStr(mProgressBar->value() / 1000);
            mLabel->setText(diff);
        }

    }
}

qint64 StopWatch ::getmTimeLimit()
{
    return mTimeLimit;
}
void StopWatch ::setmTimeLimit(qint64 time)
{
    mTimeLimit = time;

    mLabel->setText(getTimeStr(mTimeLimit));
    mProgressBar->setMinimum(0);
    mProgressBar->setMaximum(mTimeLimit * 1000);
}

void StopWatch ::setTimeSlot(int t)
{
    emit stop();
    setmTimeLimit(t);
}


void StopWatch::speak(QString str)
{
    speak(str.toStdWString());
}
void StopWatch::speak(std::string str)
{
    std::wstring wstr;
    wstr.assign(str.begin(), str.end());
    speak(wstr);
}
void StopWatch::speak(std::wstring str)
{
    if(FAILED(CoInitialize(NULL)))
        return;
    else
    {
        ISpVoice *pVoice = NULL;
        HRESULT hr = CoCreateInstance(CLSID_SpVoice,
                                      NULL,
                                      CLSCTX_ALL,
                                      IID_ISpVoice,
                                      (void **)&pVoice);

        if( SUCCEEDED( hr ) )
        {
            hr = pVoice->Speak(str.c_str(),
                               SPF_IS_XML,
                               NULL );

            pVoice->Release();
            pVoice = NULL;
        }

        CoUninitialize();
    }
}

void StopWatch::setMentSlot(QString ment)
{
    mAnnouncement = ment;
}

