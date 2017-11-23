#include <opencv2/opencv.hpp>
#include <iostream>

3.1 图像读取和灰度化

编程时采用上文所描述的第二种方法来实现图像的灰度化。其中ptr数组中保存的灰度化后的图像数据。具体的灰度化后的效果如图3所示。
[cpp] view plain copy
IplImage* ColorImage = cvLoadImage("12.jpg", -1);   //读入图像，获取彩图指针  
IplImage* OpenCvGrayImage;                            //定义变换后的灰度图指针  
unsigned char* ptr;                                   //指向图像的数据首地址  
if (ColorImage == NULL)
return;
int i = ColorImage->width * ColorImage->height;
BYTE data1;       //中间过程变量  
BYTE data2;
BYTE data3;
ptr = new unsigned char[i];
for (intj = 0; j < ColorImage->height; j++)                 //对RGB加权平均，权值参考OpenCV  
{
	for (intx = 0; x < ColorImage->width; x++)
	{
		data1 = (BYTE)ColorImage->imageData[j*ColorImage->widthStep + i * 3];     //B分量  
		data2 = (BYTE)ColorImage->imageData[j*ColorImage->widthStep + i * 3 + 1]; //G分量  
		data3 = (BYTE)ColorImage->imageData[j*ColorImage->widthStep + i * 3 + 2]; //R分量  
		ptr[j*ColorImage->width + x] = (BYTE)(0.072169*data1 + 0.715160*data2 + 0.212671*data3);
	}
}
OpenCvGrayImage = cvCreateImageHeader(cvGetSize(ColorImage), ColorImage->depth, 1);
cvSetData(GrayImage, ptr, GrayImage->widthStep);         //根据数据生成灰度图  
cvNamedWindow("GrayImage", CV_WINDOW_AUTOSIZE);
cvShowImage("GrayImage", OpenCvGrayImage);               //显示灰度图  
cvWaitKey(0);
cvDestroyWindow("GrayImage");


3.2 图像的高斯滤波

根据上面所讲的边缘检测过程，下一个步骤就是对图像进行高斯滤波。可根据之前博文描述的方法获取一维或者二维的高斯滤波核。因此进行图像高斯滤波可有两种实现方式，以下具体进行介绍。
首先定义该部分的通用变量：
[cpp] view plain copy
double nSigma = 0.4;                            //定义高斯函数的标准差  
int nWidowSize = 1 + 2 * ceil(3 * nSigma);            //定义滤波窗口的大小  
int nCenter = (nWidowSize) / 2;                   //定义滤波窗口中心的索引  
两种方法都需要用到的变量：
[cpp] view plain copy
int nWidth = OpenCvGrayImage->width;                             //获取图像的像素宽度  
int nHeight = OpenCvGrayImage->height;                           //获取图像的像素高度  
unsigned char* nImageData = new unsigned char[nWidth*nHeight];   //暂时保存图像中的数据  
unsigned char*pCanny = new unsigned char[nWidth*nHeight];        //为平滑后的图像数据分配内存  
double* nData = new double[nWidth*nHeight];                      //两次平滑的中间数据  
for (int j = 0; j < nHeight; j++)                                     //获取数据  
{
	for (i = 0; i < nWidth; i++)
		nImageData[j*nWidth + i] = (unsigned char)OpenCvGrayImage->imageData[j*nWidth + i];
}
3.2.1 根据一维高斯核进行两次滤波
1）生成一维高斯滤波系数
[cpp] view plain copy
//////////////////////生成一维高斯滤波系数/////////////////////////////  
double* pdKernal_1 = new double[nWidowSize];    //定义一维高斯核数组  
double  dSum_1 = 0.0;                           //求和，用于进行归一化          
////////////////////////一维高斯函数公式//////////////////////////////       
////                   x*x                           /////////////////  
////          -1*----------------                    /////////////////  
////         1     2*Sigma*Sigma                     /////////////////  
////   ------------ e                                /////////////////  
////                                                 /////////////////  
////   \/2*pi*Sigma                                  /////////////////  
//////////////////////////////////////////////////////////////////////  
for (int i = 0; i < nWidowSize; i++)
{
	double nDis = (double)(i - nCenter);
	pdKernal_1[i] = exp(-(0.5)*nDis*nDis / (nSigma*nSigma)) / (sqrt(2 * 3.14159)*nSigma);
	dSum_1 += pdKernal_1[i];
}
for (i = 0; i < nWidowSize; i++)
{
	pdKernal_1[i] /= dSum_1;                 //进行归一化  
}

