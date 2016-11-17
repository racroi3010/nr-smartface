#ifndef MATTOQIMAGEUTIL_H
#define MATTOQIMAGEUTIL_H
#include "opencv2/highgui/highgui.hpp"
#include <QImage>
#include <QDebug>
QImage Mat2QImage(const cv::Mat&);
#endif // MATTOQIMAGEUTIL_H
