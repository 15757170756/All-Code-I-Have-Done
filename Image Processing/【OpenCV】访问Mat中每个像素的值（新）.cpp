#include <opencv2/opencv.hpp>

using namespace::std;
using namespace::cv;

//�����㣺.ptr��[]������
//
//Mat��ֱ�ӵķ��ʷ�����ͨ��.ptr<>�����õ�һ�е�ָ�룬����[]����������ĳһ�е�����ֵ��
// using .ptr and []  

void colorReduce0(cv::Mat &image, int div = 64) 
{
	int nr = image.rows; // number of rows  
	int nc = image.cols * image.channels(); // total number of elements per line  
	for (int j = 0; j < nr; j++) {
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++) {
			data[i] = data[i] / div*div + div / 2;
		}
	}
}


//����һ��.ptr��ָ�����
//
//����[]�����������ǿ����ƶ�ָ��*++����Ϸ�������ĳһ�����������ص�ֵ��
// using .ptr and * ++   
void colorReduce1(cv::Mat &image, int div = 64) {
	int nr = image.rows; // number of rows  
	int nc = image.cols * image.channels(); // total number of elements per line  
	for (int j = 0; j < nr; j++) {
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++) {
			*data++ = *data / div*div + div / 2;
		} // end of row                   
	}
}


//��������.ptr��ָ�������ȡģ����
//
//�������ͷ���һ�ķ��ʷ�ʽ��ͬ����ͬ����color reduce��ģ���������������
// using .ptr and * ++ and modulo  
void colorReduce2(cv::Mat &image, int div = 64) {
	int nr = image.rows; // number of rows  
	int nc = image.cols * image.channels(); // total number of elements per line  
	for (int j = 0; j < nr; j++) {
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++) {
			int v = *data;
			*data++ = v - v%div + div / 2;
		} // end of row                   
	}
}


/*��������.ptr��ָ�������λ����
���ڽ��������ĵ�Ԫdivͨ����2�����η���
������еĳ˷��ͳ�����������λ�����ʾ��*/
// using .ptr and * ++ and bitwise  
void colorReduce3(cv::Mat &image, int div = 64) {
	int nr = image.rows; // number of rows  
	int nc = image.cols * image.channels(); // total number of elements per line  
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// mask used to round the pixel value  
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0  
	for (int j = 0; j < nr; j++) {
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++) {
			*data++ = *data&mask + div / 2;
		} // end of row                   
	}
}


/*�����ģ�ָ������
�����ĺͷ�������������ķ�����ͬ��
��ͬ������ָ���������*++������*/
// direct pointer arithmetic  
void colorReduce4(cv::Mat &image, int div = 64) {
	int nr = image.rows; // number of rows  
	int nc = image.cols * image.channels(); // total number of elements per line  
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	int step = image.step; // effective width  
	// mask used to round the pixel value  
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0  
	// get the pointer to the image buffer  
	uchar *data = image.data;
	for (int j = 0; j < nr; j++) {
		for (int i = 0; i < nc; i++) {
			*(data + i) = *data&mask + div / 2;
		} // end of row                   
		data += step;  // next line  
	}
}



/*�����壺.ptr��*++��λ�����Լ�image.cols * image.channels()
���ַ�������û�м���nc�������Ǹ������ķ�������*/
// using .ptr and * ++ and bitwise with image.cols * image.channels()  
void colorReduce5(cv::Mat &image, int div = 64) {
	int nr = image.rows; // number of rows  
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// mask used to round the pixel value  
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0  
	for (int j = 0; j < nr; j++) {
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < image.cols * image.channels(); i++) {
			*data++ = *data&mask + div / 2;
		} // end of row                   
	}
}


/*������������ͼ��
Mat�ṩ��isContinuous()���������鿴Mat���ڴ����ǲ��������洢��
�������ͼƬ���洢��һ���С�*/
// using .ptr and * ++ and bitwise (continuous)  
void colorReduce6(cv::Mat &image, int div = 64) {
	int nr = image.rows; // number of rows  
	int nc = image.cols * image.channels(); // total number of elements per line  
	if (image.isContinuous())  {
		// then no padded pixels  
		nc = nc*nr;
		nr = 1;  // it is now a 1D array  
	}
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// mask used to round the pixel value  
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0  
	for (int j = 0; j < nr; j++) {
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++) {
			*data++ = *data&mask + div / 2;
		} // end of row                   
	}
}


/*�����ߣ�continuous+channels
�뷽����������ͬ��Ҳ�ǳ����ġ�*/
// using .ptr and * ++ and bitwise (continuous+channels)  
void colorReduce7(cv::Mat &image, int div = 64) {
	int nr = image.rows; // number of rows  
	int nc = image.cols; // number of columns  
	if (image.isContinuous())  {
		// then no padded pixels  
		nc = nc*nr;
		nr = 1;  // it is now a 1D array  
	}
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// mask used to round the pixel value  
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0  
	for (int j = 0; j < nr; j++) {
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++) {
			*data++ = *data&mask + div / 2;
			*data++ = *data&mask + div / 2;
			*data++ = *data&mask + div / 2;
		} // end of row                   
	}
}



