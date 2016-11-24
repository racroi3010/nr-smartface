#ifndef CHECKLICENSETHREAD_H
#define CHECKLICENSETHREAD_H

#include "FixedQThread.h"
#include "faceenginebuilder.h"
#include <QMessageBox>
#include <QProcess>
class CheckLicenseThread: public FixedQThread
{
    Q_OBJECT
public:
    CheckLicenseThread();
    void run();
signals:
    void validateLicense(bool result);
    void startValidateLicense();
};

#endif // CHECKLICENSETHREAD_H