2）分别进行x向和y向的一维加权滤波，滤波后的数据保存在矩阵pCanny中
[cpp] view plain copy
for (i = 0; i < nHeight; i++)                               //进行x向的高斯滤波(加权平均)  
{
	for (j = 0; j < nWidth; j++)
	{
		double dSum = 0;
		double dFilter = 0;                                       //滤波中间值  
		for (int nLimit = (-nCenter); nLimit <= nCenter; nLimit++)
		{
			if ((j + nLimit) >= 0 && (j + nLimit) < nWidth)       //图像不能超出边界  
			{
				dFilter += (double)nImageData[i*nWidth + j + nLimit] * pdKernal_1[nCenter + nLimit];
				dSum += pdKernal_1[nCenter + nLimit];
			}
		}
		nData[i*nWidth + j] = dFilter / dSum;
	}
}

for (i = 0; i < nWidth; i++)                                //进行y向的高斯滤波(加权平均)  
{
	for (j = 0; j < nHeight; j++)
	{
		double dSum = 0.0;
		double dFilter = 0;
		for (int nLimit = (-nCenter); nLimit <= nCenter; nLimit++)
		{
			if ((j + nLimit) >= 0 && (j + nLimit) < nHeight)       //图像不能超出边界  
			{
				dFilter += (double)nData[(j + nLimit)*nWidth + i] * pdKernal_1[nCenter + nLimit];
				dSum += pdKernal_1[nCenter + nLimit];
			}
		}
		pCanny[j*nWidth + i] = (unsigned char)(int)dFilter / dSum;
	}
}

3.2.2 根据二维高斯核进行滤波

1）生成二维高斯滤波系数
[cpp] view plain copy
//////////////////////生成一维高斯滤波系数//////////////////////////////////    
double* pdKernal_2 = new double[nWidowSize*nWidowSize]; //定义一维高斯核数组  
double  dSum_2 = 0.0;                                   //求和，进行归一化        
///////////////////////二维高斯函数公式////////////////////////////////////      
////                         x*x+y*y                        ///////////////  
////                   -1*--------------                ///////////////  
////         1             2*Sigma*Sigma                ///////////////  
////   ---------------- e                                   ///////////////  
////   2*pi*Sigma*Sigma                                     ///////////////  
///////////////////////////////////////////////////////////////////////////  
for (i = 0; i < nWidowSize; i++)
{
	for (int j = 0; j < nWidowSize; j++)
	{
		int nDis_x = i - nCenter;
		int nDis_y = j - nCenter;
		pdKernal_2[i + j*nWidowSize] = exp(-(1 / 2)*(nDis_x*nDis_x + nDis_y*nDis_y)
			/ (nSigma*nSigma)) / (2 * 3.1415926*nSigma*nSigma);
		dSum_2 += pdKernal_2[i + j*nWidowSize];
	}
}
for (i = 0; i < nWidowSize; i++)
{
	for (int j = 0; j < nWidowSize; j++)                 //进行归一化  
	{
		pdKernal_2[i + j*nWidowSize] /= dSum_2;
	}
}

2）采用高斯核进行高斯滤波，滤波后的数据保存在矩阵pCanny中
[cpp] view plain copy
int x;
int y;
for (i = 0; i < nHeight; i++)
{
	for (j = 0; j < nWidth; j++)
	{
		double dFilter = 0.0;
		double dSum = 0.0;
		for (x = (-nCenter); x <= nCenter; x++)                     //行  
		{
			for (y = (-nCenter); y <= nCenter; y++)             //列  
			{
				if ((j + x) >= 0 && (j + x) < nWidth && (i + y) >= 0 && (i + y) < nHeight) //判断边缘  
				{
					dFilter += (double)nImageData[(i + y)*nWidth + (j + x)]
						* pdKernal_2[(y + nCenter)*nWidowSize + (x + nCenter)];
					dSum += pdKernal_2[(y + nCenter)*nWidowSize + (x + nCenter)];
				}
			}
		}
		pCanny[i*nWidth + j] = (unsigned char)dFilter / dSum;
	}
}

