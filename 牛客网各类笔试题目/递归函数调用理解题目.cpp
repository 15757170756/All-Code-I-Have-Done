#include <iostream>
#include <cmath>

using namespace std;

int function2(int a[], int b, int e)
{
	if (e - b <= 1)
		return abs(a[b] - a[e]) >= 3 ? a[b] : a[e];
	int l = 0, r = 0;
	l = function2(a, b, b + (e - b) / 2);
	if (l % 2 == 0)
		r = function2(a, b + (e - b) / 2 + 1, e);
	else
		return l;
	if (l | r)
		return l | r;
	else
		return r;
}

int main()
{
	int a[] = { 10, 5, 8, 4, 5, 20, 2, 3 };
	cout << function2(a, 0, sizeof(a) / sizeof(1)) << endl;

	int b[] = { 3, 5, 8, 4, 8, 30, 2, 3 };
	cout << function2(b, 0, sizeof(b) / sizeof(1)) << endl;

	return 0;
}