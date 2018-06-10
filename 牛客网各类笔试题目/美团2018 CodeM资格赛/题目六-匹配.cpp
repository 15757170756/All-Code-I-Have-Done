/*
[编程|1000分] 匹配
时间限制：C/C++ 3秒，其他语言 6秒
空间限制：C/C++ 262144K，其他语言 524288K
题目描述
美团外卖日订单已经超过2000万，背后有一个非常复杂的智能调度系统。
我们考虑一个简化的情形，有n个外卖小哥要去 n 家商店取货，
第 i 个外卖小哥到达商店 j 需要时间 e[i][j] 。
现在有 m 对外卖小哥和商店的合作关系。假定每个外卖小哥只能取到一个货物，
每个商店只需要一位外卖小哥取货。
询问最少多少时间，能有 k 位外卖小哥到达 k 个商店取到货物？对于每个 k ，
都输出一个数表示最少使用时间，如果无解输出 -1。
输入描述:
第一行输入两个整数 n , m （1 <= n <= 1000 , 1 <= m <= 100000）。
接下来 m 行，每行输入 3 个整数 i , j , 
e[i][j] (1 <= i, j <= n , 0 <= e[i][j] <= 10^9)，定义如题所述。
注：本题测试用例较多，请耐心等待判题结果，也可以去排行榜刷新查看自己的提交结果。
输出描述:
输出一行n个整数，第 i 个整数，表示当 k=i 时，
需要的最少时间，如果无解输出-1，结尾无空格。
示例1
输入
3 7
1 3 5
2 3 2
3 1 7
1 2 0
2 3 2
3 2 0
2 1 5
输出
0 2 5
*/











/*

*/
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <bitset>
#include <cmath>
#include <ctime>
#include <queue>
#include <set>
#include <map>
#define fi first
#define se second
#define PA pair<int,int>
#define VI vector<int>
#define VP vector<PA >
#define mk(x,y) make_pair(x,y)
#define int64 long long
#define db double
#define N 1010
#define M 100010
#define For(i,x,y) for (i=x;i<=y;i++)
using namespace std;
struct ww {
	int a, b, c;
} a[M];
int i, j, k, n, m, t, ans, T;
int b[N], c[N], d[N], pre[N];
bool Rea[N];
VI e[N];

inline bool cc1(const ww &a, const ww &b) {
	return a.c < b.c;
}

void dfs1(int x) {
	if (!x || Rea[x]) return;
	Rea[x] = 1;
	int i;
	for (i = 0; i < e[x].size(); i++) {
		int A = e[x][i];
		if (!pre[A]) pre[A] = x;
		dfs1(d[A]);
	}
}
inline void Pre() {
	memset(Rea, 0, sizeof(Rea));
	memset(pre, 0, sizeof(pre));
	int i;
	For(i, 1, n) if (!c[i]) dfs1(i);
}
int dfs(int x, int y) {
	if (Rea[x]) return 0;
	Rea[x] = 1;
	int i;
	for (i = y; i < e[x].size(); i++) {
		int A = e[x][i];
		if (!pre[A]) pre[A] = x;
		if (!d[A] || dfs(d[A], 0)) {
			c[x] = A;
			d[A] = x;
			return 1;
		}
	}
	return 0;
}
void Dfs(int x) {
	if (!x) return;
	int A = pre[x];
	int B = c[A];
	c[A] = x;
	d[x] = A;
	Dfs(B);
}
inline void Add(ww b) {
	int x = b.a, y = b.b;
	e[x].push_back(y);
	if (Rea[x]) {
		Rea[x] = 0;
		int z = c[x];
		if (dfs(x, e[x].size() - 1)) {
			ans++;
			Dfs(z);
			Pre();
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	t = 0;
	For(i, 1, m) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		a[++t] = (ww){x, y, z};
	}
	sort(a+1, a+t+1, cc1);
	memset(b, 255, sizeof(b));
	memset(c, 0, sizeof(c));
	memset(d, 0, sizeof(d));
	For(i, 1, n) e[i].clear();
	Pre();
	ans = 0;
	For(i, 1, t) {
		Add(a[i]);
		if (b[ans] < 0) b[ans] = a[i].c;
		if (ans == n) break;
	}
	For(i, 1, n) printf("%d%c", b[i], i == n ? '\n' : ' ');
	return 0;
}