#ifndef CHECKLICENSETHREAD_H
#define CHECKLICENSETHREAD_H

#include "FixedQThread.h"
#include "faceenginebuilder.h"
class CheckLicenseThread: public FixedQThread
{
    Q_OBJECT
public:
    CheckLicenseThread();
    void run();
signals:
    void checkLicense(bool result);
};

#endif // CHECKLICENSETHREAD_H
