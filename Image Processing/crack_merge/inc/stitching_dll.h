#pragma once
#include <opencv2/opencv.hpp>
#ifdef _WIN32
#ifdef stitchImgs_EXPORTS
#define STITCHING_API __declspec(dllexport)
#else
#define STITCHING_API __declspec(dllimport)
#endif
#else
#define STITCHING_API 
#endif
#ifdef __cplusplus
extern "C" {
#endif

	typedef void* STITCHING_HANDLE;
	typedef unsigned char uchar;

	STITCHING_API STITCHING_HANDLE STITCHING_Create();
	STITCHING_API int STITCHING_Destroy(STITCHING_HANDLE* hnd);
	STITCHING_API int STITCHING_Process(STITCHING_HANDLE hnd, const char* imgNames, char* outName, int rows, int cols);
	STITCHING_API int STITCHING_GetPosition(STITCHING_HANDLE hnd, int imgIndex, int posX, int posY, int* outPosX, int* outPosY);

	STITCHING_API void STITCHING_testGetPos(cv::Mat& img, cv::Mat& resultGray, int imgIndex, STITCHING_HANDLE hnd);
	enum{IN_BOUND = 0, OUT_OF_BOUND = -1};


#ifdef __cplusplus
}
#endif
