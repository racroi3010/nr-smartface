#include "neuroalg.h"

NeuroAlg::NeuroAlg(){

}

NeuroAlg::~NeuroAlg(){

}

bool NeuroAlg::imageReg(QString userName, cv::Mat& frame){
    NResult result = N_OK;
    QString tempFile = QDir::currentPath() +"/feature/" + userName + ".dat";
    HNBuffer hBuffer = NULL;
    bool rs = true;
    // create template from mat

    result = createTemplate(frame, &hBuffer);
    if(NFailed(result)){
        PrintErrorMsg(N_T("createTemplate() failed (result = %d)!"), result);
        rs = false;
        goto FINALLY;
    }

    result = NFileWriteAllBytesCN(N_T(tempFile.toStdString().c_str()), hBuffer);
    if(NFailed(result)){
        PrintErrorMsg(N_T("NFileWriteAllBytesCN() failed (result = %d)!"), result);
        rs = false;
        goto FINALLY;
    } else {
        cv::cvtColor(frame, frame, CV_RGB2BGR);
        QString path = QDir::currentPath() + "/temp/" + userName + ".bmp";
        cv::imwrite(path.toStdString(), frame);
    }

FINALLY:
    {
        result = NObjectSet(NULL, (HNObject *)&hBuffer);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result);
        }

    }

    return rs;
}

QString NeuroAlg::imageCmp(cv::Mat& frame){
    NResult result = N_OK;
    QString username = "";

    HNImage hImage = NULL;
    HNSubject hProbeSubject = NULL;
    HNString hSubjectId = NULL;
    HNBuffer hBuffer = NULL;
    // create subject for probe template

    result = NSubjectCreate(&hProbeSubject);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NSubjectCreate() failed (result = %d)!"), result);
        goto FINALLY;
    }
    // create probe subject id

    result = NStringCreate(N_T("ProbeSubject"), &hSubjectId);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NStringCreate() failed (result = %d)!"), result);
        goto FINALLY;
    }
    // create template buffer from mat

    result = createTemplate(frame, &hBuffer);
    if(NFailed(result)){
        PrintErrorMsg(N_T("createTemplate() failed (result = %d)!"), result);
        goto FINALLY;
    }

    // set template for probe subject
    result = CreateSubject(hProbeSubject, &hBuffer, hSubjectId);
    if(NFailed(result)){
        PrintErrorMsg(N_T("CreateSubject() failed (result = %d)!"), result);
        goto FINALLY;
    }

    // perform identification
    result = NBiometricEngineIdentify(hBiometricClientForId, hProbeSubject, &biometricStatusForId);
    if (NFailed(result))
    {
        PrintErrorMsg(N_T("NBiometricEngineIdentify() failed (result = %d)!"), result);
        goto FINALLY;
    }

    if(biometricStatusForId == nbsOk){
        // retrieve matching results array
        HNMatchingResult * hMatchingResults = NULL;
        NInt resultsCount = 0;
        NInt maxScore = 0;
        result = NSubjectGetMatchingResults(hProbeSubject, &hMatchingResults, &resultsCount);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NSubjectGetMatchingResults() failed (result = %d)!"), result);
            goto FINALLY;
        }

        for(int i = 0; i < resultsCount; i ++){
            NInt matchScore = 0;
            const NChar * szMatchId = NULL;
            HNString hMatchId = NULL;
            result = NMatchingResultGetId(hMatchingResults[i], &hMatchId);
            if (NFailed(result))
            {
                PrintErrorMsg(N_T("NMatchingResultGetId() failed (result = %d)!"), result);
                continue;
            }

            result = NStringGetBuffer(hMatchId, NULL, &szMatchId);
            if (NFailed(result))
            {
                PrintErrorMsg(N_T("NStringGetBuffer() failed (result = %d)!"), result);
                continue;
            }

            result = NMatchingResultGetScore(hMatchingResults[i], &matchScore);
            if (NFailed(result))
            {
                PrintErrorMsg(N_T("NMatchingResultGetScore() failed (result = %d)!"), result);
                continue;
            }
            if(maxScore < matchScore){
                maxScore = matchScore;
                username = QString(szMatchId);
            }

            // free unneeded hMatchId
            result = NStringSet(NULL, &hMatchId);
            if (NFailed(result))
            {
                PrintErrorMsg(N_T("NStringSet() failed (result = %d)!"), result);
                continue;
            }
        }


    }
