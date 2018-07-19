#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>

using namespace::std;
using namespace::cv;

int main()
{
#if 1
	string imgName = "1-6_.JPG";
	KeyPoint p1;
	Mat img = imread(imgName);
	cout << img.step << endl << img.cols << endl
		<< img.rows << endl << img.channels() << endl
		<< img.depth() << endl << img.type() << endl
		<< img.size << endl;
	//int rows = img.rows, colums = img.cols;
	//int rowPart = rows / 4, colPart = colums / 4;
	//cout << rowPart << ' ' << colPart << endl;
	//for (int i = 0; i < 4; ++i) {
	//	for (int j = 0; j < 4; ++j) {
	//		Mat tmpImg = 
	//			img(Range(i*rowPart, i*rowPart + 960), Range(j*colPart, j*colPart+1440));
	//		//Mat tmpImg = img(Range(1, 1), Range(1440, 960));
	//		ostringstream ss;
	//		ss << i + 1 << '-' << j + 1 << ".jpg";
	//		string tmpImgName = ss.str();
	//		cout << tmpImgName << endl;
	//		imwrite(tmpImgName, tmpImg);
	//	}
	//}
#endif
	//cv::Mat src = cv::imread("1-1.jpg");
	//cv::Mat dst;

	////旋转角度  
	//double angle = 45;

	//cv::Size src_sz = src.size();
	//cv::Size dst_sz(src_sz.height*2, src_sz.width*2);
	//int len = std::max(src.cols, src.rows);

	////指定旋转中心  
	//cv::Point2f center(len / 2., len / 2.);

	////获取旋转矩阵（2x3矩阵）  
	//cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, 1.0);
	//cout << rot_mat << endl;

	////根据旋转矩阵进行仿射变换  
	//cv::warpAffine(src, dst, rot_mat, dst_sz);

	////显示旋转效果  
	//cv::imshow("image", src);
	//cv::imshow("result", dst);

	//cv::imwrite("1-1rotate45.jpg", dst);

	//cv::waitKey(0);


	return 0;


}