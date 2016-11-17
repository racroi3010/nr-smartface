#include "UserUtil.h"
UserUtil * UserUtil::m_userUtil = 0;
UserUtil::UserUtil()
{
    filePath = QDir::currentPath() + "/feature/";
    filePath_image= QDir::currentPath() + "/temp/";
    filePath_hist= QDir::currentPath() + "/history/";
    tag_startElement = "USER";
    tag_startRootElement = "USERS";
    tag_userNumber = "user_number";
    tag_userName = "user_name";
    tag_userImage = "user_image";
    tag_dateTime = "user_time";
}
UserUtil::~UserUtil()
{

}
UserUtil * UserUtil::getInstance()
{
    if(m_userUtil == 0)
    {
        m_userUtil = new UserUtil();
    }
    return m_userUtil;
}
bool UserUtil::saveUserDom(QString userNumber, QString userName, cv::Mat userImage, cv::Rect face)
{
    QDomDocument doc("usersxml");
    QString fileXml = this->filePath + "users.xml";
    QFile file(fileXml);
    if(!file.exists())
    {
        if(!file.open(QIODevice::WriteOnly))
        {
            return false;
        }
    }

     QDomElement docElem;
    if(!doc.setContent(&file))
    {
        docElem = doc.createElement(this->tag_startRootElement);
        doc.appendChild(docElem);
    }
    else
    {
        docElem = doc.documentElement();
    }
    file.close();
    QString userImagePath = "";
    if(userImage.data != 0)
    {
        userImagePath = this->filePath_image + userNumber + ".jpg";
        cv::imwrite(userImagePath.toStdString(), userImage);

//        userFacePath = this->filePath_image + userNumber + ".jpg";
//        cv::imwrite(userFacePath.toStdString(), userImage(face));
    }

    QDomElement elem = doc.createElement(this->tag_startElement);
    docElem.appendChild(elem);

    QDomElement elem_userNumber = doc.createElement(this->tag_userNumber);
    elem_userNumber.appendChild(doc.createTextNode(userNumber));

    QDomElement elem_userName = doc.createElement(this->tag_userName);
    elem_userName.appendChild(doc.createTextNode(userName));

    QDomElement elem_userImage = doc.createElement(this->tag_userImage);
    elem_userImage.appendChild(doc.createTextNode(userImagePath));

    QDomElement elem_dateTime = doc.createElement(this->tag_dateTime);
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeStr = dateTime.toString("yyyy.MM.dd-hh:mm:ss");
    elem_dateTime.appendChild(doc.createTextNode(dateTimeStr));


    elem.appendChild(elem_userNumber);
    elem.appendChild(elem_userName);
    elem.appendChild(elem_userImage);
    elem.appendChild(elem_dateTime);


    QFile newFile(fileXml);
    if(!newFile.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QTextStream tx(&newFile);

    tx << doc.toString();
    //std::cout << doc.toString().toStdString() << std::endl;
    newFile.close();

    return true;
}
bool UserUtil::saveUserDom(QString userNumber, QString userName, cv::Mat userImage)
{
    QDomDocument doc("usersxml");
    QString fileXml = this->filePath + "users.xml";
    QFile file(fileXml);
    if(!file.exists())
    {
        if(!file.open(QIODevice::WriteOnly))
        {
            return false;
        }
    }

     QDomElement docElem;
    if(!doc.setContent(&file))
    {
        docElem = doc.createElement(this->tag_startRootElement);
        doc.appendChild(docElem);
    }
    else
    {
        docElem = doc.documentElement();
    }
    file.close();
    QString userImagePath = "";
    if(userImage.data != 0)
    {
        userImagePath = this->filePath_image + userNumber + ".bmp";
        cv::cvtColor(userImage, userImage, CV_BGR2RGB);
        cv::imwrite(userImagePath.toStdString(), userImage);

//        // create icon
//        cv::Mat temp;
//        cv::resize(userImage, temp, cv::Size(IMAGE_LABEL_WIDTH_4, IMAGE_LABEL_HEIGHT_4));
//        QString userImagePathIco = this->filePath_image + userNumber + "_ico.bmp";
//        cv::imwrite(userImagePathIco.toStdString(), temp);
    }

    QDomElement elem = doc.createElement(this->tag_startElement);
    docElem.appendChild(elem);

    QDomElement elem_userNumber = doc.createElement(this->tag_userNumber);
    elem_userNumber.appendChild(doc.createTextNode(userNumber));

    QDomElement elem_userName = doc.createElement(this->tag_userName);
    elem_userName.appendChild(doc.createTextNode(userName));

    QDomElement elem_userImage = doc.createElement(this->tag_userImage);
    elem_userImage.appendChild(doc.createTextNode(userImagePath));

    QDomElement elem_dateTime = doc.createElement(this->tag_dateTime);
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeStr = dateTime.toString("yyyy.MM.dd-hh:mm:ss");
    elem_dateTime.appendChild(doc.createTextNode(dateTimeStr));


    elem.appendChild(elem_userNumber);
    elem.appendChild(elem_userName);
    elem.appendChild(elem_userImage);
    elem.appendChild(elem_dateTime);

    QFile newFile(fileXml);
    if(!newFile.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QTextStream tx(&newFile);

    tx << doc.toString();
    //std::cout << doc.toString().toStdString() << std::endl;
    newFile.close();

    return true;
}
bool UserUtil::saveUserDom(QString userNumber, QString userName)
{
    QDomDocument doc("usersxml");
    QString fileXml = this->filePath + "users.xml";
    QFile file(fileXml);
    if(!file.exists())
    {
        if(!file.open(QIODevice::WriteOnly))
        {
            return false;
        }
    }

     QDomElement docElem;
    if(!doc.setContent(&file))
    {
        docElem = doc.createElement(this->tag_startRootElement);
        doc.appendChild(docElem);
    }
    else
    {
        docElem = doc.documentElement();
    }
    file.close();
    QString userImagePath = this->filePath_image + userNumber + ".bmp";

    QDomElement elem = doc.createElement(this->tag_startElement);
    docElem.appendChild(elem);

    QDomElement elem_userNumber = doc.createElement(this->tag_userNumber);
    elem_userNumber.appendChild(doc.createTextNode(userNumber));

    QDomElement elem_userName = doc.createElement(this->tag_userName);
    elem_userName.appendChild(doc.createTextNode(userName));

    QDomElement elem_userImage = doc.createElement(this->tag_userImage);
    elem_userImage.appendChild(doc.createTextNode(userImagePath));

    QDomElement elem_dateTime = doc.createElement(this->tag_dateTime);
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeStr = dateTime.toString("yyyy.MM.dd-hh:mm:ss");
    elem_dateTime.appendChild(doc.createTextNode(dateTimeStr));


    elem.appendChild(elem_userNumber);
    elem.appendChild(elem_userName);
    elem.appendChild(elem_userImage);
    elem.appendChild(elem_dateTime);

    QFile newFile(fileXml);
    if(!newFile.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QTextStream tx(&newFile);

    tx << doc.toString();
    //std::cout << doc.toString().toStdString() << std::endl;
    newFile.close();

    return true;
}
bool UserUtil::saveHistDom(QString userNumber)
{
    QDomDocument doc("usersxml");
    QString fileXml = this->filePath_hist + "users.xml";
    QFile file(fileXml);
    if(!file.exists())
    {
        if(!file.open(QIODevice::WriteOnly))
        {
            return false;
        }
    }

     QDomElement docElem;
    if(!doc.setContent(&file))
    {
        docElem = doc.createElement(this->tag_startRootElement);
        doc.appendChild(docElem);
    }
    else
    {
        docElem = doc.documentElement();
    }
    file.close();
    QString userImagePath = this->filePath_hist + userNumber + ".bmp";

    QDomElement elem = doc.createElement(this->tag_startElement);
    docElem.appendChild(elem);

    QDomElement elem_userNumber = doc.createElement(this->tag_userNumber);
    elem_userNumber.appendChild(doc.createTextNode(userNumber));

    QDomElement elem_userImage = doc.createElement(this->tag_userImage);
    elem_userImage.appendChild(doc.createTextNode(userImagePath));

    QDomElement elem_dateTime = doc.createElement(this->tag_dateTime);
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeStr = dateTime.toString("yyyy.MM.dd-hh:mm:ss");
    elem_dateTime.appendChild(doc.createTextNode(dateTimeStr));


    elem.appendChild(elem_userNumber);
    elem.appendChild(elem_userImage);
    elem.appendChild(elem_dateTime);

    QFile newFile(fileXml);
    if(!newFile.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QTextStream tx(&newFile);

    tx << doc.toString();
    //std::cout << doc.toString().toStdString() << std::endl;
    newFile.close();

    return true;
}

std::vector<User> UserUtil::readXMLDom()
{
    std::vector<User> users;
    QDomDocument doc("usersxml");
    QString fileXml = this->filePath + "users.xml";
    QFile file(fileXml);
    if(!file.exists())
    {
        return users;
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        return users;
    }
    if(!doc.setContent(&file))
    {
        file.close();
        return users;
    }

    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    QString tag = "";
    while(!n.isNull())
    {
        QDomElement e = n.toElement();
        if(!e.isNull())
        {
            //tag = e.tagName();
            //std::cout << tag.toStdString() << std::endl;
            User user;
            QDomNodeList eChilds = e.childNodes();
            for(int i = 0; i < eChilds.size(); i ++)
            {
                QDomElement eChildElem = eChilds.at(i).toElement();
                if(eChildElem.tagName() == this->tag_userNumber)
                {
                    user.userNumber = eChildElem.text();
                }
                else if(eChildElem.tagName() == this->tag_userName)
                {
                    user.userName = eChildElem.text();
                }
                else if(eChildElem.tagName() == this->tag_userImage)
                {
                    user.userImagePath = eChildElem.text();
                }
                else if(eChildElem.tagName() == this->tag_dateTime)
                {
                    user.dateTime = eChildElem.text();
                }
                std::cout << eChildElem.tagName().toStdString() << std::endl;
            }
            users.push_back(user);
        }
        n = n.nextSibling();
    }
    return users;
}
std::vector<User> UserUtil::readXMLHistDom()
{
    std::vector<User> users;
    QDomDocument doc("usersxml");
    QString fileXml = this->filePath_hist + "users.xml";
    QFile file(fileXml);
    if(!file.exists())
    {
        return users;
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        return users;
    }
    if(!doc.setContent(&file))
    {
        file.close();
        return users;
    }

    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    QString tag = "";
    while(!n.isNull())
    {
        QDomElement e = n.toElement();
        if(!e.isNull())
        {
            //tag = e.tagName();
            //std::cout << tag.toStdString() << std::endl;
            User user;
            QDomNodeList eChilds = e.childNodes();
            for(int i = 0; i < eChilds.size(); i ++)
            {
                QDomElement eChildElem = eChilds.at(i).toElement();
                if(eChildElem.tagName() == this->tag_userNumber)
                {
                    user.userNumber = eChildElem.text();
                }
                else if(eChildElem.tagName() == this->tag_userImage)
                {
                    user.userImagePath = eChildElem.text();
                }
                else if(eChildElem.tagName() == this->tag_dateTime)
                {
                    user.dateTime = eChildElem.text();
                }
                std::cout << eChildElem.tagName().toStdString() << std::endl;
            }
            users.insert(users.begin(), user);
        }
        n = n.nextSibling();
    }
    return users;
}

bool UserUtil::checkExist(QString num)
{
    bool flag = false;
    QDomDocument doc("usersxml");
    QString fileXml = this->filePath + "users.xml";
    QFile file(fileXml);
    if(!file.exists())
    {
        return flag;
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        return flag;
    }
    if(!doc.setContent(&file))
    {
        file.close();
        return flag;
    }

    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();

    QString tag = "";
    while(!n.isNull())
    {
        QDomElement e = n.toElement();
        if(!e.isNull())
        {
            //tag = e.tagName();
            //std::cout << tag.toStdString() << std::endl;
            QDomNodeList eChilds = e.childNodes();
            for(int i = 0; i < eChilds.size(); i ++)
            {
                QDomElement eChildElem = eChilds.at(i).toElement();
                if(eChildElem.tagName() == this->tag_userNumber)
                {
                    if(eChildElem.text() == num)
                    {
                        flag = true;
                        break;
                    }
                }
            }
        }
        n = n.nextSibling();
    }
    return flag;
}
bool UserUtil::removeUser(QString userNumber)
{
    bool flag = false;
    QDomDocument doc("usersxml");
    QString fileXml = this->filePath + "users.xml";
    QFile file(fileXml);
    if(!file.exists())
    {
        return flag;
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        return flag;
    }
    if(!doc.setContent(&file))
    {
        file.close();
        return flag;
    }

    // <USERS>
    QDomElement docElem = doc.documentElement();

    // FIRST <USER>
    QDomNode n = docElem.firstChild();
    QString imgPath = "";
    while(!n.isNull())
    {
        // FIRST USER
        QDomElement e = n.toElement();
        if(!e.isNull())
        {
            // LIST NODE ATT
            QDomNodeList eChilds = e.childNodes();
            for(int i = 0; i < eChilds.size(); i ++)
            {
                QDomElement eChildElem = eChilds.at(i).toElement();
                // NODE <USER NUMBER>
                if(eChildElem.tagName() == this->tag_userNumber
                        && eChildElem.text() == userNumber)
                {
                    flag = true;
                    break;

                }


            }
            if(flag)
            {
                e.parentNode().removeChild(e);
                QFile::remove(filePath_image + userNumber + ".bmp");
                QFile::remove(filePath + userNumber + ".fet");
            }
        }
        n = n.nextSibling();
    }

    QFile newFile(fileXml);
    if(!newFile.open(QIODevice::WriteOnly))
    {
        flag = false;
    }
    QTextStream tx(&newFile);

    tx << doc.toString();
    //std::cout << doc.toString().toStdString() << std::endl;
    newFile.close();

    return flag;
}
bool UserUtil::removeUsers(std::vector<User> users)
{
    bool flag = false;
    QDomDocument doc("usersxml");
    QString fileXml = this->filePath + "users.xml";
    QFile file(fileXml);
    if(!file.exists())
    {
        return flag;
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        return flag;
    }
    if(!doc.setContent(&file))
    {
        file.close();
        return flag;
    }

    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();

    QString tag = "";

    // test


    QFile newFile(fileXml);
    if(!newFile.open(QIODevice::WriteOnly))
    {
        flag = false;
    }
    QTextStream tx(&newFile);

    tx << doc.toString();
    //std::cout << doc.toString().toStdString() << std::endl;
    newFile.close();

    return flag;
}
int UserUtil::getLastId()
{
    int lastId = -1;
    QDomDocument doc("usersxml");
    QString fileXml = this->filePath + "users.xml";
    QFile file(fileXml);
    if(!file.exists())
    {
        return lastId;
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        return lastId;
    }
    if(!doc.setContent(&file))
    {
        file.close();
        return lastId;
    }

    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    int curId;
    while(!n.isNull())
    {
        // FIRST USER
        QDomElement e = n.toElement();
        if(!e.isNull())
        {
            // LIST NODE ATT
            QDomNodeList eChilds = e.childNodes();
            for(int i = 0; i < eChilds.size(); i ++)
            {
                QDomElement eChildElem = eChilds.at(i).toElement();
                // NODE <USER NUMBER>
                if(eChildElem.tagName() == this->tag_userNumber)
                {
                    QString temp = eChildElem.text();
                    if((curId = temp.toInt()) > lastId)
                    {
                        lastId = curId;
                    }
                    break;

                }


            }

        }

        n = n.nextSibling();
    }


    QFile newFile(fileXml);
    if(!newFile.open(QIODevice::WriteOnly))
    {
        lastId = -1;
    }
    QTextStream tx(&newFile);

    tx << doc.toString();
    //std::cout << doc.toString().toStdString() << std::endl;
    newFile.close();

    return lastId;
}
