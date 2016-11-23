#ifndef NEOFACEALG_H
#define NEOFACEALG_H
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <errno.h>


// SMART FACE
#include "NeoFaceM.h"
#include "feature.h"
#include "preferencehandler.h"

// OPENCV
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/gpu/gpu.hpp>


//QT
#include <QDir>
#include <qdebug.h>

//
#include "facealginterface.h"

#define		TEXT_COLOR	Scalar(0,0,255)
#define		FEATURE_MAX_COUNT	100
#define		FEATURE_SIZE		5048	// 5047  or  2531  or  527
#define		FEATURE_SIZE_MIN	527		// minimum


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FILE_NAME_MAX 200

/////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32) || defined (_WIN64)
    CWinApp theApp;
#else
    #define strcpy_s(a, b)                        strcpy(a, b)

    #define ZeroMemory(a,b)                   memset((a), 0, (b))
    #define LPCTSTR            char*
    #define CString            std::string
#endif

typedef struct tagBITMAPFILEHEADER {
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
} BITMAPFILEHEADER;


using namespace std;
using namespace cv;
using namespace NeoFaceM;

class NeoFaceAlg: public FaceAlgInterface
{
public:
    bool imageReg(QString userName, cv::Mat& frame);
    QString imageCmp(cv::Mat& frame);
    Rect faceDetect(cv::Mat& frame);
    bool LoadFeatures(const char* lpPath, int iAlg);
    //bool saveImage(cv::Mat& frame, QString userName);


    bool close();

    bool checkLicense();
private:
    char* CT2A(LPCTSTR x);

    const char* CT2A(CString x);
    /**
     * Serialize the feature which is given as first argment.
     * And output the file which name is given as second argment.
     *
     */
    bool SerializeFeature(CFaceFeature *fet,char* fileName); //VA»
    /**
     * Input the specified feature file.
     *
     */
    void* ReadTargetFetData(char* fileName); //??Qbgf??ðÇÞ
    /**
     * Load the bitmap file.
     *
     */
    int LoadBMP(char* pFileName, BITMAPINFO &info, void **body);  //bmpð?h·é




    /**
     * Create Compound feature file.
     *
     */
    bool MakeDBFetFile(feature *fet, int iAlg);
    /**
     * Create the Feature file for target side.
     * This feature file can use for entry in the DB.
     *
     */
    bool EnrollCompoundFeatures(vector<feature *> &Features, char* lpPath, int iAlg);  //¡Á¥ðLü·é
    /**
     * Create the feature for query side.
     *
     */
    CFaceFeature* MakeQueryFetObj(feature *fet, int iAlg);

    /**
     * Execute face verification
     */
    bool Verify(vector<feature *> features, int iAlg);

    void DeleteArray(vector<feature *> arrayFeature);  //ððú·é
    /**
     * Main function.
     *
     */


    //int CImageControl::IplImageToBitmap(IplImage * pImage, BITMAPFILEHEADER * pbfHeader, BITMAPINFO * pBmpInfo, void ** ppVoid, bool bFlipped)
    int IplImageToBitmap(IplImage * pImage, BITMAPFILEHEADER * pbfHeader, BITMAPINFO * pBmpInfo, void ** ppVoid, bool bFlipped);


    /**
     * Create Compound feature
     *
     */
    int MakeFeature(BITMAPINFO * pBmpInfo, void * pVoidBody, void * CamFeature, long * plSize, int iAlg );


    /**
     * Create Compound feature file - from Cam image.
     *
     */
    bool MakeDBFetFile2( BITMAPINFO * pBmpInfo, void * pVoidBody, Mat frame, int iAlg, QString userName);


    /**
      * Score Check
      */
    bool MakeFeature(BITMAPINFO * pBmpInfo, void * pVoidBody, void * CamFeature, long * plSize, RECT* rctFace, int iAlg);

    //properties
    BYTE	gFeatureBuffer[FEATURE_MAX_COUNT][FEATURE_SIZE];
    char	gFeatureName[FEATURE_MAX_COUNT][256];
    int		gFeatureCnt;
    long	gFileSize;
};

#endif // NEOFACEALG_H
