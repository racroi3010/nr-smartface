#ifndef PREFERENCEHANDLER_H
#define PREFERENCEHANDLER_H
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QDir>
#include <iostream>

#include <NCore.h>
#include <NBiometrics.h>

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


    float getMaxRoll() const;
    void setMaxRoll(float value);

    float getMaxYaw() const;
    void setMaxYaw(float value);

    int getQualityThreshold() const;
    void setQualityThreshold(int value);

    bool getUseLivenessCheck() const;
    void setUseLivenessCheck(bool value);

    int getLivenessThreshold() const;
    void setLivenessThreshold(int value);

    NLivenessMode getLivenessMode() const;
    void setLivenessMode(const NLivenessMode &value);

    NMatchingSpeed getMatchSpeed() const;
    void setMatchSpeed(const NMatchingSpeed &value);

    int getTokenImageWidth() const;
    void setTokenImageWidth(int value);

    int getTokenQualityThreshold() const;
    void setTokenQualityThreshold(int value);

    int getSharpnessThreshold() const;
    void setSharpnessThreshold(int value);

    int getBgUniformThreshold() const;
    void setBgUniformThreshold(int value);

    int getGrayDensityThreshold() const;
    void setGrayDensityThreshold(int value);

    NTemplateSize getTemplateSize() const;
    void setTemplateSize(const NTemplateSize &value);

    bool getDetectAllFeature() const;
    void setDetectAllFeature(bool value);

    int getMatchMaxResult() const;
    void setMatchMaxResult(int value);

    bool getMatchFirstResult() const;
    void setMatchFirstResult(bool value);

    int getLivenessBlinkTimeout() const;
    void setLivenessBlinkTimeout(int value);

private:
    static PreferenceHandler * m_preHandler;
    PreferenceHandler();
#ifdef USE_NEURO
    int eyeDistance;
    QString tag_eye_distance;

    int confident;
    QString tag_confident;

    float maxRoll;
    QString tag_max_roll;

    float maxYaw;
    QString tag_max_yaw;

    int qualityThreshold;
    QString tag_quality_threshold;

    bool useLivenessCheck;
    QString tag_use_liveness_check;

    int livenessThreshold;
    QString tag_liveness_threshold;

    int livenessBlinkTimeout;
    QString tag_liveness_blink;

    NLivenessMode livenessMode;
    QString tag_liveness_mode;

    NMatchingSpeed matchSpeed;
    QString tag_match_speed;

    int tokenImageWidth;
    QString tag_token_image_width;

    int tokenQualityThreshold;
    QString tag_token_quality_theshold;

    int sharpnessThreshold;
    QString tag_sharpness_threshold;

    int bgUniformThreshold;
    QString tag_bg_uniform_threshold;

    int grayDensityThreshold;
    QString tag_gray_density_threshold;

    NTemplateSize templateSize;
    QString tag_template_size;

    bool detectAllFeature;
    QString tag_detect_all_feature;

    bool mmatchingDetail;
    QString tag_matching_detail;

    int matchMaxResult;
    QString tag_match_max_result;

    bool matchFirstResult;
    QString tag_match_first_result;

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
