#include "tvf.h"
vector<int> findpeaks(int* num)
{
	vector<int>  sign;
	for (int i = 1; i<256; i++)
	{
		int diff = num[i] - num[i - 1];
		if (diff>0)
		{
			sign.push_back(1);
		}
		else if (diff<0)
		{
			sign.push_back(-1);
		}
		else
		{
			sign.push_back(0);
		}
	}
	vector<int> indMax;
	vector<int> indMin;
	for (int j = 1; j<sign.size(); j++)
	{
		int diff = sign[j] - sign[j - 1];
		if (diff<0)
		{
			indMax.push_back(j);
		}
		else if (diff>0)
		{
			indMin.push_back(j);
		}
	}
	return indMin;
}
void testTres(cv::Mat &srcI) {
	int scale = 1;//缩小比例
	int patchwidth = 128;
	int patchheight = 128;



	IplImage* src0 = &IplImage(srcI);//= cvLoadImage("0U0A0115.JPG", CV_LOAD_IMAGE_GRAYSCALE);//输入，原图
	
	cvNormalize(src0, src0, 0, 255, CV_MINMAX);
	CvSize newsize;
	newsize.width = (src0->width) / scale;
	newsize.height = (src0->height) / scale;
	
	CvSize newsize1;
	newsize1.width = (src0->width) +128;
	newsize1.height = (src0->height) +128;

	IplImage* dst = cvCreateImage(newsize1, src0->depth, src0->nChannels);
	IplImage* src = cvCreateImage(newsize1, src0->depth, src0->nChannels);
	for (int i = 0; i<dst->height; i++)
	{
		for (int j = 0; j<dst->width; j++)
		{
			*(dst->imageData + i*(dst->width) + j) = 255;
		}
	}
	//cvResize(src0, src, CV_INTER_LINEAR);

	int width = patchwidth;
	int height = patchheight;
	int step = src->widthStep;

	
	cv::Mat srcD;
	copyMakeBorder(srcI, srcD, 0, patchheight, 0, patchheight, cv::BORDER_REFLECT);
	//cout << "border extend before  " << srcI.rows << ' ' << srcI.cols << endl;
	//cout << "border extend after   "<<srcD.rows << ' ' << srcD.cols << endl;
		
	src = &IplImage(srcD);
	for (int row = 0; row + patchheight - 1<src->height; row = row + patchheight)
	{
		for (int col = 0; col + patchwidth - 1<src->width; col = col + patchwidth)
		{

			CvRect rect;
			rect.x = col;
			rect.y = row;
			rect.width = patchwidth;
			rect.height = patchheight;
			cvSetImageROI(src, rect);


			//求直方图hist
			uchar* data = (uchar*)src->imageData;
			int hist[256] = { 0 };
			for (int i = 0; i<height; i++)
			{
				for (int j = 0; j<width; j++)
				{
					hist[data[i*step + j]]++;
				}
			}

			//直方图平滑
			for (int i = 2; i<254; i++)
			{
				hist[i] = (hist[i - 2] + hist[i - 1] + hist[i] + hist[i + 1] + hist[i + 2]) / 5;

			}


			// drawhist(hist);


			//寻找波谷
			vector<int> indMin = findpeaks(hist);
			int th = 0;
			for (int i = 0; i<indMin.size(); i++)
			{

				int val = indMin[i];
				if (val>200)
					break;
				val = val + 10;
				if ((val - 10) >= 0 && abs(hist[val - 20] - hist[val])<25 && (val + 45)<255 && (hist[val + 35] - hist[val])>80)
				{
					th = val;
				}
			}

			//以波谷为阈值
			CvSize size;
			size.width = patchwidth;
			size.height = patchheight;
			IplImage* src2 = cvCreateImage(size, src->depth, src->nChannels);
			cvCopy(src, src2);
			for (int ii = 0; ii<patchheight; ii++)
			{
				for (int jj = 0; jj<patchwidth; jj++)
				{
					uchar b = *(src2->imageData + ii*patchwidth + jj);
					if (th == 0 || b>th + 20)
					{

						*(dst->imageData + (row + ii)*(dst->widthStep) + (col + jj)) = 255;
					}
					else
					{
						*(dst->imageData + (row + ii)*(dst->widthStep) + (col + jj)) = 0;
					}

				}
			}

			cvReleaseImage(&src2);
			cvResetImageROI(src);
			//cvSaveImage("src2.jpg",src);
		}
	}
	

	cvSaveImage("115.jpg", dst);//输出，作为图像保存
	//cvReleaseImage(&src0);
	//cvReleaseImage(&src);
	//cvReleaseImage(&dst);

}