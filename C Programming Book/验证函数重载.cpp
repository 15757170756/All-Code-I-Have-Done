#include <iostream>

using namespace::std;

int func(int a, int b)
{
	return a + b;
}

int func(double a, double b)
{
	return static_cast<int>(a + b);
}

int main()
{
	int a = 1, b = 2;
	double c = 1.1, d = 2.2;
	cout << func(a, b) << endl;
	cout << func(c, d) << endl;
}