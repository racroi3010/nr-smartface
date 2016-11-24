#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H
//QT
#include <QtCore/QTime>
#include <QtCore/QThread>
#include <QImage>
// OPENCV
#include "opencv2/highgui/highgui.hpp"

// HELLOCV
#include "SharedImageBuffer.h"
#include "FixedQThread.h"

class CameraThread: public FixedQThread
{
    Q_OBJECT
public:

    CameraThread(int deviceNumber);
    CameraThread(int deviceNumber, SharedImageBuffer * sharedImageBuffer);
    ~CameraThread();
    bool connectToCamera();
    bool disconnectCamera();
    bool stop();
    bool checkStop();
    int getCamWidth();
    int getCamHeight();

    void takePicture(cv::Mat& frame);
    void pause();
    void resume();
    void setBuffer(SharedImageBuffer *buffer);

    static CameraThread * getInstance(int deviceNumber);
    static int video_width;
    static int video_height;
private:
    int deviceNumber;
    cv::VideoCapture cap;
    QMutex doStopMutex;
    QMutex doPauseMutex;
    volatile bool isStop;
    volatile bool isPause;
    int camWidth;
    int camHeight;
    static CameraThread *ct;
    SharedImageBuffer * sharedImageBuffer;
protected:
    void run();

signals:
    void newFrame(QImage& image);
};
#endif // CAMERATHREAD_H
