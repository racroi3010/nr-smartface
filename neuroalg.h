#ifndef NEUROALG_H
#define NEUROALG_H

#include <NCore.h>
#include <NBiometricClient.h>
#include <NBiometrics.h>
#include <NMedia.h>
#include <NLicensing.h>

#include "facealginterface.h"
#include "TutorialUtils.h"

class NeuroAlg: public FaceAlgInterface
{
public:
    NeuroAlg();
    bool imageReg(QString userName, cv::Mat& frame);
    QString imageCmp(cv::Mat& frame);
    cv::Rect faceDetect(cv::Mat& frame);
    bool LoadFeatures(const char* lpPath, int iAlg);
    //bool saveImage(cv::Mat& frame, QString userName);

    bool close();

    bool checkLicense();

private:
    NResult createSubjectFromImage(HNSubject hSubject, const NChar * fileName, HNString subjectId);
    HNImage convertMat2Image(cv::Mat frame);
};

#endif // NEUROALG_H
