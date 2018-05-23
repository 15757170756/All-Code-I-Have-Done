#include <iostream>
#include <cstring>
#include <cmath>

using namespace::std;

/*
这个方法比较巧妙
*/
int NumberOf0(int n)
{
	int count = 0;
	while (n + 1) {
		++count;
		n = (n + 1) | n;
	}
	return count;
}

int main()
{
	int n = -1234;
	int cnt = NumberOf0(n);
	cout << cnt << endl;

	return 0;
}
