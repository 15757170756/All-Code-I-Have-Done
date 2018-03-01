#include "include.h"
#include "sift.h"

int main(void)
{
	//声明当前帧IplImage指针  
	IplImage* src = NULL;
	IplImage* image1 = NULL;
	IplImage* grey_im1 = NULL;
	IplImage* DoubleSizeImage = NULL;

	IplImage* mosaic1 = NULL;
	IplImage* mosaic2 = NULL;

	CvMat* mosaicHorizen1 = NULL;
	CvMat* mosaicHorizen2 = NULL;
	CvMat* mosaicVertical1 = NULL;

	CvMat* image1Mat = NULL;
	CvMat* tempMat = NULL;

	ImageOctaves *Gaussianpyr;
	int rows, cols;

#define Im1Mat(ROW,COL) ((float *)(image1Mat->data.fl + image1Mat->step/sizeof(float) *(ROW)))[(COL)]  

	//灰度图象像素的数据结构  
#define Im1B(ROW,COL) ((uchar*)(image1->imageData + image1->widthStep*(ROW)))[(COL)*3]  
#define Im1G(ROW,COL) ((uchar*)(image1->imageData + image1->widthStep*(ROW)))[(COL)*3+1]  
#define Im1R(ROW,COL) ((uchar*)(image1->imageData + image1->widthStep*(ROW)))[(COL)*3+2]  

	storage = cvCreateMemStorage(0);

	//读取图片  
	if ((src = cvLoadImage("street1.jpg", 1)) == 0)  // test1.jpg einstein.pgm back1.bmp  
		return -1;

	//为图像分配内存   
	image1 = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 3);
	grey_im1 = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
	DoubleSizeImage = cvCreateImage(cvSize(2 * (src->width), 2 * (src->height)), IPL_DEPTH_8U, 3);

	//为图像阵列分配内存，假设两幅图像的大小相同，tempMat跟随image1的大小  
	image1Mat = cvCreateMat(src->height, src->width, CV_32FC1);
	//转化成单通道图像再处理  
	cvCvtColor(src, grey_im1, CV_BGR2GRAY);
	//转换进入Mat数据结构,图像操作使用的是浮点型操作  
	cvConvert(grey_im1, image1Mat);

	double t = (double)cvGetTickCount();
	//图像归一化  
	cvConvertScale(image1Mat, image1Mat, 1.0 / 255, 0);

	int dim = min(image1Mat->rows, image1Mat->cols);
	numoctaves = (int)(log((double)dim) / log(2.0)) - 2;    //金字塔阶数  
	numoctaves = min(numoctaves, MAXOCTAVES);

	//SIFT算法第一步，预滤波除噪声，建立金字塔底层  
	tempMat = ScaleInitImage(image1Mat);
	//SIFT算法第二步，建立Guassian金字塔和DOG金字塔  
	Gaussianpyr = BuildGaussianOctaves(tempMat);

	t = (double)cvGetTickCount() - t;
	printf("the time of build Gaussian pyramid and DOG pyramid is %.1f/n", t / (cvGetTickFrequency()*1000.));

