#include "stopwatch.h"

StopWatch :: StopWatch(QWidget * parent, qint64 timeLimit, QString ment)
    : QWidget(parent)
    , mRunning(false)
    , mStartTime()
    , mProgressBar(new QProgressBar())
{
    mTimeLimit = timeLimit;
    mAnnouncement = ment;
    mLabel = new QLabel("00:00:00");
    check30 = false;
    checkR60 = false;
    checkR30 = false;



    mStart = new QPushButton();
    QPixmap startImg("./play.svg");
    QIcon startIcon(startImg);
    mStart->setIcon(startIcon);
    mStart->setIconSize(QSize(100,100));
    mStart->setFlat(true);


    mPause = new QPushButton();
    QPixmap pauseImg("./pause.svg");
    QIcon pauseIcon(pauseImg);
    mPause->setIcon(pauseIcon);
    mPause->setIconSize(QSize(100,100));
    mPause->setFlat(true);

    mStop = new QPushButton();
    QPixmap stopImg("./stop.svg");
    QIcon stopIcon(stopImg);
    mStop->setIcon(stopIcon);
    mStop->setIconSize(QSize(100,100));
    mStop->setFlat(true);



    QGridLayout * gridLayout = new QGridLayout(this);


    gridLayout->addWidget(mLabel,   0, 0, 1, 3);
    gridLayout->addWidget(mProgressBar,   1, 0, 1, 3);
    gridLayout->addWidget(mStart,   2, 0, 1, 1);
    gridLayout->addWidget(mPause,   2, 1, 1, 1);
    gridLayout->addWidget(mStop,    2, 2, 1, 1);

    connect(mStart, SIGNAL(clicked()), SLOT(start()));
    connect(mPause, SIGNAL(clicked()), SLOT(pause()));
    connect(mStop, SIGNAL(clicked()), SLOT(stop()));

    QFont font("Arial", this->size().height()*2, QFont::Bold);


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

    check30 = false;
    checkR60 = false;
    checkR30 = false;

    if(usedTime <= 1000)
    {
        mLabel->setText(QString("정지"));
    }
    else if(usedTime >= 60000)
    {
        mLabel->setText(QString("[%1 분 %2 초]")
                        .arg(usedTime / 60000)
                        .arg(usedTime % 60000 / 1000));

        if(mTimeAnnouncement)
            speak(QString("[%1 분 %2 초 발언 하였습니다.]")
              .arg(usedTime / 60000)
              .arg(usedTime % 60000 / 1000));

        speak(mEndAnnouncement);
    }
    else
    {
        mLabel->setText(QString("[%1 초]")
                        .arg(usedTime / 1000));

        if(mTimeAnnouncement)
            speak(QString("[%1 초 발언 하였습니다.]")
              .arg(usedTime / 1000));

        speak(mEndAnnouncement);
    }

    mRunning = false;
    mProgressBar->setValue(0);


}

QString StopWatch :: getTimeStr(qint64 time)
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

void StopWatch ::timerEvent(QTimerEvent *)
{
    if(mRunning)
    {
        mSessionTime = mStartTime.msecsTo(QDateTime::currentDateTime());
        mStartTime = QDateTime::currentDateTime();

        QString diff;
        mProgressBar->setValue(mProgressBar->value() + mSessionTime);

        if(mProgressBar->value() / 1000 == 30 && !check30)
        {
            QSound::play("./30초.wav");
            check30 = true;
        }
        if(mProgressBar->value() / 1000 == mTimeLimit - 60 && !checkR60)
        {
            QSound::play("./60초전.wav");
            checkR60 = true;
        }
        if(mProgressBar->value() / 1000 == mTimeLimit - 30 && !checkR30)
        {
            QSound::play("./30초전.wav");
            checkR30 = true;
        }




        if(mProgressBar->value() / 1000 >= mTimeLimit)
        {
            check30 = false;
            checkR60 = false;
            checkR30 = false;

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

    mLabel->setText(getTimeStr(mProgressBar->value() / 1000));
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

void StopWatch::setMentSlot(QString ment, QString endMent, bool timeMent)
{
    mAnnouncement = ment;
    mEndAnnouncement = endMent;
    mTimeAnnouncement = timeMent;
}

void StopWatch::resizeEvent(QResizeEvent*)
{
    QFont font("Arial", this->size().height()/5, QFont::Bold);
    mLabel->setFont(font);
}
