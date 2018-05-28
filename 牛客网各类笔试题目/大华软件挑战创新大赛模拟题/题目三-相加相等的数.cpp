/*
"有一种特殊的正整数（int类型），将数分为两侧，
每侧至少有一位数，两侧的每个数字相加相等，
请写出判断的方法用来检测是否这种数。
比如：1236,可以拆分为123和6。"

"输入的第一行指定用例数量T；
用例的第二行输入正整数；"

输出是否为特殊的正整数


"bool is_magicnum(int number)

intput:
2
1232145
4543622

output:
1
1"

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

using namespace::std;

bool is_magicnum(int number)
{
	vector<int> vec;
	while (number) {
		int temp = number % 10;
		vec.push_back(temp);
		number /= 10;
	}
	reverse(vec.begin(), vec.end());
	vector<int>::iterator iter = vec.begin();
	for (int i = 1; i < vec.size(); ++i) {
		int sum1 = accumulate(iter, iter + i, 0);
		int sum2 = accumulate(iter + i, vec.end(), 0);
		//cout << sum1 << ' ' << sum2 << endl;
		if (sum2 == sum1)
			return true;
	}
	return false;
}

void test1()
{
	cout << is_magicnum(1232145) << endl;
	cout << is_magicnum(4543622) << endl;

}

int main(int argc, char* argv[])
{
	test1();

	return 0;
}

















//参考答案
#include <stdio.h>
#include <iostream>
using namespace std;

int CalculateSum(unsigned int nNum)
{
	int nFactor = 10;
	int nSum = 0;
	while (nNum > 0)
	{
		nSum += nNum % nFactor;
		nNum /= nFactor;
	}
	return nSum;
}

bool check_result(unsigned int nNum)
{
	bool bMagic = false;
	// this number should be big than 10
	if (nNum < 10)
	{
		return false;
	}

	unsigned int tmp = nNum;
	int nFactor = 10;		// Factor begin with 10. xxxx|x
	while (nFactor < nNum)
	{
		int nRightNum = tmp % nFactor;	// the nNum is departed by '|' from nRightNum and nLeftNum. 
		int nLeftNum = tmp / nFactor;

		int nRightSum = CalculateSum(nRightNum);
		int nLeftSum = CalculateSum(nLeftNum);

		// if two sum are equal,then the nNum is a magic number.
		if (nRightSum == nLeftSum)
		{
			bMagic = true;
			break;
		}

		// move the Factor to the left. 
		nFactor *= 10;
	}
	return bMagic;
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int nNum = 0;
		cin >> nNum;
		bool bMagic = check_result(nNum);
		cout << bMagic << endl;
	}
	return 0;
}