FINALLY:
    {
        // free
        result = NObjectSet(NULL, (HNObject *)&hProbeSubject);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result);
        }
        result = NStringSet(NULL, (HNString *)&hSubjectId);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NStringSet() failed (result = %d)!"), result);
        }
        result = NObjectSet(NULL, (HNObject *)&hBuffer);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result);

        }
        result = NObjectSet(NULL, (HNObject *)&hImage);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result);
        }
    }


    return username;
}

cv::Rect NeuroAlg::faceDetect(cv::Mat& frame){
    cv::Rect rec(0, 0, 0, 0);
    NResult result = N_OK;

    HNImage hImage = NULL;
    HNSubject hSubject = NULL;
    HNFace hFace = NULL;
    HNBiometricClient hBiometricClient = NULL;
    NBiometricStatus biometricStatus = nbsNone;
    HNLAttributes hLAtributes = NULL;
    NInt facesDetected = 0;
    // create subject
    result = NSubjectCreate(&hSubject);
    if(NFailed(result)){
        PrintErrorMsg(N_T("NSubjectCreate() failed (result = %d)!"), result);
        goto FINALLY;
    }

    // create face for the subject
    result = NFaceCreate(&hFace);
    if(NFailed(result)){
        PrintErrorMsg(N_T("NFaceCreate() failed (result = %d)!"), result);
        goto FINALLY;
    }

    // set data
    convertMat2Image(frame, &hImage);
    result = NFaceSetImage(hFace, hImage);
    if (NFailed(result))
    {
        PrintErrorMsg(N_T("NFaceSetImage() failed (result = %d)!"), result);
        goto FINALLY;
    }


    // set the face for the subject
    result = NSubjectAddFace(hSubject, hFace, NULL);
    if(NFailed(result)){
        PrintErrorMsg(N_T("NSubjectAddFace() failed (result = %d)!"), result);
        goto FINALLY;
    }

    // create biometric client

    result = NBiometricClientCreate(&hBiometricClient);
    if(NFailed(result)){
        PrintErrorMsg(N_T("NBiometricClientCreate() failed (result = %d)!"), result);
        goto FINALLY;
    }

    // create the template

    result = NBiometricEngineCreateTemplate(hBiometricClient, hSubject, &biometricStatus);
    if (NFailed(result))
    {
        PrintErrorMsg(N_T("NBiometricEngineCreateTemplate() failed (result = %d)!"), result);
        goto FINALLY;
    }

    // retrieve the number of faces detected

    result = NSubjectGetFaceCount(hSubject, &facesDetected);
    if(NFailed(result)){
        PrintErrorMsg(N_T("NSubjectGetFaceCount() failed (result = %d)!"), result);
        goto FINALLY;
    }

    // get face

    if(facesDetected){
        std::cout << facesDetected << std::endl;
        result = NFaceGetObject(hFace, 0, &hLAtributes);
        if(NFailed(result)){
            //std::cout << "NFaceGetObject failed" << std::endl;
            result = PrintErrorMsgWithLastError(N_T("NFaceGetObject() failed (result = %d)!"), result);
            goto FINALLY;
        }

        NRect boundingRect;
        result = NLAttributesGetBoundingRect(hLAtributes, &boundingRect);
        if(NFailed(result)){
            PrintErrorMsg(N_T("NLAttributesGetBoundingRect() failed (result = %d)!"), result);
            goto FINALLY;
        }

        rec = cv::Rect(boundingRect.X, boundingRect.Y, boundingRect.Width, boundingRect.Height);


    }
FINALLY:
    {
    //    // free
        result = NObjectSet(NULL, (HNObject *)&hSubject);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result);
        }
        result = NObjectSet(NULL, (HNObject *)&hFace);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result);
        }

        result = NObjectSet(NULL, (HNObject *)&hBiometricClient);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result);
        }
    //    result = NStringSet(NULL, (HNString *)&biometricStatus);
    //    if (NFailed(result))
    //    {
    //        PrintErrorMsg(N_T("NStringSet() failed (result = %d)!"), result);
    //    }
        result = NObjectSet(NULL, (HNObject *)&hLAtributes);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result);
        }

        result = NObjectSet(NULL, (HNObject *)&hImage);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result);
        }
    }



    return rec;

}

