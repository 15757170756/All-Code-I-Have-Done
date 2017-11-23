//�˴����ǽ��ѷ����������۵ĳ���Ķ�֮����°汾������Ϊ�����ؼ������������groundTruth,
//�Լ�����ȵ�ground  truth,ָ����鵽�ģ�PPT����д�ı���һ��

#include<opencv2/opencv.hpp>
#include<ctime>
//#include<stdlib.h>
#include"crack_detection.h"
#include<cstdio>
#include<iostream>
#include<Image.h>
#define DERI_TH  (30/255.)
#define WIDTH  1296
#define HEIGHT  864
int getImgLength(FILE* file) {
	//FILE *file = fopen(fileName, "r");
	int curpos,length;
	curpos = ftell(file);
	assert(file != NULL);
	fseek(file, 0L, SEEK_END);
	length = ftell(file);
	fseek(file, curpos, SEEK_SET);
	return length;
}
void main()
{
	clock_t start,finish;
	start = clock();
	
	//img.imread("E:/DCIM/100CANON/IMG_4383.jpg");
	//img.imread("E:\\SciResearch\\BridgeProject\\DCIM\\100CANON\\test.png");
	//img.imread("E:\\SciResearch\\BridgeProject\\DCIM\\100CANON\\IMG_4457.jpg");
	//img.imread("E:\\SciResearch\\BridgeProject\\XDNewImg\\0U0A0074.jpg");
	//cv::Mat srcImg = cv::imread("E:\\SciResearch\\BridgeProject\\DCIM\\100CANON\\IMG_4465.jpg");
	//imshow("pg",srcImg);

	int fileLength;

	FILE* file = fopen("0001_0600_0000.jpg","rb");
	//FILE* file = fopen("D:\\BridgeProject\\partTest\\save\\4-4.jpg", "rb");  //��һ���޸�
	//FILE* file = fopen("D:\\BridgeProject\\20170425Width\\0U0A1075-3.jpg", "rb");

	//�˴���ȡ�ĵ��ǲ������ܵ�ͼƬ
	//FILE*  file = fopen("D:\\BridgeProject\\partTest\\PerformaceTest\\srcImg\\0U0A0103.JPG", "rb");
	//FILE*  file = fopen("D:\\BridgeProject\\partTest\\PerformaceTest\\drawPicture\\0023_1150_0800.jpg", "rb");
	//FILE*  file = fopen("D:\\BridgeProject\\20170426_211605\\0030_0550_1000.jpg", "rb");
	FImage showImg;
	showImg.imread("0001_0600_0000.jpg");
	//showImg.imread("D:\\BridgeProject\\partTest\\save\\4-4.jpg");   //�ڶ����޸�

	//showImg.imread("D:\\BridgeProject\\20170425Width\\0U0A1075-3.jpg");
	//showImg.imread("D:\\BridgeProject\\partTest\\PerformaceTest\\srcImg\\0U0A0103.JPG");
	//showImg.imread("D:\\BridgeProject\\partTest\\PerformaceTest\\drawPicture\\0023_1150_0800.jpg");
	//showImg.imread("D:\\BridgeProject\\20170426_211605\\0030_0550_1000.jpg");

	 


	FImage grayImg;
	showImg.desaturate(grayImg);
	//grayImg.imresize(0.25);
	//grayImg.imshow("gray");
	int grayWidth = grayImg.width();
	int grayHeight = grayImg.height();

	fileLength = getImgLength(file);
	unsigned char *buff = new unsigned char[fileLength];
	fread(buff, sizeof(uchar), fileLength, file);

	CRACK_DETECTOR_HANDLE hnd = CRACK_DETECTOR_Create();
	CRACK_DETECTOR_Process(hnd, buff, fileLength);

	int crackNum = 0;
	crackNum = CRACK_DETECTOR_GetCrackNumber(hnd);
	std::cout<<"the number of the crack is:"<<crackNum<<std::endl;

	double width = 0;
	width = CRACK_DETECTOR_GetCrackWidth(hnd, 0);
	//std::cout<<"the width of the crack 1 is "<<width<<std::endl;


	double length = 0;
	length = CRACK_DETECTOR_GetCrackLength(hnd, 0);
	std::cout<<"the length of the crack 1 is "<<length<<std::endl;

	int outPosNum = 0;
	int* outPos = new int[2 * grayWidth * grayHeight];
	outPosNum = CRACK_DETECTOR_GetCrackPositions(hnd, 0, outPos);

	grayImg.setValue(0);
	for(int i = 0; i < outPosNum*2 - 1; i++){
		int j = i + 1;
		grayImg[outPos[j] * grayWidth + outPos[i]] = 255;
		i++;
	}
	grayImg.imshow("firstCrack");
	finish = clock();
	double total = (double)(finish - start)/CLOCKS_PER_SEC;
	printf("the total time is:%lf s\n",total);
	cv::waitKey(0);
	delete[] outPos;
}
