/*
时间限制：1秒

空间限制：32768K

一个数轴上共有N个点，第一个点的坐标是度度熊现在位置，第N-1个点是度度熊的家。
现在他需要依次的从0号坐标走到N - 1号坐标。
但是除了0号坐标和N - 1号坐标，他可以在其余的N-2个坐标中选出一个点，
并直接将这个点忽略掉，问度度熊回家至少走多少距离？
输入描述 :
输入一个正整数N, N <= 50。

接下来N个整数表示坐标，正数表示X轴的正方向，负数表示X轴的负方向。
绝对值小于等于100

输出描述 :
输出一个整数表示度度熊最少需要走的距离。

输入例子1 :
4
1 4 -1 3

输出例子1 :
4
*/

//我的代码，通过率为60%。。。
//测试用例:
//20
//74 84 92 23 5 - 70 - 47 - 59 24 - 86 - 39 99 85 - 42 54 100 47 - 3 42 38
//
//对应输出应该为 :
//
//		836
//
//	你的输出为 :
//
//		  1000
#include <set>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace::std;

int main()
{
	vector<int> vec;
	int N, temp;
	cin >> N;
	while (N--) {
		cin >> temp;
		vec.push_back(temp);
	}

	int thisDis, maxDis = 0;
	int maxIdx;
	vector<int> vecDis;
	for (int i = 0; i < vec.size() - 1; ++i) {
		int thisDis = abs(vec[i + 1] - vec[i]);
		if (thisDis > maxDis) {
			maxDis = thisDis;
			maxIdx = i;
		}
	}

	int sumDis = 0;
	for (int i = 0; i < vec.size() - 1; ++i) {
		if (i == maxIdx) {
			thisDis = abs(vec[i + 2] - vec[i]);
			++i;
		}
		else
			thisDis = abs(vec[i + 1] - vec[i]);
		sumDis += thisDis;
	}

	cout << sumDis << endl;
}










//网上找的

//说一下自己的思路。在若干点中选择一点，使全程的路程最小。
//其实说白了就是选择一点i，使其缩小的距离最大，
//即原来的距离是dis(i - 1, i) + dis(i, i + 1)，
//去掉点i之后的距离是dis(i - 1, i + 1)，只要遍历一遍，
//求出每个点上面两个距离的差值，求最大值，
//就可以确定要忽略哪个点了
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
int main()
{
	int n;
	cin >> n;
	//学习一下这种初始化方法
	vector<int> vec(n);
	for (int &i : vec)
		cin >> i;

	int max = 0;
	int index = -1;
	int yuanlai;
	int houlai;
	for (vector<int>::size_type i = 1; i < n - 1; ++i) {
		yuanlai = abs(vec[i] - vec[i - 1]) + abs(vec[i] - vec[i + 1]);
		houlai = abs(vec[i - 1] - vec[i + 1]);
		if (yuanlai - houlai > max) {
			max = yuanlai - houlai;
			index = i;
		}
	}
	if (index != -1)
		vec.erase(vec.begin() + index);
	int sum = 0;
	for (vector<int>::size_type i = 0; i < vec.size() - 1; ++i)
		sum += abs(vec[i] - vec[i + 1]);
	cout << sum;
	return 0;
}