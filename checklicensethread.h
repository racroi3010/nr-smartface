#ifndef CHECKLICENSETHREAD_H
#define CHECKLICENSETHREAD_H

#include "FixedQThread.h"
#include "faceenginebuilder.h"
#include <QMessageBox>
class CheckLicenseThread: public FixedQThread
{
    Q_OBJECT
public:
    CheckLicenseThread(QMessageBox *msgBox);
    void run();
signals:
    void validateLicense(bool result);
};

#endif // CHECKLICENSETHREAD_H
