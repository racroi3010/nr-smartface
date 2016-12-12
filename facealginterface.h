#ifndef FACEALGINTERFACE
#define FACEALGINTERFACE
// OPENCV
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/gpu/gpu.hpp>
//QT
#include <QDir>
#include <qdebug.h>
#include "engineparams.h"
class FaceAlgInterface{
public:
    virtual bool imageReg(QString userName, cv::Mat& frame) = 0;
    virtual QString imageCmp(cv::Mat& frame) = 0;
    virtual cv::Rect faceDetect(cv::Mat& frame) = 0;
    virtual bool LoadFeatures(const char* lpPath, int iAlg) = 0;
    virtual bool prepare()=0;


    virtual bool close() = 0;

    virtual bool checkLicense() = 0;
    virtual EngineParams getEngineParams() = 0;
    bool saveImage(cv::Mat& frame, QString userName){
        cv::cvtColor(frame, frame, CV_BGR2RGB);
        QString path = QDir::currentPath() + "/history/" + userName + ".bmp";
        cv::imwrite(path.toStdString(), frame);
        return true;
    }


};

#endif // FACEALGINTERFACE