bool NeuroAlg::LoadFeatures(const char* lpPath, int iAlg){
    NResult result = N_OK;

    QDir* dir = new QDir(QString(lpPath));
    dir->setNameFilters(QStringList("*.dat"));
    dir->setFilter(QDir::Files|QDir::NoDotAndDotDot|QDir::NoSymLinks);
    QFileInfoList files = dir->entryInfoList();
    HNSubject hTemplateSubject = NULL;
    QFileInfo f;
    HNString hSubjectId = NULL;

    HNBiometricTask hBiometricTaskForId = NULL;
    bool rs = true;
    // create biometric client
    result = NBiometricClientCreate(&hBiometricClientForId);
    if (NFailed(result))
    {
        PrintErrorMsg(N_T("NBiometricClientCreate() failed (result = %d)!"), result);
        rs = false;
        goto FINALLY;
    }

    // create biometric task to enroll

    result = NBiometricEngineCreateTask(hBiometricClientForId, nboEnroll, NULL, NULL, &hBiometricTaskForId);
    if (NFailed(result))
    {
        PrintErrorMsg(N_T("NBiometricEngineCreateTask() failed (result = %d)!"), result);
        rs = false;
        goto FINALLY;
    }

    // read templates



    for(int i = 0; i < files.count(); i ++){
        f = files[i];
        // create subject for gallery templates
        result = NSubjectCreate(&hTemplateSubject);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NSubjectCreate() failed (result = %d)!"), result);
            continue;
        }
        // create gallery subject id
        result = NStringFormat(&hSubjectId, N_T(f.baseName().toStdString().c_str()));
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NStringFormat() failed (result = %d)!"), result);
            continue;
        }
        // set template for gallery subject
        result = CreateSubject(hTemplateSubject, f.absoluteFilePath().toStdString().c_str(), hSubjectId);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("CreateSubject() failed (result = %d)!"), result);
            continue;
        }

        // add subject to biometric task
        result = NBiometricTaskAddSubject(hBiometricTaskForId, hTemplateSubject, NULL);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NBiometricTaskAddSubject() failed (result = %d)!"), result);
            continue;
        }

        // free unneeded hTemplateSubject
        result = NObjectSet(NULL, (HNObject *)&hTemplateSubject);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result);
            continue;
        }

        // free unneeded hSubjectId
        result = NStringSet(NULL, &hSubjectId);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NStringSet() failed (result = %d)!"), result);
            continue;
        }

    }
    // perform biometric task
    result = NBiometricEnginePerformTask(hBiometricClientForId, hBiometricTaskForId);
    if (NFailed(result))
    {
        PrintErrorMsg(N_T("NBiometricEnginePerformTask() failed (result = %d)!"), result);
        rs = false;
        goto FINALLY;
    }

    // retrieve biometric task's status
    result = NBiometricTaskGetStatus(hBiometricTaskForId, &biometricStatusForId);
    if (NFailed(result))
    {
        PrintErrorMsg(N_T("NBiometricTaskGetStatus() failed (result = %d)!"), result);
        rs = false;
        goto FINALLY;
    }

    if(biometricStatusForId == nbsOk){
        NInt matchingThreshold = PreferenceHandler::getInstance()->getMatching();
        NBool parameter = NTrue;
        // set matching threshold
        result = NObjectSetPropertyP(hBiometricClientForId, N_T("Matching.Threshold"), N_TYPE_OF(NInt32), naNone, &matchingThreshold, sizeof(matchingThreshold), 1, NTrue);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NBiometricTaskGetStatus() failed (result = %d)!"), result);
            rs = false;
            goto FINALLY;
        }

        // set matching speed
        result = NObjectSetPropertyP(hBiometricClientForId, N_T("Matching.WithDetails"), N_TYPE_OF(NBoolean), naNone, &parameter, sizeof(parameter), 1, NTrue);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NBiometricTaskGetStatus() failed (result = %d)!"), result);
            rs = false;
            goto FINALLY;
        }
    }
FINALLY:
    {
    //    // free
        result = NObjectSet(NULL, (HNObject *)&hBiometricTaskForId);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result);
        }
       delete dir;
    }

    return rs;
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

