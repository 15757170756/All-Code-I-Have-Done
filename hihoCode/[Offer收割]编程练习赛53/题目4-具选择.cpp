/*
https://hihocoder.com/contest/offers53/problem/4

题目4 : 工具选择
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
现有N个工具，每个工具有M个属性，每个属性j是一个0到P-1间的整数aij。第i个工具的效用是:

tools1.png

你的任务是从中选取若干工具，使得其效用总和最大。所选出的工具集合S={s1，s2，……，sr}中须满足不能存在冗余工具：即不存在一组有非零元素的整数k1,k2,……,kr∈[0, P-1]，对于任意属性j，均有

tools2.png

输入
第一行三个整数N，M，P分别表示工具数量，属性数量，以及整数P，数据保证P是一个素数。

第二行到第N+1行每行包含M个整数，分别为每个工具的属性值。

M ≤ 100， N≤1000，P≤104

输出
输出共一行，包含一个整数U表述所选工具集合的最大效用和

样例输入
4 2 5
1 1
2 1
4 2
2 0
样例输出
24
*/


#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int a[1111][111], id[1111];
LL sum[1111];

bool cmp(int i, int j){
	return sum[i] > sum[j];
}

typedef pair<int, int> pii;
vector<pii> v;

LL qpow(LL a, LL b, LL mod)
{
	LL ret = 1LL;
	while (b)
	{
		if (b & 1) ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ret;
}

LL inv(LL x, LL mod)
{
	return qpow(x, mod - 2, mod);
}

int main(){
	int N, M, P;
	scanf("%d %d %d", &N, &M, &P);
	for (int i = 1; i <= N; i++){
		id[i] = i;
		for (int j = 1; j <= M; j++) scanf("%d", &a[i][j]), sum[i] += a[i][j] * a[i][j];
	}
	sort(id + 1, id + 1 + N, cmp);
	LL ans = 0;
	for (int i = 1; i <= N; i++){
		int x = id[i];
		for (int j = 0; j < v.size(); j++){
			int y = v[j].first, z = v[j].second;
			if (a[x][z]){
				LL tmp = a[x][z] * inv(a[y][z], P) % P;
				for (int k = 1; k <= M; k++) a[x][k] = (a[x][k] - a[y][k] * tmp % P + P) % P;
			}
		}
		int ok = 0;
		for (int j = 1; j <= M; j++)
			if (a[x][j]) { ok = j; break; }
		if (ok){
			for (int j = 0; j < v.size(); j++){
				int y = v[j].first;
				if (a[y][ok]){
					LL tmp = a[y][ok] * inv(a[x][ok], P) % P;
					for (int k = 1; k <= M; k++) a[y][k] = (a[y][k] - a[x][k] * tmp % P + P) % P;
				}
			}
			v.push_back(pii(x, ok));
			ans += sum[x];
		}
	}
	printf("%lld\n", ans);
	return 0;
}
