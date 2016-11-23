#include "checklicensethread.h"

CheckLicenseThread::CheckLicenseThread(QMessageBox *msgBox)
{
    if(msgBox){
        msgBox->setModal(true);
        msgBox->show();
    }
}

void CheckLicenseThread::run(){
    bool rs = FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->checkLicense();
    emit validateLicense(rs);
}

