#ifndef FIXEDQTHREAD_H
#define FIXEDQTHREAD_H

//QT
#include <QtCore/QTime>
#include <QtCore/QThread>
#include <QImage>

class FixedQThread: public QThread
{
Q_OBJECT
public:
    FixedQThread()
    {
       connect(this, SIGNAL(finished()), SLOT(waitForReallyFinished()));
    }
private:
    void waitForReallyFinished()
    {
        wait();
        emit reallyFinished();
    }

signals:
    void reallyFinished();
};
#endif // FIXEDQTHREAD_H
