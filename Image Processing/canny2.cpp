#include <opencv2/opencv.hpp>
#include <iostream>

本文使用opencv的图像、结构、部分函数、c++实现，力求简单明了。
主要也是四个步骤：
1.高斯滤波
2.梯度及幅值的求取
3.非极大值抑制
4.双阈值边缘连接
好，现在开始介绍，原理可以参考我列举的大神的帖子，我把我那码的不太整齐的代码列举一下。
1.高斯滤波
1.1产生二维高斯滤波模板
[cpp] view plain copy
Mat createGaussianKernel2D(int ksize, float sigma)
{
	//sigma越大，离散程度越厉害，因此加权的过程中，中心值的权重越弱，由此带来的图像越模糊；  
	//计算没有归一化的高斯核  
	Mat kernel = Mat::zeros(ksize, ksize, CV_32FC1);
	int ci = (ksize - 1) / 2;
	int cj = (ksize - 1) / 2;
	for (int i = -1 * ci; i <= ci; i++)
	{
		float *data = kernel.ptr<float>(i + ci);
		for (int j = -1 * cj; j <= cj; j++)
		{
			float eval = (-1 * float(1) / 2 * ((float(i)*i + float(j)*j) / (sigma*sigma)));
			data[j + cj] = exp(eval);
		}
	}

	//计算高斯核的和  
	float kernelSum = 0.0f;
	for (int i = 0; i < ksize; i++)
	{
		float *data = kernel.ptr<float>(i);
		for (int j = 0; j < ksize; j++)
		{
			kernelSum += data[j];
		}
	}
	//归一化高斯核  
	for (int i = 0; i < ksize; i++)
	{
		float *data = kernel.ptr<float>(i);
		for (int j = 0; j < ksize; j++)
		{
			data[j] = data[j] / kernelSum;
		}
	}
	return kernel;
}

1.2使用高斯模板进行高斯滤波
[cpp] view plain copy
void gaussianFilter(const Mat &src, Mat& dst, int ksize = 3, float sigma = 1.0)
{
	int height = src.rows;
	int width = src.cols;
	int stype = src.type();
	Mat kernel = createGaussianKernel2D(5, sigma);
	int hf = ksize / 2;
	//为原始图像添加黑色边缘，滤波时从边缘开始滤波  
	Mat _src = Mat::zeros(height + hf * 2, width + hf * 2, stype);
	for (int i = hf; i < _src.rows - hf; i++)
	{
		uchar *in = (uchar*)src.ptr<uchar>(i - hf);
		uchar *out = _src.ptr<uchar>(i);
		for (int j = hf; j < _src.cols - hf; j++)
		{
			out[j] = in[j - hf];
		}
	}

	float conSum = 0.0f;
	dst = Mat::zeros(height, width, stype);
	for (int i = 0; i < _src.rows - 2 * hf; i++)
	{
		uchar *dst_data = dst.ptr<uchar>(i);
		for (int j = 0; j < _src.cols - 2 * hf; j++)
		{
			//对每个像素，使用高斯核进行卷积  
			for (int m = 0; m < kernel.rows; m++)
			{
				uchar *_src_data = _src.ptr<uchar>(i + m);
				float *ker_data = kernel.ptr<float>(m);
				for (int n = 0; n < kernel.cols; n++)
				{
					conSum += ker_data[n] * (float)_src_data[j + n];
				}
			}
			//将卷积得到的结果赋值给目的像素  
			dst_data[j] = (uchar)conSum;
			conSum = 0.0f;
		}
	}
}
[cpp] view plain copy
2.梯度及幅值的求取梯度求取使用opencv自带的sobel边缘检测器
Mat dx = Mat::zeros(_srcGray.rows, _srcGray.cols, CV_32FC1);
Mat dy = Mat::zeros(_srcGray.rows, _srcGray.cols, CV_32FC1);
Mat mag = Mat::zeros(_srcGray.rows, _srcGray.cols, CV_32FC1); 
Sobel(_srcGauBlur, dx, CV_32FC1, 1, 0, sobel_size);
Sobel(_srcGauBlur, dy, CV_32FC1, 0, 1, sobel_size);

