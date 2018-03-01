
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
	//�����
	std::vector<std::vector<cv::Point3f>> objectPoints;  //��������ϵ��3D��
	std::vector<std::vector<cv::Point2f>> imagePoints;  //��������ϵ��2D��
	//�������
	cv::Mat cameraMatrix; //������ڲ�������
	cv::Mat distCoeffs;  //͸������ϵ������
	std::vector<cv::Mat> rotateVectors;
	std::vector<cv::Mat> translationVectors;
	//�궨��ʽ
	int flag;
	//����ͼ��ȥ���� 
	cv::Mat map1, map2;
	bool mustInitUndistort;

public:
	CameraCalibrator() : flag(0), mustInitUndistort(true) {};

	//����궨ͼƬ��ȡ�ǵ�
	int addChessboardPoints(const std::vector<std::string>& filelist, cv::Size & boardSize);
	//��ӳ��������Ӧ��ͼ���
	void addPoints(const std::vector<cv::Point2f>& imageCorners, const std::vector<cv::Point3f>& objectCorners);
	// �궨���
	double calibrate(cv::Size &imageSize);
	// ���ñ궨��ʽ
	void setCalibrationFlag(bool radial8CoeffEnabled = false, bool tangentialParamEnabled = false);
	// ����͸������(�궨֮�������Ч)
	cv::Mat CameraCalibrator::remap(const cv::Mat &image);

	// ��ȡ����
	cv::Mat getCameraMatrix() const { return cameraMatrix; }
	cv::Mat getDistCoeffs()   const { return distCoeffs; }
	cv::Mat getRotateVectors(int idx) const { return rotateVectors[idx]; }
	cv::Mat getTranslationVectors(int idx)   const { return translationVectors[idx]; }
};

#endif


