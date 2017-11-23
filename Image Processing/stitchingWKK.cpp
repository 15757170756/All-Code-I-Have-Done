#if 1

#include <opencv2/imgproc/imgproc.hpp>    
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

void match_point(int i, Mat &img1, Mat &img2, Point2f &p1, Point2f &p2);

int main(int argc, char *argv[])
{
	double t = getTickCount();
	vector<Mat> imgs;
	double loc[16][2];
	if (argc == 1)
		return -1;
	string resultImg = "full.jpg";
	for (int i = 1, j = 0; i < argc; ++i, ++j) {
		Mat tempImg = imread(argv[i]);
		string strCol = (string(argv[i])).substr(29, 4);
		string strRow = (string(argv[i])).substr(34, 4);
		loc[j][0] = (stof(strRow)) * 4;
		loc[j][1] = (stof(strCol)) * 4;
		resize(tempImg, tempImg, Size(), 0.2, 0.2);
		imgs.push_back(tempImg);
	}

	for (int i = argc - 2; i >= 0; --i) {
		loc[i][0] = loc[i][0] - loc[0][0] + 1;
		loc[i][1] = loc[i][1] - loc[0][1] + 1;
	}

	for (int i = 0; i < argc - 1; ++i) {
		cout << loc[i][0] << " " << loc[i][1] << endl;
	}

	double everyResize[16] = { 0 };

	Point2f p1, p2;
	for (int i = 0; i < 3; ++i) {
		match_point(i, imgs[i], imgs[i + 1], p1, p2);
		everyResize[i] = (loc[i + 1][1] - loc[i][1]) / (p1.x - p2.x);
		//cout << everyResize[i] << endl;
	}
	everyResize[3] = everyResize[2];

	for (int i = 7; i >= 5; --i) {
		match_point(i, imgs[i], imgs[i - 1], p1, p2);
		everyResize[i] = (loc[i - 1][1] - loc[i][1]) / (p1.x - p2.x);
		//cout << everyResize[i] << endl;
	}
	everyResize[4] = everyResize[5];

	for (int i = 8; i < 11; ++i) {
		match_point(i, imgs[i], imgs[i + 1], p1, p2);
		everyResize[i] = (loc[i + 1][1] - loc[i][1]) / (p1.x - p2.x);
		//cout << everyResize[i] << endl;
	}
	everyResize[11] = everyResize[10];

	for (int i = 15; i >= 13; --i) {
		match_point(i, imgs[i], imgs[i - 1], p1, p2);
		everyResize[i] = (loc[i - 1][1] - loc[i][1]) / (p1.x - p2.x);
		//cout << everyResize[i] << endl;
	}
	everyResize[12] = everyResize[13];

	for (int i = 0; i < 16; ++i)
		cout << everyResize[i] << endl;

	Mat allImg(6000, 8000, CV_8UC3);
	for (int i = 0; i < argc - 1; ++i) {
		resize(imgs[i], imgs[i], Size(), everyResize[i], everyResize[i]);
		//cout << "imgRows:" << imgs[i].rows << endl;
		//cout << "imgColos:" << imgs[i].cols << endl;
		//int imgRows = ((i == 0) ? 0 : imgs[i].rows);
		//int imgColos = ((i == 0) ? 0 : imgs[i].cols);
		for (int j1 = static_cast<int>(loc[i][0]) - 1, j2 = 0; j2 < imgs[i].rows; ++j1, ++j2)
			for (int k1 = static_cast<int>(loc[i][1]) - 1, k2 = 0; k2 < imgs[i].cols; ++k1, ++k2) {
				//cout << j1 << " " << k1 << endl;
				allImg.at<Vec3b>(j1, k1) = imgs[i].at<Vec3b>(j2, k2);
			}
	}

	imwrite(resultImg, allImg);

	cout << "total time: " << (getTickCount() - t) / getTickFrequency() << " s." << endl;
	return 0;
}


void match_point(int i, Mat &img1, Mat &img2, Point2f &p1, Point2f &p2)
{
	Mat img1Gray, img2Gray;
	cvtColor(img1, img1Gray, CV_BGR2GRAY);
	cvtColor(img2, img2Gray, CV_BGR2GRAY);
	Ptr<Feature2D> Detector = SIFT::create();
	vector<KeyPoint> keyPoint1, keyPoint2;
	Detector->detect(img1Gray, keyPoint1); //获取SIFT特征点
	Detector->detect(img2Gray, keyPoint2);

	Ptr<Feature2D> Descriptor = SIFT::create();
	Mat imageDesc1, imageDesc2;
	Descriptor->compute(img1Gray, keyPoint1, imageDesc1);
	//cout << "imageDesc1:" << imageDesc1.rows << " " << imageDesc1.cols << endl;
	Descriptor->compute(img2Gray, keyPoint2, imageDesc2);
	//cout << "imageDesc2:" << imageDesc2.rows << " " << imageDesc2.cols << endl;

	FlannBasedMatcher matcher;
	vector<vector<DMatch>> matchePoints;
	vector<DMatch> GoodMatchePoints;

	vector<Mat> train_desc(1, imageDesc2);
	matcher.add(train_desc);
	matcher.train();

	matcher.knnMatch(imageDesc1, matchePoints, 2);
	cout << "total match points: " << matchePoints.size() << endl;

	// Lowe's algorithm,获取优秀匹配点
	for (int i = 0; i < matchePoints.size(); i++)
		if (matchePoints[i][0].distance < 0.4 * matchePoints[i][1].distance)
			GoodMatchePoints.push_back(matchePoints[i][0]);

	cout << "good match points: " << GoodMatchePoints.size() << endl;

	Mat first_match;
	drawMatches(img1, keyPoint2, img2, keyPoint1, GoodMatchePoints, first_match);
	//imshow("first_match ", first_match);
	string str1 = to_string(i) + "first_match.jpg";
	imwrite(str1, first_match);

	vector<Point2f> imagePoints1, imagePoints2;

	for (int i = 0; i < GoodMatchePoints.size(); i++)
	{
		imagePoints2.push_back(keyPoint2[GoodMatchePoints[i].queryIdx].pt);
		imagePoints1.push_back(keyPoint1[GoodMatchePoints[i].trainIdx].pt);
	}

	int image1PointsNum = imagePoints1.size();
	int image2PointsNum = imagePoints2.size();

	double sumImgKeyPointsX = 0, sumImgKeyPointsY = 0;
	for (int i = 0; i < image1PointsNum; ++i) {
		sumImgKeyPointsX += imagePoints1[i].x;
		sumImgKeyPointsY += imagePoints1[i].y;
	}
	p1.x = sumImgKeyPointsX / image1PointsNum;
	p1.y = sumImgKeyPointsY / image1PointsNum;

	sumImgKeyPointsX = 0; sumImgKeyPointsY = 0;
	for (int i = 0; i < image2PointsNum; ++i) {
		sumImgKeyPointsX += imagePoints2[i].x;
		sumImgKeyPointsY += imagePoints2[i].y;
	}
	p2.x = sumImgKeyPointsX / image2PointsNum;
	p2.y = sumImgKeyPointsY / image2PointsNum;
}

#endif