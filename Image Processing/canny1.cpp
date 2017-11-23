#include <opencv2/opencv.hpp>
#include <iostream>

3.1 ͼ���ȡ�ͻҶȻ�

���ʱ���������������ĵڶ��ַ�����ʵ��ͼ��ĻҶȻ�������ptr�����б���ĻҶȻ����ͼ�����ݡ�����ĻҶȻ����Ч����ͼ3��ʾ��
[cpp] view plain copy
IplImage* ColorImage = cvLoadImage("12.jpg", -1);   //����ͼ�񣬻�ȡ��ͼָ��  
IplImage* OpenCvGrayImage;                            //����任��ĻҶ�ͼָ��  
unsigned char* ptr;                                   //ָ��ͼ��������׵�ַ  
if (ColorImage == NULL)
return;
int i = ColorImage->width * ColorImage->height;
BYTE data1;       //�м���̱���  
BYTE data2;
BYTE data3;
ptr = new unsigned char[i];
for (intj = 0; j < ColorImage->height; j++)                 //��RGB��Ȩƽ����Ȩֵ�ο�OpenCV  
{
	for (intx = 0; x < ColorImage->width; x++)
	{
		data1 = (BYTE)ColorImage->imageData[j*ColorImage->widthStep + i * 3];     //B����  
		data2 = (BYTE)ColorImage->imageData[j*ColorImage->widthStep + i * 3 + 1]; //G����  
		data3 = (BYTE)ColorImage->imageData[j*ColorImage->widthStep + i * 3 + 2]; //R����  
		ptr[j*ColorImage->width + x] = (BYTE)(0.072169*data1 + 0.715160*data2 + 0.212671*data3);
	}
}
OpenCvGrayImage = cvCreateImageHeader(cvGetSize(ColorImage), ColorImage->depth, 1);
cvSetData(GrayImage, ptr, GrayImage->widthStep);         //�����������ɻҶ�ͼ  
cvNamedWindow("GrayImage", CV_WINDOW_AUTOSIZE);
cvShowImage("GrayImage", OpenCvGrayImage);               //��ʾ�Ҷ�ͼ  
cvWaitKey(0);
cvDestroyWindow("GrayImage");


3.2 ͼ��ĸ�˹�˲�

�������������ı�Ե�����̣���һ��������Ƕ�ͼ����и�˹�˲����ɸ���֮ǰ���������ķ�����ȡһά���߶�ά�ĸ�˹�˲��ˡ���˽���ͼ���˹�˲���������ʵ�ַ�ʽ�����¾�����н��ܡ�
���ȶ���ò��ֵ�ͨ�ñ�����
[cpp] view plain copy
double nSigma = 0.4;                            //�����˹�����ı�׼��  
int nWidowSize = 1 + 2 * ceil(3 * nSigma);            //�����˲����ڵĴ�С  
int nCenter = (nWidowSize) / 2;                   //�����˲��������ĵ�����  
���ַ�������Ҫ�õ��ı�����
[cpp] view plain copy
int nWidth = OpenCvGrayImage->width;                             //��ȡͼ������ؿ��  
int nHeight = OpenCvGrayImage->height;                           //��ȡͼ������ظ߶�  
unsigned char* nImageData = new unsigned char[nWidth*nHeight];   //��ʱ����ͼ���е�����  
unsigned char*pCanny = new unsigned char[nWidth*nHeight];        //Ϊƽ�����ͼ�����ݷ����ڴ�  
double* nData = new double[nWidth*nHeight];                      //����ƽ�����м�����  
for (int j = 0; j < nHeight; j++)                                     //��ȡ����  
{
	for (i = 0; i < nWidth; i++)
		nImageData[j*nWidth + i] = (unsigned char)OpenCvGrayImage->imageData[j*nWidth + i];
}
3.2.1 ����һά��˹�˽��������˲�
1������һά��˹�˲�ϵ��
[cpp] view plain copy
//////////////////////����һά��˹�˲�ϵ��/////////////////////////////  
double* pdKernal_1 = new double[nWidowSize];    //����һά��˹������  
double  dSum_1 = 0.0;                           //��ͣ����ڽ��й�һ��          
////////////////////////һά��˹������ʽ//////////////////////////////       
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
	pdKernal_1[i] /= dSum_1;                 //���й�һ��  
}

