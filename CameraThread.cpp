#include "CameraThread.h"
CameraThread * CameraThread::ct = 0;
int CameraThread::video_width = 320;
int CameraThread::video_height = 240;
CameraThread::CameraThread(int deviceNumber)
{
    this->deviceNumber =  deviceNumber;
    this->isStop = false;
    this->isPause = false;
}
CameraThread::CameraThread(int deviceNumber, SharedImageBuffer * sharedImageBuffer) : FixedQThread()
  , deviceNumber(deviceNumber)
  ,  sharedImageBuffer(sharedImageBuffer)
{
    this->isStop = false;
    this->isPause = false;
}
CameraThread::~CameraThread()
{
    stop();
    disconnectCamera();
}
CameraThread * CameraThread::getInstance(int deviceNumber)
{
    if(ct == 0)
    {
        ct = new CameraThread(deviceNumber);
    }
    return ct;
}

bool CameraThread::connectToCamera()
{
    bool flag = cap.open(deviceNumber);
//    this->cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
//    this->cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    this->camWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    this->camHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    return flag;
}
int CameraThread::getCamWidth()
{
    return this->camWidth;
}
int CameraThread::getCamHeight()
{
    return this->camHeight;
}
bool CameraThread::disconnectCamera()
{
   if(cap.isOpened())
   {
       cap.release();
       return true;
   }
   return false;
}
void CameraThread::run()
{
    bool flag;
    cv::Mat frame;
    while(1)
    {
        ////////////////////////////////
        // Stop thread if doStop=TRUE //
        ////////////////////////////////
        doStopMutex.lock();
        if(isStop)
        {
            isStop=false;
            doStopMutex.unlock();
            break;
        }
        doStopMutex.unlock();
        /////////////////////////////////


        flag = cap.read(frame);

        if(!flag) continue;

        sharedImageBuffer->getByDeviceNumber(deviceNumber)->add(frame, true);

        /////////////////////////////////
        // pause
        doPauseMutex.lock();
        if(this->isPause)
        {
            doPauseMutex.unlock();
            continue;
        }
        doPauseMutex.unlock();


        cv::cvtColor(frame, frame, CV_BGR2RGB);
        QImage qImage(frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
        emit newFrame(qImage);
    }
}
bool CameraThread::stop()
{
    QMutexLocker locker(&doStopMutex);
    isStop=true;
    return true;
}
void CameraThread::pause()
{
    QMutexLocker locker(&doPauseMutex);
    this->isPause = true;
}
void CameraThread::resume()
{
    QMutexLocker locker(&doPauseMutex);
    this->isPause = false;
}

void CameraThread::takePicture(cv::Mat& frame)
{
//    if(cap.isOpened())
//    {
//        cap.read(frame);
//    }
    frame = this->sharedImageBuffer->getByDeviceNumber(this->deviceNumber)->get().clone();
}
void CameraThread::setBuffer(SharedImageBuffer *buffer)
{
    this->sharedImageBuffer = buffer;
}
