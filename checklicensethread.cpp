#include "checklicensethread.h"

CheckLicenseThread::CheckLicenseThread()
{
}

void CheckLicenseThread::run(){
    QProcess process;
    process.start(QDir::currentPath() + "/license/pgd");
    process.waitForBytesWritten();
    if(!process.waitForFinished(2)){
        process.kill();
        process.waitForFinished(2);
    }
    emit startValidateLicense();
    bool rs = FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->checkLicense();
    emit validateLicense(rs);
}

