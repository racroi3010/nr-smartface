#include "videoprocessing.h"

VideoProcessing::VideoProcessing(BaseDialog *dialog): mDialog(dialog)
{
    deviceId = 0;
    isCameraConnected = false;
    init();
}
VideoProcessing::~VideoProcessing()
{

}

void VideoProcessing::init()
{
    sharedImageBuffer = new SharedImageBuffer();
    Buffer<Mat> *imageBuffer = new Buffer<Mat>(24);
    sharedImageBuffer->add(0, imageBuffer, false);

    cameraThread = new CameraThread(deviceId, sharedImageBuffer);
    processingThread = new ProcessingThread(sharedImageBuffer, deviceId);

    connect(cameraThread, SIGNAL(reallyFinished()), cameraThread, SLOT(deleteLater()));
    connect(processingThread, SIGNAL(reallyFinished()), processingThread, SLOT(deleteLater()));

}
bool VideoProcessing::start()
{
    if(!cameraThread->connectToCamera())
    {
        qDebug() << "Connecting Camera Error \n";
        return false;
    }
    else
    {
        isCameraConnected = true;
        qDebug() << "Connecting Camera Success \n";
        cameraThread->start();
        processingThread->start();

        connect(cameraThread, SIGNAL(newFrame(QImage)), mDialog, SLOT(updateFrame(QImage)));
        if(processingThread->checkLicense())
        {

            //processingThread->setMode(ProcessingThread::MODE_FACE_DETECT);
            connect(processingThread, SIGNAL(newFace(QRect)), mDialog, SLOT(updateFace(QRect)));
            connect(processingThread, SIGNAL(newUser(QString)), mDialog, SLOT(updateUser(QString)));
        }
        else
        {
            return false;
        }


    }
    return true;
}
bool VideoProcessing::capture(cv::Mat &image)
{
    if(image.data)
    {
        cameraThread->resume();
        image.data = NULL;
        return true;
    }
    else
    {
        cameraThread->pause();
        cameraThread->takePicture(image);
        if(!processingThread->checkFace(image))
        {
            image.data = NULL;
            return false;
        }
        return true;
    }

}
void VideoProcessing::shot(cv::Mat &image)
{
    cameraThread->takePicture(image);
}

void VideoProcessing::resumeCam()
{
    cameraThread->resume();
}
bool VideoProcessing::checkFaceLicense()
{
    return processingThread->checkLicense();
}

bool VideoProcessing::registerUser(QString userNumber, QString userName, cv::Mat image, QString &msg)
{
    if(processingThread->registerUser(userNumber, image, msg))
    {
        return UserUtil::getInstance()->saveUserDom(userNumber, userName);
    }
    return false;
}
bool VideoProcessing::saveImage(cv::Mat& image, QString userNumber)
{
    if(processingThread->saveImage(image, userNumber))
    {
       return UserUtil::getInstance()->saveHistDom(userNumber);
    }
    return false;
}

bool VideoProcessing::checkExistUser(QString userNumber)
{
    return UserUtil::getInstance()->checkExist(userNumber);
}

void VideoProcessing::close()
{
    if(isCameraConnected)
    {
        // have to disconnect before quit thread
        disconnect(cameraThread, SIGNAL(newFrame(QImage)), mDialog, SLOT(updateFrame(QImage)));
        disconnect(processingThread, SIGNAL(newUser(QString)), mDialog, SLOT(updateUser(QString)));

        // Stop processing thread
        if(processingThread->isRunning())
            stopProcessingThread();

        // Stop capture thread
        if(cameraThread->isRunning())
            stopCameraThread();


        // Automatically start frame processing (for other streams)
        if(sharedImageBuffer->isSyncEnabledForDeviceNumber(deviceId))
            sharedImageBuffer->setSyncEnabled(true);

        // Remove from shared buffer
        sharedImageBuffer->removeByDeviceNumber(deviceId);
        // Disconnect camera
        if(cameraThread->disconnectCamera())
            qDebug() << "[" << deviceId << "] Camera successfully disconnected.";
        else
            qDebug() << "[" << deviceId << "] WARNING: Camera already disconnected.";

        isCameraConnected = false;

    }

}
void VideoProcessing::stopProcessingThread()
{
    processingThread->stop();
    sharedImageBuffer->wakeAll(); // This allows the thread to be stopped if it is in a wait-state
    processingThread->wait();
}
void VideoProcessing::stopCameraThread()
{
    cameraThread->stop();
    sharedImageBuffer->wakeAll(); // This allows the thread to be stopped if it is in a wait-state
    // Take one frame off a FULL queue to allow the capture thread to finish
    if(sharedImageBuffer->getByDeviceNumber(deviceId)->isFull())
        sharedImageBuffer->getByDeviceNumber(deviceId)->get();
    cameraThread->wait();
}
bool VideoProcessing::isRunning()
{
    return isCameraConnected;
}
