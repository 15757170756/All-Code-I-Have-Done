﻿/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Hi被坏女巫抓进一座由无限多个格子组成的矩阵迷宫。

小Hi一开始处于迷宫(x, y)的位置，迷宫的出口在(a, b)。
小Hi发现迷宫被女巫施加了魔法，假设当前他处在(x, y)的位置，
那么他只能移动到(x+y, y)或者(x, x+y)的位置上。

小Hi想知道自己能不能逃离迷宫。

输入
第一行包含一个整数T，代表测试数据的组数。

以下N行每行包含4个整数x, y, a, b，表示起点在(x, y)，出口在(a, b)。

对于30%的数据，1 ≤ T ≤ 10, 1 ≤ x, y, a, b ≤ 100

对于80%的数据，1 ≤ T ≤ 1000, 1 ≤ x, y, a, b ≤ 1000

对于100%的数据，1 ≤ T ≤ 10000, 1 ≤ x, y, a, b ≤ 109

输出
对于每组数据输出一行YES或者NO，表示小Hi是否能逃离迷宫。

样例输入
2
1 1 8 13
2 2 100 101
样例输出
YES
NO
*/


#include<iostream>
#include<string>
#include<stdio.h>
#include<algorithm>
using namespace std;
int flag;
void dfs(int a, int b, int x, int y)
{
	if (a == x&&b == y)
		flag = 1;
	if (a > x || b > y)
		return;
	dfs(a + b, b, x, y);
	dfs(a, a + b, x, y);
}
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int a, b, x, y;
		scanf("%d%d%d%d", &x, &y, &a, &b);
		while (x <= a && y <= b && a != b)
		{
			if (x == a && y == b) 
				break;
			if (a < b)
			{
				if (b % a != 0) b %= a;
				else b = a;
			}
			else
			{
				if (a % b != 0) a %= b;
				else a = b;
			}
		}
		if (x == a && y == b) puts("YES");
		else puts("NO");
	}
}







//自己写的
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
#include <climits>

using namespace std;

int t, x, y, a, b;

bool dfs(int x, int y)
{
	if (x == a && y == b)
		return true;
	if (x > a || y > b)
		return false;
	return (dfs(x + y, y) || dfs(x, x + y));
}

void work()
{
	if (dfs(x, y))
		printf("YES\n");
	else
		printf("NO\n");
}

int main(int argc, char* argv[])
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d%d", &x, &y, &a, &b);
		work();
	}

	return 0;
}

/*
结果:Memory Limit Exceeded
*/





















#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

long long x, y, a, b;

int T;

bool judge(long long a, long long b) {
	if (a == x && b == y) return true;
	while (a != x && b != y) {
		if (a == 0 || b == 0) return false;
		if (a > b) a = a % b;
		else b = b % a;
	}
	if (a == x) {
		if (b >= y && (b - y) % a == 0) return true;
		return false;
	}
	if (b == y) {
		if (a >= x && (a - x) % b == 0) return true;
		return false;
	}
	return true;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%lld %lld %lld %lld", &x, &y, &a, &b);
		if (judge(a, b)) printf("YES\n");
		else printf("NO\n");
	}

	return 0;
}