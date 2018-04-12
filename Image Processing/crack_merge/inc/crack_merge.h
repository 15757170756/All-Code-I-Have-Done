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
		int point_count;   /*���ѷ�����ص�ĸ�����һ��(x,y)����һ��*/
	};

	typedef void* STITCHING_HANDLE;

	// handler: STITCHING_Create() �������ľ��
	// file_names: ����ͼ�ļ����б�, '|'�ָ�
	// rows, cols: ���м���
	// in_cracks: �����ѷ���Ϣ����ͼ˳������
	// in_cracks_count: ÿ��ͼ����ѷ���������ͼ˳������
	// in_cracks_data: �ѷ�λ����Ϣ����ͼ˳�����У�ÿ��ͼ�ڿ����ж���ѷ죩
	// out_cracks, out_cracks_max_count: ����ѷ���Ϣ
	// out_cracks_data, out_cracks_data_max_len: ����ѷ�λ����Ϣ
	CRACK_MERGE_API int MergeAllCracks(
		STITCHING_HANDLE handler, const char* file_names, int rows, int cols,
		CRACK_INFO* in_cracks, int* in_cracks_count, int* in_cracks_data,
		CRACK_INFO* out_cracks, int out_cracks_max_count, 
		int* out_cracks_data, int out_cracks_data_max_len);

#ifdef __cplusplus
}
#endif

#endif // _CRACK_MERGE_H