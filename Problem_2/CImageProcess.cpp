#include "stdafx.h"
#include "CImageProcess.h"

cv::Mat CImageProcess::PicResize(cv::Mat srcImg, int width, int height)
{
	IplImage * src = &IplImage(srcImg);
	IplImage * desc;

	float ratio_x = float(width) / float(srcImg.cols);
	float ratio_y = float(height) / float(srcImg.rows);
	float ratio = ratio_x < ratio_y ? ratio_x : ratio_y;

	CvSize sz;
	sz.width = int(srcImg.cols * ratio);
	sz.height = int(srcImg.rows * ratio);
	desc = cvCreateImage(sz, src->depth, src->nChannels);
	cvResize(src, desc, CV_INTER_CUBIC);

	return cvarrToMat(desc);
}

Point2i CImageProcess::GetContourCentralPoint(vector<Point2i> cnt)
{
	cv::Moments M = moments(cnt);
	int cx = int(M.m10 / M.m00);
	int cy = int(M.m01 / M.m00);

	return Point2i(cx, cy);
}

vector<Point> CImageProcess::GetContourRect(vector<Point2i> cnt)
{
	RotatedRect rotRect = minAreaRect(cnt); // ( center (x,y), (width, height), angle of rotation )
	Point2f pts[4];
	rotRect.points(pts);
	vector<Point> rectPoints(pts, pts + 4);

	return rectPoints;
}

vector<vector<Point>> CImageProcess::GetQRCodeLandmark(cv::Mat srcImg)
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

	// Contours
	vector<vector<Point>> contours, landmarks;
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
			landmarks.push_back(contours[i]);
	}

	return landmarks;
}

Rect2i CImageProcess::GetQRCodeRect(vector<vector<Point>> landmarks)
{
	int size = landmarks.size() * 4;
	int *pointx = new int[size];
	int *pointy = new int[size];
	for (int i = 0; i < landmarks.size(); i++)
	{
		vector<Point> keypoints = GetContourRect(landmarks[i]);
		for (int j = 0; j < keypoints.size(); j++)
		{
			pointx[j + i * 4] = keypoints[j].x;
			pointy[j + i * 4] = keypoints[j].y;
		}
	}
	sort(pointx, pointx + size);
	sort(pointy, pointy + size);

	int minX = pointx[0];
	int minY = pointy[0];
	int maxX = pointx[size - 1];
	int maxY = pointy[size - 1];
	Rect2i rect(Point(minX, minY), Point(maxX, maxY));

	return rect;
}

Rect2i CImageProcess::GetQRCodeAvatar(cv::Mat src, Rect codeRect)
{
	cv::Mat mask = cv::Mat::zeros(src.size(), CV_8UC1);
	//mask(codeRect).setTo(255);
	//src.copyTo(maskImg, mask);

	cv::Mat grayImg, binarImg;
	cv::Mat codeImg = src(codeRect);
	cvtColor(codeImg, grayImg, CV_RGB2GRAY);
	GaussianBlur(grayImg, grayImg, Size(3, 3), 0);
	threshold(grayImg, binarImg, 0, 255, THRESH_OTSU);

	vector<vector<Point>> contours;
	vector<Point> avatarCnt, avatarPoints;
	Rect avatarRect;
	findContours(binarImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	if (contours.size())
	{
		int offsetx = codeRect.x;
		int offsety = codeRect.y;

		avatarCnt = contours[0];
		avatarPoints = GetContourRect(avatarCnt);
		for (int i = 0; i < avatarPoints.size(); i++)
		{
			avatarPoints[i].x += offsetx;
			avatarPoints[i].y += offsety;
		}

		avatarRect = Rect(avatarPoints[0], avatarPoints[2]);
	}

	return avatarRect;
}