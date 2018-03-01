#include "stdafx.h"
#include <iostream>  
#include <iomanip>  
#include <fstream>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"  
#include "opencv2/objdetect/objdetect.hpp"  
#include "opencv2/features2d/features2d.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/calib3d/calib3d.hpp"  
#include "opencv2/nonfree/nonfree.hpp"  
#include "opencv2/imgproc/imgproc_c.h"  
#include "opencv2/legacy/legacy.hpp"  
#include "opencv2/legacy/compat.hpp"  

#include <fstream>
#include<io.h>
#include<ctime>
#include<queue>
#include"crack_detection.h"
using namespace cv;
using namespace std;
//800,500
//拍的较黑的水平和垂直的数字是：800,500
//拍的较亮的水平和垂直的数字是：600,300
#define HORI_OVERLAP 600
#define VERTI_OVERLAP 300
#define MATCH_COUNT 30
#define SCALE 4
#define CUT_ROWS 0.02
int img_rows = 0;
int img_cols = 0;
int stitchImgRows = 0;
int stitchImgCols = 0;
double mosaicArr[10000];
void getFiles1(string path, vector<string>& files){
	long hfile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hfile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1){
		do{
			if ((fileinfo.attrib & _A_SUBDIR)){
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles1(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else{
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				files.push_back(fileinfo.name);
			}
		} while (_findnext(hfile, &fileinfo) == 0);
		_findclose(hfile);
	}
}

void getFiles2(string path, vector<string>& files){
	long hfile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hfile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1){
		do{
			if ((fileinfo.attrib & _A_SUBDIR)){
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles2(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));

			}
		} while (_findnext(hfile, &fileinfo) == 0);
		_findclose(hfile);
	}
}

void filesOrderAdjust(vector<string>& fileNames, vector<string>& imgNames, int vertiNum, int horiNum){
	for (int i = 0; i < vertiNum; i++){
		if (i % 2 == 0){
			int begin = i*horiNum;
			for (int j = 0; j < horiNum; j++){
				imgNames.push_back(fileNames[begin]);
				begin++;
			}
		}
		else{
			int begin = (i + 1)*horiNum - 1;
			for (int j = 0; j < horiNum; j++){
				imgNames.push_back(fileNames[begin]);///////////
				begin--;
			}
		}
	}
}

void AverageVariance(Mat lpLab, int Width, int Height, double& al, double& aa, double& ab, double& vl, double& va, double& vb)
{
	double suml = 0;
	double suma = 0;
	double sumb = 0;
	double lsuml = 0;
	double lsuma = 0;
	double lsumb = 0;

	//分行求平均，避免和过大而溢出  
	for (int j = 0; j < Height; j++)
	{
		for (int i = 0; i < Width; i++)
		{
			lsuml += (double)lpLab.at<Vec3b>(j, i)[0];
			lsuma += (double)lpLab.at<Vec3b>(j, i)[1];
			lsumb += (double)lpLab.at<Vec3b>(j, i)[2];
		}
		suml += lsuml / Width;
		suma += lsuma / Width;
		sumb += lsumb / Width;
		lsuml = lsuma = lsumb = 0;
	}
	al = suml / Height;
	aa = suma / Height;
	ab = sumb / Height;

	suml = suma = sumb = 0;
	for (int j = 0; j < Height; j++)
	{
		for (int i = 0; i < Width; i++)
		{
			suml += pow((double)lpLab.at<Vec3b>(j, i)[0] - al, 2);
			suma += pow((double)lpLab.at<Vec3b>(j, i)[1] - aa, 2);
			sumb += pow((double)lpLab.at<Vec3b>(j, i)[2] - ab, 2);
		}
	}
	vl = sqrt(suml);
	va = sqrt(suma);
	vb = sqrt(sumb);
}

Mat TranRein(Mat& lpDIBBits, int lmageWidth, int lmageHeight, Mat& lpDIBBits2, int lmageWidth2, int lmageHeight2, Mat& lpDIBBits3)
{
	int i;
	int j;
	int nindex;
	double al, aa, ab, vl, va, vb, al2, aa2, ab2, vl2, va2, vb2;
	//目标图像转换为lab，并求lab的均值及标准差  
	Mat img1;
	cvtColor(lpDIBBits, img1, CV_BGR2Lab);
	//cout << img1.at<Vec3b>(0, 0) << endl;
	AverageVariance(img1, lmageWidth, lmageHeight, al, aa, ab, vl, va, vb);

	//源图像转换为lab，并求lab的均值及标准差  
	Mat img2;
	cvtColor(lpDIBBits2, img2, CV_BGR2Lab);
	AverageVariance(img2, lmageWidth2, lmageHeight2, al2, aa2, ab2, vl2, va2, vb2);

	//求结果图像的lab  
	Mat lpDIBBits32;
	cvtColor(lpDIBBits3, lpDIBBits32, CV_BGR2Lab);
	for (int j = 0; j < lmageHeight; j++)
	{
		for (int i = 0; i < lmageWidth; i++)
		{
			//cout << "1:  " << img1.at<Vec3b>(j, i) << endl << "2:  " << (short)(((double)img1.at<Vec3b>(j, i)[0] - al) * vl2 / vl + al2) << endl << endl;
			lpDIBBits32.at<Vec3b>(j, i)[0] = (short)(((double)img1.at<Vec3b>(j, i)[0] - al) * vl2 / vl + al2 + 0.5);
			lpDIBBits32.at<Vec3b>(j, i)[1] = (short)(((double)img1.at<Vec3b>(j, i)[1] - aa) * va2 / va + aa2 + 0.5);
			lpDIBBits32.at<Vec3b>(j, i)[2] = (short)(((double)img1.at<Vec3b>(j, i)[2] - ab) * vb2 / vb + ab2 + 0.5);
		}
	}



	//将结果图像的lab转换为RGB  
	cvtColor(lpDIBBits32, lpDIBBits32, CV_Lab2BGR);
	imshow("test", lpDIBBits3 - lpDIBBits32);
	cvWaitKey();
	return lpDIBBits3;
}



