#include "crack_merge.h"
#include "longestPathByPoint.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "stitching_dll.h"
#include "ClosetPairFromTwoGroup.h"
#include "getwidthDll.h"
using namespace std;
struct CrackInputInfo
{
	CRACK_INFO info;
	int imgIdx;
	int *xy;
	int len;
};
static int ConnectNearLine(Edges &edges, const vector<vector<int> > &lines, double threshold = 4.);
//TODO: getWidth dll test
enum{ WIDTH_INVALID = 0, WIDTH_VALID = 1};
#define IMG_1_4 1
#define FAKE_WIDTH 1
//Fake getWidth
int getWidth(vector<double> &width, vector<int> &valid, const cv::Mat &img, const vector<int> &xy_arr)
{
	int point_cnt = xy_arr.size() / 2;
	width.resize(point_cnt);
	valid.resize(point_cnt);
	for (int i = 0; i < point_cnt; ++i)
	{
		width[i] = rand() * 1.0 / RAND_MAX;
		valid[i] = (rand() > (RAND_MAX / 2.0)) ? WIDTH_INVALID : WIDTH_VALID;
	}
	
	return 0;
}
void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}


CRACK_MERGE_API int MergeAllCracks(
	STITCHING_HANDLE handler, const char* file_names, int rows, int cols,
	CRACK_INFO* in_cracks, int* in_cracks_count, int* in_cracks_data,
	CRACK_INFO* out_cracks, int out_cracks_max_count,
	int* out_cracks_data, int out_cracks_data_max_len)
{
	//split file_names to get vec<names>
	string imgName(file_names);
	vector<string> img_names;
	cout << file_names << endl;
	SplitString(imgName, img_names, string("|"));

	Edges edges;
	int *in_xy = in_cracks_data;
	int imgCnt = rows * cols;
	vector<CrackInputInfo> crackIn;
	int in_cracks_idx = 0;
	double pixel_width;
	for (int imgIdx = 0; imgIdx < imgCnt; ++imgIdx)
	{
		int crackNum = in_cracks_count[imgIdx];
		for (int i = 0; i < crackNum; ++i)
		{
			CrackInputInfo info;
			info.imgIdx = imgIdx;
			info.info = in_cracks[in_cracks_idx++];
			info.xy = in_xy;
			in_xy += info.info.point_count * 2;
			crackIn.push_back(info);
			pixel_width = info.info.length / info.info.point_count;
		}
	}
	cout << "input " << in_cracks_idx << " cracks\n";
	
	vector<vector<int> > projected_line;
	GETWIDTH_HANDLE *hnd = NULL;
	cv::Mat img;
	string img_name;
	for (int i = 0; i < crackIn.size(); ++i)
	{
		CrackInputInfo &info = crackIn[i];
		int len = info.info.point_count * 2;
		cout << "crack " << i << " length = " << len / 2 << endl;
		
		// split lines by proj_flag 
		if (img_name.empty()|| img_names[info.imgIdx] != img_name)
		{
			std::cout << "Reading image :" << img_names[info.imgIdx] << std::endl;
			cv::Mat ori = cv::imread(img_names[info.imgIdx]);
#if IMG_1_4
			resize(ori, ori, cv::Size(ori.cols / 4, ori.rows / 4));
#endif
			img = ori;
			img_name = img_names[info.imgIdx];
		} else
		{
			std::cout << "Reloading image :" << img_names[info.imgIdx] << std::endl;
		}

		if (img.empty())
		{
			std::cout << "error on reading image :" << img_names[info.imgIdx] << endl;
			return 0;
		}

		vector<double> crack_width;
		vector<int> width_valid;
		vector<int> position(info.xy, info.xy + info.info.point_count * 2);
#if IMG_1_4
		std::transform(position.begin(), position.end(), position.begin(), [](int x) {return x / 4;});
#endif
#if FAKE_WIDTH
		getWidth(crack_width, width_valid, img, position);
#else
//		std::cout << "get width end" << std::endl;
		GETWIDTH_GetWidth(hnd, crack_width, width_valid, img, position);
#endif
//		img.release();
		for (int j = 0; j < len; ) {
			int nx, ny;
			while (j < len && STITCHING_GetPosition(handler, info.imgIdx, info.xy[j], info.xy[j + 1], &nx, &ny) == OUT_OF_BOUND)
			{
				j += 2;
			}
			vector<int> line; //loop variable
			vector<cv::KeyPoint> line_with_info;
			//update width in line_with_info
			while (j < len && STITCHING_GetPosition(handler, info.imgIdx, info.xy[j], info.xy[j + 1], &nx, &ny) == IN_BOUND)
			{
				line.push_back(nx);
				line.push_back(ny);
				// use cv::KeyPoint.size represent width, cv::KeyPoint.class_id represent valid flag
				line_with_info.emplace_back(nx, ny, crack_width[j / 2], -1, 0, 0, width_valid[j / 2]);
				j += 2;
			}

			if (line.size() > 1) {
				edges.addLine(line_with_info);
				projected_line.push_back(line);
			}
		}	
	}
	img.release();
	cout << "spliting begin" << endl;
	//connect lines if min(pairwise point distance) below threshold
	// use projected_line
	double connect_st = cv::getTickCount();
	ConnectNearLine(edges, projected_line, 30);
	cout << "connect nearby lines cost :" << (cv::getTickCount() - connect_st) / cv::getTickFrequency() * 1000 << " ms\n";
	SplitTree split;
	//TODO: adjust value 20
	split(&edges, 3);
	cout << "spliting end" << endl;
	vector<vector<cv::KeyPoint> > lines_out;
	split.getSortedLines(lines_out, [](const vector<cv::KeyPoint> &v1, const vector<cv::KeyPoint> &v2) {return v1.size() > v2.size(); });
	int out_crack_num = min((int)lines_out.size(), out_cracks_max_count);

	int *outPtr = out_cracks_data;
	cout << "line_out.size() = " << lines_out.size() << endl;
	cout << "out_cracks_max_count = " << out_cracks_max_count << endl;
	for (int i = 0; i < out_crack_num; ++i)
	{
		if (outPtr - out_cracks_data + lines_out[i].size() * 2 >= out_cracks_data_max_len)
		{
			out_crack_num = i;
			break;
		}
		CRACK_INFO info;
		cout << "CRACK " << i << " has " << lines_out[i].size()<< " points \n";
		info.point_count = lines_out[i].size();
		info.length = info.point_count * pixel_width;
		//write to outPtr
		//width info update interface
		double widthMax = DBL_MIN;
//		double widthMin = DBL_MAX;
		double widthAvg = 0;
		int valid_cnt = 0;
		for (int j = 0; j < lines_out[i].size(); ++j)
		{
			
			outPtr[j * 2] = lines_out[i][j].pt.x;
			outPtr[j * 2 + 1] = lines_out[i][j].pt.y;
			if (lines_out[i][j].class_id == WIDTH_VALID){
				double width = lines_out[i][j].size;
#if IMG_1_4
				width *= 4;
#endif
				widthMax = max(width, widthMax);

				//			widthMin = min(width, widthMin);
				widthAvg += width;
				valid_cnt++;
			}
		}
		if (valid_cnt == 0) {
			valid_cnt = 1;
		}
		info.width = widthAvg / valid_cnt;
		info.max_width = widthMax;
//		copy(lines_out[i].begin(), lines_out[i].end(), outPtr);
		outPtr += lines_out[i].size() * 2;
		out_cracks[i] = info;
	}
	
	return out_crack_num;
}

