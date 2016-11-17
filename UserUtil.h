#ifndef USERUTIL_H
#define USERUTIL_H
#include "user.h"
#include "Constants.h"

#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QDir>
#include <QDateTime>

#include "opencv2/highgui/highgui.hpp"
#include <vector>
#include <iostream>
class UserUtil: public QObject
{
Q_OBJECT
public:
    UserUtil();
    ~UserUtil();

    //static bool saveUser(User user);
    bool saveUserDom(QString userNumber, QString userName, cv::Mat userImage, cv::Rect face);
    bool saveUserDom(QString userNumber, QString userName, cv::Mat userImage);
    bool saveUserDom(QString userNumber, QString userName);
    bool saveHistDom(QString userNumber);

    bool removeUser(QString userNumber);
    bool removeUsers(std::vector<User> users);

    std::vector<User> readXMLDom();
    std::vector<User> readXMLHistDom();
    bool checkExist(QString userNumber);
    int getLastId();

    static UserUtil * getInstance();
private:
    QString filePath;
    QString filePath_image;
    QString filePath_hist;
    QString tag_startRootElement;
    QString tag_startElement;
    QString tag_userNumber;
    QString tag_userName;
    QString tag_userImage;
    QString tag_dateTime;
    static UserUtil * m_userUtil;

};

#endif // USERUTIL_H