EngineParams NeuroAlg::getEngineParams(){
    NeuroEngineParams params;

    NInt32 minInterOcular; //Faces.MinimalInterOcularDistance
    NUInt8 threshold; // Faces.ConfidenceThreshold
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
    NBoolean matchingThreshold; // Matching.Threshold

    // create biometric client
    HNBiometricClient hBiometricClient;
    NBool hasValue = NFalse;
    NResult result = NBiometricClientCreate(&hBiometricClient);
    if(NFailed(result)){
        result = PrintErrorMsgWithLastError(N_T("NBiometricClientCreate() failed (result = %d)!"), result);
        return params;
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.MinimalInterOcularDistance"), N_TYPE_OF(NInt32), naNone, &minInterOcular, sizeof(minInterOcular), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setMinInterOcular(minInterOcular);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.ConfidenceThreshold"), N_TYPE_OF(NUInt8), naNone, &threshold, sizeof(threshold), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setConfThreshold(threshold);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.MaximalRoll"), N_TYPE_OF(NSingle), naNone, &maxRoll, sizeof(maxRoll), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setMaxRoll(maxRoll);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.MaximalYaw"), N_TYPE_OF(NSingle), naNone, &maxYaw, sizeof(maxYaw), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setMaxYaw(maxYaw);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.QualityThreshold"), N_TYPE_OF(NUInt8), naNone, &qualityThreshold, sizeof(qualityThreshold), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setQualityThreshold(qualityThreshold);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.UseLivenessCheck"), N_TYPE_OF(NBoolean), naNone, &useLivenessCheck, sizeof(useLivenessCheck), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setUseLivenessCheck(useLivenessCheck);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.LivenessThreshold"), N_TYPE_OF(NUInt8), naNone, &livenessThresHold, sizeof(livenessThresHold), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setLivenessThresHold(livenessThresHold);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.LivenessBlinkTimeout"), N_TYPE_OF(NUInt32), naNone, &livenessBlinkTimeOut, sizeof(livenessBlinkTimeOut), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setLivenessBlinkTimeOut(livenessBlinkTimeOut);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.LivenessMode"), N_TYPE_OF(NLivenessMode), naNone, &livenessMode, sizeof(livenessMode), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setLivenessMode(livenessMode);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.MatchingSpeed"), N_TYPE_OF(NMatchingSpeed), naNone, &matchSpeed, sizeof(matchSpeed), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setMatchSpeed(matchSpeed);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.TokenImageWidth"), N_TYPE_OF(NUInt32), naNone, &tokenImageWidth, sizeof(tokenImageWidth), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setTokenImageWidth(tokenImageWidth);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.TokenQualityThreshold"), N_TYPE_OF(NUInt8), naNone, &tokenQualityThreshold, sizeof(tokenQualityThreshold), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setTokenQualityThreshold(tokenQualityThreshold);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.SharpnessThreshold"), N_TYPE_OF(NUInt8), naNone, &sharpnessThreshold, sizeof(sharpnessThreshold), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setSharpnessThreshold(sharpnessThreshold);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.BackgroundUniformityThreshold"), N_TYPE_OF(NUInt8), naNone, &bgUniformityThreshold, sizeof(bgUniformityThreshold), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setBgUniformityThreshold(bgUniformityThreshold);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.GrayscaleDensityThreshold"), N_TYPE_OF(NUInt8), naNone, &grayDensityThreshold, sizeof(grayDensityThreshold), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setGrayDensityThreshold(grayDensityThreshold);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.TemplateSize"), N_TYPE_OF(NTemplateSize), naNone, &templateSize, sizeof(templateSize), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setTemplateSize(templateSize);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Faces.DetectAllFeaturePoints"), N_TYPE_OF(NBoolean), naNone, &detectAllFeature, sizeof(detectAllFeature), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setDetectAllFeature(detectAllFeature);
    }


    result = NObjectGetPropertyP(hBiometricClient, N_T("Matching.WithDetails"), N_TYPE_OF(NBoolean), naNone, &matchingWithDetail, sizeof(matchingWithDetail), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setMatchingWithDetail(matchingWithDetail);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Matching.MaximalResultCount"), N_TYPE_OF(NInt32), naNone, &matchingMaxResult, sizeof(matchingMaxResult), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setMatchingMaxResult(matchingMaxResult);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Matching.FirstResultOnly"), N_TYPE_OF(NBoolean), naNone, &matchingFirstResult, sizeof(matchingFirstResult), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setMatchingFirstResult(matchingFirstResult);
    }

    result = NObjectGetPropertyP(hBiometricClient, N_T("Matching.Threshold"), N_TYPE_OF(NBoolean), naNone, &matchingThreshold, sizeof(matchingThreshold), 1, &hasValue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
    } else if(hasValue){
        params.setMatchingThreshold(matchingThreshold);
    }

    return params;

}
void NeuroAlg::convertMat2Image(cv::Mat frame, HNImage *hImage){
    //cv::cvtColor(frame, frame, CV_BGR2RGB);
    NResult result = NImageCreateFromDataEx(NPF_RGB_8U, frame.cols, frame.rows, 0, frame.cols * 3
                                            , (void*)frame.data, frame.cols * frame.rows * 3, NI_SRC_ALPHA_CHANNEL_FIRST, hImage);
    if (NFailed(result))
    {
        std::cout << "NImageCreateFromDataEx failed" << std::endl;

    }
}
NResult NeuroAlg::CreateSubject(HNSubject hSubject, HNBuffer *hBuffer, HNString subjectId){
//    HNBuffer hBuffer = NULL;
    NResult result = N_OK;

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
NResult NeuroAlg::CreateSubject(HNSubject hSubject, const NChar * fileName, HNString subjectId)
{
    HNBuffer hBuffer = NULL;
    NResult result = N_OK;

    // read template
    result = NFileReadAllBytesCN(fileName, &hBuffer);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NFileReadAllBytesCN() failed (result = %d)!"), result);
        goto FINALLY;
    }

    // set template for subject
    result = NSubjectSetTemplateBuffer(hSubject, hBuffer);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NSubjectSetTemplateBuffer() failed (result = %d)!"), result);
        goto FINALLY;
    }

    // set the id for the subject
    result = NSubjectSetIdN(hSubject, subjectId);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NSubjectSetIdN() failed (result = %d)!"), result);
        goto FINALLY;
    }

