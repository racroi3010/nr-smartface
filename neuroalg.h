#ifndef NEUROALG_H
#define NEUROALG_H

#include <QDir>

#include <NCore.h>
#include <NBiometricClient.h>
#include <NBiometrics.h>
#include <NMedia.h>
#include <NLicensing.h>

#include "facealginterface.h"
#include "TutorialUtils.h"
#include "preferencehandler.h"
#include "neuroengineparams.h"

class NeuroAlg: public FaceAlgInterface
{
public:
    NeuroAlg();
    ~NeuroAlg();
    bool imageReg(QString userName, cv::Mat& frame);
    QString imageCmp(cv::Mat& frame);
    cv::Rect faceDetect(cv::Mat& frame);
    bool LoadFeatures(const char* lpPath, int iAlg);
    //bool saveImage(cv::Mat& frame, QString userName);

    bool close();

    bool checkLicense();
    EngineParams getEngineParams();
private:

    // license
    const NChar * components = {N_T("Biometrics.FaceExtraction")};
    const NChar * additionalComponents1 = N_T("Biometrics.FaceSegmentsDetection");
    const NChar * additionalComponents2 = N_T("Biometrics.FaceMatching");

    // face matching

    HNBiometricClient hBiometricClientForId = NULL;
    NBiometricStatus biometricStatusForId = nbsNone;



    NResult createTemplate(cv::Mat frame, HNBuffer *hBuffer);
    NResult CreateSubject(HNSubject hSubject, HNBuffer *hBuffer, HNString subjectId);
    NResult CreateSubject(HNSubject hSubject, const NChar * fileName, HNString subjectId);
    NResult createSubjectFromImage(HNSubject hSubject, const NChar * fileName, HNString subjectId);
    void convertMat2Image(cv::Mat frame, HNImage *hImage);
};

#endif // NEUROALG_H
