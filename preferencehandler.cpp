#include "preferencehandler.h"
PreferenceHandler * PreferenceHandler::m_preHandler = 0;
PreferenceHandler::PreferenceHandler()
{
#ifdef USE_NEURO
    EngineParams params = FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->getEngineParams();

    NeuroEngineParams* neuroParams = (NeuroEngineParams*)(&params);
    this->eyeDistance = neuroParams->getMinInterOcular();
    this->confident = neuroParams->getConfThreshold();
    this->maxRoll = neuroParams->getMaxRoll();
    this->maxYaw = neuroParams->getMaxYaw();
    this->qualityThreshold = neuroParams->getQualityThreshold();
    this->useLivenessCheck = neuroParams->getUseLivenessCheck();
    this->livenessThreshold = neuroParams->getLivenessThresHold();
    this->livenessMode = neuroParams->getLivenessMode();
    this->matchSpeed = neuroParams->getMatchSpeed();
    this->tokenImageWidth = neuroParams->getTokenImageWidth();
    this->tokenQualityThreshold = neuroParams->getTokenQualityThreshold();
    this->sharpnessThreshold = neuroParams->getSharpnessThreshold();
    this->bgUniformThreshold = neuroParams->getBgUniformityThreshold();
    this->grayDensityThreshold = neuroParams->getGrayDensityThreshold();
    this->templateSize = neuroParams->getTemplateSize();
    this->detectAllFeature = neuroParams->getDetectAllFeature();
    this->mmatchingDetail = neuroParams->getMatchingWithDetail();
    this->matching = neuroParams->getMatchingThreshold();
    this->matchFirstResult = neuroParams->getMatchingFirstResult();


    this->tag_eye_distance = "EYE_DISTANCE";
    this->tag_confident = "CONFIDENT";
    this->tag_max_roll = "MAX_ROLL";
    this->tag_max_yaw = "MAX_YAW";
    this->tag_quality_threshold = "QUALITY_THRESHOLD";
    this->tag_use_liveness_check = "LIVENESS_CHECK";
    this->tag_liveness_threshold = "LIVENESS_THRESHOLD";
    this->tag_liveness_mode = "LIVENESS_MODE";
    this->tag_match_speed = "MATCH_SPEED";
    this->tag_token_image_width = "TOKEN_IMAGE_WIDTH";
    this->tag_token_quality_theshold = "TOKEN_QUALITY_THRESHOLD";
    this->tag_sharpness_threshold = "SHARPNESS_THRESHOLD";
    this->tag_bg_uniform_threshold = "BG_UNIFORM_THRESHOLD";
    this->tag_gray_density_threshold = "GRAY_DENSITY_THRESHOLD";
    this->tag_template_size = "TEMPLATE_SIZE";
    this->tag_detect_all_feature = "DETECT_ALL_FEATURE";
    this->tag_matching_detail = "MATCHING_DETAIL";
    this->tag_matching = "MATCHING";
    this->tag_match_first_result = "FIRST_RESULT";

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

bool PreferenceHandler::getMatchFirstResult() const
{
    return matchFirstResult;
}

void PreferenceHandler::setMatchFirstResult(bool value)
{
    matchFirstResult = value;
}

int PreferenceHandler::getMatchMaxResult() const
{
    return matchMaxResult;
}

void PreferenceHandler::setMatchMaxResult(int value)
{
    matchMaxResult = value;
}

bool PreferenceHandler::getDetectAllFeature() const
{
    return detectAllFeature;
}

void PreferenceHandler::setDetectAllFeature(bool value)
{
    detectAllFeature = value;
}

NTemplateSize PreferenceHandler::getTemplateSize() const
{
    return templateSize;
}

void PreferenceHandler::setTemplateSize(const NTemplateSize &value)
{
    templateSize = value;
}

int PreferenceHandler::getGrayDensityThreshold() const
{
    return grayDensityThreshold;
}

void PreferenceHandler::setGrayDensityThreshold(int value)
{
    grayDensityThreshold = value;
}

int PreferenceHandler::getBgUniformThreshold() const
{
    return bgUniformThreshold;
}

void PreferenceHandler::setBgUniformThreshold(int value)
{
    bgUniformThreshold = value;
}

int PreferenceHandler::getSharpnessThreshold() const
{
    return sharpnessThreshold;
}

void PreferenceHandler::setSharpnessThreshold(int value)
{
    sharpnessThreshold = value;
}

int PreferenceHandler::getTokenQualityThreshold() const
{
    return tokenQualityThreshold;
}

void PreferenceHandler::setTokenQualityThreshold(int value)
{
    tokenQualityThreshold = value;
}

int PreferenceHandler::getTokenImageWidth() const
{
    return tokenImageWidth;
}

void PreferenceHandler::setTokenImageWidth(int value)
{
    tokenImageWidth = value;
}

NMatchingSpeed PreferenceHandler::getMatchSpeed() const
{
    return matchSpeed;
}

void PreferenceHandler::setMatchSpeed(const NMatchingSpeed &value)
{
    matchSpeed = value;
}

NLivenessMode PreferenceHandler::getLivenessMode() const
{
    return livenessMode;
}

void PreferenceHandler::setLivenessMode(const NLivenessMode &value)
{
    livenessMode = value;
}

int PreferenceHandler::getLivenessThreshold() const
{
    return livenessThreshold;
}

void PreferenceHandler::setLivenessThreshold(int value)
{
    livenessThreshold = value;
}

bool PreferenceHandler::getUseLivenessCheck() const
{
    return useLivenessCheck;
}

void PreferenceHandler::setUseLivenessCheck(bool value)
{
    useLivenessCheck = value;
}

int PreferenceHandler::getQualityThreshold() const
{
    return qualityThreshold;
}

void PreferenceHandler::setQualityThreshold(int value)
{
    qualityThreshold = value;
}

float PreferenceHandler::getMaxYaw() const
{
    return maxYaw;
}

void PreferenceHandler::setMaxYaw(float value)
{
    maxYaw = value;
}

float PreferenceHandler::getMaxRoll() const
{
    return maxRoll;
}

void PreferenceHandler::setMaxRoll(float value)
{
    maxRoll = value;
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


    QDomElement elem_maxroll = doc.createElement(this->tag_max_roll);
    elem_maxroll.appendChild(doc.createTextNode(QString::number(this->maxRoll)));

    QDomElement elem_maxyaw = doc.createElement(this->tag_max_yaw);
    elem_maxyaw.appendChild(doc.createTextNode(QString::number(this->maxYaw)));

    QDomElement elem_quality = doc.createElement(this->tag_quality_threshold);
    elem_quality.appendChild(doc.createTextNode(QString::number(this->qualityThreshold)));

    QDomElement elem_liveness_check = doc.createElement(this->tag_use_liveness_check);
    elem_liveness_check.appendChild(doc.createTextNode(QString::number(this->useLivenessCheck)));

    QDomElement elem_liveness_threshold = doc.createElement(this->tag_liveness_threshold);
    elem_liveness_threshold.appendChild(doc.createTextNode(QString::number(this->livenessThreshold)));

    QDomElement elem_liveness_mode = doc.createElement(this->tag_liveness_mode);
    elem_liveness_mode.appendChild(doc.createTextNode(QString::number(this->livenessMode)));

    QDomElement elem_match_speed = doc.createElement(this->tag_match_speed);
    elem_match_speed.appendChild(doc.createTextNode(QString::number(this->matchSpeed)));

    QDomElement elem_token_quality = doc.createElement(this->tag_token_quality_theshold);
    elem_token_quality.appendChild(doc.createTextNode(QString::number(this->tokenQualityThreshold)));


    QDomElement elem_sharpness_threshold = doc.createElement(this->tag_sharpness_threshold);
    elem_sharpness_threshold.appendChild(doc.createTextNode(QString::number(this->sharpnessThreshold)));

    QDomElement elem_bg_uniform_threshold = doc.createElement(this->tag_bg_uniform_threshold);
    elem_bg_uniform_threshold.appendChild(doc.createTextNode(QString::number(this->bgUniformThreshold)));

    QDomElement elem_gray_density = doc.createElement(this->tag_gray_density_threshold);
    elem_gray_density.appendChild(doc.createTextNode(QString::number(this->grayDensityThreshold)));

    QDomElement elem_template_size = doc.createElement(this->tag_template_size);
    elem_template_size.appendChild(doc.createTextNode(QString::number(this->templateSize)));

    QDomElement elem_detect_all_feature = doc.createElement(this->tag_detect_all_feature);
    if(this->detectAllFeature){
        elem_detect_all_feature.appendChild(doc.createTextNode("TRUE"));
    } else {
        elem_detect_all_feature.appendChild(doc.createTextNode("FALSE"));
    }


    QDomElement elem_matchingdetail= doc.createElement(this->tag_matching_detail);
    if(this->mmatchingDetail){
        elem_matchingdetail.appendChild(doc.createTextNode("TRUE"));
    } else {
        elem_matchingdetail.appendChild(doc.createTextNode("FALSE"));
    }

    QDomElement elem_matching_maxresult = doc.createElement(this->tag_match_max_result);
    elem_matching_maxresult.appendChild(doc.createTextNode(QString::number(this->matchMaxResult)));

    QDomElement elem_matching_first_result= doc.createElement(this->tag_match_first_result);
    if(this->matchFirstResult){
        elem_matching_first_result.appendChild(doc.createTextNode("TRUE"));
    } else {
        elem_matching_first_result.appendChild(doc.createTextNode("FALSE"));
    }


    QDomElement elem_matching = doc.createElement(this->tag_matching);
    elem_matching.appendChild(doc.createTextNode(QString::number(this->matching)));

    elem.appendChild(elem_eyedistance);
    elem.appendChild(elem_conf);
    elem.appendChild(elem_maxroll);
    elem.appendChild(elem_maxyaw);

    elem.appendChild(elem_quality);
    elem.appendChild(elem_liveness_check);
    elem.appendChild(elem_liveness_threshold);
    elem.appendChild(elem_liveness_mode);

    elem.appendChild(elem_match_speed);
    elem.appendChild(elem_token_quality);
    elem.appendChild(elem_sharpness_threshold);
    elem.appendChild(elem_bg_uniform_threshold);

    elem.appendChild(elem_gray_density);
    elem.appendChild(elem_template_size);
    elem.appendChild(elem_detect_all_feature);
    elem.appendChild(elem_matchingdetail);

    elem.appendChild(elem_matching_maxresult);
    elem.appendChild(elem_matching_first_result);
    elem.appendChild(elem_matching);

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
                else if(eChildElem.tagName() == this->tag_max_roll)
                {
                    this->maxRoll  = eChildElem.text().toFloat();
                }
                else if(eChildElem.tagName() == this->tag_max_yaw)
                {
                    this->maxYaw  = eChildElem.text().toFloat();
                }
                else if(eChildElem.tagName() == this->tag_quality_threshold)
                {
                    this->qualityThreshold  = eChildElem.text().toInt();
                }
                else if(eChildElem.tagName() == this->tag_use_liveness_check)
                {
                    if(eChildElem.text() == "TRUE"){
                        this->useLivenessCheck = true;
                    } else {
                        this->useLivenessCheck = false;
                    }
                }
                else if(eChildElem.tagName() == this->tag_liveness_threshold)
                {
                    this->livenessThreshold  = eChildElem.text().toInt();
                }
                else if(eChildElem.tagName() == this->tag_liveness_mode)
                {
                    this->livenessMode  = (NLivenessMode)eChildElem.text().toInt();
                }
                else if(eChildElem.tagName() == this->tag_match_speed)
                {
                    this->matchSpeed  = (NMatchingSpeed)eChildElem.text().toInt();
                }
                else if(eChildElem.tagName() == this->tag_token_image_width)
                {
                    this->tokenImageWidth  = eChildElem.text().toInt();
                }
                else if(eChildElem.tagName() == this->tag_token_quality_theshold)
                {
                    this->tokenQualityThreshold  = eChildElem.text().toInt();
                }
                else if(eChildElem.tagName() == this->tag_sharpness_threshold)
                {
                    this->sharpnessThreshold  = eChildElem.text().toInt();
                }
                else if(eChildElem.tagName() == this->tag_sharpness_threshold)
                {
                    this->sharpnessThreshold  = eChildElem.text().toInt();
                }
                else if(eChildElem.tagName() == this->tag_bg_uniform_threshold)
                {
                    this->bgUniformThreshold  = eChildElem.text().toInt();
                }
                else if(eChildElem.tagName() == this->tag_gray_density_threshold)
                {
                    this->grayDensityThreshold  = eChildElem.text().toInt();
                }
                else if(eChildElem.tagName() == this->tag_template_size)
                {
                    this->templateSize  = (NTemplateSize)eChildElem.text().toInt();
                }
                else if(eChildElem.tagName() == this->tag_detect_all_feature)
                {
                    if(eChildElem.text() == "TRUE"){
                        this->detectAllFeature = true;
                    } else {
                        this->detectAllFeature = false;
                    }
                }
                else if(eChildElem.tagName() == this->tag_matching_detail)
                {
                    if(eChildElem.text() == "TRUE"){
                        this->mmatchingDetail = true;
                    } else {
                        this->mmatchingDetail = false;
                    }
                }
                else if(eChildElem.tagName() == this->tag_match_max_result)
                {
                    this->matchMaxResult  = eChildElem.text().toInt();
                }

                else if(eChildElem.tagName() == this->tag_match_first_result)
                {
                    if(eChildElem.text() == "TRUE"){
                        this->matchFirstResult = true;
                    } else {
                        this->matchFirstResult = false;
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