Mat IntensityTrans(Mat srcImg, Mat dstImg)
{
	Mat rltImg = srcImg.clone();
	Mat refImg = dstImg.clone();

	cvtColor(rltImg, rltImg, CV_BGR2YCrCb);
	cvtColor(refImg, refImg, CV_BGR2YCrCb);

	double al, aa, ab, vl, va, vb, al2, aa2, ab2, vl2, va2, vb2;
	AverageVariance(rltImg, rltImg.cols, rltImg.rows, al, aa, ab, vl, va, vb);
	AverageVariance(refImg, refImg.cols, refImg.rows, al2, aa2, ab2, vl2, va2, vb2);

	//求结果图像的yuv  
	for (int j = 0; j < rltImg.rows; j++)
	{
		for (int i = 0; i < rltImg.cols; i++)
		{
			//cout << rltImg.at<Vec3b>(j, i)[0] - (short)(((double)rltImg.at<Vec3b>(j, i)[0] - al) * vl2 / vl + al2 + 0.5) << endl;
			rltImg.at<Vec3b>(j, i)[0] = (short)(((double)rltImg.at<Vec3b>(j, i)[0] - al) * vl2 / vl + al2 + 0.5);
			rltImg.at<Vec3b>(j, i)[1] = (short)(((double)rltImg.at<Vec3b>(j, i)[1] - aa) * va2 / va + aa2 + 0.5);
			rltImg.at<Vec3b>(j, i)[2] = (short)(((double)rltImg.at<Vec3b>(j, i)[2] - ab) * vb2 / vb + ab2 + 0.5);
		}
	}

	//将结果图像的lab转换为RGB  
	cvtColor(rltImg, rltImg, CV_YCrCb2BGR);
	imshow("test", rltImg - srcImg);
	cvWaitKey();
	return rltImg;
}

void getLeftRightSurf(cv::Mat& leftImg, cv::Mat& rightImg, cv::Mat& result, double* arr){
	int width = leftImg.cols;
	int height = leftImg.rows;
	//rightImg=rightImg(cv::Rect(0,0,rightImg.cols,height));


	int roiCols = HORI_OVERLAP;
	int roiRows = leftImg.rows;

	cv::Mat leftRoiImg = leftImg(cv::Rect(leftImg.cols - roiCols, 0, roiCols, roiRows));
	cv::Mat rightRoiImg = rightImg(cv::Rect(0, 0, roiCols, roiRows));

	Mat leftGray;
	Mat rightGray;
	cvtColor(leftRoiImg, leftGray, CV_BGR2GRAY);
	cvtColor(rightRoiImg, rightGray, CV_BGR2GRAY);

	int minHessian = 400;
	SurfFeatureDetector detector(minHessian);
	vector<KeyPoint> leftKeyPoints, rightKeyPoints;
	detector.detect(leftGray, leftKeyPoints);
	detector.detect(rightGray, rightKeyPoints);
	SurfDescriptorExtractor extractor;

	Mat leftDescriptor, rightDescriptor;
	extractor.compute(leftGray, leftKeyPoints, leftDescriptor);
	extractor.compute(rightGray, rightKeyPoints, rightDescriptor);

	FlannBasedMatcher matcher;
	vector<DMatch> matches;

	matcher.match(leftDescriptor, rightDescriptor, matches);

	int matchCount = leftDescriptor.rows;
	if (matchCount > MATCH_COUNT)
	{
		matchCount = MATCH_COUNT;
		sort(matches.begin(), matches.begin() + leftDescriptor.rows);
	}

	vector<Point2f> leftPoints;
	vector<Point2f> rightPoints;
	for (int i = 0; i < matchCount; i++)
	{
		Point2f leftP;
		leftP.x = leftKeyPoints[matches[i].queryIdx].pt.x + (leftImg.cols - roiCols);
		leftP.y = leftKeyPoints[matches[i].queryIdx].pt.y;
		leftPoints.push_back(leftP);
		rightPoints.push_back(rightKeyPoints[matches[i].trainIdx].pt);
	}

	Mat homo = findHomography(rightPoints, leftPoints, CV_RANSAC);
	//std::cout << "the homo is:" << endl;
	//cout << homo << endl;
	Mat tiledImg;
	//cv::warpPerspective(rightImg, tiledImg, homo, Size(leftImg.cols + rightImg.cols, rightImg.rows));
	//imwrite("E:\\SciResearch\\BridgeProject\\20170606_195300\\twoImgResults\\testImg1.jpg", tiledImg);
	//leftImg.copyTo(Mat(tiledImg, Rect(0, 0, leftImg.cols, leftImg.rows)));


	if (homo.at<double>(0, 0) < 0.6 || homo.at<double>(0, 0)>1){

		int minHessian = 400;
		SiftFeatureDetector detector(minHessian);
		vector<KeyPoint> leftKeyPoints, rightKeyPoints;
		detector.detect(leftGray, leftKeyPoints);
		detector.detect(rightGray, rightKeyPoints);
		SiftDescriptorExtractor extractor;

		Mat leftDescriptor, rightDescriptor;
		extractor.compute(leftGray, leftKeyPoints, leftDescriptor);
		extractor.compute(rightGray, rightKeyPoints, rightDescriptor);

		FlannBasedMatcher matcher;
		vector<DMatch> matches;

		matcher.match(leftDescriptor, rightDescriptor, matches);

		int matchCount = leftDescriptor.rows;
		if (matchCount > MATCH_COUNT)
		{
			matchCount = MATCH_COUNT;
			sort(matches.begin(), matches.begin() + leftDescriptor.rows);
		}

		vector<Point2f> leftPoints;
		vector<Point2f> rightPoints;
		for (int i = 0; i < matchCount; i++)
		{
			Point2f leftP;
			leftP.x = leftKeyPoints[matches[i].queryIdx].pt.x + (leftImg.cols - roiCols);
			leftP.y = leftKeyPoints[matches[i].queryIdx].pt.y;
			leftPoints.push_back(leftP);
			rightPoints.push_back(rightKeyPoints[matches[i].trainIdx].pt);
		}

		//if (homo.at<double>(0, 0)>1||homo.at<double>(0,0)<0.6){
		//	homo.at<double>(0, 0) = 0.9;
		//}
		homo = findHomography(rightPoints, leftPoints, CV_RANSAC);
		//std::cout << "the homo <0 is:" << endl;
		//cout << homo << endl;
		//Mat tiledImg;
		//cv::warpPerspective(rightImg, tiledImg, homo, Size(leftImg.cols + rightImg.cols, rightImg.rows));
		//imwrite("E:\\SciResearch\\BridgeProject\\20170606_195300\\twoImgResults\\testImg1.jpg", tiledImg);
		//leftImg.copyTo(Mat(tiledImg, Rect(0, 0, leftImg.cols, leftImg.rows)));

	}

	cv::warpPerspective(rightImg, tiledImg, homo, Size(leftImg.cols + rightImg.cols, rightImg.rows));
	leftImg.copyTo(Mat(tiledImg, Rect(0, 0, leftImg.cols, leftImg.rows)));




	Mat upPoint = Mat::zeros(3, 1, CV_64FC1);
	upPoint.at<double>(0, 0) = rightImg.cols - 1;
	upPoint.at<double>(1, 0) = 0;
	upPoint.at<double>(2, 0) = 1;

	Mat downPoint = Mat::zeros(3, 1, CV_64FC1);
	downPoint.at<double>(0, 0) = rightImg.cols - 1;
	downPoint.at<double>(1, 0) = rightImg.rows - 1;
	downPoint.at<double>(2, 0) = 1;

	Mat upPmat = homo*upPoint;
	Mat downPmat = homo*downPoint;
	int upLoc = (int)(upPmat.at<double>(0, 0) / (upPmat.at<double>(2, 0)));
	int downLoc = (int)(downPmat.at<double>(0, 0) / (downPmat.at<double>(2, 0)));

	int endLoc = upLoc>downLoc ? downLoc : upLoc;
	if (endLoc >= tiledImg.cols){
		endLoc = tiledImg.cols - 1;
	}
	//cout<<"the end poinnt is:  "<<endLoc<<endl;
	//imwrite("E:\\SciResearch\\BridgeProject\\20170606_195300\\twoImgResults\\testImg2.jpg", tiledImg);
	result = tiledImg(cv::Rect(0, 0, endLoc + 1, leftImg.rows));
	//imwrite("D:\\BridgeProject\\20170619_160908\\tempImgs\\incResult.jpg", result);
	cv::waitKey();
	int arrRows = homo.rows;
	int arrCols = homo.cols;
	int type = homo.type();
	assert(type == CV_64FC1);
	for (int i = 0; i<arrRows; i++){
		for (int j = 0; j<arrCols; j++){
			arr[i*arrCols + j] = homo.at<double>(i, j);
			//cout << "the num is: " << arr[i*arrCols + j] << endl;
		}
	}
	//std::cout << "the arr row and col is " << arrRows << "  " << arrCols << endl;
}

