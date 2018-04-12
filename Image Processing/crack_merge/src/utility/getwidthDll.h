#pragma once
#include <vector>
//#include <opencv2/opencv.hpp>
#ifdef _WIN32
#ifdef getWidth_EXPORTS
#define GETWIDTH_API __declspec(dllexport)
#else
#define GETWIDTH_API __declspec(dllimport)
#endif
#else
#define GETWIDTH_API 
#endif


#ifdef __cplusplus
extern "C" {
#endif

	//using namespace cv;
	typedef void* GETWIDTH_HANDLE;
	typedef unsigned char uchar;

	GETWIDTH_API GETWIDTH_HANDLE GETWIDTH_Create();
	GETWIDTH_API int GETWIDTH_GetWidth(GETWIDTH_HANDLE* hnd, std::vector<double> &width, std::vector<int> &valid, const cv::Mat &srcImage, const std::vector<int> &xy_arr);


#ifdef __cplusplus
}
#endif