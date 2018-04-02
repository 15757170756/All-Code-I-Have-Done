/*
题目4 : 评论框排版
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Hi正在给hihoCoder的查看代码添加评论功能。用户可以对某一行代码进行评论，评论发表之后会在代码右侧插入一个评论框。

#include <iostream>
using namespace std;
int n;
long long a[100010], s[100010];					+-------------------+
long long mn, mini;						|What?    	    |
int main()							+-------------------+
{
cin >> n;
for(int i = 0; i < n; i++) cin >> a[i];
s[0] =  a[0];
mn = 0;
mini = 0;
for(int i = 1; i < n; i++) {				+-------------------+
s[i] = s[i-1] + a[i];				|What happened in   |
if(s[i] <= mn) {			        |this loop?         |
mn = s[i];                              |I'm confused...    |
mini = i;                               +-------------------+
}
}
if(s[n-1] <= 0) cout << 0 << endl;                      +-------------------+
else cout << (mini + 1) % n + 1 << endl;                |I think 0 should be|
return 0;                                               |1...               |
}                                                               +-------------------+


评论框有一定的高度。在没有其他评论框干扰的情况下，在第K行插入一个高H的评论框，会占据[K, K+H-1]行。

如果第K行已经被某个之前的评论框占据，系统会自动向下找到第一个空行，插入评论框。

如果插入的评论框与下方的评论框有交集，下方的评论框会被向后推到插入的评论框之后。

例如假设已经有3个评论框分别占据了[1, 5], [7, 8], [10, 15]行，现在要在第3行插入一个高5行的评论框。则这个评论框最终会位于[6, 10]，并且把原来在[7, 8]和[10, 15]的评论框分别推到[11, 12], [13, 18]。

已知初始时一条评论都没有，给定一系列操作包括添加评论框和对评论框位置的询问，请你对每个询问输出答案。

操作包括：

I K H: 表示要在第K行插入一个高H行的评论框

Q X:   表示询问第X个插入的评论框现在在什么位置 (保证之前至少已经插入过X个评论框)

输入
第一行包含一个整数N，表示操作的数量。

以下N行每行一个操作。

对于30%的操作，1 ≤ N ≤ 1000

对于100%的操作，1 ≤ N ≤ 100000 1 ≤ K, H ≤ 1000000

输出
依次对于每个查询操作，输出一行两个整数A和B，表示占据[A, B]行。

样例输入
5
I 1 5
I 8 10
I 5 5
Q 3
Q 2
样例输出
6 10
11 20
*/


#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
typedef long long LL;
typedef  pair<LL, LL> pii;
set<pii> S;
set<pii> ::iterator it, itt;

// UF
int fa[maxn];
LL pos[maxn], dis[maxn], sz[maxn], ss[maxn];
void init(int n)
{
	for (int i = 1; i <= n; i++) dis[i] = 0, fa[i] = i;
}
int Find(int x)
{
	if (fa[x] == x) return x;
	int y = Find(fa[x]);
	dis[x] += dis[fa[x]];
	return fa[x] = y;
}
void Union(int x, int y)
{
	x = Find(x), y = Find(y);
	if (x == y) return;
	if (pos[x] > pos[y] || pos[x] == pos[y] && x > y) swap(x, y);
	dis[y] = sz[x];
	sz[x] += sz[y];
	fa[y] = x;
}

int main(void)
{
	int N, x = 0;
	scanf("%d", &N);
	init(N);
	for (int i = 1; i <= N; i++)
	{
		char s[11];
		scanf("%s", s);
		if (s[0] == 'I')
		{
			x++;
			scanf("%d %d", pos + x, sz + x), ss[x] = sz[x];
			pii tmp = pii(pos[x], x);
			it = S.upper_bound(tmp);
			if (it != S.begin())
			{
				it--;
				int y = (*it).second;
				if (pos[y] + sz[y] >= pos[x]) Union(x, y);
				else S.insert(tmp), it = S.find(tmp);
			}
			else S.insert(tmp), it = S.find(tmp);
			while (1)
			{
				itt = it;
				itt++;
				if (itt == S.end()) break;
				int X = (*it).second, Y = (*itt).second;
				if (pos[X] + sz[X] >= pos[Y]) S.erase(itt), Union(X, Y);
				else break;
			}
		}
		else
		{
			int X;
			scanf("%d", &X);
			int Y = Find(X);
			printf("%lld %lld\n", pos[Y] + dis[X], pos[Y] + dis[X] + ss[X] - 1);
		}
	}
	return 0;
}
