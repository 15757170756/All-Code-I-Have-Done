/*
题目3 : 数组分拆II
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定一个包含N个整数的数组A=[A1, A2, ... AN]。小Ho想将A拆分成若干连续的子数组，使得每个子数组中的整数都是两两不同的。

在满足以上条件的前提下，小Ho想知道子数组数量最少是多少。

同时他还想知道，在数量最少的前提下有多少中不同的拆法。

例如对于[1, 2, 3, 1, 2, 1]，最少需要3个子数组。有5种不同的拆法：

[1], [2, 3, 1], [2, 1]

[1, 2], [3, 1], [2, 1]

[1, 2], [3, 1, 2], [1]

[1, 2, 3], [1], [2, 1]

[1, 2, 3], [1, 2], [1]

输入
第一行包含一个整数N。

第二行包含N个整数A1, A2, ... AN。

对于30%的数据，满足1 ≤ N ≤ 10

对于60%的数据，满足1 ≤ N ≤ 1000

对于100%的数据，满足1 ≤ N ≤ 100000, 1 ≤ Ai ≤ 100000

输出
输出两个整数。第一个表示子数组最少的数量，第二个表示在数量最少的前提下有多少种拆法。

由于拆法可能非常多，你只需要输出答案除以1000000007的余数。

样例输入
6
1 2 3 1 2 1
样例输出
3 5
*/



#include <map>
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

int n, p1[101111], p2[101111], f[101111], a[101111], cur[101111], p[101111];
long long g[101111], Sum[101111];
long long MOD = 1000000007;
bool v[101111];

void work() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	memset(cur, -1, sizeof(cur));
	for (int i = 0; i < n; ++i) {
		p1[i] = cur[a[i]];
		cur[a[i]] = i;
	}
	memset(cur, -1, sizeof(cur));
	for (int i = n - 1; i >= 0; --i) {
		p2[i] = cur[a[i]];
		cur[a[i]] = i;
	}
	int prev = -1;
	for (int i = 0; i < n; ++i) {
		if (v[a[i]]) {
			prev++;
			while (a[prev] != a[i]) {
				v[a[prev]] = false;
				prev++;
			}
		}
		p[i] = prev;
		v[a[i]] = true;
	}

	memset(f, -1, sizeof(f));
	for (int i = 0; i < n; ++i) {
		if (p[i] == -1) {
			f[i] = 1;
		}
		else {
			if (f[i] == -1) f[i] = f[p[i]] + 1;
			else f[i] = min(f[i], f[p[i]] + 1);
		}
	}

	prev = 0;
	for (int i = 0; i < n; ++i) {
		// g[i] = sum(g[j], f[j]+1=f[i] && j>=p[i])
		if (p[i] == -1) {
			g[i] = 1;
			Sum[f[i]] += g[i];
			Sum[f[i]] %= MOD;
		}
		else {
			for (int j = max(0, p[i - 1]); j < p[i]; ++j) {
				Sum[f[j]] -= g[j];
				Sum[f[j]] %= MOD;
			}
			g[i] += Sum[f[i] - 1];
			Sum[f[i]] += g[i];
			Sum[f[i]] %= MOD;
		}
	}
	printf("%d %lld\n", f[n - 1], (g[n - 1] + MOD) % MOD);

}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	int TestCase = 1;
	//scanf("%d", &TestCase);
	while (TestCase--) {
		work();
	}
	return 0;
}
