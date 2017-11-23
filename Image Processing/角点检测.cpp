#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat src, src_gray;

int maxCorners = 23;
int maxTrackbar = 100;

RNG rng(12345);  //RNG：random number generator，随机数产生器
char* source_window = "Image";

void goodFeaturesToTrack_Demo(int, void*);

int main()
{
	//转化为灰度图
	src = imread("chess1.jpg", 1);
	resize(src, src, Size(960, 640));
	cvtColor(src, src_gray, CV_BGR2GRAY);

	namedWindow(source_window, CV_WINDOW_AUTOSIZE);

	//创建trackbar
	createTrackbar("MaxCorners:", source_window, &maxCorners, maxTrackbar, goodFeaturesToTrack_Demo);

	imshow(source_window, src);

	goodFeaturesToTrack_Demo(0, 0);

	waitKey(0);
	return(0);
}

void goodFeaturesToTrack_Demo(int, void*)
{
	if (maxCorners < 1) { maxCorners = 1; }

	//初始化 Shi-Tomasi algorithm的一些参数
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;

	//给原图做一次备份
	Mat copy;
	copy = src.clone();

	// 角点检测
	goodFeaturesToTrack(src_gray, corners, maxCorners, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);

	//画出检测到的角点
	cout << "** Number of corners detected: " << corners.size() << endl;
	int r = 4;
	for (int i = 0; i < corners.size(); i++)
	{
		circle(copy, corners[i], r, Scalar(rng.uniform(0, 255), rng.uniform(0, 255),
			rng.uniform(0, 255)), -1, 8, 0);
	}

	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, copy);
}