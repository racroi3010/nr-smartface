#include "neofacealg.h"

NeoFaceAlg::NeoFaceAlg()
{

}
bool NeoFaceAlg::SerializeFeature(CFaceFeature *fet,char* fileName) //VA»
{
#ifdef USE_NEOFACE
    void *data;
    long size;

    // Serialize the Compound feature.
    int iRet = 0;
#ifdef USE_NEOFACE
    iRet = fet->Serialize(&data, &size, NFP_SERIALIZETYPE_COMPOUND);
#endif
    if(iRet != NFP_SUCCESS)
    {
        fprintf(stderr,"Serialize error.\n");
        return false;
    }

    char cBuf[128];
    FILE* fd = fopen(fileName, "wb");
    if(fd == 0)
    {
        strcpy_s(cBuf, CT2A((LPCTSTR)fileName));
        fprintf(stderr,"[%s] cannot open file.\n",cBuf);
        return false;
    }
    // Output the Compound feature.
    size_t szRet = fwrite(data,1,size,fd);
    if((long)szRet != size)
    {
        strcpy_s(cBuf, CT2A((LPCTSTR)fileName));
        fprintf(stderr,"[%s] cannot write file.\n",fileName);
        return false;
    }

    fclose(fd);

#ifdef USE_NEOFACE
    // Free serealized data.
    fet->FreeSerializeData(data);

#endif
#endif
    return true;
}
/**
 * Input the specified feature file.
 *
 */
void* NeoFaceAlg::ReadTargetFetData(char* fileName) //??Qbgf??ðÇÞ
{
#ifdef USE_NEOFACE
#if defined(_WIN32) || defined (_WIN64)
    HANDLE hr = CreateFile((LPCTSTR)fileName,
                           GENERIC_READ,
                           FILE_SHARE_READ,
                           NULL,
                           OPEN_EXISTING,
                           FILE_ATTRIBUTE_NORMAL,
                           NULL);

    // Get the file size of feature file.
    DWORD size = GetFileSize(hr,NULL);
    CloseHandle(hr);
    if(size < 0)
    {
        return NULL;
    }
#else
    struct stat buf;
    if(stat(fileName, &buf)<0)
    {
        return NULL;
    }
    if(buf.st_size < 0)
    {
        return NULL;
    }

    unsigned long size = buf.st_size;
#endif
    // Allocate the memory of feature file.
    char cBuf[128];
    void *data = malloc(size);
    if(data == NULL)
    {
        fprintf(stderr, "malloc failed\n");
        return NULL;
    }

    FILE* fd = fopen(fileName, "rb");
    if(fd == 0)
    {
        strcpy_s(cBuf, CT2A((LPCTSTR)fileName));
        fprintf(stderr,"[%s] cannot open file.\n",cBuf);
        free(data);
        return NULL;
    }
    // Read the feature file.
    size_t szRet = fread(data,1,size,fd);
    if(szRet != size)
    {
        strcpy_s(cBuf, CT2A((LPCTSTR)fileName));
        fprintf(stderr,"[%s] cannot read file.\n",cBuf);
        fclose(fd);
        free(data);
        return NULL;
    }

    fclose(fd);

    return data;
#endif
    return NULL;
}

/**
 * Load the bitmap file.
 *
 */