static int ConnectNearLine(Edges &edges, const vector<vector<int> > &lines, double threshold)
{
	int sz = lines.size();
	ClosetPairFromTwoGroup cls;
	auto dist = [](int x, int y, int xx, int yy)
	{
		return sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
	};
	for (int i = 0; i < sz; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			vector<int> nearest_pair = cls.findClosetPairNaive(lines[i].data(), lines[i].size(), lines[j].data(), lines[j].size());
			vector<cv::KeyPoint> kpt_arr;
			if (dist(nearest_pair[0], nearest_pair[1], nearest_pair[2], nearest_pair[3]) < threshold)
			{
				int u, v;
				
				u = edges.get_id(nearest_pair[0], nearest_pair[1]);
				v = edges.get_id(nearest_pair[2], nearest_pair[3]);
				if (u == -1 || v == -1)
				{
					cout << "******************ERROR*****************" << endl;
					cout << nearest_pair[0] << endl << nearest_pair[1] << endl << nearest_pair[2] << endl << nearest_pair[3] << endl;
					cout << "lines size = "<<lines[i].size() << endl << lines[j].size() << endl;
				}
				kpt_arr.push_back(edges.getPointViaId(u));
				kpt_arr.push_back(edges.getPointViaId(v));
//				cv::KeyPoint k1, k2;
//				k1 = cv::KeyPoint(nearest_pair[0], nearest_pair[1], 0);
//				k2 = cv::KeyPoint(nearest_pair[2], nearest_pair[3], 0);
//				kpt_arr.push_back(k1);
//				kpt_arr.push_back(k2);
//				if (u == -1 || v == -1)
//				{
//					cout << "******************ERROR*****************" << endl;
//					cout << nearest_pair[0] << endl << nearest_pair[1] << endl << nearest_pair[2] << endl << nearest_pair[3] << endl;
//				}
				edges.addLine(kpt_arr); // just add one edge
//				cout << i << "->" << j << " : " << dist(nearest_pair[0], nearest_pair[1], nearest_pair[2], nearest_pair[3]) << endl;
//				cout << "\tsize of i =" << lines[i].size() / 2 << "\n\tsize of j = " << lines[j].size() / 2 << endl;
			}
		}
	}
	return 0;
}