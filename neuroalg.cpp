#include "neuroalg.h"

NeuroAlg::NeuroAlg()
{



}

bool NeuroAlg::imageReg(QString userName, cv::Mat& frame){
    NResult result = N_OK;

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

    // set data
    //frame = cv::imread("et.bmp", CV_LOAD_IMAGE_COLOR);

    result = NFaceSetImage(hFace, convertMat2Image(frame));
    if (NFailed(result))
    {
        std::cout << "NImageCreateFromDataEx failed" << std::endl;
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
        } else {
            QString path = QDir::currentPath() + "/temp/" + userName + ".bmp";
            cv::imwrite(path.toStdString(), frame);
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
    // face detection
    HNSubject hSubject = NULL;
    HNFace hFace = NULL;
    HNBiometricClient hBiometricClient = NULL;
    NBiometricStatus biometricStatus = nbsNone;
    HNLAttributes hLAtributes = NULL;
    // create subject
    result = NSubjectCreate(&hSubject);
    if(NFailed(result)){
        std::cout << "NSubjectCreate failed" << std::endl;
        return rec;
    }

    // create face for the subject
    result = NFaceCreate(&hFace);
    if(NFailed(result)){
        std::cout << "NFaceCreate failed" << std::endl;
        return rec;
    }

    // set data
    result = NFaceSetImage(hFace, convertMat2Image(frame));
    if (NFailed(result))
    {
        std::cout << "NImageCreateFromDataEx failed" << std::endl;
        return rec;
    }


    // set the face for the subject
    result = NSubjectAddFace(hSubject, hFace, NULL);
    if(NFailed(result)){
        std::cout << "NSubjectAddFace failed" << std::endl;
        return rec;
    }

    // create biometric client

    result = NBiometricClientCreate(&hBiometricClient);
    if(NFailed(result)){
        std::cout << "NBiometricClientCreate failed" << std::endl;
        return rec;
    }

    // create the template

    result = NBiometricEngineCreateTemplate(hBiometricClient, hSubject, &biometricStatus);
    if (NFailed(result))
    {
        std::cout << "NBiometricEngineCreateTemplate failed" << std::endl;
        return rec;
    }

    // retrieve the number of faces detected
    NInt facesDetected = 0;
    result = NSubjectGetFaceCount(hSubject, &facesDetected);
    if(NFailed(result)){
        std::cout << "NSubjectGetFaceCount failed" << std::endl;
        return rec;
    }

    // get face

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

    result = NObjectSet(NULL, (HNObject *)&hSubject);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed (result = %d)!"), result);
    }
    result = NObjectSet(NULL, (HNObject *)&hFace);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed (result = %d)!"), result);
    }
    result = NObjectSet(NULL, (HNObject *)&hLAtributes);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed (result = %d)!"), result);
    }
    result = NObjectSet(NULL, (HNObject *)&hBiometricClient);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed (result = %d)!"), result);
    }
    result = NObjectSet(NULL, (HNObject *)&biometricStatus);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NObjectSet() failed (result = %d)!"), result);
    }

    return rec;

}

