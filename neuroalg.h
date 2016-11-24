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

class NeuroAlg: public FaceAlgInterface
{
public:
    bool imageReg(QString userName, cv::Mat& frame);
    QString imageCmp(cv::Mat& frame);
    cv::Rect faceDetect(cv::Mat& frame);
    bool LoadFeatures(const char* lpPath, int iAlg);
    //bool saveImage(cv::Mat& frame, QString userName);

    bool close();

    bool checkLicense();
private:

    // license
    const NChar * components = {N_T("Biometrics.FaceExtraction")};
    const NChar * additionalComponents1 = N_T("Biometrics.FaceSegmentsDetection");
    const NChar * additionalComponents2 = N_T("Biometrics.FaceMatching");
    // face detection
    HNSubject hSubject = NULL;
    HNFace hFace = NULL;
    HNBiometricClient hBiometricClient = NULL;
    NBiometricStatus biometricStatus = nbsNone;
    HNLAttributes hLAtributes = NULL;

    // compare
    HNSubject hProbeSubject = NULL;
    HNString hSubjectId = NULL;
    HNBuffer hBuffer = NULL;

    // face matching
    HNBiometricClient hBiometricClientForId = NULL;
    NBiometricStatus biometricStatusForId = nbsNone;


    NResult createTemplate(cv::Mat frame, HNBuffer *hBuffer);
    NResult CreateSubject(HNSubject hSubject, HNBuffer *hBuffer, HNString subjectId);
    NResult CreateSubject(HNSubject hSubject, const NChar * fileName, HNString subjectId);
    NResult createSubjectFromImage(HNSubject hSubject, const NChar * fileName, HNString subjectId);
    HNImage convertMat2Image(cv::Mat frame);
};

#endif // NEUROALG_H