3.3 图像增强——计算图像梯度及其方向
根据上文分析可知，实现代码如下
[cpp] view plain copy
//////////////////同样可以用不同的检测器/////////////////////////  
/////    P[i,j]=(S[i,j+1]-S[i,j]+S[i+1,j+1]-S[i+1,j])/2     /////  
/////    Q[i,j]=(S[i,j]-S[i+1,j]+S[i,j+1]-S[i+1,j+1])/2     /////  
/////////////////////////////////////////////////////////////////  
double* P = new double[nWidth*nHeight];                 //x向偏导数  
double* Q = new double[nWidth*nHeight];                 //y向偏导数  
int* M = new int[nWidth*nHeight];                       //梯度幅值  
double* Theta = new double[nWidth*nHeight];             //梯度方向  
//计算x,y方向的偏导数  
for (i = 0; i < (nHeight - 1); i++)
{
	for (j = 0; j < (nWidth - 1); j++)
	{
		P[i*nWidth + j] = (double)(pCanny[i*nWidth + min(j + 1, nWidth - 1)] - pCanny[i*nWidth + j] + pCanny[min(i + 1, nHeight - 1)*nWidth + min(j + 1, nWidth - 1)] - pCanny[min(i + 1, nHeight - 1)*nWidth + j]) / 2;
		Q[i*nWidth + j] = (double)(pCanny[i*nWidth + j] - pCanny[min(i + 1, nHeight - 1)*nWidth + j] + pCanny[i*nWidth + min(j + 1, nWidth - 1)] - pCanny[min(i + 1, nHeight - 1)*nWidth + min(j + 1, nWidth - 1)]) / 2;
	}
}
//计算梯度幅值和梯度的方向  
for (i = 0; i < nHeight; i++)
{
	for (j = 0; j < nWidth; j++)
	{
		M[i*nWidth + j] = (int)(sqrt(P[i*nWidth + j] * P[i*nWidth + j] + Q[i*nWidth + j] * Q[i*nWidth + j]) + 0.5);
		Theta[i*nWidth + j] = atan2(Q[i*nWidth + j], P[i*nWidth + j]) * 57.3;
		if (Theta[i*nWidth + j] < 0)
			Theta[i*nWidth + j] += 360;              //将这个角度转换到0~360范围  
	}
}


3.4 非极大值抑制