void getUpDownSurf(cv::Mat& upImg, cv::Mat& downImg, cv::Mat& result){
	//int width=upImg.cols;
	//int height=upImg.rows;
	//downImg=downImg(cv::Rect(0,0,width,downImg.rows));

	//int roiCols=upImg.cols;
	//int roiRows=VERTI_OVERLAP;

	/*cv::Mat upRoiImg=upImg(cv::Rect(0,upImg.rows-roiRows,roiCols,roiRows));
	cv::Mat downRoiImg=downImg(cv::Rect(0,0,roiCols,roiRows));*/
	//cv::Mat upRoiImg=upImg;
	//cv::Mat downRoiImg=downImg;

	//imwrite("E:\\SciResearch\\BridgeProject\\20170606_195300\\twoImgResults\\upRoiImg.jpg", upRoiImg);
	//imwrite("E:\\SciResearch\\BridgeProject\\20170606_195300\\twoImgResults\\downRoiImg.jpg", downRoiImg);
	Mat upGray;
	Mat downGray;
	cvtColor(upImg, upGray, CV_BGR2GRAY);
	cvtColor(downImg, downGray, CV_BGR2GRAY);

	int minHessian = 400;
	//SurfFeatureDetector detector(minHessian);
	SiftFeatureDetector detector(minHessian);

	vector<KeyPoint> upKeyPoints, downKeyPoints;
	detector.detect(upGray, upKeyPoints);
	detector.detect(downGray, downKeyPoints);


	//SurfDescriptorExtractor extractor;
	SiftDescriptorExtractor extractor;
	Mat upDescriptor, downDescriptor;
	extractor.compute(upGray, upKeyPoints, upDescriptor);
	extractor.compute(downGray, downKeyPoints, downDescriptor);

	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(upDescriptor, downDescriptor, matches);

	int matchCount = upDescriptor.rows;
	if (matchCount > 30)
	{
		matchCount = 30;
		sort(matches.begin(), matches.begin() + upDescriptor.rows);
	}
	//std::cout << "the mathcount is" << matchCount << endl;
	vector<Point2f> upPoints;
	vector<Point2f> downPoints;
	/*for (int i = 0; i < matchCount; i++)
	{
	Point2f upP;
	upP.x=upKeyPoints[matches[i].queryIdx].pt.x;
	upP.y=upKeyPoints[matches[i].queryIdx].pt.y+(upImg.rows-roiRows);
	upPoints.push_back(upP);
	downPoints.push_back(downKeyPoints[matches[i].trainIdx].pt);
	}*/
	for (int i = 0; i < matchCount; i++)
	{
		//Point2f upP;
		//upP.x=upKeyPoints[matches[i].queryIdx].pt.x;
		//upP.y=upKeyPoints[matches[i].queryIdx].pt.y+(upImg.rows-roiRows);
		//upP.y=upKeyPoints[matches[i].queryIdx].pt.y;
		//upPoints.push_back(upP);
		upPoints.push_back(upKeyPoints[matches[i].queryIdx].pt);
		downPoints.push_back(downKeyPoints[matches[i].trainIdx].pt);
	}

	Mat homo = findHomography(downPoints, upPoints, CV_RANSAC);
	//cout << "the homo is" << homo << endl;
	Mat tiledImg;
	cv::warpPerspective(downImg, tiledImg, homo, Size(upImg.cols, upImg.rows + downImg.rows));
	//imwrite("E:\\SciResearch\\BridgeProject\\20170606_195300\\twoImgResults\\tiledImgdown.jpg", tiledImg);
	upImg.copyTo(Mat(tiledImg, Rect(0, 0, upImg.cols, upImg.rows)));

	Mat leftPoint = Mat::zeros(3, 1, CV_64FC1);
	leftPoint.at<double>(0, 0) = 0;
	leftPoint.at<double>(1, 0) = downImg.rows - 1;
	leftPoint.at<double>(2, 0) = 1;

	Mat rightPoint = Mat::zeros(3, 1, CV_64FC1);
	rightPoint.at<double>(0, 0) = downImg.cols - 1;
	rightPoint.at<double>(1, 0) = downImg.rows - 1;
	rightPoint.at<double>(2, 0) = 1;

	Mat leftPmat = homo*leftPoint;
	Mat rightPmat = homo*rightPoint;
	int leftLoc = (int)(leftPmat.at<double>(1, 0) / (leftPmat.at<double>(2, 0)));
	int rightLoc = (int)(rightPmat.at<double>(1, 0) / (rightPmat.at<double>(2, 0)));

	int endLoc = leftLoc>rightLoc ? leftLoc : rightLoc;
	//cout << "the end poinnt is:  " << endLoc << endl;
	//cv::imshow("tiledImg",tiledImg);
	//imwrite("E:\\SciResearch\\BridgeProject\\20170606_195300\\twoImgResults\\tiledImg111.jpg", tiledImg);
	result = tiledImg(cv::Rect(0, 0, upImg.cols, endLoc));
	//imwrite("E:\\SciResearch\\BridgeProject\\20170606_195300\\twoImgResults\\result.jpg", result);

}

