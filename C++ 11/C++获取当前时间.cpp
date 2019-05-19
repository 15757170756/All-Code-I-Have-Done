// 计算一个算法的耗时
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

// 获取系统当前时间
std::string getCurrentSystemTime()
{
	auto tt = std::chrono::system_clock::to_time_t
		(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	char date[60] = { 0 };
	sprintf(date, "%d-%02d-%02d-%02d.%02d.%02d",
		(int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday,
		(int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
	return std::string(date);
}

int main()
{
	using namespace std::chrono;
	steady_clock::time_point t1 = steady_clock::now();
	std::cout << "printing out 1000 stars...\n";
	for (int i = 0; i < 1000; ++i) std::cout << "*";
	std::cout << std::endl;
	steady_clock::time_point t2 = steady_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	std::cout << "It took me " << time_span.count() << " seconds.";
	std::cout << std::endl;
}
// --------------------- 
// 作者：LIZhang2016 
// 来源：CSDN 
// 原文：https://blog.csdn.net/baidu_31872269/article/details/82886569 
// 版权声明：本文为博主原创文章，转载请附上博文链接！

