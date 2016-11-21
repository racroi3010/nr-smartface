#include "ProcessingThread.h"
int ProcessingThread::MODE_FACE_DETECT = 0;
int ProcessingThread::MODE_FACE_RECOGN = 1;
ProcessingThread::ProcessingThread(SharedImageBuffer *sharedImageBuffer, int deviceNumber) : FixedQThread(),
    sharedImageBuffer(sharedImageBuffer)
{
    // Save Device Number
    this->deviceNumber=deviceNumber;
    // Initialize members
    this->doStop=false;
    this->isStop = false;

#ifdef USE_NEOFACE
    this->faceAlg = new NeoFaceAlg();
#elif defined(USE_NEURO)
    this->faceAlg = new NeuroAlg();
#endif

    featurePath = QDir::currentPath() + "/feature/";
    this->faceAlg->LoadFeatures(featurePath.toStdString().c_str(), 0);
}
ProcessingThread::~ProcessingThread()
{
    stop();

}

void ProcessingThread::run()
{
    while(1)
    {
        ////////////////////////////////
        // Stop thread if doStop=TRUE //
        ////////////////////////////////
        this->doStopMutex.lock();
        if(this->doStop)
        {
            this->doStop=false;
            this->doStopMutex.unlock();
            this->faceAlg->close();
            break;
        }
        this->doStopMutex.unlock();
        /////////////////////////////////
        /////////////////////////////////

        this->processingMutex.lock();
        // Get frame from queue, store in currentFrame, set ROI
        QString msg = "";
        this->currentFrame=this->sharedImageBuffer->getByDeviceNumber(this->deviceNumber)->get().clone();
        cv::Rect face = this->faceAlg->faceDetect(currentFrame);
        QRect rect(face.x, face.y, face.width, face.height);
        emit newFace(rect);

        //QString userName = this->faceAlg->imageCmp(currentFrame);
        //qDebug() << msg + "\n";
        //emit newUser(userName);


        this->processingMutex.unlock();
    }
    qDebug() << "Stopping processing thread...";
}



void ProcessingThread::stop()
{
    QMutexLocker locker(&doStopMutex);
    this->doStop=true;
}
void ProcessingThread::setMode(int mode)
{
    this->proMode = mode;
}
bool ProcessingThread::checkLicense()
{
    return this->faceAlg->checkLicense();
}
bool ProcessingThread::registerUser(QString userNumber, cv::Mat& frame, QString &msg)
{
    return this->faceAlg->imageReg(userNumber, frame);
}
bool ProcessingThread::saveImage(cv::Mat& frame, QString userNumber)
{
    return this->faceAlg->saveImage(frame, userNumber);
}
bool ProcessingThread::checkFace(cv::Mat& frame)
{
    cv::Rect face = this->faceAlg->faceDetect(frame);
    if(face.width == 0 || face.height == 0)
    {
        return false;
    }
    return true;
}