2���ֱ����x���y���һά��Ȩ�˲����˲�������ݱ����ھ���pCanny��
[cpp] view plain copy
for (i = 0; i < nHeight; i++)                               //����x��ĸ�˹�˲�(��Ȩƽ��)  
{
	for (j = 0; j < nWidth; j++)
	{
		double dSum = 0;
		double dFilter = 0;                                       //�˲��м�ֵ  
		for (int nLimit = (-nCenter); nLimit <= nCenter; nLimit++)
		{
			if ((j + nLimit) >= 0 && (j + nLimit) < nWidth)       //ͼ���ܳ����߽�  
			{
				dFilter += (double)nImageData[i*nWidth + j + nLimit] * pdKernal_1[nCenter + nLimit];
				dSum += pdKernal_1[nCenter + nLimit];
			}
		}
		nData[i*nWidth + j] = dFilter / dSum;
	}
}

for (i = 0; i < nWidth; i++)                                //����y��ĸ�˹�˲�(��Ȩƽ��)  
{
	for (j = 0; j < nHeight; j++)
	{
		double dSum = 0.0;
		double dFilter = 0;
		for (int nLimit = (-nCenter); nLimit <= nCenter; nLimit++)
		{
			if ((j + nLimit) >= 0 && (j + nLimit) < nHeight)       //ͼ���ܳ����߽�  
			{
				dFilter += (double)nData[(j + nLimit)*nWidth + i] * pdKernal_1[nCenter + nLimit];
				dSum += pdKernal_1[nCenter + nLimit];
			}
		}
		pCanny[j*nWidth + i] = (unsigned char)(int)dFilter / dSum;
	}
}

3.2.2 ���ݶ�ά��˹�˽����˲�

1�����ɶ�ά��˹�˲�ϵ��
[cpp] view plain copy
//////////////////////����һά��˹�˲�ϵ��//////////////////////////////////    
double* pdKernal_2 = new double[nWidowSize*nWidowSize]; //����һά��˹������  
double  dSum_2 = 0.0;                                   //��ͣ����й�һ��        
///////////////////////��ά��˹������ʽ////////////////////////////////////      
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
	for (int j = 0; j < nWidowSize; j++)                 //���й�һ��  
	{
		pdKernal_2[i + j*nWidowSize] /= dSum_2;
	}
}

