/*

*/


cv::Mat src = cv::imread("lenna.jpg");
cv::Mat dst;

cv::Size dst_sz = src.size();

//定义平移矩阵
cv::Mat t_mat = cv::Mat::zeros(2, 3, CV_32FC1);

t_mat.at<float>(0, 0) = 1;
t_mat.at<float>(0, 2) = 20; //水平平移量
t_mat.at<float>(1, 1) = 1;
t_mat.at<float>(1, 2) = 10; //竖直平移量

//根据平移矩阵进行仿射变换
cv::warpAffine(src, dst, t_mat, dst_sz);

//显示平移效果
cv::imshow("image", src);
cv::imshow("result", dst);

cv::waitKey(0);

return 0;