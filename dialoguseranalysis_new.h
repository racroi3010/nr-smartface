#ifndef DIALOGUSERANALYSIS_NEW_H
#define DIALOGUSERANALYSIS_NEW_H

// SMART FACE
#include "CameraThread.h"
#include "ProcessingThread.h"
#include "SharedImageBuffer.h"
#include "Constants.h"
#include "imagelabel.h"
#include "BaseDialog.h"
#include "videoprocessing.h"
#include "dialoguserlisthist.h"
#include "dialogmatching.h"

// QT
#include <QDialog>
#include <QVBoxLayout>
#include <QPainter>
#include <QRect>
#include <QTimer>

namespace Ui {
class DialogUserAnalysis_New;
}

class DialogUserAnalysis_New : public BaseDialog
{
    Q_OBJECT

public:
    explicit DialogUserAnalysis_New(QWidget *parent = 0);
    ~DialogUserAnalysis_New();
protected slots:
    void updateFrame(QImage& qImage);
    void updateUser(QString user);
    void updateFace(QRect rect);
private slots:
    void on_btnMenu_clicked();

    void on_btnUserList_clicked();

private:
    Ui::DialogUserAnalysis_New *ui;
    VideoProcessing *vProcessing;
    DialogMatching *d;
    QRect currentFace;
    QString currentUserNumber;
    cv::Mat currentImage;
};

#endif // DIALOGUSERANALYSIS_NEW_H
