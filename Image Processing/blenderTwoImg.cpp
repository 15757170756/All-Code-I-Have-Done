#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/stitching.hpp>
#include <opencv2/stitching/detail/matchers.hpp>
#include <opencv2/stitching/detail/blenders.hpp>

using namespace cv;
using namespace std;

int main()

//TEST(MultiBandBlender, CanBlendTwoImages)
{
	Mat image1 = imread("0006_1370_1360.jpg");
	Mat image2 = imread("0007_1030_1360.jpg");
	//ASSERT_EQ(image1.rows, image2.rows); ASSERT_EQ(image1.cols, image2.cols);

	Mat image1s, image2s;
	image1.convertTo(image1s, CV_16S);
	image2.convertTo(image2s, CV_16S);

	Mat mask1(image1s.size(), CV_8U);
	mask1(Rect(0, 0, mask1.cols / 2, mask1.rows)).setTo(255);
	mask1(Rect(mask1.cols / 2, 0, mask1.cols - mask1.cols / 2, mask1.rows)).setTo(0);
	imwrite("mask1.jpg", mask1);


	Mat mask2(image2s.size(), CV_8U);
	mask2(Rect(0, 0, mask2.cols / 2, mask2.rows)).setTo(0);
	mask2(Rect(mask2.cols / 2, 0, mask2.cols - mask2.cols / 2, mask2.rows)).setTo(255);
	imwrite("mask2.jpg", mask2);

	detail::MultiBandBlender blender(false, 5);

	blender.prepare(Rect(0, 0, max(image1s.cols, image2s.cols), max(image1s.rows, image2s.rows)));
	blender.feed(image1s, mask1, Point(0, 0));
	blender.feed(image2s, mask2, Point(0, 0));

	Mat result_s, result_mask;
	blender.blend(result_s, result_mask);
	Mat result; 
	result_s.convertTo(result, CV_8U);

	imwrite("result_s.jpg", result);
	//imwrite("result_mask.jpg", result_mask);

	//Mat expected = imread(string(cvtest::TS::ptr()->get_data_path()) + "stitching/baboon_lena.png");
	//double psnr = cvtest::PSNR(expected, result);
	//EXPECT_GE(psnr, 50);
}