根据上文所述的工作原理，这部分首先需要求解每个像素点在其邻域内的梯度方向的两个灰度值，然后判断是否为潜在的边缘，如果不是则将该点灰度值设置为0.
首先定义相关的参数如下：
[cpp] view plain copy
unsigned char* N = new unsigned char[nWidth*nHeight];  //非极大值抑制结果  
int g1 = 0, g2 = 0, g3 = 0, g4 = 0;                            //用于进行插值，得到亚像素点坐标值  
double dTmp1 = 0.0, dTmp2 = 0.0;                           //保存两个亚像素点插值得到的灰度数据  
double dWeight = 0.0;                                    //插值的权重  
其次，对边界进行初始化：
[cpp] view plain copy
for (i = 0; i < nWidth; i++)
{
	N[i] = 0;
	N[(nHeight - 1)*nWidth + i] = 0;
}
for (j = 0; j < nHeight; j++)
{
	N[j*nWidth] = 0;
	N[j*nWidth + (nWidth - 1)] = 0;
}
进行局部最大值寻找，根据上文图1所述的方案进行插值，然后判优，实现代码如下：
[cpp] view plain copy
for (i = 1; i < (nWidth - 1); i++)
{
	for (j = 1; j < (nHeight - 1); j++)
	{
		int nPointIdx = i + j*nWidth;       //当前点在图像数组中的索引值  
		if (M[nPointIdx] == 0)
			N[nPointIdx] = 0;         //如果当前梯度幅值为0，则不是局部最大对该点赋为0  
		else
		{
			////////首先判断属于那种情况，然后根据情况插值///////  
			////////////////////第一种情况///////////////////////  
			/////////       g1  g2                  /////////////  
			/////////           C                   /////////////  
			/////////           g3  g4              /////////////  
			/////////////////////////////////////////////////////  
			if (((Theta[nPointIdx] >= 90) && (Theta[nPointIdx] < 135)) ||
				((Theta[nPointIdx] >= 270) && (Theta[nPointIdx] < 315)))
			{
				//////根据斜率和四个中间值进行插值求解  
				g1 = M[nPointIdx - nWidth - 1];
				g2 = M[nPointIdx - nWidth];
				g3 = M[nPointIdx + nWidth];
				g4 = M[nPointIdx + nWidth + 1];
				dWeight = fabs(P[nPointIdx]) / fabs(Q[nPointIdx]);   //反正切  
				dTmp1 = g1*dWeight + g2*(1 - dWeight);
				dTmp2 = g4*dWeight + g3*(1 - dWeight);
			}
			////////////////////第二种情况///////////////////////  
			/////////       g1                      /////////////  
			/////////       g2  C   g3              /////////////  
			/////////               g4              /////////////  
			/////////////////////////////////////////////////////  
			else if (((Theta[nPointIdx] >= 135) && (Theta[nPointIdx] < 180)) ||
				((Theta[nPointIdx] >= 315) && (Theta[nPointIdx] < 360)))
			{
				g1 = M[nPointIdx - nWidth - 1];
				g2 = M[nPointIdx - 1];
				g3 = M[nPointIdx + 1];
				g4 = M[nPointIdx + nWidth + 1];
				dWeight = fabs(Q[nPointIdx]) / fabs(P[nPointIdx]);   //正切  
				dTmp1 = g2*dWeight + g1*(1 - dWeight);
				dTmp2 = g4*dWeight + g3*(1 - dWeight);
			}
			////////////////////第三种情况///////////////////////  
			/////////           g1  g2              /////////////  
			/////////           C                   /////////////  
			/////////       g4  g3                  /////////////  
			/////////////////////////////////////////////////////  
			else if (((Theta[nPointIdx] >= 45) && (Theta[nPointIdx] < 90)) ||
				((Theta[nPointIdx] >= 225) && (Theta[nPointIdx] < 270)))
			{
				g1 = M[nPointIdx - nWidth];
				g2 = M[nPointIdx - nWidth + 1];
				g3 = M[nPointIdx + nWidth];
				g4 = M[nPointIdx + nWidth - 1];
				dWeight = fabs(P[nPointIdx]) / fabs(Q[nPointIdx]);   //反正切  
				dTmp1 = g2*dWeight + g1*(1 - dWeight);
				dTmp2 = g3*dWeight + g4*(1 - dWeight);
			}
			////////////////////第四种情况///////////////////////  
			/////////               g1              /////////////  
			/////////       g4  C   g2              /////////////  
			/////////       g3                      /////////////  
			/////////////////////////////////////////////////////  
			else if (((Theta[nPointIdx] >= 0) && (Theta[nPointIdx] < 45)) ||
				((Theta[nPointIdx] >= 180) && (Theta[nPointIdx] < 225)))
			{
				g1 = M[nPointIdx - nWidth + 1];
				g2 = M[nPointIdx + 1];
				g3 = M[nPointIdx + nWidth - 1];
				g4 = M[nPointIdx - 1];
				dWeight = fabs(Q[nPointIdx]) / fabs(P[nPointIdx]);   //正切  
				dTmp1 = g1*dWeight + g2*(1 - dWeight);
				dTmp2 = g3*dWeight + g4*(1 - dWeight);
			}
		}
		//////////进行局部最大值判断，并写入检测结果////////////////  
		if ((M[nPointIdx] >= dTmp1) && (M[nPointIdx] >= dTmp2))
			N[nPointIdx] = 128;
		else
			N[nPointIdx] = 0;
	}
}
3.5双阈值检测实现