2�����ø�˹�˽��и�˹�˲����˲�������ݱ����ھ���pCanny��
[cpp] view plain copy
int x;
int y;
for (i = 0; i < nHeight; i++)
{
	for (j = 0; j < nWidth; j++)
	{
		double dFilter = 0.0;
		double dSum = 0.0;
		for (x = (-nCenter); x <= nCenter; x++)                     //��  
		{
			for (y = (-nCenter); y <= nCenter; y++)             //��  
			{
				if ((j + x) >= 0 && (j + x) < nWidth && (i + y) >= 0 && (i + y) < nHeight) //�жϱ�Ե  
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

3.3 ͼ����ǿ��������ͼ���ݶȼ��䷽��
�������ķ�����֪��ʵ�ִ�������
[cpp] view plain copy
//////////////////ͬ�������ò�ͬ�ļ����/////////////////////////  
/////    P[i,j]=(S[i,j+1]-S[i,j]+S[i+1,j+1]-S[i+1,j])/2     /////  
/////    Q[i,j]=(S[i,j]-S[i+1,j]+S[i,j+1]-S[i+1,j+1])/2     /////  
/////////////////////////////////////////////////////////////////  
double* P = new double[nWidth*nHeight];                 //x��ƫ����  
double* Q = new double[nWidth*nHeight];                 //y��ƫ����  
int* M = new int[nWidth*nHeight];                       //�ݶȷ�ֵ  
double* Theta = new double[nWidth*nHeight];             //�ݶȷ���  
//����x,y�����ƫ����  
for (i = 0; i < (nHeight - 1); i++)
{
	for (j = 0; j < (nWidth - 1); j++)
	{
		P[i*nWidth + j] = (double)(pCanny[i*nWidth + min(j + 1, nWidth - 1)] - pCanny[i*nWidth + j] + pCanny[min(i + 1, nHeight - 1)*nWidth + min(j + 1, nWidth - 1)] - pCanny[min(i + 1, nHeight - 1)*nWidth + j]) / 2;
		Q[i*nWidth + j] = (double)(pCanny[i*nWidth + j] - pCanny[min(i + 1, nHeight - 1)*nWidth + j] + pCanny[i*nWidth + min(j + 1, nWidth - 1)] - pCanny[min(i + 1, nHeight - 1)*nWidth + min(j + 1, nWidth - 1)]) / 2;
	}
}
//�����ݶȷ�ֵ���ݶȵķ���  
for (i = 0; i < nHeight; i++)
{
	for (j = 0; j < nWidth; j++)
	{
		M[i*nWidth + j] = (int)(sqrt(P[i*nWidth + j] * P[i*nWidth + j] + Q[i*nWidth + j] * Q[i*nWidth + j]) + 0.5);
		Theta[i*nWidth + j] = atan2(Q[i*nWidth + j], P[i*nWidth + j]) * 57.3;
		if (Theta[i*nWidth + j] < 0)
			Theta[i*nWidth + j] += 360;              //������Ƕ�ת����0~360��Χ  
	}
}


3.4 �Ǽ���ֵ����

�������������Ĺ���ԭ���ⲿ��������Ҫ���ÿ�����ص����������ڵ��ݶȷ���������Ҷ�ֵ��Ȼ���ж��Ƿ�ΪǱ�ڵı�Ե����������򽫸õ�Ҷ�ֵ����Ϊ0.
���ȶ�����صĲ������£�
[cpp] view plain copy
unsigned char* N = new unsigned char[nWidth*nHeight];  //�Ǽ���ֵ���ƽ��  
int g1 = 0, g2 = 0, g3 = 0, g4 = 0;                            //���ڽ��в�ֵ���õ������ص�����ֵ  
double dTmp1 = 0.0, dTmp2 = 0.0;                           //�������������ص��ֵ�õ��ĻҶ�����  
double dWeight = 0.0;                                    //��ֵ��Ȩ��  
��Σ��Ա߽���г�ʼ����
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
���оֲ����ֵѰ�ң���������ͼ1�����ķ������в�ֵ��Ȼ�����ţ�ʵ�ִ������£�
[cpp] view plain copy
for (i = 1; i < (nWidth - 1); i++)
{
	for (j = 1; j < (nHeight - 1); j++)
	{
		int nPointIdx = i + j*nWidth;       //��ǰ����ͼ�������е�����ֵ  
		if (M[nPointIdx] == 0)
			N[nPointIdx] = 0;         //�����ǰ�ݶȷ�ֵΪ0�����Ǿֲ����Ըõ㸳Ϊ0  
		else
		{
			////////�����ж��������������Ȼ����������ֵ///////  
			////////////////////��һ�����///////////////////////  
			/////////       g1  g2                  /////////////  
			/////////           C                   /////////////  
			/////////           g3  g4              /////////////  
			/////////////////////////////////////////////////////  
			if (((Theta[nPointIdx] >= 90) && (Theta[nPointIdx] < 135)) ||
				((Theta[nPointIdx] >= 270) && (Theta[nPointIdx] < 315)))
			{
				//////����б�ʺ��ĸ��м�ֵ���в�ֵ���  
				g1 = M[nPointIdx - nWidth - 1];
				g2 = M[nPointIdx - nWidth];
				g3 = M[nPointIdx + nWidth];
				g4 = M[nPointIdx + nWidth + 1];
				dWeight = fabs(P[nPointIdx]) / fabs(Q[nPointIdx]);   //������  
				dTmp1 = g1*dWeight + g2*(1 - dWeight);
				dTmp2 = g4*dWeight + g3*(1 - dWeight);
			}
			////////////////////�ڶ������///////////////////////  
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
				dWeight = fabs(Q[nPointIdx]) / fabs(P[nPointIdx]);   //����  
				dTmp1 = g2*dWeight + g1*(1 - dWeight);
				dTmp2 = g4*dWeight + g3*(1 - dWeight);
			}
			////////////////////���������///////////////////////  
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
				dWeight = fabs(P[nPointIdx]) / fabs(Q[nPointIdx]);   //������  
				dTmp1 = g2*dWeight + g1*(1 - dWeight);
				dTmp2 = g3*dWeight + g4*(1 - dWeight);
			}
			////////////////////���������///////////////////////  
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
				dWeight = fabs(Q[nPointIdx]) / fabs(P[nPointIdx]);   //����  
				dTmp1 = g1*dWeight + g2*(1 - dWeight);
				dTmp2 = g3*dWeight + g4*(1 - dWeight);
			}
		}
		//////////���оֲ����ֵ�жϣ���д������////////////////  
		if ((M[nPointIdx] >= dTmp1) && (M[nPointIdx] >= dTmp2))
			N[nPointIdx] = 128;
		else
			N[nPointIdx] = 0;
	}
}
3.5˫��ֵ���ʵ��

1��������Ӧ��������

[cpp] view plain copy
int nHist[1024];
int nEdgeNum;             //���ܱ߽���  
int nMaxMag = 0;          //����ݶ���  
int nHighCount;

2������Ҷ�ͼ��ͳ��ֱ��ͼ�����������ݶȷ�ֵ�ļ��㹫ʽ��֪�������ݶȷ�ֵΪ��

�������nHistΪ1024�㹻������ʵ��ͳ��ֱ��ͼ��
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
3����ȡ����ݶȷ�ֵ��Ǳ�ڱ�Ե�����
[cpp] view plain copy
nEdgeNum = nHist[0];
nMaxMag = 0;                    //��ȡ�����ݶ�ֵ        
for (i = 1; i < 1024; i++)           //ͳ�ƾ����������ֵ���ơ����ж�������  
{
	if (nHist[i] != 0)       //�ݶ�Ϊ0�ĵ��ǲ�����Ϊ�߽���  
	{
		nMaxMag = i;
	}
	nEdgeNum += nHist[i];   //����non-maximum suppression���ж�������  
}

4������������ֵ
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
dThrHigh = j;                                   //����ֵ  
dThrLow = (int)((dThrHigh)* dRatLow + 0.5);    //����ֵ  

��δ������˼�ǣ����ջҶ�ֵ�ӵ͵��ߵ�˳��ѡȡǰ79%���Ҷ�ֵ�е����ĻҶ�ֵΪ����ֵ������ֵ��ԼΪ����ֵ��һ�롣���Ǹ��ݾ������ݵ����ģ����ڸ��õز���ѡȡ���������ߺ���������о���
5�����б�Ե���
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

���ϴ����ڷǼ���ֵ���Ʋ����Ķ�ֵ�ҶȾ����Ǳ�ڵ��а��ո���ֵѰ�ұ�Ե���������ҵ��ĵ�Ϊ����Ѱ���������������ֵ�ĵ㣬�Ӷ��γ�һ���պϵ�������Ȼ����ڲ����������ĵ㣬�������´���ֱ��ɾ������
[cpp] view plain copy
//����û������Ϊ�߽�ĵ�����Ϊ�Ǳ߽��  
for (i = 0; i < nHeight; i++)
{
	for (j = 0; j < nWidth; j++)
	{
		if (N[i*nWidth + j] != 255)
		{
			N[i*nWidth + j] = 0;   // ����Ϊ�Ǳ߽��  
		}
	}
}
����TraceEdge����Ϊһ��Ƕ�׺�����������ÿ�����ص��������Ѱ�����������ĵ㡣��ʵ�ִ������£�
[cpp] view plain copy
void TraceEdge(int y, int x, int nThrLow, LPBYTE pResult, int *pMag, SIZE sz)
{
	//��8�������ؽ��в�ѯ  
	int xNum[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int yNum[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	LONG yy, xx, k;
	for (k = 0; k < 8; k++)
	{
		yy = y + yNum[k];
		xx = x + xNum[k];
		if (pResult[yy*sz.cx + xx] == 128 && pMag[yy*sz.cx + xx] >= nThrLow)
		{
			//�õ���Ϊ�߽��  
			pResult[yy*sz.cx + xx] = 255;
			//�Ըõ�Ϊ�����ٽ��и���  
			TraceEdge(yy, xx, nThrLow, pResult, pMag, sz);
		}
	}
}
