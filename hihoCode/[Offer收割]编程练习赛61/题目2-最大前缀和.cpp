/*
题目2 : 最大前缀和
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定一个长度为n的序列a[1..n]，现在你可以进行最多k次操作，
每次操作能交换序列中任意两个数，要求最大化最大前缀和的值。

最大前缀和的定义：

maxpre.png

输入
第一行两个非负整数n,k，1 ≤ n ≤ 50000，1 ≤ k ≤ 3。

第二行n个整数，第i个整数表示ai   (|ai| ≤ 109)

输出
输出一个非负整数，表示最大的最大前缀和的值。

样例输入
5 1
-1 -3 2 3 2
样例输出
6
*/


#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <ctime>
#include <string>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


int MAXINT = 1000000002;
long long ans, sum;
int n, k, a[51111], l[51111][4], r[51111][4];

void work() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}

	l[0][0] = l[0][1] = l[0][2] = MAXINT;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 3; ++j) {
			l[i][j] = l[i - 1][j];
		}
		l[i][3] = a[i];
		for (int j = 2; j >= 0; --j) {
			if (l[i][j] > l[i][j + 1]) {
				swap(l[i][j], l[i][j + 1]);
			}
		}
	}
	r[n + 1][0] = r[n + 1][1] = r[n + 1][2] = -MAXINT;
	for (int i = n; i >= 1; --i) {
		for (int j = 0; j < 3; ++j) {
			r[i][j] = r[i + 1][j];
		}
		r[i][3] = a[i];
		for (int j = 2; j >= 0; --j) {
			if (r[i][j] < r[i][j + 1]) {
				swap(r[i][j], r[i][j + 1]);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		sum += a[i];
		long long x = sum;
		for (int j = 0; j < k; ++j) {
			if (l[i][j] != MAXINT && r[i + 1][j] != -MAXINT) {
				x += r[i + 1][j] - l[i][j];
			}
		}
		ans = max(ans, x);
	}
	printf("%lld\n", ans);

}

int main() {
#ifndef ONLINE_JUDGE
	// freopen("input.txt", "r", stdin);
	int t = clock();
#endif
	int TestCase = 1, Case = 0;
	//scanf("%d", &TestCase);
	while (TestCase--) {
		Case++;
		//printf("Case #%d: ", Case);
		work();
	}
#ifndef ONLINE_JUDGE
	cerr << "time = " << clock() - t << " ms" << endl;
#endif
	return 0;
}
