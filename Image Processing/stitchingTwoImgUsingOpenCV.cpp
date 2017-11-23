#include <opencv2/imgproc/imgproc.hpp>    
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

void OptimizeSeam(Mat& img1, Mat& trans, Mat& dst);

typedef struct
{
	Point2f left_top;
	Point2f left_bottom;
	Point2f right_top;
	Point2f right_bottom;
}four_corners_t;

four_corners_t corners;

void CalcCorners(const Mat& H, const Mat& src)
{
	double v2[] = { 0, 0, 1 };//���Ͻ�
	double v1[3];//�任�������ֵ
	Mat V2 = Mat(3, 1, CV_64FC1, v2);  //������
	Mat V1 = Mat(3, 1, CV_64FC1, v1);  //������

	V1 = H * V2;
	//���Ͻ�(0,0,1)
	cout << "V2: " << V2 << endl;
	cout << "V1: " << V1 << endl;
	corners.left_top.x = v1[0] / v1[2];
	corners.left_top.y = v1[1] / v1[2];

	//���½�(0,src.rows,1)
	v2[0] = 0;
	v2[1] = src.rows;
	v2[2] = 1;
	V2 = Mat(3, 1, CV_64FC1, v2);  //������
	V1 = Mat(3, 1, CV_64FC1, v1);  //������
	V1 = H * V2;
	corners.left_bottom.x = v1[0] / v1[2];
	corners.left_bottom.y = v1[1] / v1[2];

	//���Ͻ�(src.cols,0,1)
	v2[0] = src.cols;
	v2[1] = 0;
	v2[2] = 1;
	V2 = Mat(3, 1, CV_64FC1, v2);  //������
	V1 = Mat(3, 1, CV_64FC1, v1);  //������
	V1 = H * V2;
	corners.right_top.x = v1[0] / v1[2];
	corners.right_top.y = v1[1] / v1[2];

	//���½�(src.cols,src.rows,1)
	v2[0] = src.cols;
	v2[1] = src.rows;
	v2[2] = 1;
	V2 = Mat(3, 1, CV_64FC1, v2);  //������
	V1 = Mat(3, 1, CV_64FC1, v1);  //������
	V1 = H * V2;
	corners.right_bottom.x = v1[0] / v1[2];
	corners.right_bottom.y = v1[1] / v1[2];

}

