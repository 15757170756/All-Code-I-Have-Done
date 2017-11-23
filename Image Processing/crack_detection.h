#ifndef _CRACK_DETECTION_H
#define _CRACK_DETECTION_H


//#ifdef crack_detection_EXPORTS
//#define CRACK_API __declspec(dllexport)
//#else
//#define CRACK_API __declspec(dllimport)
//#endif

#define CRACK_API

#ifdef __cplusplus
extern "C" {
#endif

	typedef void* CRACK_DETECTOR_HANDLE;
	typedef unsigned char uchar;


	CRACK_API CRACK_DETECTOR_HANDLE CRACK_DETECTOR_Create();
	CRACK_API int CRACK_DETECTOR_Destroy(CRACK_DETECTOR_HANDLE* hnd);

	CRACK_API int CRACK_DETECTOR_Process(CRACK_DETECTOR_HANDLE hnd, uchar* imgData, int dataLen);

	CRACK_API int CRACK_DETECTOR_GetCrackNumber(CRACK_DETECTOR_HANDLE hnd);
	CRACK_API double CRACK_DETECTOR_GetCrackWidth(CRACK_DETECTOR_HANDLE hnd, int crackIndex);
	CRACK_API double CRACK_DETECTOR_GetCrackLength(CRACK_DETECTOR_HANDLE hnd, int crackIndex);
	CRACK_API int CRACK_DETECTOR_GetCrackPositions(CRACK_DETECTOR_HANDLE hnd, int crackIndex, int* outPos);


	CRACK_API int CRACK_DETECTOR_SetSmooth(CRACK_DETECTOR_HANDLE hnd, double sigma);
	CRACK_API int CRACK_DETECTOR_SetSeedsRange(CRACK_DETECTOR_HANDLE hnd, double range);
	CRACK_API int CRACK_DETECTOR_SetCrackDis(CRACK_DETECTOR_HANDLE hnd, double dis);
	CRACK_API int CRACK_DETECTOR_SetCrackLength(CRACK_DETECTOR_HANDLE hnd, double length);
	CRACK_API int CRACK_DETECTOR_SetWidthRange(CRACK_DETECTOR_HANDLE hnd, double range);
	CRACK_API int CRACK_DETECTOR_SetWidthAverage(CRACK_DETECTOR_HANDLE hnd, double average);


#ifdef __cplusplus
}
#endif




struct CrackInfor{
	double maxWidth;
	double width;
	double length;
	int vertexNum;//一条裂缝上的顶点的数量
	int vertexIdx[5000];
	int vertexIdy[5000];
};



#endif // _CRACK_DETECTION_H