/*�����ˣ�Mat _iterator
����������ķ���������
��Mat�ṩ�ĵ���������ǰ���[]��������ָ�룬
Ѫͳ�����Ĺٷ�����~*/
// using Mat_ iterator   
void colorReduce8(cv::Mat &image, int div = 64) {
	// get iterators  
	cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();
	for (; it != itend; ++it) {
		(*it)[0] = (*it)[0] / div*div + div / 2;
		(*it)[1] = (*it)[1] / div*div + div / 2;
		(*it)[2] = (*it)[2] / div*div + div / 2;
	}
}


/*�����ţ�Mat_ iterator ��λ����
�ѷ������еĳ˳�������λ���㡣*/
// using Mat_ iterator and bitwise  
void colorReduce9(cv::Mat &image, int div = 64) {
	// div must be a power of 2  
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// mask used to round the pixel value  
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0  
	// get iterators  
	cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();
	for (; it != itend; ++it) {
		(*it)[0] = (*it)[0] & mask + div / 2;
		(*it)[1] = (*it)[1] & mask + div / 2;
		(*it)[2] = (*it)[2] & mask + div / 2;
	}
}



/*����ʮ��MatIterator_
�ͷ����˻�����ͬ����*/
// using Mat_ iterator and bitwise  
// using MatIterator_   
void colorReduce10(cv::Mat &image, int div = 64) {
	cv::Mat_<cv::Vec3b> cimage = image;
	cv::Mat_<cv::Vec3b>::iterator it = cimage.begin();
	cv::Mat_<cv::Vec3b>::iterator itend = cimage.end();
	for (; it != itend; it++) {
		(*it)[0] = (*it)[0] / div*div + div / 2;
		(*it)[1] = (*it)[1] / div*div + div / 2;
		(*it)[2] = (*it)[2] / div*div + div / 2;
	}
}



/*����ʮһ��ͼ������*/
// using (j,i)  
void colorReduce11(cv::Mat &image, int div = 64) {
	int nr = image.rows; // number of rows  
	int nc = image.cols; // number of columns  
	for (int j = 0; j < nr; j++) {
		for (int i = 0; i < nc; i++) {
			image.at<cv::Vec3b>(j, i)[0] = image.at<cv::Vec3b>(j, i)[0] / div*div + div / 2;
			image.at<cv::Vec3b>(j, i)[1] = image.at<cv::Vec3b>(j, i)[1] / div*div + div / 2;
			image.at<cv::Vec3b>(j, i)[2] = image.at<cv::Vec3b>(j, i)[2] / div*div + div / 2;
		} // end of row                   
	}
}


/*����ʮ�����������ͼ��
֮ǰ�ķ�������ֱ���޸�ԭͼ��
����ʮ���½������ͼ����Ҫ���ں����ʱ��Աȡ�*/
// with input/ouput images  
void colorReduce12(const cv::Mat &image, // input image   
	cv::Mat &result,      // output image  
	int div = 64) {
	int nr = image.rows; // number of rows  
	int nc = image.cols; // number of columns  
	// allocate output image if necessary  
	result.create(image.rows, image.cols, image.type());
	// created images have no padded pixels  
	nc = nc*nr;
	nr = 1;  // it is now a 1D array  
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// mask used to round the pixel value  
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0  
	for (int j = 0; j < nr; j++) {
		uchar* data = result.ptr<uchar>(j);
		const uchar* idata = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++) {
			*data++ = (*idata++)&mask + div / 2;
			*data++ = (*idata++)&mask + div / 2;
			*data++ = (*idata++)&mask + div / 2;
		} // end of row                   
	}
}


/*����ʮ�������ز�����
Mat������+&�Ȳ�������
����ֱ�ӽ�����Scalar(B,G,R)���ݽ���λ�������ѧ���㡣*/
// using overloaded operators  
void colorReduce13(cv::Mat &image, int div = 64) {
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// mask used to round the pixel value  
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0  
	// perform color reduction  
	image = (image&cv::Scalar(mask, mask, mask)) + cv::Scalar(div / 2, div / 2, div / 2);
}


//ptr��������Դ�룺
inline uchar* Mat::ptr(int y)
{
	return data + step.p[0] * y;
}



//at��������Դ�룺
template<typename _Tp> inline _Tp& Mat::at(int i0, int i1)
{
	return ((_Tp*)(data + step.p[0] * i0))[i1];
}


/*���Կ�����ָ��*++���ʺ�λ���������ķ�����
�����ϵļ���image.cols*image.channles()�����˴����ظ���ʱ�䣻
���������������Ȼ��ȫ��������Զ����ָ�����㣻
ͨ��ͼ������(j,i)����ʱ�����ģ�
ʹ�����ز�����ֱ������Ч����ߡ�*/