/*
时间限制：1秒
空间限制：32768K

小Q今天在上厕所时想到了这个问题：有n个数，
两两组成二元组，差最小的有多少对呢？差最大呢？
输入描述:
输入包含多组测试数据。
对于每组测试数据：
N - 本组测试数据有n个数
a1,a2...an - 需要计算的数据
保证:
1<=N<=100000,0<=ai<=INT_MAX.
输出描述:
对于每组数据，输出两个数，第一个数表示差最小的对数，
第二个数表示差最大的对数。
输入例子1:
6
45 12 45 32 5 6
输出例子1:
1 2
*/


/*
我觉得这个题目的坑是在——输入包含多组测试数据。
当然也是我太不专业了，因为多组测试数据，这样
定义变量的时候一定得放在while循环里边
比如vector<int> vec;如果放在while循环外面
这样会导致vec一直在加数据，结果肯定不对。
但是这个题目总体来说比较简单。
*/


#include <algorithm>
#include <vector>
#include <iostream>

using namespace::std;

int main()
{
	int n;
	while (cin >> n) {
		int pairOfMaxNum = 0, pairOfMinNum = 0;
		int temp;
		vector<int> vec;
		for (int i = 0; i < n; ++i) {
			cin >> temp;
			vec.emplace_back(temp);
		}

		sort(vec.begin(), vec.end());
		int minNum = vec[0], maxNum = vec[n - 1];
		int minCnt = count(vec.begin(), vec.end(), minNum);
		int maxCnt = count(vec.begin(), vec.end(), maxNum);
		pairOfMaxNum = minCnt * maxCnt;

		vector<int> vecDiff;
		for (int i = 0; i < n - 1; ++i) {
			int diff = vec[i + 1] - vec[i];
			vecDiff.emplace_back(diff);
		}

		sort(vecDiff.begin(), vecDiff.end());

		int minDiffNum = vecDiff[0];
		if (0 == minDiffNum) {
			for (int i = 1; i < n; ++i) {
				int j = i - 1;
				while (j >= 0 && vec[j] == vec[i]) {
					++pairOfMinNum;
					--j;
				}
			}
		}

		else {
			pairOfMinNum = count(vecDiff.begin(),
				vecDiff.end(), vecDiff[0]);
		}

		cout << pairOfMinNum << ' ' << pairOfMaxNum << endl;
	}

	return 0;
}