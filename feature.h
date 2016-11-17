#ifndef FEATURE_H
#define FEATURE_H
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
#define CString std::string
class feature
{
public:
    feature(){
    }
    CString fileName;
    CString name;
    CString fetFileName;
};
#endif // FEATURE_H
