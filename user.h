#ifndef USER_H
#define USER_H
#include <QString>
#include <QImage>
#include "CameraThread.h"
struct User
{
    QString userNumber;
    QString userName;
    QString userImagePath;
    QString dateTime;
    bool isSelected;

};


#endif // USER_H
