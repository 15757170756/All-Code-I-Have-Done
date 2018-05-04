/*
"网络上有一台流媒体服务器S和一台客户端C，S向C发送流媒体数据。
1、S的发送速率为M；
2、C有一个缓冲区B，最大值大小为X，B接收来自S的流媒体，
C处理B中的数据并清理，B的处理速度为N。
3、为保证C处理的效率，当缓冲区大小超过80%时，
C发送停止命令给S，S将停止向C发送数据。
4、当缓冲区大小小于60%时，C向S发送重启发送数据命令，S向C发送数据。
5、题中所有单位都是基本单位。

请设计一个函数handle_data_func，用来处理缓冲区B,
并计算C第一次向S发送重启发送数据命令的时间T0及每次发送重启命令的的时间间隔T1。
注意：输出默认保留两位小数"

"输入的第一行指定用例数量T；
用例的第二行输入速率M、N；
用例的第三行输入缓冲区大小X；"

客户端C第一次向服务端S发送重启发送数据命令的时间及时间间隔。

不考虑网络上的延时。


"
int handle_data_func(int M,int N,int X,int &T1)
input:
1
2 1
10
output:
10.00
4.00

"

*/



#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>
#include <unordered_set>
#include <sstream>
#include <map>
#include <iterator>
#include <set>
#include <stack>
#include <deque>
#include <functional>
#include <cstdlib>
#include <ctime>

using namespace::std;

float handle_data_func(float M, float N, float X, float &T1)
{
	float d = M - N;
	float T01, T02;
	T01 = 0.8*X / d;
	T02 = (0.8 - 0.6)*X / N;
	T1 = (0.8 - 0.6)*X*(1.0 / N + 1.0 / d);
	return (T01 + T02);
}

double handle_data_func2(double M, double N, double X, double &T1)
{
	double v = M - N;
	double t1 = 0.0, t2 = 0.0;
	t1 = (0.8 * X) / v;
	t2 = (0.2 * X) / N;

	double T0 = t1 + t2;

	t1 = (0.2 * X) / v;

	T1 = t1 + t2;
	return T0;

}

void test1()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		float M, N, X;
		scanf("%f%f", &M, &N);
		scanf("%f", &X);
		float T1, T2;
		T2 = handle_data_func(M, N, X, T1);
		printf("%.2f\n%.2f\n", T2, T1);
	}
}

void test2()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		double M, N, X;
		scanf("%lf%lf", &M, &N);
		scanf("%lf", &X);
		double T1, T2;
		T2 = handle_data_func2(M, N, X, T1);
		printf("%.2f\n%.2f\n", T2, T1);
	}
}



int main(int argc, char* argv[])
{
	test1();
	test2();

	return 0;
}

























//参考答案
/* 试题描述
* 网络上有一台流媒体服务器S和一台客户端C，S向C发送流媒体数据。
* 1、S的发送速率为M；
* 2、C有一个缓冲区B，最大值大小为X，B接收来自S的流媒体，C处理B中的数据并清理，B的处理速度为N。
* 3、为保证C处理的效率，当缓冲区大小超过80%时，C发送停止命令给S，S将停止向C发送数据。
* 4、当缓冲区大小小于60%时，C向S发送重启发送数据命令，S向C发送数据。
* 5、题中所有单位都是基本单位。
* 请设计一个函数handle_data_func，用来处理缓冲区B，并计算C第一次向S发送重启发送数据命令的时间T0及每次发送重启命令的的时间间隔T1。
*/
#include<iostream>
#include<stdio.h>
using namespace std;

double handle_data_func(double M, double N, double X, double &T1)
{
	double T0 = 0;
	double nSpeed = M - N;					// 发送速度减去接收速度为客户端的累积速度。
	T0 = 0.8*X / nSpeed + 0.2*X / N;
	T1 = 0.2*X / nSpeed + 0.2*X / N;
	return T0;
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		double M, N, X;
		double T0, T1 = 0;
		cin >> M >> N >> X;

		T0 = handle_data_func(M, N, X, T1);
		if (T0 <= 0)
		{
			cout << "You must input some wrong parameters" << endl;
		}
		else
		{
			printf("%.2f\n", T0);
			printf("%.2f\n", T1);
		}
	}
	return 0;
}