void getUpDownSurf1(cv::Mat& upImg, cv::Mat& downImg, cv::Mat& result, double* vertiArr){
	int width = upImg.cols;
	int height = upImg.rows;
	//downImg = downImg(cv::Rect(0, 0, width, downImg.rows));
	if (upImg.data == NULL || downImg.data == NULL){
		cout << "图像为空" << endl;
	}
	//cv::imshow("upImg", upImg);
	//cv::imshow("downIMg", downImg);
	//cv::waitKey();
	int roiCols = upImg.cols;
	int roiRows = VERTI_OVERLAP;

	//cv::Mat upRoiImg = upImg(cv::Rect(0, upImg.rows - roiRows, roiCols, roiRows));
	//cv::Mat downRoiImg = downImg(cv::Rect(0, 0, roiCols, roiRows));
	cv::Mat upRoiImg = upImg(cv::Rect(0, upImg.rows - roiRows, upImg.cols, roiRows));
	cv::Mat downRoiImg = downImg(cv::Rect(0, 0, downImg.cols, roiRows));
	Mat upGray;
	Mat downGray;
	cvtColor(upRoiImg, upGray, CV_BGR2GRAY);
	cvtColor(downRoiImg, downGray, CV_BGR2GRAY);

	int minHessian = 400;
	SurfFeatureDetector detector(minHessian);
	//SiftFeatureDetector detector(minHessian);

	vector<KeyPoint> upKeyPoints, downKeyPoints;
	detector.detect(upGray, upKeyPoints);
	detector.detect(downGray, downKeyPoints);


	SurfDescriptorExtractor extractor;
	//SiftDescriptorExtractor extractor;
	Mat upDescriptor, downDescriptor;
	extractor.compute(upGray, upKeyPoints, upDescriptor);
	extractor.compute(downGray, downKeyPoints, downDescriptor);

	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(upDescriptor, downDescriptor, matches);

	int matchCount = upDescriptor.rows;
	if (matchCount > 30)
	{
		matchCount = 30;
		sort(matches.begin(), matches.begin() + upDescriptor.rows);
	}
	//cout<<"the mathcount is "<<matchCount<<endl;
	vector<Point2f> upPoints;
	vector<Point2f> downPoints;
	/*for (int i = 0; i < matchCount; i++)
	{
	Point2f upP;
	upP.x=upKeyPoints[matches[i].queryIdx].pt.x;
	upP.y=upKeyPoints[matches[i].queryIdx].pt.y+(upImg.rows-roiRows);
	upPoints.push_back(upP);
	downPoints.push_back(downKeyPoints[matches[i].trainIdx].pt);
	}*/
	for (int i = 0; i < matchCount; i++)
	{
		Point2f upP;
		upP.x = upKeyPoints[matches[i].queryIdx].pt.x;
		upP.y = upKeyPoints[matches[i].queryIdx].pt.y + (upImg.rows - roiRows);
		upPoints.push_back(upP);
		//upPoints.push_back(upKeyPoints[matches[i].queryIdx].pt);	
		downPoints.push_back(downKeyPoints[matches[i].trainIdx].pt);
	}

	Mat homo = findHomography(downPoints, upPoints, CV_RANSAC);
	//cout << "the homo is  " << homo << endl;



	if (homo.at<double>(0, 0) < 0.6){
		int minHessian = 400;
		//SurfFeatureDetector detector(minHessian);
		SiftFeatureDetector detector(minHessian);

		vector<KeyPoint> upKeyPoints, downKeyPoints;
		detector.detect(upGray, upKeyPoints);
		detector.detect(downGray, downKeyPoints);


		//SurfDescriptorExtractor extractor;
		SiftDescriptorExtractor extractor;
		Mat upDescriptor, downDescriptor;
		extractor.compute(upGray, upKeyPoints, upDescriptor);
		extractor.compute(downGray, downKeyPoints, downDescriptor);

		FlannBasedMatcher matcher;
		vector<DMatch> matches;
		matcher.match(upDescriptor, downDescriptor, matches);

		int matchCount = upDescriptor.rows;
		if (matchCount > 30)
		{
			matchCount = 30;
			sort(matches.begin(), matches.begin() + upDescriptor.rows);
		}
		//cout<<"the mathcount is "<<matchCount<<endl;
		vector<Point2f> upPoints;
		vector<Point2f> downPoints;

		for (int i = 0; i < matchCount; i++)
		{
			Point2f upP;
			upP.x = upKeyPoints[matches[i].queryIdx].pt.x;
			upP.y = upKeyPoints[matches[i].queryIdx].pt.y + (upImg.rows - roiRows);
			upPoints.push_back(upP);
			//upPoints.push_back(upKeyPoints[matches[i].queryIdx].pt);	
			downPoints.push_back(downKeyPoints[matches[i].trainIdx].pt);
		}

		homo = findHomography(downPoints, upPoints, CV_RANSAC);
		//cout << "the homo is  " << homo << endl;

	}
	Mat tiledImg;
	cv::warpPerspective(downImg, tiledImg, homo, Size(upImg.cols, upImg.rows + downImg.rows));
	//imwrite("E:\\SciResearch\\BridgeProject\\20170606_195300\\twoImgResults\\tiledImgdown.jpg", tiledImg);
	upImg.copyTo(Mat(tiledImg, Rect(0, 0, upImg.cols, upImg.rows)));

	Mat leftPoint = Mat::zeros(3, 1, CV_64FC1);
	leftPoint.at<double>(0, 0) = 0;
	leftPoint.at<double>(1, 0) = downImg.rows - 1;
	leftPoint.at<double>(2, 0) = 1;

	Mat rightPoint = Mat::zeros(3, 1, CV_64FC1);
	rightPoint.at<double>(0, 0) = downImg.cols - 1;
	rightPoint.at<double>(1, 0) = downImg.rows - 1;
	rightPoint.at<double>(2, 0) = 1;

	Mat leftPmat = homo*leftPoint;
	Mat rightPmat = homo*rightPoint;
	int leftLoc = (int)(leftPmat.at<double>(1, 0) / (leftPmat.at<double>(2, 0)));
	int rightLoc = (int)(rightPmat.at<double>(1, 0) / (rightPmat.at<double>(2, 0)));

	//int endLoc=leftLoc>rightLoc?leftLoc:rightLoc;
	int endLoc = leftLoc>rightLoc ? rightLoc : leftLoc;
	//cout << "the end poinnt is:  " << endLoc << endl;
	//cout << "the img rows is  " << tiledImg.rows << endl;
	//if (endLoc > tiledImg.rows){
	//	endLoc = tiledImg.rows;
	//}
	//cv::imshow("tiledImg",tiledImg);
	//imwrite("E:\\SciResearch\\BridgeProject\\20170606_195300\\twoImgResults\\tiledImg111.jpg", tiledImg);
	cv::Mat tempImg = tiledImg(cv::Rect(0, 0, upImg.cols, endLoc));
	result = tempImg.clone();
	//imwrite("D:\\BridgeProject\\20170619_160908\\tempImgs\\resultverti.jpg", result);
	int arrRows = homo.rows;
	int arrCols = homo.cols;
	for (int i = 0; i<arrRows; i++){
		for (int j = 0; j<arrCols; j++){
			vertiArr[i*arrCols + j] = homo.at<double>(i, j);
		}
	}
}
void getHoriAll(std::vector<string>& imgs, cv::Mat& result, int rows, int cols, int rowsIndex, double* horiArr){
	cv::Mat leftImg, rightImg, resultImg;
	//	double* arr=new double[9];

	for (int j = 0; j<cols - 1; j++){
		//cout << j << endl;

		if (j == 0){
			int imgIndex = rowsIndex*cols + j;
			//cout << imgs[imgIndex] << endl;
			leftImg = cv::imread(imgs[imgIndex]);
			rightImg = cv::imread(imgs[imgIndex + 1]);
			cv::resize(leftImg, leftImg, cv::Size(leftImg.cols / SCALE, leftImg.rows / SCALE));
			cv::resize(rightImg, rightImg, cv::Size(rightImg.cols / SCALE, rightImg.rows / SCALE));
			//	getLeftRightSurf(leftImg,rightImg,resultImg,arr);
			//	memcpy(horiArr+j*9*sizeof(double),arr,9*sizeof(double));
			getLeftRightSurf(leftImg, rightImg, resultImg, horiArr + j * 9);
		}
		else{
			int imgIndex = rowsIndex*cols + j;
			leftImg = resultImg;
			rightImg = cv::imread(imgs[imgIndex + 1]);
			cv::resize(rightImg, rightImg, cv::Size(rightImg.cols / SCALE, rightImg.rows / SCALE));
			//	getLeftRightSurf(leftImg,rightImg,resultImg,arr);
			//memcpy(horiArr+j*9*sizeof(double),arr,9*sizeof(double));
			getLeftRightSurf(leftImg, rightImg, resultImg, horiArr + j * 9);
		}

	}
	result = resultImg.clone();
	//delete[] arr;
}