FINALLY:
    {
        NResult result2 = NObjectSet(NULL, (HNObject *)&hBuffer);
        if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
    }

    return result;
}
NResult NeuroAlg::createTemplate(cv::Mat frame, HNBuffer *hBuffer){
    NResult result = N_OK;

    // create subject
    HNSubject hSubject = NULL;
    HNFace hFace = NULL;
    HNImage hImage = NULL;
    NBiometricStatus biometricsStatus = nbsNone;
    NTemplateSize templateSize = ntsLarge;
    NBoolean parameter = NTrue;
    NBool hasEx = NFalse;
    HNBiometricClient hBiometricClient = NULL;

    convertMat2Image(frame, &hImage);

    result = NSubjectCreate(&hSubject);
    if(NFailed(result)){
        result = PrintErrorMsgWithLastError(N_T("NSubjectCreate() failed (result = %d)!"), result);
        goto FINALLY;
    }

    // create face

    result = NFaceCreate(&hFace);
    if(NFailed(result)){
        result = PrintErrorMsgWithLastError(N_T("NFaceCreate() failed (result = %d)!"), result);
        goto FINALLY;
    }

    // set data
    //frame = cv::imread("et.bmp", CV_LOAD_IMAGE_COLOR);

    result = NFaceSetImage(hFace, hImage);
    if (NFailed(result))
    {
        result = PrintErrorMsgWithLastError(N_T("NFaceSetImage() failed (result = %d)!"), result);
        goto FINALLY;
    }

    // set the face for the subject
    result = NSubjectAddFace(hSubject, hFace, NULL);
    if(NFailed(result)){
        result = PrintErrorMsgWithLastError(N_T("NSubjectAddFace() failed (result = %d)!"), result);
        goto FINALLY;
    }

    // create biometric client

    result = NBiometricClientCreate(&hBiometricClient);
    if(NFailed(result)){
        result = PrintErrorMsgWithLastError(N_T("NBiometricClientCreate() failed (result = %d)!"), result);
        goto FINALLY;
    }



   // set template size to large

    result = NObjectSetPropertyP(hBiometricClient, N_T("Faces.TemplateSize"), N_TYPE_OF(NTemplateSize), naNone, &templateSize, sizeof(templateSize), 1, NTrue);
    if (NFailed(result)) {
        result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
        goto FINALLY;
    }

    if (hasEx) {
        // set detect all facial features
        result = NObjectSetPropertyP(hBiometricClient, N_T("Faces.DetectAllFeaturePoints"), N_TYPE_OF(NBoolean), naNone, &parameter, sizeof(parameter), 1, NTrue);
        if(NFailed(result)){
            result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
            goto FINALLY;
        }
    }

    // create template


    result = NBiometricEngineCreateTemplate(hBiometricClient, hSubject, &biometricsStatus);
    if(NFailed(result)){
        result = PrintErrorMsgWithLastError(N_T("NBiometricEngineCreateTemplate() failed (result = %d)!"), result);
        goto FINALLY;
    }

    if(biometricsStatus == nbsOk){
        std::cout << "template extracted" << std::endl;
        // retrieve the template from subject

        result = NSubjectGetTemplateBuffer(hSubject, hBuffer);
        if(NFailed(result)){
            result = PrintErrorMsgWithLastError(N_T("NSubjectGetTemplateBuffer() failed (result = %d)!"), result);
            goto FINALLY;
        }
    }
FINALLY:
    {
    //    // free
        result = NObjectSet(NULL, (HNObject *)&hSubject);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result);
        }
        result = NObjectSet(NULL, (HNObject *)&hFace);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result);
        }

        result = NObjectSet(NULL, (HNObject *)&hBiometricClient);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result);
        }

        result = NObjectSet(NULL, (HNObject *)&hImage);
        if (NFailed(result))
        {
            PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result);
        }
    }

    return result;
}
