
#ifndef CAMERACALIBRATOR_H
#define CAMERACALIBRATOR_H

#include <vector>
#include <iostream>

#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
class CameraCalibrator {
private:
	//输入点
	std::vector<std::vector<cv::Point3f>> objectPoints;  //世界坐标系（3D）
	std::vector<std::vector<cv::Point2f>> imagePoints;  //像素坐标系（2D）
	//输出矩阵
	cv::Mat cameraMatrix; //摄像机内参数矩阵
	cv::Mat distCoeffs;  //透镜畸变系数矩阵
	std::vector<cv::Mat> rotateVectors;
	std::vector<cv::Mat> translationVectors;
	//标定方式
	int flag;
	//用于图像去畸变 
	cv::Mat map1, map2;
	bool mustInitUndistort;

public:
	CameraCalibrator() : flag(0), mustInitUndistort(true) {};

	//导入标定图片提取角点
	int addChessboardPoints(const std::vector<std::string>& filelist, cv::Size & boardSize);
	//添加场景点与对应的图像点
	void addPoints(const std::vector<cv::Point2f>& imageCorners, const std::vector<cv::Point3f>& objectCorners);
	// 标定相机
	double calibrate(cv::Size &imageSize);
	// 设置标定方式
	void setCalibrationFlag(bool radial8CoeffEnabled = false, bool tangentialParamEnabled = false);
	// 消除透镜畸变(标定之后调用有效)
	cv::Mat CameraCalibrator::remap(const cv::Mat &image);

	// 获取矩阵
	cv::Mat getCameraMatrix() const { return cameraMatrix; }
	cv::Mat getDistCoeffs()   const { return distCoeffs; }
	cv::Mat getRotateVectors(int idx) const { return rotateVectors[idx]; }
	cv::Mat getTranslationVectors(int idx)   const { return translationVectors[idx]; }
};

#endif


