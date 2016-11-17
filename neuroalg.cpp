#include "neuroalg.h"

NeuroAlg::NeuroAlg()
{

}

bool NeuroAlg::imageReg(QString userName, cv::Mat& frame){
    NResult result = N_OK;
    const NChar * additionalComponents = N_T("Biometrics.FaceSegmentsDetection");
    NBool additionalObtained = NFalse;
    result = NLicenseObtainComponents(N_T("/local"), N_T("5000"), additionalComponents, &additionalObtained);
    if(NFailed(result)){
        std::cout << "NLicenseObtainComponents() failed" << std::endl;
        return false;
    }
    // create subject
    HNSubject hSubject = NULL;
    result = NSubjectCreate(&hSubject);
    if(NFailed(result)){
        std::cout << "NSubjectCreate() failed" << std::endl;
        return false;
    }

    // create face
    HNFace hFace = NULL;
    result = NFaceCreate(&hFace);
    if(NFailed(result)){
        std::cout << "NFaceCreate() failed" << std::endl;
        return false;
    }

    // write image
    cv::cvtColor(frame, frame, CV_BGR2RGB);
    QString path = QDir::currentPath() + "/temp/" + userName + ".bmp";
    cv::imwrite(path.toStdString(), frame);

    // read and set the image for the face
    result = NBiometricSetFileName(hFace, N_T(path.toStdString().c_str()));
    if(NFailed(result)){
        std::cout << "NBiometricSetFileName() failed" << std::endl;
        return false;
    }


    // set capture option to nbcoNone
    result = NBiometricSetCaptureOptions(hFace, nbcoNone);
    if(NFailed(result)){
        std::cout << "NBiometricSetCaptureOptions() failed" << std::endl;
        return false;
    }

    // set the face for the subject
    result = NSubjectAddFace(hSubject, hFace, NULL);
    if(NFailed(result)){
        std::cout << "NSubjectAddFace() failed" << std::endl;
        return false;
    }

    // create biometric client
    HNBiometricClient hBiometricClient = NULL;
    result = NBiometricClientCreate(&hBiometricClient);
    if(NFailed(result)){
        std::cout << "NBiometricClientCreate() failed" << std::endl;
        return false;
    }

    NTemplateSize templateSize = ntsLarge;
    NBoolean parameter = NTrue;
    NBool hasEx = NFalse;

   // set template size to large
    result = NObjectSetPropertyP(hBiometricClient, N_T("Faces.TemplateSize"), N_TYPE_OF(NTemplateSize), naNone, &templateSize, sizeof(templateSize), 1, NTrue);
    if (NFailed(result)) {
        std::cout << "NObjectSetPropertyP() failed" << std::endl;
        return false;
    }

    result = NLicenseIsComponentActivated(additionalComponents, &hasEx);
    if (NFailed(result)) {
        std::cout << "NObjectSetPropertyP() failed" << std::endl;
        return false;
    }

    if (hasEx) {
        // set detect all facial features
        result = NObjectSetPropertyP(hBiometricClient, N_T("Faces.DetectAllFeaturePoints"), N_TYPE_OF(NBoolean), naNone, &parameter, sizeof(parameter), 1, NTrue);
        if(NFailed(result)){
            std::cout << "NObjectSetPropertyP() failed" << std::endl;
            return false;
        }
    }

    // create template
    NBiometricStatus biometricsStatus = nbsNone;

    result = NBiometricEngineCreateTemplate(hBiometricClient, hSubject, &biometricsStatus);
    if(NFailed(result)){
        std::cout << "NBiometricEngineCreateTemplate() failed" << std::endl;
        return false;
    }

    if(biometricsStatus == nbsOk){
        std::cout << "template extracted" << std::endl;
        // retrieve the template from subject
        HNBuffer hBuffer = NULL;
        result = NSubjectGetTemplateBuffer(hSubject, &hBuffer);
        if(NFailed(result)){
            std::cout << "NSubjectGetTemplateBuffer() failed" << std::endl;
            return false;
        }
        QString tempFile = QDir::currentPath() +"/feature/" + userName + ".dat";
        result = NFileWriteAllBytesCN(N_T(tempFile.toStdString().c_str()), hBuffer);
        if(NFailed(result)){
            std::cout << "NFileWriteAllBytesCN() failed" << std::endl;
            return false;
        }
    } else {

        std::cout << "template extraction failed" << std::endl;
        return false;
    }
    //NBiometricSetSampleBuffer()

    return true;
}
NResult NeuroAlg::createSubjectFromImage(HNSubject hSubject, const NChar * fileName, HNString subjectId){
    HNBuffer hBuffer = NULL;
    NResult result = N_OK;

//    // create template
//    // create subject
//    HNSubject hSubject = NULL;
//    result = NSubjectCreate(&hSubject);
//    if(NFailed(result)){
//        std::cout << "NSubjectCreate() failed" << std::endl;
//        return false;
//    }

//    // create face
//    HNFace hFace = NULL;
//    result = NFaceCreate(&hFace);
//    if(NFailed(result)){
//        std::cout << "NFaceCreate() failed" << std::endl;
//        return false;
//    }

//    // read and set the image for the face
//    result = NBiometricSetFileName(hFace, fileName);
//    if(NFailed(result)){
//        std::cout << "NBiometricSetFileName() failed" << std::endl;
//        return false;
//    }

//    // set capture option to nbcoNone
//    result = NBiometricSetCaptureOptions(hFace, nbcoNone);
//    if(NFailed(result)){
//        std::cout << "NBiometricSetCaptureOptions() failed" << std::endl;
//        return false;
//    }

//    // set the face for the subject
//    result = NSubjectAddFace(hSubject, hFace, NULL);
//    if(NFailed(result)){
//        std::cout << "NSubjectAddFace() failed" << std::endl;
//        return false;
//    }

//    // create biometric client
//    HNBiometricClient hBiometricClient = NULL;
//    result = NBiometricClientCreate(&hBiometricClient);
//    if(NFailed(result)){
//        std::cout << "NBiometricClientCreate() failed" << std::endl;
//        return false;
//    }

//    NTemplateSize templateSize = ntsLarge;
//    NBoolean parameter = NTrue;
//    NBool hasEx = NFalse;

//   // set template size to large
//    result = NObjectSetPropertyP(hBiometricClient, N_T("Faces.TemplateSize"), N_TYPE_OF(NTemplateSize), naNone, &templateSize, sizeof(templateSize), 1, NTrue);
//    if (NFailed(result)) {
//        std::cout << "NObjectSetPropertyP() failed" << std::endl;
//        return false;
//    }

//    result = NLicenseIsComponentActivated(additionalComponents, &hasEx);
//    if (NFailed(result)) {
//        std::cout << "NObjectSetPropertyP() failed" << std::endl;
//        return false;
//    }

//    if (hasEx) {
//        // set detect all facial features
//        result = NObjectSetPropertyP(hBiometricClient, N_T("Faces.DetectAllFeaturePoints"), N_TYPE_OF(NBoolean), naNone, &parameter, sizeof(parameter), 1, NTrue);
//        if(NFailed(result)){
//            std::cout << "NObjectSetPropertyP() failed" << std::endl;
//            return false;
//        }
//    }

//    // create template
//    NBiometricStatus biometricsStatus = nbsNone;

//    result = NBiometricEngineCreateTemplate(hBiometricClient, hSubject, &biometricsStatus);
//    if(NFailed(result)){
//        std::cout << "NBiometricEngineCreateTemplate() failed" << std::endl;
//        return false;
//    }

//    if(biometricsStatus == nbsOk){
//        std::cout << "template extracted" << std::endl;
//        // retrieve the template from subject
//        HNBuffer hBuffer = NULL;
//        result = NSubjectGetTemplateBuffer(hSubject, &hBuffer);
//        if(NFailed(result)){
//            std::cout << "NSubjectGetTemplateBuffer() failed" << std::endl;
//            return false;
//        }

//        // set template for subject
//        result = NSubjectSetTemplate(hSubject, hBuffer);

//        if(NFailed(result)){
//            std::cout << "NSubjectSetTemplate() failed" << std::endl;
//            return false;
//        }

//        // set the id for the subject
//        result = NSubjectSetIdN(hSubject, subjectId);
//        if(NFailed(result)){
//            std::cout << "NSubjectSetIdN() failed" << std::endl;
//            return false;
//        }



//    } else {

//        std::cout << "template extraction failed" << std::endl;
//        return false;
//    }

    return false;
}

