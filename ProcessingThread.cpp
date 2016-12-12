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

//#ifdef USE_NEOFACE
//    this->faceAlg = new NeoFaceAlg();
//#elif defined(USE_NEURO)
//    this->faceAlg = new NeuroAlg();
//#endif

    featurePath = QDir::currentPath() + "/feature/";
    FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->LoadFeatures(featurePath.toStdString().c_str(), 0);
    FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->prepare();
}
ProcessingThread::~ProcessingThread()
{
    stop();

}

void ProcessingThread::run()
{
    cv::Mat imgTemp;
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
            break;
        }
        this->doStopMutex.unlock();
        /////////////////////////////////
        /////////////////////////////////

        this->processingMutex.lock();
        // Get frame from queue, store in currentFrame, set ROI
        QString msg = "";
        this->currentFrame=this->sharedImageBuffer->getByDeviceNumber(this->deviceNumber)->get();
#ifdef USE_NEURO
        cv::cvtColor(this->currentFrame, imgTemp, CV_BGR2RGB);
#endif
        try {
            cv::Rect face = FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->faceDetect(imgTemp);
            QRect rect(face.x, face.y, face.width, face.height);
            emit newFace(rect);

            if(rect.width() > 0){
                QString userName = FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->imageCmp(imgTemp);
                qDebug() << msg + "\n";
                emit newUser(userName);
            }
        } catch (...) {
            qDebug() << "Exception faceDetect\n";
        }

        if(imgTemp.data){
            imgTemp.release();
        }
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
bool ProcessingThread::registerUser(QString userNumber, cv::Mat& frame, QString &msg)
{
    return FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->imageReg(userNumber, frame);
}
bool ProcessingThread::saveImage(cv::Mat& frame, QString userNumber)
{
    return FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->saveImage(frame, userNumber);
}
bool ProcessingThread::checkFace(cv::Mat& frame)
{
    cv::Rect face = FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->faceDetect(frame);
    if(face.width == 0 || face.height == 0)
    {
        return false;
    }
    return true;
}

