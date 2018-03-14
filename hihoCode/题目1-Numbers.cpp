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



#include<bits/stdc++.h>
#define N 1000009
using namespace std;

int n, m, a[N], b[N];
int main(){
	scanf("%d%d", &n, &m);
	int i;
	for (i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	int ans = a[n] - a[1];
	for (i = 1; i < n; i++) b[i] = a[i + 1] - a[i];
	sort(b + 1, b + n);
	for (i = 1; i <= m - 1 && i < n; i++) ans -= b[n - i];
	printf("%d\n", ans);
	return 0;
}
