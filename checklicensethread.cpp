#include "checklicensethread.h"

CheckLicenseThread::CheckLicenseThread()
{
}

void CheckLicenseThread::run(){
    QProcess process;
    process.start("./" + QDir::currentPath() + "/license/pgd");
    emit startValidateLicense();
    sleep(2000);
    bool rs = FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->checkLicense();
    emit validateLicense(rs);
}

