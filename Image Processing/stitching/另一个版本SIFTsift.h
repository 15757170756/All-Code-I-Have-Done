//vs2010+opencv2.2
//zdd
//Just For Fun
//zddmail@gmail.com
//2012年5月17日16:16:11

#ifndef SIFT_H
#define SIFT_H

#include <opencv2/opencv.hpp>
using namespace cv;

typedef double pixel_t;//像素类型

//初始sigma
#define INIT_SIGMA 0.5

//sigma 
#define SIGMA 1.6

//intervals
#define INTERVALS 3
 
//r
#define RATIO 10
  
#define MAX_INTERPOLATION_STEPS 5 
  
//|D(x^)| < 0.03   0.03极值点太多
#define DXTHRESHOLD 0.03

//bins = 36
#define ORI_HIST_BINS 36    

#define ORI_SIGMA_TIMES 1.5

#define ORI_WINDOW_RADIUS 3.0 * ORI_SIGMA_TIMES 

#define ORI_SMOOTH_TIMES 2
  
#define ORI_PEAK_RATIO 0.8

#define FEATURE_ELEMENT_LENGTH 128

#define DESCR_HIST_BINS 8

#define IMG_BORDER 5 

#define DESCR_WINDOW_WIDTH 4

#define DESCR_SCALE_ADJUST 3

#define DESCR_MAG_THR 0.2

#define INT_DESCR_FCTR 512.0
  
 
struct Keypoint
{
	int octave; //关键点所在组
	int interval;// 关键点所在层

	double offset_interval;//调整后的层的增量

	int x; //x,y坐标,根据octave和interval可取的层内图像
	int y;

	//scale = sigma0*pow(2.0, o+s/S)
	double scale; //空间尺度坐标

	double dx; //特征点坐标，该坐标被缩放成原图像大小 
	double dy;

	double offset_x;
	double offset_y;

	//高斯金字塔组内各层尺度坐标，不同组的相同层的sigma值相同
	//关键点所在组的组内尺度
	double octave_scale; //offset_i;

	double ori;//方向

	int descr_length;
	double descriptor[FEATURE_ELEMENT_LENGTH]; //

	double val;//极值
};
void read_features(Vector<Keypoint>&features, const char*file);//xx
void write_features(const Vector<Keypoint>&features, const char*file);

void testInverse3D();

void write_pyr(const Vector<Mat>& pyr, const char* dir);

void DrawKeyPoints(Mat &src, Vector<Keypoint>& keypoints);

const char* GetFileName(const char* dir, int i);

void ConvertToGray(const Mat& src, Mat& dst);

void DownSample(const Mat& src, Mat& dst);

void UpSample(const Mat& src, Mat& dst);

void GaussianTemplateSmooth(const Mat &src, Mat &dst, double);

void GaussianSmooth2D(const Mat &src, Mat &dst, double sigma);

void GaussianSmooth(const Mat &src, Mat &dst, double sigma);

void Sift(const Mat &src, Vector<Keypoint>& features, double sigma=SIGMA, int intervals=INTERVALS);

void CreateInitSmoothGray(const Mat &src, Mat &dst, double);

void GaussianPyramid(const Mat &src, Vector<Mat>&gauss_pyr, int octaves, int intervals, double sigma);

void Sub(const Mat& a, const Mat& b, Mat & c);

void DogPyramid(const Vector<Mat>& gauss_pyr, Vector<Mat>& dog_pyr, int octaves, int intervals);

void DetectionLocalExtrema(const Vector<Mat>& dog_pyr, Vector<Keypoint>& extrema, int octaves, int intervals);

void DrawSiftFeatures(Mat& src, Vector<Keypoint>& features);

#endif