//void stitchImgs(std::vector<string>& imgNames,cv::Mat& result,int rows,int cols){
//	queue<cv::Mat> horiQueue;
//	
//	for(int i=0;i<rows;i++){
//		cv::Mat horiResult;
//		getHoriAll(imgNames,horiResult,rows,cols,i,horiArr);
//		
//		horiQueue.push(horiResult);
//	}
//	cv::Mat upImg=horiQueue.front();
//	horiQueue.pop();
//	while(!horiQueue.empty()){
//		cv::Mat downImg=horiQueue.front();
//		horiQueue.pop();
//		getUpDownSurf1(upImg,downImg,result);
//		upImg=result;
//	}
//}

//void stitchImgs1(char* dire,cv::Mat& result,int rows,int cols){
//	
//	queue<cv::Mat> horiQueue;
//	vector<string> fileNames,imgNames;
//	getFiles2(dire,fileNames);
//	filesOrderAdjust(fileNames,imgNames,rows,cols);
//	cv::Mat rowsImg=cv::imread(imgNames[0]);
//	/*double cutRowsTemp=(rowsImg.rows/SCALE)*(CUT_ROWS);
//	int cutRows=(int)cutRowsTemp;*/
//	int cutRows=(int)(rowsImg.rows/SCALE)*(CUT_ROWS);
//	std::cout<<"cutRows is "<<cutRows<<endl;
//	rowsImg.release();
//	for(int i=0;i<rows;i++){
//		cv::Mat horiResult;
//		getHoriAll(imgNames,horiResult,rows,cols,i);
//		
//		if(i==0){
//			cv::imwrite("E:\\SciResearch\\BridgeProject\\20170606_195300\\twoImgResults\\horicutBefore.jpg", horiResult);
//		}
//		horiResult=horiResult(cv::Rect(0,0,horiResult.cols,horiResult.rows-cutRows));
//		if(i==0){
//			cv::imwrite("E:\\SciResearch\\BridgeProject\\20170606_195300\\twoImgResults\\horicutAfter.jpg", horiResult);
//		}
//		//horiQueue.push(horiResult);
//		horiQueue.push(horiResult);
//	}
//	cv::Mat upImg=horiQueue.front();
//	horiQueue.pop();
//	while(!horiQueue.empty()){
//		cv::Mat downImg=horiQueue.front();
//		horiQueue.pop();
//		getUpDownSurf1(upImg,downImg,result);
//		upImg=result;
//	}
//}

//int stitchImgs2(char* imgNames, char* outName, int rows, int cols, double* mosaicArr,int length)