1）定义相应参数如下

[cpp] view plain copy
int nHist[1024];
int nEdgeNum;             //可能边界数  
int nMaxMag = 0;          //最大梯度数  
int nHighCount;

2）构造灰度图的统计直方图，根据上文梯度幅值的计算公式可知，最大的梯度幅值为：

因此设置nHist为1024足够。以下实现统计直方图：
[cpp] view plain copy
for (i = 0; i < 1024; i++)
	nHist[i] = 0;
for (i = 0; i < nHeight; i++)
{
	for (j = 0; j < nWidth; j++)
	{
		if (N[i*nWidth + j] == 128)
			nHist[M[i*nWidth + j]]++;
	}
}
3）获取最大梯度幅值及潜在边缘点个数
[cpp] view plain copy
nEdgeNum = nHist[0];
nMaxMag = 0;                    //获取最大的梯度值        
for (i = 1; i < 1024; i++)           //统计经过“非最大值抑制”后有多少像素  
{
	if (nHist[i] != 0)       //梯度为0的点是不可能为边界点的  
	{
		nMaxMag = i;
	}
	nEdgeNum += nHist[i];   //经过non-maximum suppression后有多少像素  
}

4）计算两个阈值
[cpp] view plain copy
double  dRatHigh = 0.79;
double  dThrHigh;
double  dThrLow;
double  dRatLow = 0.5;
nHighCount = (int)(dRatHigh * nEdgeNum + 0.5);
j = 1;
nEdgeNum = nHist[1];
while ((j < (nMaxMag - 1)) && (nEdgeNum < nHighCount))
{
	j++;
	nEdgeNum += nHist[j];
}
dThrHigh = j;                                   //高阈值  
dThrLow = (int)((dThrHigh)* dRatLow + 0.5);    //低阈值  

这段代码的意思是，按照灰度值从低到高的顺序，选取前79%个灰度值中的最大的灰度值为高阈值，低阈值大约为高阈值的一半。这是根据经验数据的来的，至于更好地参数选取方法，作者后面会另文研究。
5）进行边缘检测
[cpp] view plain copy
SIZE sz;
sz.cx = nWidth;
sz.cy = nHeight;
for (i = 0; i < nHeight; i++)
{
	for (j = 0; j < nWidth; j++)
	{
		if ((N[i*nWidth + j] == 128) && (M[i*nWidth + j] >= dThrHigh))
		{
			N[i*nWidth + j] = 255;
			TraceEdge(i, j, dThrLow, N, M, sz);
		}
	}
}

以上代码在非极大值抑制产生的二值灰度矩阵的潜在点中按照高阈值寻找边缘，并以所找到的点为中心寻找邻域内满足低阈值的点，从而形成一个闭合的轮廓。然后对于不满足条件的点，可用如下代码直接删除掉。
[cpp] view plain copy
//将还没有设置为边界的点设置为非边界点  
for (i = 0; i < nHeight; i++)
{
	for (j = 0; j < nWidth; j++)
	{
		if (N[i*nWidth + j] != 255)
		{
			N[i*nWidth + j] = 0;   // 设置为非边界点  
		}
	}
}
其中TraceEdge函数为一个嵌套函数，用于在每个像素点的邻域内寻找满足条件的点。其实现代码如下：
[cpp] view plain copy
void TraceEdge(int y, int x, int nThrLow, LPBYTE pResult, int *pMag, SIZE sz)
{
	//对8邻域像素进行查询  
	int xNum[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int yNum[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	LONG yy, xx, k;
	for (k = 0; k < 8; k++)
	{
		yy = y + yNum[k];
		xx = x + xNum[k];
		if (pResult[yy*sz.cx + xx] == 128 && pMag[yy*sz.cx + xx] >= nThrLow)
		{
			//该点设为边界点  
			pResult[yy*sz.cx + xx] = 255;
			//以该点为中心再进行跟踪  
			TraceEdge(yy, xx, nThrLow, pResult, pMag, sz);
		}
	}
}
