/*
题目3 : 等差子数列
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定N个整数A1, A2, ... AN，小Hi会询问你M个问题。

对于每个问题小Hi给出两个整数L和R(L ≤ R)，请你找出[AL, AL+1, AL+2, ... AR]
中最长的等差连续子数列，并输出其长度。

例如[2, 3, 5, 7, 9]中最长的等差连续子数列是[3, 5, 7, 9]长度为4。

输入
第一行包含两个整数N和M。

第二行包含N个整数A1, A2, ... AN。

以下M行每行包含两个整数L和R，代表一次询问。

对于30%的数据，1 ≤ N, M ≤ 1000

对于100%的数据，1 ≤ N, M ≤ 100000 0 ≤ Ai ≤ 10000000

输出
依次对于每个询问输出一个整数，代表答案。

样例输入
6 2
1 2 3 5 7 9
2 6
1 4
样例输出
4
3
*/


#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;

// UF
int fa[maxn];
void init(int n)
{
	for (int i = 0; i <= n; i++) fa[i] = i;
}
int Find(int x)
{
	return fa[x] == x ? x : fa[x] = Find(fa[x]);
}
void Union(int x, int y)
{
	x = Find(x);
	y = Find(y);
	if (x > y) swap(x, y);
	if (x != y) fa[y] = x;
}

// seg
const int INF = 1e9;
int M[maxn << 2], tag[maxn << 2];
void gather(int p)
{
	M[p] = max(M[p << 1], M[p << 1 | 1]);
}
void push(int p)
{
	if (tag[p])
	{
		tag[p << 1] += tag[p];
		tag[p << 1 | 1] += tag[p];
		M[p << 1] += tag[p];
		M[p << 1 | 1] += tag[p];
		tag[p] = 0;
	}
}
void build(int p, int l, int r)
{
	tag[p] = M[p] = 0;
	if (l < r)
	{
		int mid = (l + r) >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
		gather(p);
	}
}
void modify(int p, int tl, int tr, int l, int r, int v)
{
	if (tl > tr) return;
	if (tr < l || r < tl) return;
	if (l <= tl && tr <= r)
	{
		tag[p] += v;
		M[p] += v;
		return;
	}
	push(p);
	int mid = (tl + tr) >> 1;
	modify(p << 1, tl, mid, l, r, v);
	modify(p << 1 | 1, mid + 1, tr, l, r, v);
	gather(p);
}
int query(int p, int tl, int tr, int l, int r)
{
	if (tl > tr) return -INF;
	if (tr < l || r < tl) return -INF;
	if (l <= tl && tr <= r) return M[p];
	push(p);
	int mid = (tl + tr) >> 1;
	return max(query(p << 1, tl, mid, l, r), query(p << 1 | 1, mid + 1, tr, l, r));
}

int A[maxn], L[maxn], R[maxn], id[maxn], ans[maxn];

bool cmp(int i, int j)
{
	return R[i] < R[j];
}

int main(void)
{
	int N, M;
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) scanf("%d", A + i);
	for (int i = 1; i <= M; i++) scanf("%d %d", L + i, R + i), id[i] = i;
	sort(id + 1, id + 1 + M, cmp);

	init(N);
	int p = 1;
	A[0] = 1e9;
	modify(1, 1, N, 1, 1, 1);
	for (int i = 1; i <= M; i++)
	{
		int x = id[i];
		while (p < R[x])
		{
			p++;
			if (A[p] - A[p - 1] == A[p - 1] - A[p - 2]) Union(p, p - 1);
			modify(1, 1, N, Find(p) - 1, p, 1);
		}
		ans[x] = query(1, 1, N, L[x], R[x]);
	}
	for (int i = 1; i <= M; i++) printf("%d\n", ans[i]);
	return 0;
}