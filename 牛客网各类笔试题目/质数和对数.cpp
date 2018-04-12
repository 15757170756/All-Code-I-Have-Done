/*
给定一个正整数，编写程序计算有多少对质数的和等于输入的这个正整数，
并输出结果。输入值小于1000. 如，输入为10，程序应该输出结果为2。
（共有两对质数的和为10，分别为（5,5）,（3,7））

这笔试怎么这么简单，看来确实是越来越难了。
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <iterator>

using namespace::std;

bool isPrime(size_t n)
{
	if (n == 2)
		return true;
	if (n == 1)
		return false;
	int k = (int)sqrt(n);
	int i;
	for (i = 2; i <= k; ++i) {
		if (n % i == 0)
			return false;
	}
	if (i > k)
		return true;
	else
		return false;
}

int main(int argc, char* argv[])
{
	//freopen("input.txt", "r", stdin);
	while (1) {
		int n;
		cin >> n;
		int cnt = 0;
		for (int i = 2; i <= n / 2; ++i) {
			if (isPrime(i)
				&& isPrime(n - i)) {
				cout << n << '=' << i << '+' << n - i << endl;
				++cnt;
			}
		}

		cout << cnt << endl;
	}
	return 0;
}


