#ifndef _CRACK_MERGE_H
#define _CRACK_MERGE_H


#ifdef crack_merge_EXPORTS
#define CRACK_MERGE_API __declspec(dllexport)
#else
#define CRACK_MERGE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	struct CRACK_INFO{
		double length;
		double width;
		double max_width;
		double contrast;
		int point_count;   /*该裂缝的像素点的个数，一对(x,y)是算一个*/
	};

	typedef void* STITCHING_HANDLE;

	// handler: STITCHING_Create() 所创建的句柄
	// file_names: 所有图文件的列表, '|'分隔
	// rows, cols: 几行几列
	// in_cracks: 所有裂缝信息，按图顺序排列
	// in_cracks_count: 每张图里的裂缝条数，按图顺序排列
	// in_cracks_data: 裂缝位置信息，按图顺序排列（每张图内可能有多个裂缝）
	// out_cracks, out_cracks_max_count: 输出裂缝信息
	// out_cracks_data, out_cracks_data_max_len: 输出裂缝位置信息
	CRACK_MERGE_API int MergeAllCracks(
		STITCHING_HANDLE handler, const char* file_names, int rows, int cols,
		CRACK_INFO* in_cracks, int* in_cracks_count, int* in_cracks_data,
		CRACK_INFO* out_cracks, int out_cracks_max_count, 
		int* out_cracks_data, int out_cracks_data_max_len);

#ifdef __cplusplus
}
#endif

#endif // _CRACK_MERGE_H