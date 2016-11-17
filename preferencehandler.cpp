#include "preferencehandler.h"
PreferenceHandler * PreferenceHandler::m_preHandler = 0;
PreferenceHandler::PreferenceHandler()
{
    this->relValue = 0.4;
    this->maxRelValue = 0.7;
    this->eyeMin = 20;
    this->eyeMax = 240;
    tag_relValue = "REL_VALUE";
    tag_maxRelValue = "MAX_REL_VALUE";
    tag_eyeMin = "EYE_MIN";
    tag_eyeMax = "EYE_MAX";
    tag_startRootElement = "SETTINGS";
    tag_startElement = "SET";

}
PreferenceHandler * PreferenceHandler::getInstance()
{
    if(m_preHandler == 0)
    {
        m_preHandler = new PreferenceHandler();
    }
    return m_preHandler;
}
bool PreferenceHandler::saveXMLDom()
{
    QDomDocument doc("settingxml");
    QString fileXml = QDir::currentPath() + "/temp/setting.xml";

    QDomElement docElem = doc.createElement(this->tag_startRootElement);
    doc.appendChild(docElem);

    QDomElement elem = doc.createElement(this->tag_startElement);
    docElem.appendChild(elem);

    QDomElement elem_relvalue = doc.createElement(this->tag_relValue);
    elem_relvalue.appendChild(doc.createTextNode(QString::number(this->relValue)));

    QDomElement elem_maxrelvalue = doc.createElement(this->tag_maxRelValue);
    elem_maxrelvalue.appendChild(doc.createTextNode(QString::number(this->maxRelValue)));

    QDomElement elem_eyemax= doc.createElement(this->tag_eyeMax);
    elem_eyemax.appendChild(doc.createTextNode(QString::number(this->eyeMax)));


    QDomElement elem_eyemin = doc.createElement(this->tag_eyeMin);
    elem_eyemin.appendChild(doc.createTextNode(QString::number(this->eyeMin)));

    elem.appendChild(elem_relvalue);
    elem.appendChild(elem_maxrelvalue);
    elem.appendChild(elem_eyemax);
    elem.appendChild(elem_eyemin);

    QFile newFile(fileXml);
    if(!newFile.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QTextStream tx(&newFile);

    tx << doc.toString();
    std::cout << doc.toString().toStdString() << std::endl;
    newFile.close();

    return true;
}
bool PreferenceHandler::readXMLDom()
{
    QDomDocument doc("settingxml");
    QString fileXml = QDir::currentPath() + "/temp/setting.xml";
    QFile file(fileXml);
    if(!file.exists())
    {
        return false;
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    if(!doc.setContent(&file))
    {
        file.close();
        return false;
    }

    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();

    if(!n.isNull())
    {
        QDomElement e = n.toElement();
        if(!e.isNull())
        {
            QDomNodeList eChilds = e.childNodes();
            for(int i = 0; i < eChilds.size(); i ++)
            {
                QDomElement eChildElem = eChilds.at(i).toElement();
                if(eChildElem.tagName() == this->tag_relValue)
                {
                    this->relValue  = eChildElem.text().toFloat();
                }
                else if(eChildElem.tagName() == this->tag_maxRelValue)
                {
                    this->maxRelValue = eChildElem.text().toFloat();
                }
                else if(eChildElem.tagName() == this->tag_eyeMax)
                {
                    this->eyeMax = eChildElem.text().toInt();
                }
                else if(eChildElem.tagName() == this->tag_eyeMin)
                {
                    this->eyeMin = eChildElem.text().toInt();
                }
            }
        }
    }
    return true;
}
void PreferenceHandler::setRelValue(float v)
{
    this->relValue = v;
}

void PreferenceHandler::setMaxRelValue(float v)
{
    this->maxRelValue = v;
}

void PreferenceHandler::setEyeMin(int e)
{
    this->eyeMin = e;
}

void PreferenceHandler::setEyeMax(int e)
{
    this->eyeMax = e;
}
float PreferenceHandler::getRelValue()
{
    return this->relValue;
}

float PreferenceHandler::getMaxRelValue()
{
    return this->maxRelValue;
}

int PreferenceHandler::getEyeMin()
{
    return this->eyeMin;
}

int PreferenceHandler::getEyeMax()
{
    return this->eyeMax;
}