for (int i = 0; i < _srcGray.rows; i++)
{
	float* _dx = dx.ptr<float>(i);
	float* _dy = dy.ptr<float>(i);
	float* data = mag.ptr<float>(i);
//计算幅值  
		for (int j = 0; j < _srcGray.cols; j++)
			data[j] = std::sqrt(_dx[j] * _dx[j] + _dy[j] * _dy[j]);
}
3.非极大值抑制
这里有一点要注意的，很多博文中介绍的非极大值抑制的坐标系是标准坐标系（y轴向上，x轴向右），
而opencv中的坐标系Y轴是向下的，
因此代码中45°和135°方向角的位置的计算方法按照标准坐标系看起来是错误的，
但我使用了opencv所以这样计算就是正确的了，
测试了好多次没有得到结果，最后发现是坐标系搞反了。

Mat nms = mag.clone();
for (int i = 1; i < _srcGray.rows - 1; i++)
{
	float* _dx = dx.ptr<float>(i);
	float* _dy = dy.ptr<float>(i);
	float *line0 = mag.ptr<float>(i - 1);
	float *line1 = mag.ptr<float>(i);
	float *line2 = mag.ptr<float>(i + 1);
	float *data = nms.ptr<float>(i);
	for (int j = 1; j < _srcGray.cols - 1; j++)
	{
		float direction = cv::fastAtan2(_dy[j], _dx[j]);
		if ((direction > 0 && direction <= 22.5) || (direction >157.5 &&
			direction <= 202.5) || (direction>337.5 && direction <= 360))
		{
			if (line1[j]<line1[j + 1] | line1[j] < line1[j - 1])
				data[j] = 0;
		}
		else if ((direction > 22.5 && direction <= 67.5) ||
			(direction >202.5 && direction < 247.5))
		{
			if (line1[j]<line0[j - 1] | line1[j] < line2[j + 1])
				data[j] = 0.0;
		}
		else if ((direction > 67.5 && direction <= 112.5) ||
			(direction>247.5 && direction <= 292.5))
		{
			if (line1[j] < line0[j] | line1[j] < line2[j])
				data[j] = 0.0;
		}
		else if ((direction > 112.5 && direction < 157.5) ||
			(direction>292.5 && direction < 337.5))
		{
			if (line1[j] < line0[j + 1] | line1[j] < line2[j - 1])
				data[j] = 0.0;
		}
		else{ ; }
	}
}

4.双阈值边缘连接
[cpp] view plain copy
//大于高阈值置2，也就是一定是边缘像素  
//小于高阈值大于低阈值置1，也就是可能是边缘像素  
//小于低阈值置0，也就是一定不是边缘像素  
Mat dval = Mat::zeros(_srcGray.rows, _srcGray.cols, CV_8UC1);
for (int i = 0; i < _srcGray.rows; i++)
{
	uchar *in_data = nms.ptr<uchar>(i);
	uchar *data = dval.ptr<uchar>(i);
	for (int j = 0; j < _srcGray.cols; j++)
	{
		if (in_data[j] >= high_thresh)
			data[j] = 2;
		if (in_data[j] < high_thresh &in_data[j] >= low_thresh)
			data[j] = 1;
		if (in_data[j] < low_thresh)
			data[j] = 0;
	}
}

//判断可能为边缘像素的值（1）是否加入确定为像素  
//判断准则，加入邻域内有一个确定边缘，那么可能边缘变为确定边缘  
Mat dval_find = Mat::zeros(_srcGray.rows, _srcGray.cols, CV_8UC1);
dval_find = dval.clone();
for (int i = 1; i < _srcGray.rows - 1; i++)
{
	uchar *in_data0 = dval.ptr<uchar>(i - 1);
	uchar *in_data1 = dval.ptr<uchar>(i);
	uchar *in_data2 = dval.ptr<uchar>(i + 1);
	uchar *data = dval_find.ptr<uchar>(i);
	for (int j = 1; j < _srcGray.cols - 1; j++)
	{
		if (in_data1[j] == 1)
		{
			if (in_data0[j - 1] == 2 | in_data0[j] == 2 | in_data0[j + 1] == 2\
				| in_data1[j - 1] == 2 | in_data1[j + 1] == 2\
				| in_data2[j - 1] == 2 | in_data2[j] == 2 | in_data2[j + 1] == 2)
			{
				data[j] = 2;
			}
		}
	}
}

//是确定边缘的像素，输出图像的相应位置置255  
Mat out_img = Mat::zeros(_srcGray.rows, _srcGray.cols, CV_8UC1);
for (int i = 0; i < _srcGray.rows; i++)
{
	uchar *in_data = dval_find.ptr<uchar>(i);
	uchar *data = out_img.ptr<uchar>(i);
	for (int j = 0; j < _srcGray.cols; j++)
	{
		if (in_data[j] == 2)
		{
			data[j] = 255;
		}
	}
}
