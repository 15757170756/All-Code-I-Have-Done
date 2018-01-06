/*
时间限制:8000ms
单点时限:1000ms
内存限制:256MB
描述
给定n个整数常数c[1], c[2], ..., c[n]和一个整数k。
现在需要给2k个整数变量x[1], x[2], ..., x[k], y[1], y[2], ..., y[k]赋值，满足

（1）对于所有1 ≤ i ≤ k，都有x[i] ≤ y[i]。

（2）对于所有1 ≤ i ≤ n，都存在至少一个j (1 ≤ j ≤ k)，
使得x[j] ≤ c[i] ≤ y[j]。

求出S=(y[1] + y[2] + ... + y[k]) - (x[1] + x[2] + ... + x[k])的最小值。

输入
第一行两个整数n, k。(1 ≤ n, k ≤ 100000)
接下来n行，每行一个整数c[i]。 (-1000000000 ≤ c[i] ≤ 1000000000)

输出
输出一个整数表示S的最小值。

样例解释
x[1]=-5, y[1]=4,

x[2]=10, y[2]=10.

样例输入
5 2
-5
0
10
4
0
样例输出
9
*/



/*
貌似这道题目已经算是最简单的了，但是我还是没有做出来o(╥﹏╥)o
*/



/*
网上看别人的——
按从小到大排序
定义一个区间大小为最大减最小
那么题目就是要把n个数分为k个区间，使和最小
贪心，一开始只分出1～n一个区间，后面将k-1个相邻差最大的值减去
*/

#include <iostream>
#include <algorithm>

using namespace::std;

int n, k, c[100000], d[100000];
long long ans;

bool cmp(int a, int b) { return a > b; }

int main()
{
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
		cin >> c[i];

	sort(c, c + n);
	ans = c[n - 1] - c[0];
	for (int i = 0; i < n - 1; ++i)
		d[i] = c[i + 1] - c[i];
	sort(d, d + n, cmp);
	for (int i = 0; i < k - 1; ++i)
		ans -= d[i];

	cout << ans;

	return 0;
}
