//#include<opencv2/opencv.hpp>
//#include <vector>
//#include<time.h>
//using namespace  std;
//using namespace cv;
#include "tvf.h"

vector<int> findHistPeak(int* num)
{
    vector<int>  sign;
    for(int i=1; i<256; i++)
    {
        int diff=num[i]-num[i-1];
        if(diff>0)
        {
            sign.push_back(1);
        }
        else if(diff<0)
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
    for (int j=1; j<sign.size(); j++)
    {
        int diff=sign[j]-sign[j-1];
        if(diff<0)
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
//void drawhist(int* hist)//画出直方图
//{
//	int max=0;
//	for(int i=0;i<256;i++)
//	{
//	   if(hist[i]>max)
//	   {
//		   max=hist[i];
//	   }
//	}
//	IplImage* dst=cvCreateImage(cvSize(400,300),8,3);
//	cvSet(dst,cvScalarAll(255),0);
//	double bin_width=(double)dst->width/256;
//	double bin_unith=(double)dst->height/max;
//	for(int i=0;i<256;i++)
//	{
//       CvPoint p0=cvPoint(i*bin_width,dst->height);
//	   CvPoint p1=cvPoint((i+1)*bin_width,dst->height-hist[i]*bin_unith);
//	   cvRectangle(dst,p0,p1,cvScalar(0,255),-1,8,0);
//	}
//	cvNamedWindow("hist",1);
//	cvShowImage("hist",dst);
//	cvWaitKey(0);
//	cvDestroyAllWindows();
//	cvReleaseImage(&dst);
//
//}


//主函数：只有一个输入，原图路径，输出作为图像保存
void seedFilter(cv::Mat in, cv::Mat &maskPic)
{
    int scale=1;//缩小比例
    int patchwidth=128;
    int patchheight=128;



	IplImage* src0 = &IplImage(in);//cvLoadImage("0U0A0115.JPG",CV_LOAD_IMAGE_GRAYSCALE);//输入，原图

    cvNormalize(src0,src0,0,255,CV_MINMAX);
    CvSize newsize;
    newsize.width=(src0->width)/scale;
    newsize.height=(src0->height)/scale;
    IplImage* src=cvCreateImage(newsize,src0->depth,src0->nChannels);
    IplImage* dst=cvCreateImage(newsize,src0->depth,src0->nChannels);
    for(int i=0; i<dst->height; i++)
    {
        for(int j=0; j<dst->width; j++)
        {
            *(dst->imageData+i*(dst->width)+j)=255;
        }
    }
	cvCopy(src0, src);
  //  cvResize(src0,src,CV_INTER_LINEAR);

    int width=patchwidth;
    int height=patchheight;
    int step=src->widthStep;

    for(int row0=0; row0<src->height; row0=row0+patchheight)
    {
        for (int col0=0; col0<src->width; col0=col0+patchwidth)
        {
			int row = row0, col = col0;
			if(col+patchwidth>src->width)
            {
                col=(src->width)-patchwidth;
            }
            if (row+patchheight>src->height)
            {
                row=(src->height)-patchheight;
            }

            CvRect rect;
            rect.x=col;
            rect.y=row;
            rect.width=patchwidth;
            rect.height=patchheight;
            cvSetImageROI(src,rect);


            //求直方图hist
            uchar* data=(uchar*) src->imageData;
            int hist[256]= {0};
            for(int i=0; i<height; i++)
            {
                for(int j=0; j<width; j++)
                {
                    hist[data[i*step+j]]++;
                }
            }

            //直方图平滑
            for(int i=2; i<254; i++)
            {
                hist[i]=(hist[i-2]+hist[i-1]+hist[i]+hist[i+1]+hist[i+2])/5;

            }


            // drawhist(hist);


            //寻找波谷
			vector<int> indMin = findHistPeak(hist);
            int th=0;
            for(int i=0; i<indMin.size(); i++)
            {

                int val=indMin[i];
                if (val>200)
                    break;
                val=val+10;
                if((val-10)>=0&&abs(hist[val-20]-hist[val])<0.0015*patchwidth*patchheight&&(val+45)<255&&(hist[val+35]-hist[val])>0.0049*patchwidth*patchheight)
                {
                    th=val;
                }
            }


			//th = myDesign::entropyThres(in, rect.y, rect.x, patchwidth, patchheight);
            //以波谷为阈值
            CvSize size;
            size.width=patchwidth;
            size.height=patchheight;
            IplImage* src2=cvCreateImage(size,src->depth,src->nChannels);
            cvCopy(src,src2);
            for(int ii=0; ii<patchheight; ii++)
            {
                for(int jj=0; jj<patchwidth; jj++)
                {
                    uchar b=*(src2->imageData+ii*patchwidth+jj);
                    if (th==0||b>th+20)
                    {

                        *(dst->imageData+(row+ii)*(dst->widthStep)+(col+jj))=255;
                    }
                    else
                    {
                        *(dst->imageData+(row+ii)*(dst->widthStep)+(col+jj))=0;
                    }

                }
            }

            cvReleaseImage(&src2);
            cvResetImageROI(src);
            //cvSaveImage("src2.jpg",src);
        }
    }
	maskPic = cv::cvarrToMat(dst);
	//cv::imshow("maskpic",maskPic);

//   cvSaveImage("115.jpg",dst);//输出，作为图像保存
  //  cvReleaseImage(&src0);
  //  cvReleaseImage(&src);
  //  cvReleaseImage(&dst);

	return;
}

