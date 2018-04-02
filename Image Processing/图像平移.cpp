/*

*/


cv::Mat src = cv::imread("lenna.jpg");
cv::Mat dst;

cv::Size dst_sz = src.size();

//����ƽ�ƾ���
cv::Mat t_mat = cv::Mat::zeros(2, 3, CV_32FC1);

t_mat.at<float>(0, 0) = 1;
t_mat.at<float>(0, 2) = 20; //ˮƽƽ����
t_mat.at<float>(1, 1) = 1;
t_mat.at<float>(1, 2) = 10; //��ֱƽ����

//����ƽ�ƾ�����з���任
cv::warpAffine(src, dst, t_mat, dst_sz);

//��ʾƽ��Ч��
cv::imshow("image", src);
cv::imshow("result", dst);

cv::waitKey(0);

return 0;