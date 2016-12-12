#include "neuroengineparams.h"

NeuroEngineParams::NeuroEngineParams()
{

}

NInt32 NeuroEngineParams::getMinInterOcular() const
{
    return minInterOcular;
}

void NeuroEngineParams::setMinInterOcular(const NInt32 &value)
{
    minInterOcular = value;
}

NUInt8 NeuroEngineParams::getConfThreshold() const
{
    return confThreshold;
}

void NeuroEngineParams::setConfThreshold(const NUInt8 &value)
{
    confThreshold = value;
}

NSingle NeuroEngineParams::getMaxRoll() const
{
    return maxRoll;
}

void NeuroEngineParams::setMaxRoll(const NSingle &value)
{
    maxRoll = value;
}

NSingle NeuroEngineParams::getMaxYaw() const
{
    return maxYaw;
}

void NeuroEngineParams::setMaxYaw(const NSingle &value)
{
    maxYaw = value;
}

NUInt8 NeuroEngineParams::getQualityThreshold() const
{
    return qualityThreshold;
}

void NeuroEngineParams::setQualityThreshold(const NUInt8 &value)
{
    qualityThreshold = value;
}

NBoolean NeuroEngineParams::getUseLivenessCheck() const
{
    return useLivenessCheck;
}

void NeuroEngineParams::setUseLivenessCheck(const NBoolean &value)
{
    useLivenessCheck = value;
}

NUInt8 NeuroEngineParams::getLivenessThresHold() const
{
    return livenessThresHold;
}

void NeuroEngineParams::setLivenessThresHold(const NUInt8 &value)
{
    livenessThresHold = value;
}

NUInt NeuroEngineParams::getLivenessBlinkTimeOut() const
{
    return livenessBlinkTimeOut;
}

void NeuroEngineParams::setLivenessBlinkTimeOut(const NUInt &value)
{
    livenessBlinkTimeOut = value;
}

NLivenessMode NeuroEngineParams::getLivenessMode() const
{
    return livenessMode;
}

void NeuroEngineParams::setLivenessMode(const NLivenessMode &value)
{
    livenessMode = value;
}

NMatchingSpeed NeuroEngineParams::getMatchSpeed() const
{
    return matchSpeed;
}

void NeuroEngineParams::setMatchSpeed(const NMatchingSpeed &value)
{
    matchSpeed = value;
}

NUInt32 NeuroEngineParams::getTokenImageWidth() const
{
    return tokenImageWidth;
}

void NeuroEngineParams::setTokenImageWidth(const NUInt32 &value)
{
    tokenImageWidth = value;
}

NUInt8 NeuroEngineParams::getTokenQualityThreshold() const
{
    return tokenQualityThreshold;
}

void NeuroEngineParams::setTokenQualityThreshold(const NUInt8 &value)
{
    tokenQualityThreshold = value;
}

NUInt8 NeuroEngineParams::getSharpnessThreshold() const
{
    return sharpnessThreshold;
}

void NeuroEngineParams::setSharpnessThreshold(const NUInt8 &value)
{
    sharpnessThreshold = value;
}

NUInt8 NeuroEngineParams::getBgUniformityThreshold() const
{
    return bgUniformityThreshold;
}

void NeuroEngineParams::setBgUniformityThreshold(const NUInt8 &value)
{
    bgUniformityThreshold = value;
}

NUInt8 NeuroEngineParams::getGrayDensityThreshold() const
{
    return grayDensityThreshold;
}

void NeuroEngineParams::setGrayDensityThreshold(const NUInt8 &value)
{
    grayDensityThreshold = value;
}

NTemplateSize NeuroEngineParams::getTemplateSize() const
{
    return templateSize;
}

void NeuroEngineParams::setTemplateSize(const NTemplateSize &value)
{
    templateSize = value;
}

NBoolean NeuroEngineParams::getDetectAllFeature() const
{
    return detectAllFeature;
}

void NeuroEngineParams::setDetectAllFeature(const NBoolean &value)
{
    detectAllFeature = value;
}

NBoolean NeuroEngineParams::getMatchingWithDetail() const
{
    return matchingWithDetail;
}

void NeuroEngineParams::setMatchingWithDetail(const NBoolean &value)
{
    matchingWithDetail = value;
}

NInt32 NeuroEngineParams::getMatchingMaxResult() const
{
    return matchingMaxResult;
}

void NeuroEngineParams::setMatchingMaxResult(const NInt32 &value)
{
    matchingMaxResult = value;
}

NInt32 NeuroEngineParams::getMatchingThreshold() const
{
    return matchingThreshold;
}

void NeuroEngineParams::setMatchingThreshold(const NInt32 &value)
{
    matchingThreshold = value;
}

NBoolean NeuroEngineParams::getMatchingFirstResult() const
{
    return matchingFirstResult;
}

void NeuroEngineParams::setMatchingFirstResult(const NBoolean &value)
{
    matchingFirstResult = value;
}




