#ifndef _CIMAGEPROCESS_H_
#define _CIMAGEPROCESS_H_

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <algorithm>
#include <vector>

using namespace cv;
using namespace std;

class CImageProcess
{
public:
	cv::Mat					PicResize(cv::Mat srcImg, int width, int height);
	Point2i					GetContourCentralPoint(vector<Point2i> cnt);
	vector<Point>			GetContourRect(vector<Point2i> cnt);
	vector<vector<Point>>	GetQRCodeLandmark(cv::Mat srcImg);
	Rect2i					GetQRCodeRect(vector<vector<Point>> keypoints);
	Rect2i					GetQRCodeAvatar(cv::Mat src, Rect codeRect);
};

#endif // !CIMAGEMAT_H
