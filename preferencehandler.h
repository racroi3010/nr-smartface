#ifndef PREFERENCEHANDLER_H
#define PREFERENCEHANDLER_H
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QDir>
#include <iostream>
class PreferenceHandler
{
public:
    PreferenceHandler();
    static PreferenceHandler * getInstance();

    void setRelValue(float v);
    void setMaxRelValue(float v);
    void setEyeMin(int e);
    void setEyeMax(int e);

    float getRelValue();
    float getMaxRelValue();
    int getEyeMin();
    int getEyeMax();

    bool saveXMLDom();
    bool readXMLDom();
private:
    static PreferenceHandler * m_preHandler;
    float relValue;
    float maxRelValue;
    int eyeMin;
    int eyeMax;

    QString tag_relValue;
    QString tag_maxRelValue;
    QString tag_eyeMin;
    QString tag_eyeMax;
    QString tag_startRootElement;
    QString tag_startElement;


};

#endif // PREFERENCEHANDLER_H