int main(int argc, char *argv[])
{
	double t = getTickCount();
	if (argc == 1)
		return -1;
	Mat imageRight = imread(string(argv[2]));    //��ͼ
	Mat imageLeft = imread(string(argv[1]));    //��ͼ
	string resultImg = (string(argv[1])).substr(27, 14) + "_" + (string(argv[2])).substr(27, 14) + ".jpg";
	cout << resultImg << endl;
	//imshow("p2", image01);
	//imshow("p1", image02);
	//waitKey(0);

	resize(imageRight, imageRight, Size(5760 / 4, 3840 / 4));
	resize(imageLeft, imageLeft, Size(5760 / 4, 3840 / 4));

	//�Ҷ�ͼת��  
	Mat image1, image2;
	cvtColor(imageRight, image1, CV_RGB2GRAY);
	cvtColor(imageLeft, image2, CV_RGB2GRAY);

	//��ȡ������  ;
	//SurfFeatureDetector Detector(2000);
	//vector<KeyPoint> keyPoint1, keyPoint2;
	//Detector.detect(image1, keyPoint1);
	//Detector.detect(image2, keyPoint2);

	//������������Ϊ�±ߵ�������ƥ����׼��    
	//SurfDescriptorExtractor Descriptor;
	//Mat imageDesc1, imageDesc2;
	//Descriptor.compute(image1, keyPoint1, imageDesc1);
	//Descriptor.compute(image2, keyPoint2, imageDesc2);

#if 1
	Ptr<Feature2D> Detector = SIFT::create();
	vector<KeyPoint> keyPoint1, keyPoint2;
	Detector->detect(image1, keyPoint1); //��ȡSIFT������
	Detector->detect(image2, keyPoint2);

	Ptr<Feature2D> Descriptor = SIFT::create();
	Mat imageDesc1, imageDesc2;
	Descriptor->compute(image1, keyPoint1, imageDesc1);
	cout << "imageDesc1:" << imageDesc1.rows << " " << imageDesc1.cols << endl;
	Descriptor->compute(image2, keyPoint2, imageDesc2);
	cout << "imageDesc2:" << imageDesc2.rows << " " << imageDesc2.cols << endl;

	FlannBasedMatcher matcher;
	vector<vector<DMatch>> matchePoints;
	vector<DMatch> GoodMatchePoints;

	vector<Mat> train_desc(1, imageDesc1);
	matcher.add(train_desc);
	matcher.train();

	matcher.knnMatch(imageDesc2, matchePoints, 2);
	cout << "total match points: " << matchePoints.size() << endl;

	// Lowe's algorithm,��ȡ����ƥ���
	for (int i = 0; i < matchePoints.size(); i++)
		if (matchePoints[i][0].distance < 0.4 * matchePoints[i][1].distance)
			GoodMatchePoints.push_back(matchePoints[i][0]);

	cout << "good match points: " << GoodMatchePoints.size() << endl;

	Mat first_match;
	drawMatches(imageLeft, keyPoint2, imageRight, keyPoint1, GoodMatchePoints, first_match);
	//imshow("first_match ", first_match);
	imwrite("./Image/1-16 first_match.jpg", first_match);

	vector<Point2f> imagePoints1, imagePoints2;

	for (int i = 0; i < GoodMatchePoints.size(); i++)
	{
		imagePoints2.push_back(keyPoint2[GoodMatchePoints[i].queryIdx].pt);
		imagePoints1.push_back(keyPoint1[GoodMatchePoints[i].trainIdx].pt);
	}



	//��ȡͼ��1��ͼ��2��ͶӰӳ����� �ߴ�Ϊ3*3  
	Mat homo = findHomography(imagePoints1, imagePoints2, CV_RANSAC);
	////Ҳ����ʹ��getPerspectiveTransform�������͸�ӱ任���󣬲���Ҫ��ֻ����4���㣬Ч���Բ�  
	//Mat   homo=getPerspectiveTransform(imagePoints1,imagePoints2);  
	cout << "�任����Ϊ��\n" << homo << endl << endl; //���ӳ�����      

	//������׼ͼ���ĸ���������
	CalcCorners(homo, imageRight);
	cout << "left_top:" << corners.left_top << endl;
	cout << "left_bottom:" << corners.left_bottom << endl;
	cout << "right_top:" << corners.right_top << endl;
	cout << "right_bottom:" << corners.right_bottom << endl;

	//ͼ����׼  
	Mat imageTransform1, imageTransform2;
	warpPerspective(imageRight, imageTransform1, homo, Size(MAX(corners.right_top.x, corners.right_bottom.x), imageLeft.rows));
	//warpPerspective(image01, imageTransform2, adjustMat*homo, Size(image02.cols*1.3, image02.rows*1.8));
	//imshow("ֱ�Ӿ���͸�Ӿ���任", imageTransform1);
	imwrite("trans1.jpg", imageTransform1);


	//����ƴ�Ӻ��ͼ,����ǰ����ͼ�Ĵ�С
	int dst_width = imageTransform1.cols;  //ȡ���ҵ�ĳ���Ϊƴ��ͼ�ĳ���
	int dst_height = imageLeft.rows;

	Mat dst(dst_height, dst_width, CV_8UC3);
	dst.setTo(0);

	imageTransform1.copyTo(dst(Rect(0, 0, imageTransform1.cols, imageTransform1.rows)));
	imageLeft.copyTo(dst(Rect(0, 0, imageLeft.cols, imageLeft.rows)));

	//imshow("b_dst", dst);
	imwrite("b_dst.jpg", dst);


	OptimizeSeam(imageLeft, imageTransform1, dst);


	//imshow("dst", dst);
	imwrite(resultImg, dst);

	cout << "����ʱ��" << (getTickCount() - t) / getTickFrequency() << "S" << endl;
	//waitKey();
#endif

	return 0;
}


//�Ż���ͼ�����Ӵ���ʹ��ƴ����Ȼ
void OptimizeSeam(Mat& img1, Mat& trans, Mat& dst)
{
	int start = MIN(corners.left_top.x, corners.left_bottom.x);//��ʼλ�ã����ص��������߽�  

	double processWidth = img1.cols - start;//�ص�����Ŀ��  
	int rows = dst.rows;
	int cols = img1.cols; //ע�⣬������*ͨ����
	double alpha = 1;//img1�����ص�Ȩ��  
	for (int i = 0; i < rows; i++)
	{
		uchar* p = img1.ptr<uchar>(i);  //��ȡ��i�е��׵�ַ
		uchar* t = trans.ptr<uchar>(i);
		uchar* d = dst.ptr<uchar>(i);
		for (int j = start; j < cols; j++)
		{
			//�������ͼ��trans�������صĺڵ㣬����ȫ����img1�е�����
			if (t[j * 3] == 0 && t[j * 3 + 1] == 0 && t[j * 3 + 2] == 0)
			{
				alpha = 1;
			}
			else
			{
				//img1�����ص�Ȩ�أ��뵱ǰ�������ص�������߽�ľ�������ȣ�ʵ��֤�������ַ���ȷʵ��  
				alpha = (processWidth - (j - start)) / processWidth;
			}

			d[j * 3] = p[j * 3] * alpha + t[j * 3] * (1 - alpha);
			d[j * 3 + 1] = p[j * 3 + 1] * alpha + t[j * 3 + 1] * (1 - alpha);
			d[j * 3 + 2] = p[j * 3 + 2] * alpha + t[j * 3 + 2] * (1 - alpha);

		}
	}

}



