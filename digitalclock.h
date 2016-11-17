#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H
#include <QLabel>
#include <QTimer>
#include <QLCDNumber>

class DigitalClock: public QLabel
{
    Q_OBJECT

public:
    DigitalClock(QWidget *parent);

private slots:
    //void showTime();
};

#endif // DIGITALCLOCK_H
