#ifndef NEUROENGINEPARAMS_H
#define NEUROENGINEPARAMS_H

#include <NCore.h>
#include <NBiometricClient.h>
#include <NBiometrics.h>
#include "engineparams.h"

class NeuroEngineParams : public EngineParams
{
public:
    NeuroEngineParams();

    NInt32 getMinInterOcular() const;
    void setMinInterOcular(const NInt32 &value);

    NUInt8 getConfThreshold() const;
    void setConfThreshold(const NUInt8 &value);

    NSingle getMaxRoll() const;
    void setMaxRoll(const NSingle &value);

    NSingle getMaxYaw() const;
    void setMaxYaw(const NSingle &value);

    NUInt8 getQualityThreshold() const;
    void setQualityThreshold(const NUInt8 &value);

    NBoolean getUseLivenessCheck() const;
    void setUseLivenessCheck(const NBoolean &value);

    NUInt8 getLivenessThresHold() const;
    void setLivenessThresHold(const NUInt8 &value);

    NUInt getLivenessBlinkTimeOut() const;
    void setLivenessBlinkTimeOut(const NUInt &value);

    NLivenessMode getLivenessMode() const;
    void setLivenessMode(const NLivenessMode &value);

    NMatchingSpeed getMatchSpeed() const;
    void setMatchSpeed(const NMatchingSpeed &value);

    NUInt32 getTokenImageWidth() const;
    void setTokenImageWidth(const NUInt32 &value);

    NUInt8 getTokenQualityThreshold() const;
    void setTokenQualityThreshold(const NUInt8 &value);

    NUInt8 getSharpnessThreshold() const;
    void setSharpnessThreshold(const NUInt8 &value);

    NUInt8 getBgUniformityThreshold() const;
    void setBgUniformityThreshold(const NUInt8 &value);

    NUInt8 getGrayDensityThreshold() const;
    void setGrayDensityThreshold(const NUInt8 &value);

    NTemplateSize getTemplateSize() const;
    void setTemplateSize(const NTemplateSize &value);

    NBoolean getDetectAllFeature() const;
    void setDetectAllFeature(const NBoolean &value);

    NBoolean getMatchingWithDetail() const;
    void setMatchingWithDetail(const NBoolean &value);

    NInt32 getMatchingMaxResult() const;
    void setMatchingMaxResult(const NInt32 &value);



    NInt32 getMatchingThreshold() const;
    void setMatchingThreshold(const NInt32 &value);

    NBoolean getMatchingFirstResult() const;
    void setMatchingFirstResult(const NBoolean &value);

private:

    // client
    NInt32 minInterOcular; //Faces.MinimalInterOcularDistance
    NUInt8 confThreshold; // Faces.ConfidenceThreshold
    NSingle maxRoll; // Faces.MaximalRoll
    NSingle maxYaw; // Faces.MaximalYaw

    NUInt8 qualityThreshold; // Faces.QualityThreshold

    NBoolean useLivenessCheck; // Faces.UseLivenessCheck
    NUInt8 livenessThresHold; // Faces.LivenessThreshold
    NUInt livenessBlinkTimeOut; //Faces.LivenessBlinkTimeout

    NLivenessMode livenessMode; // Faces.LivenessMode
    NMatchingSpeed matchSpeed; // Faces.MatchingSpeed

    NUInt32 tokenImageWidth; //Faces.TokenImageWidth
    NUInt8 tokenQualityThreshold; // Faces.TokenQualityThreshold
    NUInt8 sharpnessThreshold; // Faces.SharpnessThreshold

    NUInt8 bgUniformityThreshold; // Faces.BackgroundUniformityThreshold

    NUInt8 grayDensityThreshold; // Faces.GrayscaleDensityThreshold

    NTemplateSize templateSize; // Faces.TemplateSize
    NBoolean detectAllFeature; //  Faces.DetectAllFeaturePoints

    // matching
    NBoolean matchingWithDetail; // Matching.WithDetails
    NInt32 matchingMaxResult; // Matching.MaximalResultCount
    NBoolean matchingFirstResult; // Matching.FirstResultOnly
    NInt32 matchingThreshold; // Matching.Threshold
};

#endif // NEUROENGINEPARAMS_H
