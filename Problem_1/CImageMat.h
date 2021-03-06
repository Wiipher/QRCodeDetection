#ifndef _CIMAGEMAT_H_
#define _CIMAGEMAT_H_

#include "opencv2/opencv.hpp"

using namespace cv;

class CImageMat  
{  
public:   
    /*MatToCImage 
    *简介： 
    *   OpenCV的Mat转ATL/MFC的CImage，仅支持单通道灰度或三通道彩色 
    *参数： 
    *   mat：OpenCV的Mat 
    *   cimage：ATL/MFC的CImage 
    */  
    void MatToCImage(cv::Mat& mat, CImage& cimage);
  
    /*CImageToMat 
    *简介： 
    *   ATL/MFC的CImage转OpenCV的Mat，仅支持单通道灰度或三通道彩色 
    *参数： 
    *   cimage：ATL/MFC的CImage 
    *   mat：OpenCV的Mat 
    */  
    void CImageToMat(CImage& cimage, cv::Mat& mat);
}; 

#endif // !CIMAGEMAT_H