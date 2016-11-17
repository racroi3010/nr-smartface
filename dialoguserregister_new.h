#ifndef DIALOGUSERREGISTER_NEW_H
#define DIALOGUSERREGISTER_NEW_H

// SMART FACE
#include "CameraThread.h"
#include "ProcessingThread.h"
#include "SharedImageBuffer.h"
#include "Constants.h"
#include "BaseDialog.h"
#include "videoprocessing.h"
#include "dialoguserlist_new.h"
#include "dialoguserlisthist.h"

// QT
#include <QDialog>
#include <QVBoxLayout>
#include <QDateTime>
#include <QMessageBox>
#include <QPainter>

namespace Ui {
class DialogUserRegister_new;
}

class DialogUserRegister_new : public BaseDialog
{
    Q_OBJECT

public:
    explicit DialogUserRegister_new(QWidget *parent = 0);
    ~DialogUserRegister_new();

protected slots:
    void updateFrame(QImage qImage);
    void updateUser(QString user);
    void updateFace(QRect rect);

private slots:

    void on_btnMenu_clicked();

    void on_btnUserList_clicked();

    void on_btnSave_clicked();

    void on_btnCapture_clicked();

private:
    Ui::DialogUserRegister_new *ui;

    VideoProcessing *vProcessing;

    cv::Mat capImage;
    QRect currentFace;


};

#endif // DIALOGUSERREGISTER_NEW_H
