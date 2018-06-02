/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
HIHO银行等待区有一排N个座位，从左到右依次编号1~N。现在有M位顾客坐在座位上，其中第i位坐在编号Ai的座位上。

之后又陆续来了K位顾客，(K + M ≤ N) 他们都会选择坐在最"舒适"的空座位上，并且过程中没有顾客离开自己的座位。

最"舒适"的定义是：

1. 对于一个座位，我们将它左边的空座位数目记作X，它右边的空座位数目记作Y。

2. 顾客首先会选择min(X, Y)最大的座位。

3. 如果有多个选择，顾客会选择其中max(X, Y)最大的座位。

4. 如果还是有多个选择，顾客会选择其中编号最小的座位。

请你计算出之后来的K位顾客坐在几号座位上。

输入
第一行包含三个整数N，M和K。

第二行包含M个整数A1, A2, ... AM。

对于50%的数据，1 ≤ N ≤ 1000

对于100%的数据，1 ≤ N ≤ 100000,  1 ≤ Ai ≤ N,  K + M ≤ N

输出
输出K行，每行一个整数代表该位顾客座位的编号。

样例输入
10 2 3
1 10
样例输出
5
7
3
*/

#include<queue>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 100010;
struct in
{
	int id; int l; int r;
	in(){}
	in(int x, int y, int z) :id(x), l(y), r(z){}
	friend bool operator < (in a, in b){
		if (a.r - a.l == b.r - b.l) return a.id>b.id;
		return a.r - a.l < b.r - b.l;
	}
};
int a[maxn], used[maxn], L[maxn], R[maxn];
priority_queue<in>q;
int main()
{
	int N, M, K, i, j;
	scanf("%d%d%d", &N, &M, &K);
	used[0] = 1; used[N + 1] = 1;
	for (i = 1; i <= M; i++) scanf("%d", &a[i]);
	sort(a + 1, a + M + 1);
	a[0] = 0; a[M + 1] = N + 1;
	for (i = 1; i <= M + 1; i++) {
		L[i] = a[i - 1] + 1; R[i] = a[i] - 1;
		q.push(in((L[i] + R[i]) / 2, L[i], R[i]));
	}
	for (i = 1; i <= K; i++){
		in tmp = q.top(); q.pop();
		printf("%d\n", tmp.id);
		q.push(in((tmp.id - 1 + tmp.l) / 2, tmp.l, tmp.id - 1));
		q.push(in((tmp.r + tmp.id + 1) / 2, tmp.id + 1, tmp.r));
	}
	return 0;
}


/*
结果:Accepted
*/














#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10, mod = 1e9 + 7, inf = 0x3f3f3f3f;
int n, m, k, t, a[maxn], l[maxn], r[maxn];
struct node
{
	int x, y, id;
	bool operator<(const node&p)const
	{
		if (min(x, y) != min(p.x, p.y))return min(x, y)>min(p.x, p.y);
		if (max(x, y) != max(p.x, p.y))return max(x, y) > max(p.x, p.y);
		return id < p.id;
	}
};
set<node>pq;
int main()
{
	int i, j;
	scanf("%d%d%d", &n, &m, &k);
	for (i = 1; i <= m; i++)scanf("%d", &j), a[j] = 1;
	for (i = 1; i <= n; i++)l[i] = (a[i] == 0 ? l[i - 1] + 1 : 0);
	for (i = n; i >= 1; i--)r[i] = (a[i] == 0 ? r[i + 1] + 1 : 0);
	for (i = 1; i <= n; i++)l[i]--, r[i]--;
	for (i = 1; i <= n; i++)if (!a[i])pq.insert(node{ l[i], r[i], i });
	for (i = 1; i <= k; i++)
	{
		auto now = pq.begin();
		printf("%d\n", now->id);
		for (j = now->id - 1; j >= now->id - now->x; j--)
		{
			pq.erase(node{ l[j], r[j], j });
			r[j] -= now->y + 1;
			pq.insert(node{ l[j], r[j], j });
		}
		for (j = now->id + 1; j <= now->id + now->y; j++)
		{
			pq.erase(node{ l[j], r[j], j });
			l[j] -= now->x + 1;
			pq.insert(node{ l[j], r[j], j });
		}
		pq.erase(now);
		//for(j=1;j<=n;j++)printf("***%d %d\n",l[j],r[j]);
	}
	return 0;
}