int stitchImgs(const char* imgNames, char* outName, int rows, int cols, double* mosaicArr, int length){
	int arrLength = ((cols - 1) * 9 * rows + (rows - 1) * 9)*sizeof(double);
	if (length < arrLength){
		return -1;//空间长度为字节，开辟的空间不足
	}
	img_rows = rows;
	img_cols = cols;
	cv::Mat result;
	queue<cv::Mat> horiQueue;
	vector<string> fileNames, imgVec;
	//getFiles2(dire, fileNames);
	int imgCnt = rows*cols;
	char* dupNames = new char[256 * imgCnt];
	std::strcpy(dupNames, imgNames);
	char* startPtr = dupNames;
	int offset = 0;
	for (int i = 0; i < imgCnt; i++){
		offset = 0;
		while (startPtr[offset] != '|')
			offset++;

		startPtr[offset] = '\0';
		Mat img;
		img = imread(startPtr);
		//printf("%s\n", startPtr);
		if (img.data == NULL){
			return -2;//表示图像不存在
		}
		fileNames.push_back(startPtr);
		startPtr += (offset + 1);
	}
	delete[] dupNames;

	filesOrderAdjust(fileNames, imgVec, rows, cols);
	for (int i = 0; i < imgVec.size(); i++){
		//cout << imgVec[i] << endl;
	}


	cv::Mat rowsImg = cv::imread(imgVec[0]);
	int cutRows = (int)(rowsImg.rows / SCALE)*(CUT_ROWS);
	//std::cout << "cutRows is " << cutRows << endl;
	rowsImg.release();
	for (int i = 0; i<rows; i++){
		cv::Mat horiResult;
		//getHoriAll(imgNames,horiResult,rows,cols,i,horriArr);
		getHoriAll(imgVec, horiResult, rows, cols, i, mosaicArr + i*(cols - 1) * 9);
		//std::cout << "第 " << i << " 行执行完毕" << endl;
		//int length=(cols-1)*9*sizeof(double);

		//	memcpy(mosaicArr+i*(cols-1)*9,horiArr,length);
		horiResult = horiResult(cv::Rect(0, 0, horiResult.cols, horiResult.rows - cutRows));
		horiQueue.push(horiResult);
		//cv::imwrite("D:\\BridgeProject\\20170619_160908\\tempImgs\\horiImg1.jpg", horiResult);
	}


	if (horiQueue.size() == 1){
		result = horiQueue.front();
		cv::imwrite(outName, result);
		return arrLength;
	}
	//cout << "horiqueue 的大小为： " << horiQueue.size() << endl;
	cv::Mat upImg = horiQueue.front();
	horiQueue.pop();
	//cv::imshow("upImg",upImg);
	//cv::waitKey();
	//int filledLen=9*sizeof(double)*(cols-1)*rows;
	int rowIndex = 0;
	//int arrLen=9*sizeof(double);
	//int saveStart=(cols-1)*9*rows+rowIndex*9;

	while (!horiQueue.empty()){

		//cv::Mat resultTemp;
		double* saveStart = mosaicArr + (cols - 1) * 9 * rows + rowIndex * 9;
		//double* vertiArr=new double[9];
		cv::Mat downImg = horiQueue.front();
		horiQueue.pop();
		//getUpDownSurf1(upImg,downImg,result,vertiArr);
		getUpDownSurf1(upImg, downImg, result, saveStart);
		//cout << "第  " << rowIndex << "  整行拼接完成" << endl;
		upImg = result;
		//memcpy(mosaicArr+filledLen+rowIndex*arrLen,vertiArr,arrLen);
		rowIndex++;

	}
	cv::imwrite(outName, result);
	stitchImgRows = result.rows;
	stitchImgCols = result.cols;
	return arrLength;
}

void stitchImgs2(char* dire, char* outName, int rows, int cols, double* mosaicArr){
	cv::Mat result;
	queue<cv::Mat> horiQueue;
	vector<string> fileNames, imgNames;
	//	double* horiArr=new double[9*cols-9];//[];
	//	assert(horiArr != NULL);
	getFiles2(dire, fileNames);
	filesOrderAdjust(fileNames, imgNames, rows, cols);
	cv::Mat rowsImg = cv::imread(imgNames[0]);
	int cutRows = (int)(rowsImg.rows / SCALE)*(CUT_ROWS);
	//std::cout << "cutRows is " << cutRows << endl;
	rowsImg.release();
	for (int i = 0; i<rows; i++){
		cv::Mat horiResult;
		//getHoriAll(imgNames,horiResult,rows,cols,i,horriArr);
		getHoriAll(imgNames, horiResult, rows, cols, i, mosaicArr + i*(cols - 1) * 9);
		//std::cout << "第 " << i << " 行执行完毕" << endl;
		//int length=(cols-1)*9*sizeof(double);

		//	memcpy(mosaicArr+i*(cols-1)*9,horiArr,length);
		horiResult = horiResult(cv::Rect(0, 0, horiResult.cols, horiResult.rows - cutRows));
		horiQueue.push(horiResult);
		//cv::imwrite("E:\\SciResearch\\BridgeProject\\20170606_195300\\tempImgs\\horiImg1.jpg",horiResult);
	}
	cv::Mat upImg = horiQueue.front();
	horiQueue.pop();
	//int filledLen=9*sizeof(double)*(cols-1)*rows;
	int rowIndex = 0;
	//int arrLen=9*sizeof(double);
	//int saveStart=(cols-1)*9*rows+rowIndex*9;
	while (!horiQueue.empty()){
		double* saveStart = mosaicArr + (cols - 1) * 9 * rows + rowIndex * 9;
		//double* vertiArr=new double[9];
		cv::Mat downImg = horiQueue.front();
		horiQueue.pop();
		//getUpDownSurf1(upImg,downImg,result,vertiArr);
		getUpDownSurf1(upImg, downImg, result, saveStart);
		upImg = result;
		//memcpy(mosaicArr+filledLen+rowIndex*arrLen,vertiArr,arrLen);
		rowIndex++;
	}
	cv::imwrite(outName, result);
	//delete[] horiArr;
}

void testGetLeftRight(cv::Mat& leftImg, cv::Mat& rightImg, cv::Mat& result, cv::Mat& homo){
	Mat tiledImg;
	cv::warpPerspective(rightImg, tiledImg, homo, Size(leftImg.cols + rightImg.cols, rightImg.rows));
	leftImg.copyTo(Mat(tiledImg, Rect(0, 0, leftImg.cols, leftImg.rows)));

	Mat upPoint = Mat::zeros(3, 1, CV_64FC1);
	upPoint.at<double>(0, 0) = rightImg.cols - 1;
	upPoint.at<double>(1, 0) = 0;
	upPoint.at<double>(2, 0) = 1;

	Mat downPoint = Mat::zeros(3, 1, CV_64FC1);
	downPoint.at<double>(0, 0) = rightImg.cols - 1;
	downPoint.at<double>(1, 0) = rightImg.rows - 1;
	downPoint.at<double>(2, 0) = 1;

	Mat upPmat = homo*upPoint;
	Mat downPmat = homo*downPoint;
	int upLoc = (int)(upPmat.at<double>(0, 0) / (upPmat.at<double>(2, 0)));
	int downLoc = (int)(downPmat.at<double>(0, 0) / (downPmat.at<double>(2, 0)));

	int endLoc = upLoc>downLoc ? downLoc : upLoc;
	if (endLoc > tiledImg.cols){
		endLoc = tiledImg.cols;
	}
	result = tiledImg(cv::Rect(0, 0, endLoc, leftImg.rows));
}

