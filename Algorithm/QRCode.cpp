#include "QRCode.h"

void QRCode::QRCodeLocate(cv::Mat srcImg)
{
	// 预处理
	cv::Mat grayImg, edgeImg, dstImg;
	//resize(srcImg, srcImg, Size(), 0.7, 0.7);
	dstImg = srcImg.clone();
	cvtColor(srcImg, grayImg, CV_BGR2GRAY);
	GaussianBlur(grayImg, grayImg, Size(1, 1), 0);
	Canny(grayImg, edgeImg, 100, 200);
	
	cv::Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));
	dilate(edgeImg, edgeImg, element);
	imshow("Edge", edgeImg);
	waitKey(0);

	// Contours
	vector<vector<Point>> contours, keypoints;
	vector<Vec4i> hierarchy;
	findContours(edgeImg, contours, hierarchy, CV_RETR_TREE, CHAIN_APPROX_NONE);

	// Locate
	int c, ic;
	for (int i = 0; i < contours.size(); i++)
	{
		c = i;
		ic = 0;

		while (hierarchy[c][2] != -1)
		{
			c = hierarchy[c][2];
			ic++;
		}

		//cv::Mat cntImg = dstImg.clone();
		//cout << ic << endl;
		//drawContours(cntImg, contours, i, CV_RGB(88, 194, 194), 1);
		//imshow("Contours", cntImg);

		if (ic >= 4 && (hierarchy[i][0] != -1 || hierarchy[i][1] != -1)) // 定位点
			keypoints.push_back(contours[i]);
	}

	if (keypoints.size() == 0)
		cout << "Not Found !" << endl;
	else
		cout << "keypoints count : " << keypoints.size() << endl;

	for (int i = keypoints.size() - 1; i > -1; i--)
	{
		drawContours(dstImg, keypoints, i, CV_RGB(88, 194, 194), 2);
		cv::Moments M = moments(keypoints[i]);
		int cx = int(M.m10 / M.m00);
		int cy = int(M.m01 / M.m00);
		cout << "Center Point : " << Point2i(cx, cy) << endl;
		imshow("Result", dstImg);
		waitKey(0);
	}
}

void main()
{
	QRCode QRcode;
	cv::Mat src;
	src = imread("test1.jpg");
	QRcode.QRCodeLocate(src);

	waitKey(0);
}