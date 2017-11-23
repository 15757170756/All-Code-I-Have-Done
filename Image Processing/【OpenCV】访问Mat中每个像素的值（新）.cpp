//方法零：.ptr和[]操作符
//
//Mat最直接的访问方法是通过.ptr<>函数得到一行的指针，并用[]操作符访问某一列的像素值。
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


//方法一：.ptr和指针操作
//
//除了[]操作符，我们可以移动指针*++的组合方法访问某一行中所有像素的值。
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


//方法二：.ptr、指针操作和取模运算
//
//方法二和方法一的访问方式相同，不同的是color reduce用模运算代替整数除法
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


/*方法三：.ptr、指针运算和位运算
由于进行量化的单元div通常是2的整次方，
因此所有的乘法和除法都可以用位运算表示。*/
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


/*方法四：指针运算
方法四和方法三量化处理的方法相同，
不同的是用指针运算代替*++操作。*/
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



/*方法五：.ptr、*++、位运算以及image.cols * image.channels()
这种方法就是没有计算nc，基本是个充数的方法。。*/
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


/*方法六：连续图像
Mat提供了isContinuous()函数用来查看Mat在内存中是不是连续存储，
如果是则图片被存储在一行中。*/
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


/*方法七：continuous+channels
与方法六基本相同，也是充数的。*/
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



/*方法八：Mat _iterator
真正有区别的方法来啦，
用Mat提供的迭代器代替前面的[]操作符或指针，
血统纯正的官方方法~*/
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


/*方法九：Mat_ iterator 和位运算
把方法八中的乘除法换成位运算。*/
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



/*方法十：MatIterator_
和方法八基本相同。。*/
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



/*方法十一：图像坐标*/
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


/*方法十二：创建输出图像
之前的方法都是直接修改原图，
方法十二新建了输出图像，主要用于后面的时间对比。*/
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


/*方法十三：重载操作符
Mat重载了+&等操作符，
可以直接将两个Scalar(B,G,R)数据进行位运算和数学运算。*/
// using overloaded operators  
void colorReduce13(cv::Mat &image, int div = 64) {
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// mask used to round the pixel value  
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0  
	// perform color reduction  
	image = (image&cv::Scalar(mask, mask, mask)) + cv::Scalar(div / 2, div / 2, div / 2);
}


//ptr函数典型源码：
inline uchar* Mat::ptr(int y)
{
	return data + step.p[0] * y;
}



//at函数典型源码：
template<typename _Tp> inline _Tp& Mat::at(int i0, int i1)
{
	return ((_Tp*)(data + step.p[0] * i0))[i1];
}


/*可以看到，指针*++访问和位运算是最快的方法；
而不断的计算image.cols*image.channles()花费了大量重复的时间；
另外迭代器访问虽然安全，但性能远低于指针运算；
通过图像坐标(j,i)访问时最慢的，
使用重载操作符直接运算效率最高。*/