void testUpDownImg(cv::Mat& upImg, cv::Mat& downImg, cv::Mat& result, cv::Mat& homo){
	Mat tiledImg;
	cv::warpPerspective(downImg, tiledImg, homo, Size(upImg.cols, upImg.rows + downImg.rows));
	//imwrite("E:\\SciResearch\\BridgeProject\\20170606_195300\\twoImgResults\\tiledImgdown.jpg", tiledImg);
	upImg.copyTo(Mat(tiledImg, Rect(0, 0, upImg.cols, upImg.rows)));
	Mat leftPoint = Mat::zeros(3, 1, CV_64FC1);
	leftPoint.at<double>(0, 0) = 0;
	leftPoint.at<double>(1, 0) = downImg.rows - 1;
	leftPoint.at<double>(2, 0) = 1;

	Mat rightPoint = Mat::zeros(3, 1, CV_64FC1);
	rightPoint.at<double>(0, 0) = downImg.cols - 1;
	rightPoint.at<double>(1, 0) = downImg.rows - 1;
	rightPoint.at<double>(2, 0) = 1;

	Mat leftPmat = homo*leftPoint;
	Mat rightPmat = homo*rightPoint;
	int leftLoc = (int)(leftPmat.at<double>(1, 0) / (leftPmat.at<double>(2, 0)));
	int rightLoc = (int)(rightPmat.at<double>(1, 0) / (rightPmat.at<double>(2, 0)));

	int endLoc = leftLoc>rightLoc ? rightLoc : leftLoc;
	if (endLoc > tiledImg.rows){
		endLoc = tiledImg.rows;
	}
	cv::Mat tempImg = tiledImg(cv::Rect(0, 0, upImg.cols, endLoc));
	result = tempImg.clone();
}
void testGetMat(double* mosaic, int rowIndex, int cols, int j, cv::Mat& homo){
	int homoId = (rowIndex*(cols - 1) + j) * 9;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			int index = i * 3 + j;
			homo.at<double>(i, j) = mosaic[homoId + index];
		}
	}
}
void testGetMatVerti(double* mosaic, int rowIndex, int rows, int cols, cv::Mat& homo){
	//rowIndex指的是两幅图像拼接的时候，上面的那幅图像
	int used = (rows*(cols - 1)) * 9;
	int start = used + rowIndex * 9;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			homo.at<double>(i, j) = mosaic[start + i * 3 + j];
		}
	}

}
void testGetHorriAll(std::vector<string>& imgs, cv::Mat& result, int rows, int cols, int rowsIndex, double* mosaic){
	cv::Mat leftImg, rightImg, resultImg;
	//	double* arr=new double[9];

	for (int j = 0; j<cols - 1; j++){
		//cout << j << endl;

		if (j == 0){
			int imgIndex = rowsIndex*cols + j;
			//cout << imgs[imgIndex] << endl;
			leftImg = cv::imread(imgs[imgIndex]);
			rightImg = cv::imread(imgs[imgIndex + 1]);
			cv::resize(leftImg, leftImg, cv::Size(leftImg.cols / SCALE, leftImg.rows / SCALE));
			cv::resize(rightImg, rightImg, cv::Size(rightImg.cols / SCALE, rightImg.rows / SCALE));
			//	getLeftRightSurf(leftImg,rightImg,resultImg,arr);
			//	memcpy(horiArr+j*9*sizeof(double),arr,9*sizeof(double));
			cv::Mat homo(3, 3, CV_64FC1);
			testGetMat(mosaic, rowsIndex, cols, j, homo);
			testGetLeftRight(leftImg, rightImg, resultImg, homo);
		}
		else{
			int imgIndex = rowsIndex*cols + j;
			leftImg = resultImg;
			rightImg = cv::imread(imgs[imgIndex + 1]);
			cv::resize(rightImg, rightImg, cv::Size(rightImg.cols / SCALE, rightImg.rows / SCALE));
			//	getLeftRightSurf(leftImg,rightImg,resultImg,arr);
			//memcpy(horiArr+j*9*sizeof(double),arr,9*sizeof(double));
			cv::Mat homo(3, 3, CV_64FC1);
			testGetMat(mosaic, rowsIndex, cols, j, homo);
			testGetLeftRight(leftImg, rightImg, resultImg, homo);
		}

	}
	result = resultImg.clone();

}
int testStitch(const char* imgNames, char* outName, int rows, int cols, double* mosaicArr){
	int arrLength = ((cols - 1) * 9 * rows + (rows - 1) * 9)*sizeof(double);
	cv::Mat result;
	queue<cv::Mat> horiQueue;
	vector<string> fileNames, imgVec;
	//getFiles2(dire, fileNames);
	int imgCnt = rows*cols;
	char* dupNames = new char[256 * imgCnt];
	std::strcpy(dupNames, imgNames);
	char* startPtr = dupNames;
	int offset = 0;
	for (int i = 0; i < imgCnt; i++){
		offset = 0;
		while (startPtr[offset] != '|')
			offset++;

		startPtr[offset] = '\0';
		Mat img;
		img = imread(startPtr);
		//printf("%s\n", startPtr);
		if (img.data == NULL){
			return -2;//表示图像不存在
		}
		fileNames.push_back(startPtr);
		startPtr += (offset + 1);
	}
	delete[] dupNames;

	filesOrderAdjust(fileNames, imgVec, rows, cols);

	cv::Mat rowsImg = cv::imread(imgVec[0]);
	int cutRows = (int)(rowsImg.rows / SCALE)*(CUT_ROWS);
	//std::cout << "cutRows is " << cutRows << endl;
	rowsImg.release();

	for (int i = 0; i<rows; i++){
		cv::Mat horiResult;
		//getHoriAll(imgNames,horiResult,rows,cols,i,horriArr);
		testGetHorriAll(imgVec, horiResult, rows, cols, i, mosaicArr);
		//std::cout << "第 " << i << " 行执行完毕" << endl;
		//int length=(cols-1)*9*sizeof(double);

		//	memcpy(mosaicArr+i*(cols-1)*9,horiArr,length);
		horiResult = horiResult(cv::Rect(0, 0, horiResult.cols, horiResult.rows - cutRows));
		horiQueue.push(horiResult);
		//cv::imwrite("E:\\SciResearch\\BridgeProject\\20170606_195300\\tempImgs\\horiImg1.jpg",horiResult);
	}
	if (horiQueue.size() == 1){
		result = horiQueue.front();
		cv::imwrite(outName, result);
	}
	cv::Mat upImg = horiQueue.front();
	horiQueue.pop();
	//int filledLen=9*sizeof(double)*(cols-1)*rows;
	int rowIndex = 0;
	//int arrLen=9*sizeof(double);
	//int saveStart=(cols-1)*9*rows+rowIndex*9;
	while (!horiQueue.empty()){
		//double* saveStart = mosaicArr + (cols - 1) * 9 * rows + rowIndex * 9;
		cv::Mat  homo(3, 3, CV_64FC1);
		testGetMatVerti(mosaicArr, rowIndex, rows, cols, homo);
		//double* vertiArr=new double[9];
		cv::Mat downImg = horiQueue.front();
		horiQueue.pop();
		//getUpDownSurf1(upImg,downImg,result,vertiArr);
		testUpDownImg(upImg, downImg, result, homo);
		upImg = result;

		rowIndex++;
	}
	cv::imwrite(outName, result);
}

