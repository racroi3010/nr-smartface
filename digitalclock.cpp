#include "digitalclock.h"

DigitalClock::DigitalClock(QWidget *parent)
//    :QLCDNumber(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
}