QString NeuroAlg::imageCmp(cv::Mat& frame){
    NResult result = NULL;

    // create subject for probe template
    HNSubject hProbeSubject = NULL;
    result = NSubjectCreate(&hProbeSubject);
    if(NFailed(result)){
        std::cout << "NSubjectCreate() failed" << std::endl;
        return false;
    }

    // create biometric client
    HNBiometricClient hBiometricClient = NULL;
    result = NBiometricClientCreate(&hBiometricClient);
    if(NFailed(result)){
        std::cout << "NBiometricClientCreate() failed" << std::endl;
        return false;
    }
    // create probe subject id
    HNString hSubjectId = NULL;
    result = NStringCreate(N_T("ProbeSubject"), &hSubjectId);
    if(NFailed(result)){
        std::cout << "NStringCreate() failed" << std::endl;
        return false;
    }

    // write image
    cv::cvtColor(frame, frame, CV_BGR2RGB);
    QString path = QDir::currentPath() + "/temp/comparing.bmp";
    cv::imwrite(path.toStdString(), frame);

    // settemplate for probe subject
    result = createSubjectFromImage(hProbeSubject, N_T(path.toStdString().c_str()), hSubjectId);


    return NULL;
}

cv::Rect NeuroAlg::faceDetect(cv::Mat& frame){
    cv::Rect rec(0, 0, 0, 0);
    NResult result = N_OK;

    // license
    const NChar * components = { N_T("Biometrics.FaceExtraction") };
    const NChar * additionalComponents = N_T("Biometrics.FaceSegmentsDetection");
    NBool additionalObtained = NFalse;
    NBool available = NFalse;
    result = NLicenseObtainComponents(N_T("/local"), N_T("5000"), components, &available);
    if (NFailed(result))
    {
        printf(N_T("Licenses failed\n"), components);
        return rec;
    }
    if (!available)
    {
        printf(N_T("Licenses for %s not available\n"), components);
        return rec;
    }
    result = NLicenseObtainComponents(N_T("/local"), N_T("5000"), additionalComponents, &additionalObtained);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NLicenseObtainComponents() failed, result = %d\n"), result);
        return rec;
    }




    // create subject
    HNSubject hSubject = NULL;
    result = NSubjectCreate(&hSubject);
    if(NFailed(result)){
        std::cout << "NSubjectCreate failed" << std::endl;
        return rec;
    }

    // create face for the subject
    HNFace hFace = NULL;
    result = NFaceCreate(&hFace);
    if(NFailed(result)){
        std::cout << "NFaceCreate failed" << std::endl;
        return rec;
    }

    // set data
    HNBuffer hImageData = NULL;
    NBufferCreate(frame.step * frame.cols * frame.rows, &hImageData);
    NBufferGetPtr(hImageData, (void**)&frame.data);
    result = NBiometricSetSampleBuffer(hFace, hImageData);
    if(NFailed(result)){
        std::cout << "NBiometricSetSampleBuffer failed" << std::endl;
        return rec;
    }


    // set capture option
    result = NBiometricSetCaptureOptions(hFace, nbcoNone);
    if(NFailed(result)){
        std::cout << "NBiometricSetCaptureOptions failed" << std::endl;
        return rec;
    }

    // set the face for the subject
    result = NSubjectAddFace(hSubject, hFace, NULL);
    if(NFailed(result)){
        std::cout << "NSubjectAddFace failed" << std::endl;
        return rec;
    }


    // create biometric client
    HNBiometricClient hBiometricClient = NULL;
    result = NBiometricClientCreate(&hBiometricClient);

    // retrieve the number of faces detected
    NInt facesDetected = 0;
    result = NSubjectGetFaceCount(hSubject, &facesDetected);
    if(NFailed(result)){
        std::cout << "NSubjectGetFaceCount failed" << std::endl;
        return rec;
    }

    // get face
    HNLAttributes hLAtributes = NULL;
    if(facesDetected){
        std::cout << facesDetected << std::endl;
        result = NFaceGetObject(hFace, 0, &hLAtributes);
        if(NFailed(result)){
            //std::cout << "NFaceGetObject failed" << std::endl;
            result = PrintErrorMsgWithLastError(N_T("NFaceGetObject() failed (result = %d)!"), result);
            return rec;
        }

        NRect boundingRect;
        result = NLAttributesGetBoundingRect(hLAtributes, &boundingRect);
        if(NFailed(result)){
            std::cout << "NLAttributesGetBoundingRect failed" << std::endl;
            return rec;
        }

        rec = cv::Rect(boundingRect.X, boundingRect.Y, boundingRect.Width, boundingRect.Height);

    }
    return rec;

}

bool NeuroAlg::LoadFeatures(const char* lpPath, int iAlg){

}

//bool NeuroAlg::saveImage(cv::Mat& frame, QString userName){

//}

bool NeuroAlg::close(){
    NCoreOnExitEx(NFalse);
}

bool NeuroAlg::checkLicense(){
    const NChar * components = {N_T("Biometrics.FaceExtraction")};
    NBool available = NFalse;
    NResult result = NLicenseObtainComponents(N_T("/local"), N_T("5000"), components, &available);
    return NFailed(result);
}