#define ImLevels(OCTAVE,LEVEL,ROW,COL) ((float *)(Gaussianpyr[(OCTAVE)].Octave[(LEVEL)].Level->data.fl + Gaussianpyr[(OCTAVE)].Octave[(LEVEL)].Level->step/sizeof(float) *(ROW)))[(COL)]  
	//显示高斯金字塔  
	for (int i = 0; i < numoctaves; i++)
	{
		if (i == 0)
		{
			mosaicHorizen1 = MosaicHorizen((Gaussianpyr[0].Octave)[0].Level, (Gaussianpyr[0].Octave)[1].Level);
			for (int j = 2; j < SCALESPEROCTAVE + 3; j++)
				mosaicHorizen1 = MosaicHorizen(mosaicHorizen1, (Gaussianpyr[0].Octave)[j].Level);
			for (int j = 0; j < NUMSIZE; j++)
				mosaicHorizen1 = halfSizeImage(mosaicHorizen1);
		}
		else if (i == 1)
		{
			mosaicHorizen2 = MosaicHorizen((Gaussianpyr[1].Octave)[0].Level, (Gaussianpyr[1].Octave)[1].Level);
			for (int j = 2; j < SCALESPEROCTAVE + 3; j++)
				mosaicHorizen2 = MosaicHorizen(mosaicHorizen2, (Gaussianpyr[1].Octave)[j].Level);
			for (int j = 0; j < NUMSIZE; j++)
				mosaicHorizen2 = halfSizeImage(mosaicHorizen2);
			mosaicVertical1 = MosaicVertical(mosaicHorizen1, mosaicHorizen2);
		}
		else
		{
			mosaicHorizen1 = MosaicHorizen((Gaussianpyr[i].Octave)[0].Level, (Gaussianpyr[i].Octave)[1].Level);
			for (int j = 2; j < SCALESPEROCTAVE + 3; j++)
				mosaicHorizen1 = MosaicHorizen(mosaicHorizen1, (Gaussianpyr[i].Octave)[j].Level);
			for (int j = 0; j < NUMSIZE; j++)
				mosaicHorizen1 = halfSizeImage(mosaicHorizen1);
			mosaicVertical1 = MosaicVertical(mosaicVertical1, mosaicHorizen1);
		}
	}
	mosaic1 = cvCreateImage(cvSize(mosaicVertical1->width, mosaicVertical1->height), IPL_DEPTH_8U, 1);
	cvConvertScale(mosaicVertical1, mosaicVertical1, 255.0, 0);
	cvConvertScaleAbs(mosaicVertical1, mosaic1, 1, 0);

	//  cvSaveImage("GaussianPyramid of me.jpg",mosaic1);  
	cvNamedWindow("mosaic1", 1);
	cvShowImage("mosaic1", mosaic1);
	cvWaitKey(0);
	cvDestroyWindow("mosaic1");
	//显示DOG金字塔  
	for (int i = 0; i < numoctaves; i++)
	{
		if (i == 0)
		{
			mosaicHorizen1 = MosaicHorizen((DOGoctaves[0].Octave)[0].Level, (DOGoctaves[0].Octave)[1].Level);
			for (int j = 2; j < SCALESPEROCTAVE + 2; j++)
				mosaicHorizen1 = MosaicHorizen(mosaicHorizen1, (DOGoctaves[0].Octave)[j].Level);
			for (int j = 0; j < NUMSIZE; j++)
				mosaicHorizen1 = halfSizeImage(mosaicHorizen1);
		}
		else if (i == 1)
		{
			mosaicHorizen2 = MosaicHorizen((DOGoctaves[1].Octave)[0].Level, (DOGoctaves[1].Octave)[1].Level);
			for (int j = 2; j < SCALESPEROCTAVE + 2; j++)
				mosaicHorizen2 = MosaicHorizen(mosaicHorizen2, (DOGoctaves[1].Octave)[j].Level);
			for (j = 0; j < NUMSIZE; j++)
				mosaicHorizen2 = halfSizeImage(mosaicHorizen2);
			mosaicVertical1 = MosaicVertical(mosaicHorizen1, mosaicHorizen2);
		}
		else
		{
			mosaicHorizen1 = MosaicHorizen((DOGoctaves[i].Octave)[0].Level, (DOGoctaves[i].Octave)[1].Level);
			for (int j = 2; j < SCALESPEROCTAVE + 2; j++)
				mosaicHorizen1 = MosaicHorizen(mosaicHorizen1, (DOGoctaves[i].Octave)[j].Level);
			for (int j = 0; j < NUMSIZE; j++)
				mosaicHorizen1 = halfSizeImage(mosaicHorizen1);
			mosaicVertical1 = MosaicVertical(mosaicVertical1, mosaicHorizen1);
		}
	}
	//考虑到DOG金字塔各层图像都会有正负，所以，必须寻找最负的，以将所有图像抬高一个台阶去显示  
	double min_val = 0;
	double max_val = 0;
	cvMinMaxLoc(mosaicVertical1, &min_val, &max_val, NULL, NULL, NULL);
	if (min_val < 0.0)
		cvAddS(mosaicVertical1, cvScalarAll((-1.0)*min_val), mosaicVertical1, NULL);
	mosaic2 = cvCreateImage(cvSize(mosaicVertical1->width, mosaicVertical1->height), IPL_DEPTH_8U, 1);
	cvConvertScale(mosaicVertical1, mosaicVertical1, 255.0 / (max_val - min_val), 0);
	cvConvertScaleAbs(mosaicVertical1, mosaic2, 1, 0);

	//  cvSaveImage("DOGPyramid of me.jpg",mosaic2);  
	cvNamedWindow("mosaic1", 1);
	cvShowImage("mosaic1", mosaic2);
	cvWaitKey(0);

	//SIFT算法第三步：特征点位置检测，最后确定特征点的位置  
	int keycount = DetectKeypoint(numoctaves, Gaussianpyr);
	printf("the keypoints number are %d ;/n", keycount);
	cvCopy(src, image1, NULL);
	DisplayKeypointLocation(image1, Gaussianpyr);

	cvPyrUp(image1, DoubleSizeImage, CV_GAUSSIAN_5x5);
	cvNamedWindow("image1", 1);
	cvShowImage("image1", DoubleSizeImage);
	cvWaitKey(0);
	cvDestroyWindow("image1");

	//SIFT算法第四步：计算高斯图像的梯度方向和幅值，计算各个特征点的主方向  
	ComputeGrad_DirecandMag(numoctaves, Gaussianpyr);
	AssignTheMainOrientation(numoctaves, Gaussianpyr, mag_pyr, grad_pyr);
	cvCopy(src, image1, NULL);
	DisplayOrientation(image1, Gaussianpyr);

	//  cvPyrUp( image1, DoubleSizeImage, CV_GAUSSIAN_5x5 );  
	cvNamedWindow("image1", 1);
	//  cvResizeWindow("image1", 2*(image1->width), 2*(image1->height) );  
	cvShowImage("image1", image1);
	cvWaitKey(0);

	//SIFT算法第五步：抽取各个特征点处的特征描述字  
	ExtractFeatureDescriptors(numoctaves, Gaussianpyr);
	cvWaitKey(0);

	//销毁窗口  
	cvDestroyWindow("image1");
	cvDestroyWindow("mosaic1");
	//释放图像  
	cvReleaseImage(&image1);
	cvReleaseImage(&grey_im1);
	cvReleaseImage(&mosaic1);
	cvReleaseImage(&mosaic2);
	return 0;
}