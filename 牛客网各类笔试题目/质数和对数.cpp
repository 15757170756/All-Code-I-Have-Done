/*
����һ������������д��������ж��ٶ������ĺ͵�������������������
��������������ֵС��1000. �磬����Ϊ10������Ӧ��������Ϊ2��
���������������ĺ�Ϊ10���ֱ�Ϊ��5,5��,��3,7����

�������ô��ô�򵥣�����ȷʵ��Խ��Խ���ˡ�
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