STITCHING_API STITCHING_HANDLE STITCHING_Create(){
	return NULL;
}
STITCHING_API int STITCHING_Destroy(STITCHING_HANDLE* hnd){
	return 0;
}
STITCHING_API int STITCHING_Process(STITCHING_HANDLE hnd, const char* imgNames, char* outName, int rows, int cols){
	int length = stitchImgs(imgNames, outName, rows, cols, mosaicArr, 10000);
	return length;

}
STITCHING_API int STITCHING_GetPosition(STITCHING_HANDLE hnd, int imgIndex, int posX, int posY, int* outPosX, int* outPosY){
	int rows = img_rows;
	int cols = img_cols;
	//int rows = 5;
	//int cols = 5;
	vector<int> order;
	for (int i = 0; i < rows; i++){
		if (i % 2 == 0){
			int begin = i*cols;
			for (int j = 0; j < cols; j++){
				order.push_back(begin);
				begin++;
			}
		}
		else{
			int begin = (i + 1)*cols - 1;
			for (int j = 0; j < cols; j++){
				order.push_back(begin);///////////
				begin--;
			}
		}
	}
	int imgRow = 0;
	int imgCol = 0;
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			if (i*cols + j == order[imgIndex]){
				imgRow = i;
				imgCol = j;
				break;
			}
		}
	}
	//cout << imgIndex << "  " << imgRow << "  " << imgCol << endl;
	//计算该点在每一行的坐标，如果图像的列为0，则没有对应的变换矩阵
	int horiArrIndex = imgRow*(cols - 1) + (imgCol - 1);
	//cout << "hoirIndex  " << horiArrIndex << endl;
	int vertiArrIndex = rows*(cols - 1) + imgRow - 1;

	//得到该幅图图像的在一行的行变换矩阵
	cv::Mat  horiHomo(3, 3, CV_64FC1);
	int startHori = horiArrIndex * 9;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			horiHomo.at<double>(i, j) = mosaicArr[startHori + i * 3 + j];
		}
	}
	//得到该幅图图像的在上下两行的变换矩阵
	cv::Mat vertiHomo(3, 3, CV_64FC1);
	int startVerti = vertiArrIndex * 9;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			vertiHomo.at<double>(i, j) = mosaicArr[startVerti + i * 3 + j];
		}
	}

	//计算该点在行图像中的坐标
	int horiX = 0;
	int horiY = 0;
	if (imgCol == 0){
		horiX = posX;
		horiY = posY;
	}
	else{
		//将该点的坐标fang入矩阵中
		Mat point = Mat::zeros(3, 1, CV_64FC1);
		point.at<double>(0, 0) = posX;
		point.at<double>(1, 0) = posY;
		point.at<double>(2, 0) = 1;

		Mat pointMat = horiHomo*point;
		horiX = (int)(pointMat.at<double>(0, 0) / (pointMat.at<double>(2, 0)));
		horiY = (int)(pointMat.at<double>(1, 0) / (pointMat.at<double>(2, 0)));
	}

	//计算该点在整幅图像中的坐标
	int resultX = 0;
	int resultY = 0;
	if (imgRow == 0){
		resultX = horiX;
		resultY = horiY;
	}
	else{
		Mat pointHori = Mat::zeros(3, 1, CV_64FC1);
		pointHori.at<double>(0, 0) = horiX;
		pointHori.at<double>(1, 0) = horiY;
		pointHori.at<double>(2, 0) = 1;
		Mat resultMat = vertiHomo*pointHori;
		resultX = (int)(resultMat.at<double>(0, 0) / (resultMat.at<double>(2, 0)));
		resultY = (int)(resultMat.at<double>(1, 0) / (resultMat.at<double>(2, 0)));
	}
	if (resultX > stitchImgCols - 1){
		resultX = stitchImgCols - 1;
	}
	if (resultX < 0){
		resultX = 0;
	}
	if (resultY > stitchImgRows - 1){
		resultY = stitchImgRows - 1;
	}
	if (resultY < 0){
		resultY = 0;
	}
	*outPosX = resultX;
	*outPosY = resultY;
	//cout << "x:" << *outPosX << "   y:" << *outPosY << endl;
	return 0;
}
STITCHING_API void STITCHING_testGetPos(cv::Mat& img, cv::Mat& resultGray, int imgIndex, STITCHING_HANDLE hnd){
	cv::Mat grayImg;
	cvtColor(img, grayImg, CV_BGR2GRAY);
	//imshow("img", grayImg);
	//imshow("img", grayImg);
	//cv::waitKey();
	cv::resize(grayImg, grayImg, cv::Size(grayImg.cols / SCALE, grayImg.rows / SCALE));
	int xp = 0;
	int yp = 0;
	int* x = &xp;
	int* y = &yp;
	//cout << grayImg.rows << "  " << grayImg.cols << endl;
	for (int i = 0; i < grayImg.rows; i++){
		for (int j = 0; j < grayImg.cols; j++){
			if (grayImg.at<uchar>(i, j)>0){
				STITCHING_GetPosition(hnd, imgIndex, j, i, x, y);
				if (*x<0 || *x >= stitchImgCols || (*y >= stitchImgRows) || *y<0){
					continue;
				}
				resultGray.at<uchar>(*y, *x) = 255;
				//cout  <<"*x==="<<*x << "   *y=== " << *y << endl;
			}
		}
	}

}


//20170606_195300左右两幅图的重叠区域约为3385，为宽度的58.76%，，，，3385+2375=5760
//上下两幅图的重叠区域为约为1443,为高度的37.57%，，，1443+2397=3840

//20170606_183503左右两幅图的重叠区域约为2617，为宽度的45.43%，，，，2613+3147=5760
//上下两幅图的重叠区域为约为1464,为高度的38.12%，，，1464+2376=3840