bool NeuroAlg::LoadFeatures(const char* lpPath, int iAlg){
    NResult result = N_OK;

    // create biometric client
    HNBiometricClient hBiometricClient = NULL;
    result = NBiometricClientCreate(&hBiometricClient);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NBiometricClientCreate() failed (result = %d)!"), result);
        return false;
    }

    // create biometric task to enroll
    result = NBiometricEngineCreateTask(hBiometricClient, nboEnroll, NULL, NULL, &hBiometricTaskForId);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NBiometricEngineCreateTask() failed (result = %d)!"), result);
        return false;
    }


    // read templates
    QDir* dir = new QDir(QString(lpPath));
    dir->setNameFilters(QStringList("*.dat"));
    dir->setFilter(QDir::Files|QDir::NoDotAndDotDot|QDir::NoSymLinks);

    QFileInfoList files = dir->entryInfoList();
    HNSubject hTemplateSubject = NULL;
    QFileInfo f;
    HNString hSubjectId = NULL;
    for(int i = 0; i < files.count(); i ++){
        f = files[i];
        // create subject for gallery templates
        result = NSubjectCreate(&hTemplateSubject);
        if (NFailed(result))
        {
            result = PrintErrorMsgWithLastError(N_T("NSubjectCreate() failed (result = %d)!"), result);
            return false;
        }
        // create gallery subject id
        result = NStringFormat(&hSubjectId, N_T(f.baseName().toStdString().c_str()));
        if (NFailed(result))
        {
            result = PrintErrorMsgWithLastError(N_T("NStringFormat() failed (result = %d)!"), result);
            return false;
        }
//        // set template for gallery subject
//        result = CreateSubject(hGallerySubject, argv[i], hSubjectId);
//        if (NFailed(result))
//        {
//            PrintErrorMsg(N_T("CreateSubject() failed (result = %d)!"), result);
//            goto FINALLY;
//        }


    }
    delete dir;
    return true;
}

//bool NeuroAlg::saveImage(cv::Mat& frame, QString userName){

//}

bool NeuroAlg::close(){
    NResult result = N_OK;

    result = NLicenseReleaseComponents(additionalComponents2);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NLicenseReleaseComponents() failed (result = %d)!"), result);
        return false;
    }
    result = NLicenseReleaseComponents(additionalComponents1);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NLicenseReleaseComponents() failed (result = %d)!"), result);
        return false;
    }
    result = NLicenseReleaseComponents(components);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NLicenseReleaseComponents() failed (result = %d)!"), result);
        return false;
    }


    NCoreOnExitEx(NFalse);

    return true;
}

bool NeuroAlg::checkLicense(){
    NBool additionalObtained = NFalse;
    NBool available = NFalse;
    NResult result = NLicenseObtainComponents(N_T("/local"), N_T("5000"), components, &available);
    if (NFailed(result))
    {
        printf(N_T("NLicenseObtainComponents failed\n"), components);
        return false;
    }

    result = NLicenseObtainComponents(N_T("/local"), N_T("5000"), additionalComponents1, &additionalObtained);
    if (NFailed(result))
    {
        printf(N_T("NLicenseObtainComponents failed\n"), additionalComponents1);
        return false;
    }
    NBool match = NFalse;
    result = NLicenseObtainComponents(N_T("/local"), N_T("5000"), additionalComponents2, &match);
    if (NFailed(result))
    {
        printf(N_T("NLicenseObtainComponents failed\n"), additionalComponents2);
        return false;
    }
    return true;
}
HNImage NeuroAlg::convertMat2Image(cv::Mat frame){
    cv::cvtColor(frame, frame, CV_BGR2RGB);
    HNImage hImage = NULL;
    NResult result = NImageCreateFromDataEx(NPF_RGB_8U, frame.cols, frame.rows, 0, frame.cols * 3
                                            , (void*)frame.data, frame.cols * frame.rows * 3, NI_SRC_ALPHA_CHANNEL_FIRST, &hImage);
    if (NFailed(result))
    {
        std::cout << "NImageCreateFromDataEx failed" << std::endl;

    }
    return hImage;
}
NResult NeuroAlg::CreateSubject(HNSubject hSubject, HNBuffer *hBuffer, HNString subjectId){
//    HNBuffer hBuffer = NULL;
    NResult result = N_OK;

//    // read template
//    result = NFileReadAllBytesCN(fileName, &hBuffer);
//    if (NFailed(result))
//    {
//        result = PrintErrorMsgWithLastError(N_T("NFileReadAllBytesCN() failed (result = %d)!"), result);
//        return result;
//    }

    // set template for subject
    result = NSubjectSetTemplateBuffer(hSubject, *hBuffer);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NSubjectSetTemplateBuffer() failed (result = %d)!"), result);
        return result;
    }

    // set the id for the subject
    result = NSubjectSetIdN(hSubject, subjectId);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NSubjectSetIdN() failed (result = %d)!"), result);
        return result;
    }

    return result;
}
