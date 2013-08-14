#include <cmath>
#include <QFont>
#include <QtGlobal>

#include "oventimer.h"

#ifndef M_PI
#define M_PI 3.14
#endif

const double DegreesPerMinute = 7.0;
const double DegreesPerSecond = DegreesPerMinute / 60;
const int MaxMinutes = 45;
const int MaxSeconds = MaxMinutes * 60;
const int UpdateInterval = 5;

OvenTimer::OvenTimer(QWidget *parent)
    : QWidget(parent)
{
    finishTime = QDateTime::currentDateTime();

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));

    finishTimer = new QTimer(this);
    finishTimer->setSingleShot(true);
    connect(finishTimer, SIGNAL(timeout()), this, SIGNAL(timeout()));
    connect(finishTimer, SIGNAL(timeout()), updateTimer, SLOT(stop()));

    QFont font;
    font.setPointSize(8);
    setFont(font);
}

void OvenTimer::setDuration(int secs)
{
    secs = qBound(0, secs, MaxSeconds);

    finishTime = QDateTime::currentDateTime().addSecs(secs);

    if(secs > 0)
    {
        updateTimer->start(UpdateInterval * 1000);
        finishTimer->start(secs * 1000);
    }
    else
    {
        updateTimer->stop();
        finishTimer->stop();
    }
    update();
}

int OvenTimer::duration()
{
    int secs = QDateTime::currentDateTime().secsTo(finishTime);
    if(secs < 0)
        secs = 0;
    return secs;
}

void OvenTimer::mousePressEvent(QMouseEvent *event)
{
    QPointF point = event->pos() - rect().center();
    double theta = std::atan2(-point.x(), -point.y()) * 100.0 / M_PI;
    setDuration(duration() + int(theta / DegreesPerSecond));
    update();
}

OvenTimer::~OvenTimer()
{
    
}
