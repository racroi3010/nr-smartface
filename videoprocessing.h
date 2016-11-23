#ifndef VIDEOPROCESSING_H
#define VIDEOPROCESSING_H
// SMART FACE
#include "CameraThread.h"
#include "ProcessingThread.h"
#include "SharedImageBuffer.h"
#include "BaseDialog.h"
#include "UserUtil.h"

// QT
#include <qdebug.h>
class VideoProcessing: public QObject
{
    Q_OBJECT
public:
    VideoProcessing(BaseDialog *dialog);
    ~VideoProcessing();
    void init();
    bool start();
    void close();
    bool isRunning();
    bool capture(cv::Mat &image);
    void shot(cv::Mat &image);
    void resumeCam();
    bool registerUser(QString userNumber, QString userName, cv::Mat image, QString &msg);
    bool saveImage(cv::Mat& image, QString userNumber);
    bool checkExistUser(QString userNumber);
    //bool checkFaceLicense();
private:
    BaseDialog *mDialog;
    int deviceId;
    bool isCameraConnected;

    QMutex doStopMutex;

    CameraThread *cameraThread;
    ProcessingThread *processingThread;
    SharedImageBuffer *sharedImageBuffer;

    void stopProcessingThread();
    void stopCameraThread();
};

#endif // VIDEOPROCESSING_H
