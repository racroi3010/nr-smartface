#ifndef BASEDIALOG_H
#define BASEDIALOG_H
// SMART FACE
#include "Constants.h"

// QT
#include <QImage>
#include <QDialog>
#include <QString>
#include <QRect>
#include <QTime>
#include <QCoreApplication>
#include <QPalette>
#include <QDir>
class BaseDialog:public QDialog
{
Q_OBJECT
public:
    explicit BaseDialog(QWidget *parent = 0)
    {
        this->setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
        this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    }

protected slots:
    virtual void updateFrame(QImage& image) = 0;
    virtual void updateUser(QString user) = 0;
    virtual void updateFace(QRect rect) = 0;

    void delay(int miliSeconds)
    {
        QTime dieTime = QTime::currentTime().addMSecs( miliSeconds );
        while( QTime::currentTime() < dieTime )
        {
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
    }

private:

};

#define BaseDialog_iid "BaseDialog"
Q_DECLARE_INTERFACE(BaseDialog, BaseDialog_iid)

#endif // BASEDIALOG_H
