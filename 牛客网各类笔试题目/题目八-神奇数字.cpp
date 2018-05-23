/*
一个数可以用二进制表示，也可以用十进制表示，
如果该数的二进制表示法所有位数字之和等于十进制表示法所有位数字之和，则称该数为神奇数。
比如：21(十进制)=10101(二进制),
所有位数之和为2+1=3,1+0+1+0+1=3。求小于等于M的神奇数有多少个。

1<=M<=100000

Input:
2
100
300

Output:
3
11
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
#include <numeric>
#include <unordered_map>

using namespace::std;

bool isMagicNum(int num)
{
	int sum1 = 0, sum2 = 0;
	int temp = num;
	while (temp) {
		sum1 += temp % 10;
		temp /= 10;
	}
	temp = num;
	while (temp) {
		sum2 += temp % 2;
		temp /= 2;
	}
	//cout << sum1 << ' ' << sum2 << endl;

	return sum1 == sum2;
}

int getMagicNum(int num)
{
	int cnt = 0;
	for (int i = 1; i <= num; ++i)
		if (isMagicNum(i)) {
			//cout << i << endl;
			++cnt;
		}
	return cnt;
}

void test1()
{
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	while (t--) {
		int num;
		cin >> num;
		cout << getMagicNum(num) << endl;
	}

}


int main(int argc, char* argv[])
{
	test1();
	return 0;
}