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
	/*namedWindow("����ɫͨ��ͼ��");
	namedWindow("����ɫͨ��ͼ��");
	namedWindow("����ɫͨ��ͼ��");
	imshow("����ɫͨ��ͼ��", srcImageBGR[0]);
	imshow("����ɫͨ��ͼ��", srcImageBGR[1]);
	imshow("����ɫͨ��ͼ��", srcImageBGR[2]);*/

	for (int i = 0; i < 3; ++i)
		equalizeHist(srcImageBGR[i], srcImageBGR[i]);

	Mat resImage;
	merge(srcImageBGR, 3, resImage);

	imshow("�����⻯��Ĳ�ͼ��", resImage);
	imwrite("0006_1370_1360_equalizeHist.jpg", resImage);

	//waitKey(0);

	return 0;
}

