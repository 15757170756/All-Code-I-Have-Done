/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Hi学校的礼堂有N × M盏灯，排成N行M列的矩阵。

为了给校庆联欢晚会增加气氛，小Hi编写了一段程序控制灯光效果：

0. 晚会开始时，小Hi会手动点亮位于(X, Y)的灯；

1. (X, Y)被点亮后，位于(X+A, Y+B)、(X+2A, Y+2B)、(X+3A, Y+3B) ... 
的灯(如果该位置存在灯)也会被依次点亮；

2. (X, Y)被点亮后，位于(X+C, Y+D)、(X+2C, Y+2D)、(X+3C, Y+3D) ... 
的灯(如果该位置存在灯)也会被依次点亮；

给定ABCD，初始时所有灯都是熄灭的。假设晚会开始时小Hi点亮了位于(X, Y)的灯，
请你计算最终一共有多少盏灯是亮着的。

输入
第一行包含4个整数，N, M, X, Y。

第二行包含4个整数，A, B, C, D。

对于50%的数据，1 ≤ N, M ≤ 1000

对于100%的数据， 1 ≤ N, M ≤ 1000000000, 1 ≤ X ≤ N, 1 ≤ Y ≤ M, -1000000 ≤ A, B, C, D ≤ 1000000

输出
最终亮着的灯的数目。

样例输入
4 4 2 2
1 1 0 1
样例输出
5
*/



#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL gcd(LL a, LL b)
{
	if (a == 0 || b == 0) return 0;
	return a % b ? gcd(b, a % b) : b;
}
const LL INF = 1e18;

int main(void)
{
	LL N, M, X, Y, A, B, C, D, ans;
	scanf("%lld %lld %lld %lld %lld %lld %lld %lld", &N, &M, &X, &Y, &A, &B, &C, &D);
	LL ma = A > 0 ? (N - X) / A : (A < 0 ? (X - 1) / (-A) : INF);
	LL mc = C > 0 ? (N - X) / C : (C < 0 ? (X - 1) / (-C) : INF);
	LL mb = B > 0 ? (M - Y) / B : (B < 0 ? (Y - 1) / (-B) : INF);
	LL md = D > 0 ? (M - Y) / D : (D < 0 ? (Y - 1) / (-D) : INF);
	ans = 1 + (min(ma, mb) == INF ? 0 : min(ma, mb)) + (min(mc, md) == INF ? 0 : min(mc, md));
	if ((A == 0 && C == 0 || A * C > 0) && (B == 0 && D == 0 || B * D > 0) && A * D == C * B)
	{
		LL gx = gcd(abs(A), abs(C)) == 0 ? 0 : abs(A) * abs(C) / gcd(abs(A), abs(C));
		if (A < 0) gx = -gx;
		LL gy = gcd(abs(B), abs(D)) == 0 ? 0 : abs(B) * abs(D) / gcd(abs(B), abs(D));
		if (B < 0) gy = -gy;
		LL mx = gx > 0 ? (N - X) / gx : (gx < 0 ? (X - 1) / (-gx) : INF);
		LL my = gy > 0 ? (M - Y) / gy : (gy < 0 ? (Y - 1) / (-gy) : INF);
		ans -= (min(mx, my) == INF ? 0 : min(mx, my));
	}
	printf("%lld\n", ans);
	return 0;
}