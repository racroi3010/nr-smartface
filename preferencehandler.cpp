#include "preferencehandler.h"
PreferenceHandler * PreferenceHandler::m_preHandler = 0;
PreferenceHandler::PreferenceHandler()
{
#ifdef USE_NEURO
    EngineParams params = FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->getEngineParams();

    NeuroEngineParams* neuroParams = (NeuroEngineParams*)(&params);
    this->eyeDistance = neuroParams->getMinInterOcular();
    this->confident = neuroParams->getConfThreshold();

    this->mmatchingDetail = neuroParams->getMatchingWithDetail();
    this->matching = neuroParams->getMatchingThreshold();


    this->tag_eye_distance = "EYE_DISTANCE";
    this->tag_confident = "CONFIDENT";
    this->tag_matching_detail = "MATCHING_DETAIL";
    this->tag_matching = "MATCHING";

#endif
#ifdef USE_NEOFACE
    this->relValue = 0.4;
    this->maxRelValue = 0.7;
    this->eyeMin = 20;
    this->eyeMax = 240;
    tag_relValue = "REL_VALUE";
    tag_maxRelValue = "MAX_REL_VALUE";
    tag_eyeMin = "EYE_MIN";
    tag_eyeMax = "EYE_MAX";
#endif

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
#ifdef USE_NEURO

    QDomElement elem_eyedistance = doc.createElement(this->tag_eye_distance);
    elem_eyedistance.appendChild(doc.createTextNode(QString::number(this->eyeDistance)));

    QDomElement elem_conf = doc.createElement(this->tag_confident);
    elem_conf.appendChild(doc.createTextNode(QString::number(this->confident)));


    QDomElement elem_matchingdetail= doc.createElement(this->tag_matching_detail);
    if(this->mmatchingDetail){
        elem_matchingdetail.appendChild(doc.createTextNode("TRUE"));
    } else {
        elem_matchingdetail.appendChild(doc.createTextNode("FALSE"));
    }


    QDomElement elem_matching = doc.createElement(this->tag_matching);
    elem_matching.appendChild(doc.createTextNode(QString::number(this->matching)));

#endif
#ifdef USE_NEOFACE
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
#endif


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
#ifdef USE_NEURO
                if(eChildElem.tagName() == this->tag_eye_distance)
                {
                    this->eyeDistance  = eChildElem.text().toInt();
                }
                else if(eChildElem.tagName() == this->tag_confident)
                {
                    this->confident  = eChildElem.text().toInt();
                }
                else if(eChildElem.tagName() == this->tag_matching_detail)
                {
                    if(eChildElem.text() == "TRUE"){
                        this->matching = true;
                    } else {
                        this->matching = false;
                    }
                }
                else if(eChildElem.tagName() == this->tag_matching)
                {
                    this->matching  = eChildElem.text().toInt();
                }
#endif
#ifdef USE_NEOFACE
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
#endif

            }
        }
    }
    return true;
}

int PreferenceHandler::getConfident() const
{
    return confident;
}

void PreferenceHandler::setConfident(int value)
{
    confident = value;
}

int PreferenceHandler::getEyeDistance() const
{
    return eyeDistance;
}

void PreferenceHandler::setEyeDistance(int value)
{
    eyeDistance = value;
}

bool PreferenceHandler::getMmatchingDetail() const
{
    return mmatchingDetail;
}

void PreferenceHandler::setMmatchingDetail(bool value)
{
    mmatchingDetail = value;
}
#ifdef USE_NEURO
void PreferenceHandler::setMatching(int v){
    this->matching = v;
}

int PreferenceHandler::getMatching(){
    return this->matching;
}

#endif
#ifdef USE_NEOFACE
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
#endif

