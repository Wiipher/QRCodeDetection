#ifndef _QRCODE_H_
#define _QRCODE_H_

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <stdlib.h>
#include <iostream>

using namespace cv;
using namespace std;

class QRCode
{
public:
	void QRCodeLocate(cv::Mat srcImg);
};

#endif // !CIMAGEMAT_H