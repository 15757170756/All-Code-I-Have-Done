#include <opencv2/opencv.hpp>
#include <iostream>

����ʹ��opencv��ͼ�񡢽ṹ�����ֺ�����c++ʵ�֣���������ˡ�
��ҪҲ���ĸ����裺
1.��˹�˲�
2.�ݶȼ���ֵ����ȡ
3.�Ǽ���ֵ����
4.˫��ֵ��Ե����
�ã����ڿ�ʼ���ܣ�ԭ����Բο����оٵĴ�������ӣ��Ұ�������Ĳ�̫����Ĵ����о�һ�¡�
1.��˹�˲�
1.1������ά��˹�˲�ģ��
[cpp] view plain copy
Mat createGaussianKernel2D(int ksize, float sigma)
{
	//sigmaԽ����ɢ�̶�Խ��������˼�Ȩ�Ĺ����У�����ֵ��Ȩ��Խ�����ɴ˴�����ͼ��Խģ����  
	//����û�й�һ���ĸ�˹��  
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

	//�����˹�˵ĺ�  
	float kernelSum = 0.0f;
	for (int i = 0; i < ksize; i++)
	{
		float *data = kernel.ptr<float>(i);
		for (int j = 0; j < ksize; j++)
		{
			kernelSum += data[j];
		}
	}
	//��һ����˹��  
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

1.2ʹ�ø�˹ģ����и�˹�˲�
[cpp] view plain copy
void gaussianFilter(const Mat &src, Mat& dst, int ksize = 3, float sigma = 1.0)
{
	int height = src.rows;
	int width = src.cols;
	int stype = src.type();
	Mat kernel = createGaussianKernel2D(5, sigma);
	int hf = ksize / 2;
	//Ϊԭʼͼ����Ӻ�ɫ��Ե���˲�ʱ�ӱ�Ե��ʼ�˲�  
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
			//��ÿ�����أ�ʹ�ø�˹�˽��о��  
			for (int m = 0; m < kernel.rows; m++)
			{
				uchar *_src_data = _src.ptr<uchar>(i + m);
				float *ker_data = kernel.ptr<float>(m);
				for (int n = 0; n < kernel.cols; n++)
				{
					conSum += ker_data[n] * (float)_src_data[j + n];
				}
			}
			//������õ��Ľ����ֵ��Ŀ������  
			dst_data[j] = (uchar)conSum;
			conSum = 0.0f;
		}
	}
}
[cpp] view plain copy
2.�ݶȼ���ֵ����ȡ�ݶ���ȡʹ��opencv�Դ���sobel��Ե�����
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
//�����ֵ  
		for (int j = 0; j < _srcGray.cols; j++)
			data[j] = std::sqrt(_dx[j] * _dx[j] + _dy[j] * _dy[j]);
}
3.�Ǽ���ֵ����
������һ��Ҫע��ģ��ܶ಩���н��ܵķǼ���ֵ���Ƶ�����ϵ�Ǳ�׼����ϵ��y�����ϣ�x�����ң���
��opencv�е�����ϵY�������µģ�
��˴�����45���135�㷽��ǵ�λ�õļ��㷽�����ձ�׼����ϵ�������Ǵ���ģ�
����ʹ����opencv�����������������ȷ���ˣ�
�����˺ö��û�еõ�����������������ϵ�㷴�ˡ�

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

4.˫��ֵ��Ե����
[cpp] view plain copy
//���ڸ���ֵ��2��Ҳ����һ���Ǳ�Ե����  
//С�ڸ���ֵ���ڵ���ֵ��1��Ҳ���ǿ����Ǳ�Ե����  
//С�ڵ���ֵ��0��Ҳ����һ�����Ǳ�Ե����  
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

//�жϿ���Ϊ��Ե���ص�ֵ��1���Ƿ����ȷ��Ϊ����  
//�ж�׼�򣬼�����������һ��ȷ����Ե����ô���ܱ�Ե��Ϊȷ����Ե  
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

//��ȷ����Ե�����أ����ͼ�����Ӧλ����255  
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
