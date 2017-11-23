#include "include.h"

//Data structure for a float image.  
typedef struct ImageSt {        /*������ÿһ��*/

	float levelsigma;
	int levelsigmalength;
	float absolute_sigma;
	CvMat *Level;       //CvMat��OPENCV�ľ����࣬��Ԫ�ؿ�����ͼ�������ֵ         
} ImageLevels;

typedef struct ImageSt1 {      /*������ÿһ����*/
	int row, col;          //Dimensions of image.   
	float subsample;
	ImageLevels *Octave;
} ImageOctaves;

ImageOctaves *DOGoctaves;
//DOG pyr��DOG���Ӽ���򵥣��ǳ߶ȹ�һ����LoG���ӵĽ��ơ�  

ImageOctaves *mag_thresh;
ImageOctaves *mag_pyr;
ImageOctaves *grad_pyr;

//keypoint���ݽṹ��Lists of keypoints are linked by the "next" field.  
typedef struct KeypointSt
{
	float row, col; /* ������ԭͼ���С���������λ�� */
	float sx, sy;    /* ���������������λ��*/
	int octave, level;/*�������У����������ڵĽ��ݡ����*/

	float scale, ori, mag; /*���ڲ�ĳ߶�sigma,������orientation (range [-PI,PI])���Լ���ֵ*/
	float *descrip;       /*����������ָ�룺128ά��32ά��*/
	struct KeypointSt *next;/* Pointer to next keypoint in list. */
} *Keypoint;

//����������������  
Keypoint keypoints = NULL;      //������ʱ�洢�������λ�õ�  
Keypoint keyDescriptors = NULL; //��������ȷ���������Լ�����������  


CvMat * halfSizeImage(CvMat * im);     //��Сͼ���²���  
CvMat * doubleSizeImage(CvMat * im);   //����ͼ������ٷ���  
CvMat * doubleSizeImage2(CvMat * im);  //����ͼ�����Բ�ֵ  
float getPixelBI(CvMat * im, float col, float row);//˫���Բ�ֵ����  
void normalizeVec(float* vec, int dim);//������һ��    
CvMat* GaussianKernel2D(float sigma);  //�õ�2ά��˹��  
void normalizeMat(CvMat* mat);        //�����һ��  
float* GaussianKernel1D(float sigma, int dim); //�õ�1ά��˹��  

//�ھ������ش���ȷ�����и�˹���  
float ConvolveLocWidth(float* kernel, int dim, CvMat * src, int x, int y);
//������ͼ���ȷ������1D��˹���  
void Convolve1DWidth(float* kern, int dim, CvMat * src, CvMat * dst);
//�ھ������ش��߶ȷ�����и�˹���  
float ConvolveLocHeight(float* kernel, int dim, CvMat * src, int x, int y);
//������ͼ��߶ȷ������1D��˹���  
void Convolve1DHeight(float* kern, int dim, CvMat * src, CvMat * dst);
//�ø�˹����ģ��ͼ��    
int BlurImage(CvMat * src, CvMat * dst, float sigma);

//SIFT�㷨��һ����ͼ��Ԥ����  
CvMat *ScaleInitImage(CvMat * im);                  //��������ʼ��  

//SIFT�㷨�ڶ�����������˹����������  
ImageOctaves* BuildGaussianOctaves(CvMat * image);  //������˹������  

//SIFT�㷨��������������λ�ü�⣬���ȷ���������λ��  
int DetectKeypoint(int numoctaves, ImageOctaves *GaussianPyr);
void DisplayKeypointLocation(IplImage* image, ImageOctaves *GaussianPyr);

//SIFT�㷨���Ĳ��������˹ͼ����ݶȷ���ͷ�ֵ����������������������  
void ComputeGrad_DirecandMag(int numoctaves, ImageOctaves *GaussianPyr);

int FindClosestRotationBin(int binCount, float angle);  //���з���ֱ��ͼͳ��  
void AverageWeakBins(double* bins, int binCount);       //�Է���ֱ��ͼ�˲�  
//ȷ��������������  
bool InterpolateOrientation(double left, double middle, double right, double *degreeCorrection, double *peakValue);
//ȷ�����������㴦����������  
void AssignTheMainOrientation(int numoctaves, ImageOctaves *GaussianPyr, ImageOctaves *mag_pyr, ImageOctaves *grad_pyr);
//��ʾ������  
void DisplayOrientation(IplImage* image, ImageOctaves *GaussianPyr);

//SIFT�㷨���岽����ȡ���������㴦������������  
void ExtractFeatureDescriptors(int numoctaves, ImageOctaves *GaussianPyr);

//Ϊ����ʾͼ���������������ͼ��ˮƽ����ֱƴ��  
CvMat* MosaicHorizen(CvMat* im1, CvMat* im2);
CvMat* MosaicVertical(CvMat* im1, CvMat* im2);

//���������㣬����    
#define GridSpacing 4  