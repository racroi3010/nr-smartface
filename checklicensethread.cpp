#include "checklicensethread.h"

CheckLicenseThread::CheckLicenseThread()
{
}

void CheckLicenseThread::run(){
    QProcess process;
    process.start("./pgd");
    emit startValidateLicense();
    sleep(1);
    bool rs = FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->checkLicense();
    emit validateLicense(rs);
}

