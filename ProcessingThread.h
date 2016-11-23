#ifndef PROCESSINGTHREAD_H
#define PROCESSINGTHREAD_H

// OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
// Local
#include "Buffer.h"
#include "SharedImageBuffer.h"
#include "MatToQImageUtil.h"
#include "FixedQThread.h"
#include "Constants.h"

// Qt
#include <QtCore/QThread>
#include <QtCore/QTime>
#include <QtCore/QQueue>
#include <QImage>

#include "faceenginebuilder.h"


class ProcessingThread : public FixedQThread
{
    Q_OBJECT

    public:
        ProcessingThread(SharedImageBuffer *sharedImageBuffer, int deviceNumber);
        ~ProcessingThread();

        void stop();
        void setMode(int mode);
        //bool checkLicense();
        bool registerUser(QString userNumber, cv::Mat& frame, QString &msg);
        bool saveImage(cv::Mat& frame, QString userNumber);
        bool checkFace(cv::Mat& frame);

        static int MODE_FACE_DETECT;
        static int MODE_FACE_RECOGN;
    private:
        bool isStop;
        SharedImageBuffer *sharedImageBuffer;
        Mat currentFrame;

        QMutex doStopMutex;
        QMutex processingMutex;

        volatile bool doStop;

        int proMode;

//        FaceAlgInterface * faceAlg;
        int deviceNumber;
        QString featurePath;

//        void updateFPS(int);
//        void setROI();
//        void resetROI();
//        Mat currentFrameGrayscale;
//        Rect currentROI;
//        QImage frame;
//        QTime t;
//        QQueue<int> fps;
//        Size frameSize;
//        Point framePoint;
//        int fpsSum;
//        int sampleNumber;
//        int processingTime;
//        bool enableFrameProcessing;



    protected:
        void run();

    signals:
        void newFace(const QRect &rect);
        void newUser(const QString &user);
};

#endif // PROCESSINGTHREAD_H
