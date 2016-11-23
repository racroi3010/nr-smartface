#include "checklicensethread.h"

CheckLicenseThread::CheckLicenseThread()
{

}

void CheckLicenseThread::run(){
    bool rs = FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->checkLicense();
    emit checkLicense(rs);
}

