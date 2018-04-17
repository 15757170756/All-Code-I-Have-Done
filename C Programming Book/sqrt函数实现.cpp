#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <stack>
#include <queue>
#include <functional>
#include <cmath>

using namespace::std;

float mySqrt1(float n)
{
	if (n < 0)
		return -1.0;
	const float EPS = 0.00001;
	float start = 0;
	float end = n;
	float last;
	float mid = (start + end) / 2;
	do {
		float multi = mid * mid;
		if (multi > n)
			end = mid;
		else if (multi < n)
			start = mid;
		last = mid;
		mid = (start + end) / 2;
	} while (abs(mid - last) > EPS);
	return mid;
}


//牛顿迭代法，但是没有3好
float mySqrt2(float n)
{
	const float EPS = 0.0001;
	float x0 = n;
	float y0 = x0*x0 - n;
	float xn;
	do {
		xn = x0 - y0 / 2 / x0;
		x0 = xn;
		y0 = x0*x0 - n;
	} while (abs(xn * xn - n) > EPS);
	return xn;
}

float mySqrt3(float x)
{
	const float EPS = 0.0001;
	float val = x;//最终
	float last;//保存上一个计算的值
	do
	{
		last = val;
		val = (val + x / val) / 2;
	} while (abs(val - last) > EPS);
	return val;
}

float mySqrt4(float x)
{
	float xhalf = 0.5f*x;
	int i = *(int*)&x; // get bits for floating VALUE 
	i = 0x5f375a86 - (i >> 1); // gives initial guess y0
	x = *(float*)&i; // convert bits BACK to float
	x = x*(1.5f - xhalf*x*x); // Newton step, repeating increases accuracy
	x = x*(1.5f - xhalf*x*x); // Newton step, repeating increases accuracy
	x = x*(1.5f - xhalf*x*x); // Newton step, repeating increases accuracy

	return 1 / x;
}

int main(int argc, char* argv[])
{
	float n = 6565535.0;
	cout << sqrt(n) << endl;
	cout << mySqrt1(n) << endl;
	cout << mySqrt3(n) << endl;
	cout << mySqrt4(n) << endl;
}

