/*
https://blog.csdn.net/guduruyu/article/details/70799804

OpenCv
*/

cv::Mat src = cv::imread("lenna.jpg");
cv::Mat dst;

//旋转角度  
double angle = 45;

cv::Size src_sz = src.size();
cv::Size dst_sz(src_sz.height, src_sz.width);
int len = std::max(src.cols, src.rows);

//指定旋转中心  
cv::Point2f center(len / 2., len / 2.);

//获取旋转矩阵（2x3矩阵）  
cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, 1.0);

//根据旋转矩阵进行仿射变换  
cv::warpAffine(src, dst, rot_mat, dst_sz);

//显示旋转效果  
cv::imshow("image", src);
cv::imshow("result", dst);

cv::waitKey(0);

return 0;





/*
https://www.cnblogs.com/tingshuo/archive/2011/05/15/2047016.html
原理＋代码

https://blog.csdn.net/lkj345/article/details/50555870

https://blog.csdn.net/liyuan02/article/details/6750828
*/

#include <stdio.h>
#include <string>
#include <math.h>
#include <windows.h>
using namespace std;

#define PI 3.1415926535
//角度到弧度转化
#define RADIAN(angle) ((angle)*PI/180.0)

void Rotation(const string& srcFile, const string& desFile, int angle)
{
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;

	FILE *pFile;
	if ((pFile = fopen(srcFile.c_str(), "rb")) == NULL)
	{
		printf("open bmp file error.");
		exit(-1);
	}
	//读取文件和Bitmap头信息
	fseek(pFile, 0, SEEK_SET);
	fread(&bmfHeader, sizeof(BITMAPFILEHEADER), 1, pFile);
	fread(&bmiHeader, sizeof(BITMAPINFOHEADER), 1, pFile);
	//先不支持小于16位的位图
	int bitCount = bmiHeader.biBitCount;
	if (bitCount < 16)
	{
		exit(-1);
	}
	int srcW = bmiHeader.biWidth;
	int srcH = bmiHeader.biHeight;
	//原图像每一行去除偏移量的字节数
	int lineSize = bitCount * srcW / 8;
	//偏移量，windows系统要求每个扫描行按四字节对齐
	int alignBytes = ((bmiHeader.biWidth * bitCount + 31) & ~31) / 8L
		- bmiHeader.biWidth * bitCount / 8L;
	//原图像缓存
	int srcBufSize = lineSize * srcH;
	BYTE* srcBuf = new BYTE[srcBufSize];
	int i, j;
	//读取文件中数据
	for (i = 0; i < srcH; i++)
	{
		fread(&srcBuf[lineSize * i], lineSize, 1, pFile);
		fseek(pFile, alignBytes, SEEK_CUR);
	}
	//以图像中心为原点左上角，右上角，左下角和右下角的坐标,用于计算旋转后的图像的宽和高
	POINT pLT, pRT, pLB, pRB;
	pLT.x = -srcW / 2; pLT.y = srcH / 2;
	pRT.x = srcW / 2; pRT.y = srcH / 2;
	pLB.x = -srcW / 2; pLB.y = -srcH / 2;
	pRB.x = srcW / 2; pRB.y = -srcH / 2;
	//旋转之后的坐标
	POINT pLTN, pRTN, pLBN, pRBN;
	double sina = sin(RADIAN(angle));
	double cosa = cos(RADIAN(angle));

	pLTN.x = pLT.x*cosa + pLT.y*sina;
	pLTN.y = -pLT.x*sina + pLT.y*cosa;

	pRTN.x = pRT.x*cosa + pRT.y*sina;
	pRTN.y = -pRT.x*sina + pRT.y*cosa;

	pLBN.x = pLB.x*cosa + pLB.y*sina;
	pLBN.y = -pLB.x*sina + pLB.y*cosa;

	pRBN.x = pRB.x*cosa + pRB.y*sina;
	pRBN.y = -pRB.x*sina + pRB.y*cosa;
	//旋转后图像宽和高
	int desWidth = max(abs(pRBN.x - pLTN.x), abs(pRTN.x - pLBN.x));
	int desHeight = max(abs(pRBN.y - pLTN.y), abs(pRTN.y - pLBN.y));
	//分配旋转后图像的缓存
	int desBufSize = ((desWidth * bitCount + 31) / 32) * 4 * desHeight;
	BYTE *desBuf = new BYTE[desBufSize];
	//将所有像素都预置为白色
	memset(desBuf, 255, desBufSize);
	//新图像每一行字节数，带有偏移量
	int desLineSize = ((desWidth * bitCount + 31) / 32) * 4;
	//通过新图像的坐标，计算对应的原图像的坐标
	for (i = 0; i < desHeight; i++)
	{
		for (j = 0; j < desWidth; j++)
		{
			//转换到以图像为中心的坐标系，并进行逆旋转
			int tX = (j - desWidth / 2)*cos(RADIAN(360 - angle)) 
				+ (-i + desHeight / 2)*sin(RADIAN(360 - angle));

			int tY = -(j - desWidth / 2)*sin(RADIAN(360 - angle)) 
				+ (-i + desHeight / 2)*cos(RADIAN(360 - angle));
			//如果这个坐标不在原图像内，则不赋值
			if (tX > srcW / 2 || tX < -srcW / 2 
				|| tY > srcH / 2 || tY < -srcH / 2)
				continue;
			//再转换到原坐标系下
			int tXN = tX + srcW / 2; int tYN = abs(tY - srcH / 2);
			//值拷贝
			memcpy(&desBuf[i * desLineSize + j * bitCount / 8], 
				&srcBuf[tYN * lineSize + tXN * bitCount / 8], 3);
		}
	}

	//创建目标文件
	HFILE hfile = _lcreat(desFile.c_str(), 0);
	//文件头信息
	BITMAPFILEHEADER nbmfHeader;
	nbmfHeader.bfType = 0x4D42;
	nbmfHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
		+ desWidth * desHeight * bitCount / 8;
	nbmfHeader.bfReserved1 = 0;
	nbmfHeader.bfReserved2 = 0;
	nbmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	//Bitmap头信息
	BITMAPINFOHEADER   bmi;
	bmi.biSize = sizeof(BITMAPINFOHEADER);
	bmi.biWidth = desWidth;
	bmi.biHeight = desHeight;
	bmi.biPlanes = 1;
	bmi.biBitCount = bitCount;
	bmi.biCompression = BI_RGB;
	bmi.biSizeImage = 0;
	bmi.biXPelsPerMeter = 0;
	bmi.biYPelsPerMeter = 0;
	bmi.biClrUsed = 0;
	bmi.biClrImportant = 0;

	//写入文件头信息
	_lwrite(hfile, (LPCSTR)&nbmfHeader, sizeof(BITMAPFILEHEADER));
	//写入Bitmap头信息
	_lwrite(hfile, (LPCSTR)&bmi, sizeof(BITMAPINFOHEADER));
	//写入图像数据
	_lwrite(hfile, (LPCSTR)desBuf, desBufSize);
	_lclose(hfile);
}

int main(int argc, char* argv[])
{
	FILE *pFile;
	if ((pFile = fopen("e://t.bmp", "rb")) == NULL)
	{
		printf("open bmp file error.");
		return -1;
	}
	string srcFile("e://t.bmp");
	string desFile("e://Rotation.bmp");
	Rotation(srcFile, desFile, 150);
	system("pause");
	return 0;
}