#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>  
#include<vector>  

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("0006_1370_1360.jpg");
	Mat srcImageBGR[3];
	split(srcImage, srcImageBGR);
	/*namedWindow("【蓝色通道图】");
	namedWindow("【绿色通道图】");
	namedWindow("【红色通道图】");
	imshow("【蓝色通道图】", srcImageBGR[0]);
	imshow("【绿色通道图】", srcImageBGR[1]);
	imshow("【红色通道图】", srcImageBGR[2]);*/

	for (int i = 0; i < 3; ++i)
		equalizeHist(srcImageBGR[i], srcImageBGR[i]);

	Mat resImage;
	merge(srcImageBGR, 3, resImage);

	imshow("【均衡化后的彩图】", resImage);
	imwrite("0006_1370_1360_equalizeHist.jpg", resImage);

	//waitKey(0);

	return 0;
}

