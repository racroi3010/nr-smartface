#ifndef PREFERENCEHANDLER_H
#define PREFERENCEHANDLER_H
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QDir>
#include <iostream>

#include "Constants.h"
class PreferenceHandler
{
public:
    PreferenceHandler();
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
#endif
    bool saveXMLDom();
    bool readXMLDom();
private:
    static PreferenceHandler * m_preHandler;
#ifdef USE_NEURO
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