int NeoFaceAlg::LoadBMP(char* pFileName, BITMAPINFO &info, void **body)  //bmpð?h·é
{
#ifdef USE_NEOFACE
    char cBuf[128];
    FILE* fh = fopen(pFileName, "rb");

    if (fh <= 0)
    {
        fprintf(stderr,"cannot open file. File=%s detail=%s\n",pFileName,strerror(errno));
        return -1;
    }

    BITMAPFILEHEADER bitmapFileHeader;
    BITMAPINFO bitmapInfo;
    size_t dwRead;

    ZeroMemory(&bitmapFileHeader,sizeof(bitmapFileHeader));
    ZeroMemory(&bitmapInfo, sizeof(bitmapInfo));

    // Read the file headder.
    if(fread(&bitmapFileHeader.bfType,sizeof(WORD),1,fh)!=1)
    {
        printf("Error(readBmpFileHeader): can not read the bfType of the File Header.\n");
        fclose(fh);
        return -1;
    }

    if(fread(&bitmapFileHeader.bfSize,sizeof(DWORD),1,fh)!=1)
    {
        printf("Error(readBmpFileHeader): can not read the bfSize of the File Header.\n");
        fclose(fh);
        return -1;
    }

    if(fread(&bitmapFileHeader.bfReserved1,sizeof(WORD),1,fh)!=1)
    {
        printf("Error(readBmpFileHeader): can not read the bfReserved1 of the File Header.\n");
        fclose(fh);
        return -1;
    }

    if(fread(&bitmapFileHeader.bfReserved2,sizeof(WORD),1,fh)!=1)
    {
        printf("Error(readBmpFileHeader): can not read the bfReserved2 of the File Header.\n");
        fclose(fh);
        return -1;
    }

    if(fread(&bitmapFileHeader.bfOffBits,sizeof(DWORD),1,fh)!=1)
    {
        printf("Error(readBmpFileHeader): can not read the bfOffBits of the File Header.\n");
        fclose(fh);
        return -1;
    }

    // Check if "BM" is exist.(For little endian).
    if(bitmapFileHeader.bfType != 'B'+0x100*'M')
    {
        //?Specific file is not bitmap.
        strcpy_s(cBuf, CT2A((LPCTSTR)pFileName));
        fprintf(stderr,"Illegal Format. File=%s\n",cBuf);
        fclose(fh);
        return -1;
    }

    // Read the bitmap headder.
    fseek(fh,14,SEEK_SET);

    if(fread(&bitmapInfo.bmiHeader.biSize,sizeof(DWORD),1,fh)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biSize of the Info Header.\n");
        fclose(fh);
        return -1;
    }

    if(fread(&bitmapInfo.bmiHeader.biWidth,sizeof(DWORD),1,fh)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biWidth of the Info Header.\n");
        fclose(fh);
        return -1;
    }

    if(fread(&bitmapInfo.bmiHeader.biHeight,sizeof(DWORD),1,fh)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biHeight of the Info Header.\n");
        fclose(fh);
        return -1;
    }

    if(fread(&bitmapInfo.bmiHeader.biPlanes,sizeof(WORD),1,fh)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biPlanes of the Info Header.\n");
        fclose(fh);
        return -1;
    }

    if(fread(&bitmapInfo.bmiHeader.biBitCount,sizeof(WORD),1,fh)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biBitCount of the Info Header.\n");
        fclose(fh);
        return -1;
    }

    if(fread(&bitmapInfo.bmiHeader.biCompression,sizeof(DWORD),1,fh)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biCompression of the Info Header.\n");
        fclose(fh);
        return -1;
    }

    if(fread(&bitmapInfo.bmiHeader.biSizeImage,sizeof(DWORD),1,fh)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biSizeImage of the Info Header.\n");
        fclose(fh);
        return -1;
    }

    if(fread(&bitmapInfo.bmiHeader.biXPelsPerMeter,sizeof(DWORD),1,fh)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biXPelsPerMeter of the Info Header.\n");
        fclose(fh);
        return -1;
    }

    if(fread(&bitmapInfo.bmiHeader.biYPelsPerMeter,sizeof(DWORD),1,fh)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biYPelsPerMeter of the Info Header.\n");
        fclose(fh);
        return -1;
    }

    if(fread(&bitmapInfo.bmiHeader.biClrUsed,sizeof(DWORD),1,fh)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biClrUsed of the Info Header.\n");
        fclose(fh);
        return -1;
    }

    if(fread(&bitmapInfo.bmiHeader.biClrImportant,sizeof(DWORD),1,fh)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biClrImportant of the Info Header.\n");
        fclose(fh);
        return -1;
    }

    info = bitmapInfo;
    if(bitmapInfo.bmiHeader.biBitCount != 24)
    {
        // 24bit BITMAP.
        fprintf(stderr, "bitmap is not 24bit format");
        return -1;
    }

    // Read the image which image width is multiples of 4.
    if((info.bmiHeader.biWidth%4) != 0)
    {
        fprintf(stderr, "bitmap width is invalid");
        return -1;
    }

    DWORD dwImageSize = info.bmiHeader.biWidth*
                        info.bmiHeader.biHeight *
                        info.bmiHeader.biBitCount/8;

    *body = malloc(dwImageSize);

    if(body == NULL)
    {
        fprintf(stderr, "malloc failed\n");
        return -1;
    }

    info.bmiHeader.biSizeImage = dwImageSize;

    // Seek
    fseek(fh, bitmapFileHeader.bfOffBits, SEEK_SET);

    // Read the bitmap data.
    dwRead = fread(*body, 1, dwImageSize, fh);

    if(dwImageSize != dwRead)
    {
        // Error about reading file.
        strcpy_s(cBuf, CT2A((LPCTSTR)pFileName));
        fprintf(stderr, "Cannot read file. File=%s\n",cBuf);
        fclose(fh);
        return -1;
    }

    fclose(fh);
#endif
    return 1;
}



/**
 * Create Compound feature file.
 *
 */
bool NeoFaceAlg::MakeDBFetFile(feature *fet, int iAlg)
{
#ifdef USE_NEOFACE
    // Load the bitmap file.
    char cBuf[128];

    BITMAPINFO binfo;
    void *body;
#if defined(_WIN32) || defined (_WIN64)
    int iRet = LoadBMP(((fet->fileName).GetBuffer()), binfo,&body);
#else
    int iRet = LoadBMP((char*)((fet->fileName).c_str()), binfo,&body);
#endif
    if(iRet < 0)
    {
        strcpy_s(cBuf, CT2A(fet->fileName));
        fprintf(stderr, "[%s] cannot open file.\n", cBuf);
        return false;
    }

    CFaceInfo *info;
    try{
        info = new CFaceInfo();
    }catch(int err){
        if(err == NFP_NOT_INITIALILZE_ERROR)
        {
            fprintf(stderr, "License Error\n");
        }
        else
        {
            fprintf(stderr, "Unknown exception\n");
        }
        free(body);
        return false;
    }

    // Set the detection parameter.
    info->SetParamAlgorithm(iAlg);
    info->SetParamEyesRoll(15);
    info->SetParamEyesMaxWidth(PreferenceHandler::getInstance()->getEyeMax());
    info->SetParamEyesMinWidth(PreferenceHandler::getInstance()->getEyeMin());
    info->SetParamReliability(PreferenceHandler::getInstance()->getRelValue());

    // Face detection.
#ifdef USE_NEOFACE
    iRet = info->FindFace(binfo, body);
#endif

    if(iRet == NFP_CANNOT_FIND_FACE)
    {
        // Face did not detected.
        strcpy_s(cBuf, CT2A(fet->fileName));
        fprintf(stdout, "[%s] cannot find face.\n", cBuf);
        delete info;
        free(body);
        return false;
    }
    else if(iRet == NFP_SUCCESS)
    {
#ifdef USE_NEOFACE
        CFaceFeature *ffet = new CFaceFeature();

        // Create the Simplex feature.
        iRet = ffet->SetFeature(info);
        if(iRet != NFP_SUCCESS)
        {
            strcpy_s(cBuf, CT2A(fet->fileName));
            fprintf(stderr, "[%s] make feature error. %d\n", cBuf, iRet);
            delete info;
            delete ffet;
            free(body);
            return false;
        }

#endif



        // Get the eye positions.
        POINT L = info->GetLeftEye();
        POINT R = info->GetRightEye();

        strcpy_s(cBuf, CT2A(fet->name));
        fprintf(stdout,"%s  L:%d,%d  R:%d,%d\n",cBuf, L.x, L.y, R.x, R.y);

        CString fetFile;
        // Output the Compound feature file.
        bool Ret = false;
#ifdef USE_NEOFACE
    #if defined(_WIN32) || defined (_WIN64)
            fetFile.Format(_T("feature\\%s.fet"), fet->name);
            bool Ret = SerializeFeature(ffet, (char*)fetFile.GetBuffer());
    #else
            fetFile = QDir::currentPath().toStdString() +"/feature/" + fet->name + ".fet";

            bool Ret = SerializeFeature(ffet, (char*)fetFile.c_str());
    #endif

        if(Ret == false)
        {
            fprintf(stderr, "serialize error\n");
            delete info;
            delete ffet;
            free(body);
            return false;
        }
        delete info;
        delete ffet;
        free(body);
        fet->fetFileName = fetFile;
#endif


    }
    else{
        strcpy_s(cBuf, CT2A(fet->name));
        fprintf(stderr,"[%s] find face error. %d\n", cBuf, iRet);
        delete info;
        free(body);
        return false;
    }
#endif
    return true;
}

