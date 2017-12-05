#include <iostream>
#include <cstring>
#include <cmath>

using namespace::std;

/*
这里注意，如果double类型要比较等于
不要直接用等号
*/
bool equal(double num1, double num2)
{
	if ((num1 - num2 > -0.0000001) &&
		(num1 - num2 < 0.0000001))
		return true;
	else
		return false;
}

double Power1(double base, int exponent)
{
	if (equal(base, 0.0) && exponent < 0)
		return 0.0;

	double sum = 1.0;
	if (exponent == 0)
		return sum;
	else if (exponent > 0)
		for (int i = 0; i < exponent; ++i)
			sum *= base;

	else {
		exponent = -exponent;
		for (int i = 0; i < exponent; ++i)
			sum *= base;
		sum = 1 / sum;
	}

	return sum;
}

/*
这个代码exponent不能为负数
*/
double Power2(double base, unsigned int exponent)
{
	if (exponent == 0)
		return 1;
	if (exponent == 1)
		return base;

	double result = Power2(base, exponent >> 1);
	result *= result;
	if (exponent & 0x1 == 1)
		result *= base;

	return result;
}

int main()
{
	double base = -5;
	int exponent = -3;
	double result = Power1(base, exponent);
	cout << result << endl;

	result = Power2(base, exponent);
	cout << result << endl;

	return 0;
}