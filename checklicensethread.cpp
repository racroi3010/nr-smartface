#include "checklicensethread.h"

CheckLicenseThread::CheckLicenseThread()
{
}

void CheckLicenseThread::run(){
    emit startValidateLicense();
    bool rs = FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->checkLicense();
    emit validateLicense(rs);
}