/**
 * Create the Feature file for target side.
 * This feature file can use for entry in the DB.
 *
 */
bool NeoFaceAlg::EnrollCompoundFeatures(vector<feature *> &Features, char* lpPath, int iAlg)  //¡Á¥ðLü·é
{
#ifdef USE_NEOFACE
    CString str;
    bool iRet;

    Features.clear();
    //Find the Bitmap file.
    str = lpPath;
#if defined(_WIN32) || defined (_WIN64)
    str = str + "/*.bmp";
    WIN32_FIND_DATA ffData;
    HANDLE hr = FindFirstFile(str, &ffData);
    if(hr != INVALID_HANDLE_VALUE)
    {
        do
#else
    struct dirent* _dirent = 0;
    DIR *dir;
    dir =opendir(str.c_str());
    if (dir != 0)
    {
        while ((_dirent=readdir(dir))!= 0)
#endif
        {
#if defined(_WIN32) || defined (_WIN64)
#else
            int nameLength = strlen(_dirent->d_name);
            if(nameLength >= 5 &&
                (_dirent->d_name[nameLength-3] == 'b' || _dirent->d_name[nameLength-3] == 'B') &&
                (_dirent->d_name[nameLength-2] == 'm' || _dirent->d_name[nameLength-2] == 'M') &&
                (_dirent->d_name[nameLength-1] == 'p' || _dirent->d_name[nameLength-1] == 'P')
            )
            {
            }
            else
            {
                continue;
            }
#endif
            feature *fet = new feature();

#if defined(_WIN32) || defined (_WIN64)
            fet->name = ffData.cFileName;
#else
            fet->name = _dirent->d_name;
#endif
            fet->fileName = lpPath;
            fet->fileName += "/" + fet->name;

            //Output the Compound file.
            iRet = MakeDBFetFile(fet, iAlg);
            if(iRet == true)
            {
                Features.push_back(fet);
            }
            else
            {
                delete fet;
                fet = NULL;
            }
        }
#if defined(_WIN32) || defined (_WIN64)
        while( FindNextFile(hr, &ffData) );
#endif
    } else {
        fprintf(stderr, "Find First File Err\n");
        return false;
    }

#if defined(_WIN32) || defined (_WIN64)
    FindClose(hr);
#else
    closedir(dir);
#endif

    if(Features.size() == 0)
    {
        fprintf(stderr, "No Image enroll success\n");
        return false;
    }
#endif
    return true;
}

/**
 * Create the feature for query side.
 *
 */
CFaceFeature* NeoFaceAlg::MakeQueryFetObj(feature *fet, int iAlg)
{
#ifdef USE_NEOFACE
    // Load the bitmap file.
    char cBuf[128];

    BITMAPINFO binfo;
    void *body;
#if defined(_WIN32) || defined (_WIN64)
    int iRet = LoadBMP((char*)((fet->fileName).GetBuffer()), binfo, &body);
#else
    int iRet = LoadBMP((char*)((fet->fileName).c_str()), binfo,&body);
#endif
    if(iRet < 0)
    {
        strcpy_s(cBuf, CT2A(fet->fileName));
        fprintf(stderr, "[%s] cannot open file.\n", cBuf);
        return NULL;
    }

    CFaceInfo *info;

    try{
        info = new CFaceInfo();
    }catch(int err){
        if(err == NFP_NOT_INITIALILZE_ERROR)
        {
            fprintf(stderr, "License Error\n");
        }
        else
        {
            fprintf(stderr, "Unknown exception\n");
        }
        free(body);
        return NULL;
    }

    // Set the detection parameter.
    info->SetParamAlgorithm(iAlg);
    info->SetParamEyesRoll(15);
    info->SetParamEyesMaxWidth(PreferenceHandler::getInstance()->getEyeMax());
    info->SetParamEyesMinWidth(PreferenceHandler::getInstance()->getEyeMin());
    info->SetParamReliability(PreferenceHandler::getInstance()->getRelValue());

    // Face detection.
    iRet = info->FindFace(binfo, body);
    if(iRet == NFP_CANNOT_FIND_FACE)
    {
        // Face did not detected.
        strcpy_s(cBuf, CT2A(fet->fileName));
        fprintf(stdout, "[%s] cannot find face.\n", cBuf);
        free(body);
        delete info;
        return NULL;
    }
    else if(iRet != NFP_SUCCESS)
    {
        strcpy_s(cBuf, CT2A(fet->fileName));
        fprintf(stderr, "[%s] find face error. %d\n", cBuf, iRet);
        free(body);
        delete info;
        return NULL;
    }

    CFaceFeature *ffet = new CFaceFeature();

    // Create the feature.
    iRet = ffet->SetFeature(info);
    if(iRet != NFP_SUCCESS)
    {
        strcpy_s(cBuf, CT2A(fet->fileName));
        fprintf(stderr, "[%s] make feature error. %d\n", cBuf, iRet);
        free(body);
        delete info;
        delete ffet;
        return NULL;
    }

    free(body);
    delete info;
    return ffet;
#endif
    return NULL;
}

/**
 * Execute face verification
 */
bool NeoFaceAlg::Verify(vector<feature *> features, int iAlg)
{
#ifdef USE_NEOFACE
    // Create the object for face verification.
    CVerifier *verify;
    char cBuf[128];

    try{
        verify = new CVerifier();
    }catch(int err){
        if(err == NFP_NOT_INITIALILZE_ERROR)
        {
            fprintf(stderr, "License Error\n");
        }
        else
        {
            fprintf(stderr, "Unknown exception\n");
        }
        return false;
    }

    //Create the feature for query side.
    feature *fet = features[0];
    CFaceFeature *query;
    query = MakeQueryFetObj(fet, iAlg);
    if(query == NULL)
    {
        strcpy_s(cBuf, CT2A(fet->fetFileName));
        fprintf(stderr, "MakeQueryFetObj failed. %s\n", cBuf);
        delete verify;
        return false;
    }
    strcpy_s(cBuf, CT2A(fet->name));
    fprintf(stdout, "\nTarget/Query\n");
    fprintf(stdout, "           ");
    fprintf(stdout, "%11s", cBuf);

    //Get the number of files of the list.
    int iMax = (int)features.size()-1;
    int iRet, i;
    for(i = 0; i <= iMax;i++)
    {
        feature *fet = features[i];

        // Read the feature data of target side from file.
        void *target;
        fprintf(stdout, "\n");
#if defined(_WIN32) || defined (_WIN64)
        target = ReadTargetFetData((char *)(fet->fetFileName).GetBuffer());
#else
        target = ReadTargetFetData((char *)(fet->fetFileName).c_str());
#endif
        if(target == NULL)
        {
            strcpy_s(cBuf, CT2A(fet->fetFileName));
            fprintf(stderr, "ReadTargetFetData failed. %s\n", cBuf);
            delete verify;
            delete query;
            return false;
        }
        strcpy_s(cBuf, CT2A(fet->name));
        fprintf(stdout, "%-11s", cBuf);

        // Verification
        float score;
        iRet = verify->Verify(query, target, &score);
        if(iRet != NFP_SUCCESS)
        {
            fprintf(stderr, "Verify error. %d\n", iRet);
            delete verify;
            free(target);
            delete query;
            return false;
        }
        fprintf(stdout, "%11f", score);
        free(target);

    }
    fprintf(stdout, "\n\n");
    delete query;
    delete verify;
#endif
    return true;
}

void NeoFaceAlg::DeleteArray(vector<feature *> arrayFeature)  //ððú·é
{
    feature * temp;
    for(unsigned int i=0; i < arrayFeature.size();i++)
    {
        temp = arrayFeature[i];
        delete temp;
    }
    arrayFeature.clear();
}
/**
 * Main function.
 *
 */


//int CImageControl::IplImageToBitmap(IplImage * pImage, BITMAPFILEHEADER * pbfHeader, BITMAPINFO * pBmpInfo, void ** ppVoid, bool bFlipped)
int NeoFaceAlg::IplImageToBitmap(IplImage * pImage, BITMAPFILEHEADER * pbfHeader, BITMAPINFO * pBmpInfo, void ** ppVoid, bool bFlipped)
{
 #ifdef USE_NEOFACE
    int nBmpHeaderSize = 40;
    int nWidth = pImage->width;
    int nHeight = pImage->height;
    int nChannels = pImage->nChannels;
    int nFileStep = ( nWidth * nChannels + 3 ) & -4;
    int nPaletteSize = ( nChannels > 1 ) ? 0 : 1024;
    int nHeaderSize = 14 + nBmpHeaderSize + nPaletteSize;
    int nImageSize = nFileStep * nHeight;
    int nFileSize = nHeaderSize + nImageSize;

    if( pbfHeader != NULL )
    {
        pbfHeader->bfType = 0x4d42;
        pbfHeader->bfSize = nFileSize;
        pbfHeader->bfReserved1 = 0;
        pbfHeader->bfReserved2 = 0;
        pbfHeader->bfOffBits = nHeaderSize;
    }

    if( pBmpInfo != NULL )
    {
        pBmpInfo->bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
        pBmpInfo->bmiHeader.biBitCount = pImage->nChannels * 8;
        pBmpInfo->bmiHeader.biClrUsed = 0;
        pBmpInfo->bmiHeader.biCompression = 0;			// #define BI_RGB        0L
        pBmpInfo->bmiHeader.biHeight = pImage->height;
        pBmpInfo->bmiHeader.biWidth = pImage->width;
        pBmpInfo->bmiHeader.biPlanes = 1;
        pBmpInfo->bmiHeader.biSizeImage = nImageSize;
        pBmpInfo->bmiHeader.biXPelsPerMeter = 0;
        pBmpInfo->bmiHeader.biYPelsPerMeter = 0;
    }

    ( * ppVoid ) = new char[nFileSize];
    ZeroMemory( ( * ppVoid ), nFileSize );

    uchar * puszPosition = ( uchar * )( * ppVoid );

    memcpy( puszPosition, pbfHeader, sizeof( BITMAPFILEHEADER ) );
//	cvWaitKey(50);
    puszPosition += sizeof( BITMAPFILEHEADER );

    memcpy( puszPosition, pBmpInfo, sizeof( BITMAPINFO ) );
//	cvWaitKey(50);

    puszPosition += sizeof( BITMAPINFO );
    puszPosition += nHeaderSize - sizeof( BITMAPFILEHEADER ) - sizeof( BITMAPINFO );

    if( !bFlipped )
    {
        IplImage * pFlipImage = cvCreateImage( cvSize( pImage->width, pImage->height ), pImage->depth, pImage->nChannels );
        cvFlip( pImage, pFlipImage, 0 );
//		cvWaitKey(50);
        memcpy( puszPosition, pFlipImage->imageData, pBmpInfo->bmiHeader.biSizeImage );
//        cvWaitKey(10);
        cvReleaseImage( &pFlipImage );
        pFlipImage = NULL;
    }
    else
    {
        memcpy( puszPosition, pImage->imageData, pBmpInfo->bmiHeader.biSizeImage );
//		cvWaitKey(50);
    }

    return nFileSize;
#endif
    return 0;
}



/**
 * Create Compound feature
 *
 */
int NeoFaceAlg::MakeFeature(BITMAPINFO * pBmpInfo, void * pVoidBody, void * CamFeature, long * plSize, int iAlg )
{
#ifdef USE_NEOFACE
    // Load the bitmap file.
    char	cBuf[128];
    int		iRet;


    CFaceInfo *info;
    try{
        info = new CFaceInfo();
    }catch(int err){
        if(err == NFP_NOT_INITIALILZE_ERROR)
        {
            fprintf(stderr, "License Error\n");
        }
        else
        {
            fprintf(stderr, "Unknown exception\n");
        }
//		free(body);
        return false;
    }

    // Set the detection parameter.
    info->SetParamAlgorithm(iAlg);
    info->SetParamEyesRoll(15);
    info->SetParamEyesMaxWidth(PreferenceHandler::getInstance()->getEyeMax());
    info->SetParamEyesMinWidth(PreferenceHandler::getInstance()->getEyeMin());
    info->SetParamReliability(PreferenceHandler::getInstance()->getRelValue());

    // Face detection.
    iRet = info->FindFace(* pBmpInfo, pVoidBody);
    if(iRet == NFP_CANNOT_FIND_FACE)
    {
        // Face did not detected.
//		strcpy_s(cBuf, CT2A(fet->fileName));
        fprintf(stdout, "[%s] cannot find face.\n", "MakeFeature");
        delete info;
//		free(body);
        return false;
    }
    else if(iRet == NFP_SUCCESS)
    {

        CFaceFeature *ffet = new CFaceFeature();

        // Create the Simplex feature.
        iRet = ffet->SetFeature(info);
        if(iRet != NFP_SUCCESS)
        {
//			strcpy_s(cBuf, CT2A(fet->fileName));
            fprintf(stderr, "[%s] make feature error. %d\n", "MakeFeature", iRet);
            delete info;
            delete ffet;
//			free(body);
            return false;
        }



        // Get the eye positions.
        POINT L = info->GetLeftEye();
        POINT R = info->GetRightEye();

//		strcpy_s(cBuf, CT2A(fet->name));
        fprintf(stdout,"%s  L:%d,%d  R:%d,%d\n", "eye positions",  L.x, L.y, R.x, R.y);


        void *data;
        long size;

        // Serialize the Compound feature.
        int iRet = ffet->Serialize(&data, &size, NFP_SERIALIZETYPE_COMPOUND);
        if(iRet != NFP_SUCCESS)
        {
            fprintf(stderr,"Serialize error.\n");
            return false;
        }

        memcpy( CamFeature, data, size );
        *plSize = size;

        // Free serealized data.
        ffet->FreeSerializeData(data);

    }
    else{
//		strcpy_s(cBuf, CT2A(fet->name));
        fprintf(stderr,"[%s] find face error. %d\n", "MakeFeature", iRet);
        delete info;
//		free(body);
        return false;
    }
#endif
    return true;
}


/**
 * Create Compound feature file - from Cam image.
 *
 */
bool NeoFaceAlg::MakeDBFetFile2( BITMAPINFO * pBmpInfo, void * pVoidBody, Mat frame, int iAlg, QString userName)
{
#ifdef USE_NEOFACE
    char	cBuf[128];
    int		iRet;

    CFaceInfo *info;
    try{
        info = new CFaceInfo();
    }catch(int err){
        if(err == NFP_NOT_INITIALILZE_ERROR)
        {
            qDebug() << "License Error\n";
        }
        else
        {
             qDebug() <<  "Unknown exception\n";
        }
        return false;
    }

    // Set the detection parameter.
    info->SetParamAlgorithm(iAlg);
    info->SetParamEyesRoll(15);
    info->SetParamEyesMaxWidth(PreferenceHandler::getInstance()->getEyeMax());
    info->SetParamEyesMinWidth(PreferenceHandler::getInstance()->getEyeMin());
//	info->SetParamReliability(0.5f);
    info->SetParamReliability(PreferenceHandler::getInstance()->getRelValue());		// 0.6f
//	info->SetParamReliability(0.58f);		// 0.6f

    strcpy_s(cBuf, "MakeDBFetFile2" );

    // Face detection.
//	iRet = info->FindFace(binfo, body);
    iRet = info->FindFace(* pBmpInfo, pVoidBody);
    if(iRet == NFP_CANNOT_FIND_FACE)
    {
        // Face did not detected.
        qDebug() << "cannot find face.\n";
        delete info;
        return false;
    }
    else if(iRet == NFP_SUCCESS)
    {

        CFaceFeature *ffet = new CFaceFeature();

        // Create the Simplex feature.
        iRet = ffet->SetFeature(info);
        if(iRet != NFP_SUCCESS)
        {
            qDebug() <<  "make feature error.\n";
            delete info;
            delete ffet;
//			free(body);
            return false;
        }


        // Get the eye positions.
        POINT L = info->GetLeftEye();
        POINT R = info->GetRightEye();

        fprintf(stdout,"\n\n\n L:%d,%d  R:%d,%d\n\n", L.x, L.y, R.x, R.y);

        RECT rctFace = info->GetHead();
        //Rect rec(rctFace.left, rctFace.top, rctFace.right-rctFace.left, rctFace.bottom-rctFace.top);
        //rectangle(frame, rec, Scalar(0,255,0), 3);

        // Output the Compound feature file.
        CString fetFile;
        bool Ret = false;

        fetFile = QDir::currentPath().toStdString() +"/feature/" + userName.toStdString() + ".fet";
        Ret = SerializeFeature(ffet, (char*)fetFile.c_str());


        if(Ret == false)
        {
            qDebug() << "serialize error\n detail" + QString(fetFile.c_str()) ;
            delete info;
            delete ffet;
//			free(body);
            return false;
        }
        delete info;
        delete ffet;

        qDebug() <<  "successfully registered \n";



//        // save test
//        char szDebFName2[1024] = {0,};
//        CString tempFile = QDir::currentPath().toStdString() + "/temp/\%s.bmp";
//        sprintf(szDebFName2, tempFile.c_str(), userName.toStdString().c_str());
//        FILE* LogFile = fopen( szDebFName2, "wb");
//        if(LogFile == 0)
//        {
//            fprintf(stderr," cannot open file.\n" );
//            //msg = "cannot open file.\n";
//        }
//        // Output the Compound feature.
//        size_t szRet = fwrite( pVoidBody, 1, gFileSize, LogFile );

//        if((long)szRet != gFileSize)
//        {
//            fprintf(stderr," cannot write file.\n" );
//            //msg = "cannot write file.\n";
//        }

//        fclose( LogFile );

    }
    else{
        qDebug() <<  " find face error.\n";
        delete info;
        return false;
    }
#endif
    return true;
}
//bool NeoFaceAlg::saveImage(cv::Mat& frame, QString userName)
//{
//    cv::cvtColor(frame, frame, CV_BGR2RGB);
//    QString path = QDir::currentPath() + "/history/" + userName + ".bmp";
//    cv::imwrite(path.toStdString(), frame);
//    return true;
//}

char* NeoFaceAlg::CT2A(LPCTSTR x)
{
    return x;
}

const char* NeoFaceAlg::CT2A(CString x)
{
    return x.c_str();
}
bool NeoFaceAlg::MakeFeature(BITMAPINFO * pBmpInfo, void * pVoidBody, void * CamFeature, long * plSize, RECT* rctFace, int iAlg)
{
#ifdef USE_NEOFACE
    // Load the bitmap file.
    int		iRet;


    CFaceInfo *info;
    try{
        info = new CFaceInfo();
    }catch(int err){
        if(err == NFP_NOT_INITIALILZE_ERROR)
        {
            qDebug() << "License Error";
        }
        else
        {
            qDebug() <<  "Unknown exception";
        }
        return false;
    }

    // Set the detection parameter.
    info->SetParamAlgorithm(iAlg);
    info->SetParamEyesRoll(15);
    info->SetParamEyesMaxWidth(PreferenceHandler::getInstance()->getEyeMax());
    info->SetParamEyesMinWidth(PreferenceHandler::getInstance()->getEyeMin());
    info->SetParamReliability(PreferenceHandler::getInstance()->getRelValue());

    // Face detection.
    iRet = info->FindFace(* pBmpInfo, pVoidBody);
    if(iRet == NFP_CANNOT_FIND_FACE)
    {
        // Face did not detected.
        qDebug() << "cannot find face";
        delete info;
        return false;
    }
    else if(iRet == NFP_SUCCESS)
    {

        CFaceFeature *ffet = new CFaceFeature();

        // Create the Simplex feature.
        iRet = ffet->SetFeature(info);
        if(iRet != NFP_SUCCESS)
        {
            qDebug() << "make feature error";
            delete info;
            delete ffet;
            return false;
        }
        // Get the eye positions.
        POINT L = info->GetLeftEye();
        POINT R = info->GetRightEye();


//		RECT rctFace;
        *rctFace = info->GetHead();
        int		iFaceWidth  = rctFace->right  - rctFace->left;
        int		iFaceHeight = rctFace->bottom - rctFace->top;

        // ³Ê¹« ÀÛ°Å³ª Å«°æ¿ìŽÂ skip
        if  ( iFaceWidth  < PreferenceHandler::getInstance()->getEyeMin() || iFaceWidth  > (PreferenceHandler::getInstance()->getEyeMax() * 150 / 100) ||
              iFaceHeight < PreferenceHandler::getInstance()->getEyeMin() || iFaceHeight > (PreferenceHandler::getInstance()->getEyeMax() * 150 / 100) ) {
            qDebug() << QString::number(PreferenceHandler::getInstance()->getEyeMin()) +
                        ":" + QString::number(iFaceWidth) +
                    ":" + QString::number(PreferenceHandler::getInstance()->getEyeMax());
            delete info;
            delete ffet;
            return false;
        }

        void *data;
        long size;

        // Serialize the Compound feature.
        int iRet = ffet->Serialize(&data, &size, NFP_SERIALIZETYPE_COMPOUND);
        if(iRet != NFP_SUCCESS)
        {
            qDebug() << "Serialize error.";
            return false;
        }

        memcpy( CamFeature, data, size );
        *plSize = size;

        // Free serealized data.
        ffet->FreeSerializeData(data);

    }
    else{
        qDebug() <<"find face error.";
        delete info;
        return false;
    }
    qDebug() << "make feature sus.";
#endif
    return true;
}
bool NeoFaceAlg::LoadFeatures(const char* lpPath, int iAlg)
{
#ifdef USE_NEOFACE
    char	szFileName[256];
    char	szName[256];
    char	cBuf[128];

    gFeatureCnt = 0;

    CString str;
    bool iRet;

    //Find the Feature file.
    str = lpPath;

#if defined(_WIN32) || defined (_WIN64)
    str = str + "/*.fet";
    WIN32_FIND_DATA ffData;
    HANDLE hr = FindFirstFile(str, &ffData);
    if(hr != INVALID_HANDLE_VALUE)
    {
        do
#else
    struct dirent* _dirent = 0;
    DIR *dir;
    dir =opendir(str.c_str());
    if (dir != 0)
    {
        while ((_dirent=readdir(dir))!= 0)
#endif
        {
#if defined(_WIN32) || defined (_WIN64)
#else
            int nameLength = strlen(_dirent->d_name);
            if(nameLength >= 5 &&
                (_dirent->d_name[nameLength-3] == 'f' || _dirent->d_name[nameLength-3] == 'F') &&
                (_dirent->d_name[nameLength-2] == 'e' || _dirent->d_name[nameLength-2] == 'E') &&
                (_dirent->d_name[nameLength-1] == 't' || _dirent->d_name[nameLength-1] == 'T')
            )
            {
            }
            else
            {
                continue;
            }
#endif

            // read the Compound file.
            sprintf( szFileName, "%s/%s", lpPath, _dirent->d_name );
            FILE* fd = fopen(szFileName, "rb");
            if(fd == 0)
            {
                qDebug() << "cannot open file.\n";
//				free(data);
                return NULL;
            }

            // Read the feature file.
//			size_t szRet = fread(data,1,size,fd);
            size_t szRet = fread( gFeatureBuffer[gFeatureCnt], 1, FEATURE_SIZE, fd );
            if  ( szRet < FEATURE_SIZE_MIN )
            {
                qDebug() << "cannot read file.\n";
                fclose(fd);
                continue;
            }
            fclose(fd);

            // set Feature name
            strcpy( szName, _dirent->d_name );
            char	*pStr = strstr( szName, "." );
            if  ( pStr ) {
                *pStr = 0x00;		// truncate
            }
            strcpy( gFeatureName[gFeatureCnt], szName );

            gFeatureCnt ++;
            if  ( gFeatureCnt >= FEATURE_MAX_COUNT ) {
                break;
            }

        }
#if defined(_WIN32) || defined (_WIN64)
        while( FindNextFile(hr, &ffData) );
#endif
    } else {
        qDebug() << "Find First File Err\n";
        return false;
    }

#if defined(_WIN32) || defined (_WIN64)
    FindClose(hr);
#else
    closedir(dir);
#endif

    if(gFeatureCnt == 0)
    {
        qDebug() << "No Image enroll success\n";
        return false;
    }
#endif
    return true;
}


bool NeoFaceAlg::imageReg(QString userName, cv::Mat& frame)
{
#ifdef USE_NEOFACE
    IplImage * image;
    IplImage image2 = IplImage( frame );    // Mat to IplImage (Mat -> IplImage) <-- , operator IplImage()

    image = &image2;
    if  ( !image )
    {
        return false;
    }

    BITMAPFILEHEADER bmpFileHeader;
    BITMAPINFO bmpInfo;

    void * pBuf = NULL;
    memset(&bmpInfo, 0, sizeof(bmpInfo));
    IplImageToBitmap( image, &bmpFileHeader, &bmpInfo, &pBuf, false );		// convert for FC
    gFileSize = bmpFileHeader.bfSize;		// for .bmp file save test

    //Output the Compound file.
    int FindFaceAlg = NFP_ALGORITHM009F6;
    bool iRet = MakeDBFetFile2( &bmpInfo, pBuf, frame, FindFaceAlg, userName);
    if  ( pBuf ) {
        delete [] pBuf;
    }
    cv::cvtColor(frame, frame, CV_BGR2RGB);
    QString path = QDir::currentPath() + "/temp/" + userName + ".bmp";
    cv::imwrite(path.toStdString(), frame);

    return iRet;
#endif
    return false;
}
QString NeoFaceAlg::imageCmp(cv::Mat& frame)
{
    QString userName = "unknown";
#ifdef USE_NEOFACE
    int i;
    float fReliability = PreferenceHandler::getInstance()->getRelValue();
    float gfMaxReliability = PreferenceHandler::getInstance()->getMaxRelValue();
    IplImage image2 = IplImage( frame );    // Mat to IplImage (Mat -> IplImage) <-- , operator IplImage()
    IplImage * image = &image2;

    if  ( !image )
    {
        //userName = "image empty";
        return userName;
    }
    CVerifier *cverify;
    try{
        cverify = new CVerifier();
        //userName = "Verify success";
    }catch(int err){
        if(err == NFP_NOT_INITIALILZE_ERROR)
        {
            fprintf(stderr, "License Error\n");
            //userName = "License Error";
        }
        else
        {
            fprintf(stderr, "Unknown exception\n");
            //userName = "Unknown exception";

        }
        return userName;
    }

    BITMAPFILEHEADER bmpFileHeader;
    BITMAPINFO bmpInfo;


    void * pBuf = NULL;
    memset(&bmpInfo, 0, sizeof(bmpInfo));

    IplImageToBitmap( image, &bmpFileHeader, &bmpInfo, &pBuf, false );		// convert for FC

    BYTE	CamFeature[FEATURE_SIZE];
    long	lSize;
    RECT	rctFace;
    char	szMsg[256];
    int FindFaceAlg = NFP_ALGORITHM009F6;
    // comparc
    int iRet = MakeFeature( &bmpInfo, pBuf, CamFeature, &lSize, &rctFace, FindFaceAlg);
    if  ( pBuf ) {
        delete [] pBuf;
    }

    if  ( !iRet ) {
        //imshow( "NeoFace", frame );
        //userName = "Make feature false\n";
        return userName;
        //false;
    }
    float fHighScore = 0.0f;
    int iFaceIndex = 0;


    for ( i = 0; i < gFeatureCnt; i ++ ) {
        // Verification
        float score = 0.0f;
        iRet = cverify->Verify( CamFeature, gFeatureBuffer[i], &score );
        if(iRet != NFP_SUCCESS)
        {
            //userName = "Verify error.\n";
            continue;
        }
        if  ( score > fReliability  &&  score > fHighScore ) {	// °¡Àå ³ôÀº Á¡ŒöžŠ Ã£ŽÂŽÙ
            fHighScore = score;
            iFaceIndex = i;
            //userName = "matched.\n";
        } else {
            //userName = "NeoFace not matched.\n";
        }

        if( fHighScore > gfMaxReliability ) 		// score°¡ ÀÌ value ÀÌ»óÀÌžé verify ¿Ï·áÃ³ž®
        {
            break;		// ŽõÀÌ»ó ÁøÇàÇÒ ÀÌÀ¯°¡ ŸøŽÙ.
        }

    }
    if  ( fHighScore > gfMaxReliability ) {
        userName = QString::fromUtf8(gFeatureName[iFaceIndex]);
        //userName = "reliable\n";
    } else {
        //userName = QString::number(fHighScore) + ":" + QString::number(fReliability) + "low reliable\n";
    }
#endif
    return userName;
}
Rect NeoFaceAlg::faceDetect(cv::Mat& frame)
{
    Rect rect(0, 0, 0, 0);
#ifdef USE_NEOFACE
    IplImage * image;
    IplImage image2 = IplImage( frame );    // Mat to IplImage (Mat -> IplImage) <-- , operator IplImage()

    image = &image2;
    if  ( !image )
    {
        qDebug() << "image empty\n";
        return rect;
    }

    CFaceInfo *info;
    try{
        info = new CFaceInfo();
    }catch(int err){
        if(err == NFP_NOT_INITIALILZE_ERROR)
        {
            qDebug() << "License Error\n";
        }
        else
        {
            qDebug() << "Unknown exception\n";
        }
        return rect;
    }
    BITMAPFILEHEADER bmpFileHeader;
    BITMAPINFO bmpInfo;

    void * pBuf = NULL;
    memset(&bmpInfo, 0, sizeof(bmpInfo));


    IplImageToBitmap( image, &bmpFileHeader, &bmpInfo, &pBuf, false );		// convert for FC
    gFileSize = bmpFileHeader.bfSize;		// for .bmp file save test

    char	cBuf[128];
    int		iRet;

    int iAlg = NFP_ALGORITHM009F6;
    // Set the detection parameter.
    info->SetParamAlgorithm(iAlg);
    info->SetParamEyesRoll(15);
    info->SetParamEyesMaxWidth(PreferenceHandler::getInstance()->getEyeMax());
    info->SetParamEyesMinWidth(PreferenceHandler::getInstance()->getEyeMin());
//	info->SetParamReliability(0.5f);
    info->SetParamReliability(PreferenceHandler::getInstance()->getRelValue());		// 0.6f
//	info->SetParamReliability(0.58f);		// 0.6f

    strcpy_s(cBuf, "MakeDBFetFile2" );

    // Face detection.
    iRet = info->FindFace(bmpInfo, pBuf);
    if(iRet == NFP_CANNOT_FIND_FACE)
    {
        qDebug() << "cannot find face.\n";
        delete info;
        if  ( pBuf ) {
            delete [] pBuf;
        }
        return rect;
    }
    else if(iRet == NFP_SUCCESS)
    {

        CFaceFeature *ffet = new CFaceFeature();

        // Create the Simplex feature.
        iRet = ffet->SetFeature(info);
        if(iRet != NFP_SUCCESS)
        {
             qDebug() << "make feature error. \n";
             if  ( pBuf ) {
                 delete [] pBuf;
             }
            delete info;
            delete ffet;
            return rect;
        }

        RECT rctFace = info->GetHead();
        Rect rec(rctFace.left, rctFace.top, rctFace.right-rctFace.left, rctFace.bottom-rctFace.top);
        //Rect rec(0, 0, 300, 300);
        if  ( pBuf ) {
            delete [] pBuf;
        }
        return rec;
    }
    else{
        qDebug() << " find face error.\n";
        delete info;
        if  ( pBuf ) {
            delete [] pBuf;
        }
        return rect;
    }
#endif

    return rect;

}

bool NeoFaceAlg::checkLicense()
{
    int iRet = NFP_LICENSE_ERROR;
#ifdef USE_NEOFACE
    iRet = Initialize();
#endif


    if(iRet == NFP_LICENSE_ERROR)
    {
        return false;
    }
    else if(iRet != NFP_SUCCESS)
    {
        return false;
    }
#ifdef USE_NEOFACE
    CVerifier *verify;

    try{
        verify = new CVerifier();
    }catch(int err){
        if(err == NFP_NOT_INITIALILZE_ERROR)
        {
            qDebug() << "License Error";
        }
        else
        {
            qDebug() <<  "Unknown exception";
        }
        return false;
    }
#endif
    return true;
}
bool NeoFaceAlg::close()
{
    int iRet = NFP_FAILED;

#ifdef USE_NEOFACE
    iRet = Terminate();
#endif

    if(iRet != NFP_SUCCESS)
    {
        qDebug() << "Terminate error.\n";
        return false;
    }
    qDebug() << "Terminate successfully.\n";
    return true;
}
