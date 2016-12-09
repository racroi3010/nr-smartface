#ifndef PREFERENCEHANDLER_H
#define PREFERENCEHANDLER_H
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QDir>
#include <iostream>

#include "Constants.h"
#include "faceenginebuilder.h"
class PreferenceHandler
{
public:

    static PreferenceHandler * getInstance();
#ifdef USE_NEOFACE
    void setRelValue(float v);
    void setMaxRelValue(float v);
    void setEyeMin(int e);
    void setEyeMax(int e);

    float getRelValue();
    float getMaxRelValue();
    int getEyeMin();
    int getEyeMax();
#endif
#ifdef USE_NEURO
    void setMatching(int v);
    int getMatching();

    int getConfident() const;
    void setConfident(int value);

    int getEyeDistance() const;
    void setEyeDistance(int value);

    bool getMmatchingDetail() const;
    void setMmatchingDetail(bool value);
#endif
    bool saveXMLDom();
    bool readXMLDom();


private:
    static PreferenceHandler * m_preHandler;
    PreferenceHandler();
#ifdef USE_NEURO
    int eyeDistance;
    QString tag_eye_distance;

    int confident;
    QString tag_confident;

    bool mmatchingDetail;
    QString tag_matching_detail;

    int matching;
    QString tag_matching;

#endif
#ifdef USE_NEOFACE
    float relValue;
    float maxRelValue;
    int eyeMin;
    int eyeMax;
    QString tag_relValue;
    QString tag_maxRelValue;
    QString tag_eyeMin;
    QString tag_eyeMax;


#endif
    QString tag_startRootElement;
    QString tag_startElement;



};

#endif // PREFERENCEHANDLER_H
