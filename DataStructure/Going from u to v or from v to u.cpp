/*
Going from u to v or from v to u?
Time Limit: 2000MS		Memory Limit: 65536K
Total Submissions: 18561		Accepted: 5002
Description

In order to make their sons brave, Jiajia and Wind take them to a big cave. The cave has n rooms, and one-way corridors connecting some rooms. Each time, Wind choose two rooms x and y, and ask one of their little sons go from one to the other. The son can either go from x to y, or from y to x. Wind promised that her tasks are all possible, but she actually doesn't know how to decide if a task is possible. To make her life easier, Jiajia decided to choose a cave in which every pair of rooms is a possible task. Given a cave, can you tell Jiajia whether Wind can randomly choose two rooms without worrying about anything?
Input

The first line contains a single integer T, the number of test cases. And followed T cases.

The first line for each case contains two integers n, m(0 < n < 1001,m < 6000), the number of rooms and corridors in the cave. The next m lines each contains two integers u and v, indicating that there is a corridor connecting room u and room v directly.
Output

The output should contain T lines. Write 'Yes' if the cave has the property stated above, or 'No' otherwise.
Sample Input

1
3 3
1 2
2 3
3 1
Sample Output

Yes
*/


#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;
const int N = 10005;

struct Edge
{
	int to;
	Edge *next;
};

Edge *map1[N], *map2[N];  //分别保存原图和缩点后的图
int dfn[N], low[N], stack[N], belong[N], indeg[N];
int index, scc_num, top;
bool tmp[N];
int result[N];

void Tarjan(int u)
{
	dfn[u] = low[u] = ++index;
	stack[++top] = u;
	tmp[u] = true;
	for (Edge *p = map1[u]; p; p = p->next) //枚举每一条边
	{
		int v = p->to;
		if (!dfn[v])
		{
			Tarjan(v);  //dfs继续下找
			low[u] = min(low[u], low[v]);
		}
		else if (tmp[v])
		{
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (low[u] == dfn[u]) //如果节点u是强连通分量的根
	{
		int t;
		++scc_num;  //强连通分量个数加1
		do
		{
			t = stack[top--];
			tmp[t] = false;
			belong[t] = scc_num;  //记录属于第几个强连通分量
		} while (t != u);
	}
}

int Count(int n)
{
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			Tarjan(i);
	return scc_num;
}

int Find() //在新图中找入度为0的点,如果只有一个就返回位置，否则返回0
{
	int record;
	int cnt = 0;
	for (int i = 1; i <= scc_num; i++)
	{
		if (indeg[i] == 0)
		{
			cnt++;
			record = i;
		}
	}
	if (cnt == 1) return record;
	return 0;
}

bool TopSort()
{
	int u, num = 0;
	while (u = Find())
	{
		result[num++] = u;
		indeg[u] = -1;
		Edge *p = map2[u];
		while (p)
		{
			indeg[p->to]--;
			p = p->next;
		}
	}
	if (num == scc_num) return true;
	return false;
}

void Init()
{
	index = 0;
	top = 0;
	scc_num = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(indeg, 0, sizeof(indeg));
	memset(tmp, false, sizeof(tmp));
	memset(map1, NULL, sizeof(map1));
	memset(map2, NULL, sizeof(map2));
	memset(result, 0, sizeof(result));
}

int main()
{
	int T, m, n;
	scanf("%d", &T);
	while (T--)
	{
		Init();
		scanf("%d%d", &n, &m);
		while (m--)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			Edge *p = new Edge();
			p->to = b;
			p->next = map1[a];
			map1[a] = p;
		}
		int cnt = Count(n);
		if (cnt == 1)
		{
			puts("Yes");
			continue;
		}
		for (int i = 1; i <= n; i++)
		{
			Edge *p = map1[i];
			while (p)
			{
				if (belong[i] != belong[p->to])
				{
					indeg[belong[p->to]]++;
					Edge *q = new Edge();
					q->to = belong[p->to];
					q->next = map2[belong[i]];
					map2[belong[i]] = q;
				}
				p = p->next;
			}
		}
		bool flag = false;
		int ans = 0;
		for (int i = 1; i <= cnt; i++)
		{
			if (indeg[i] == 0)
				ans++;
		}
		if (ans > 1) flag = false;
		else if (TopSort()) flag = true;
		if (flag) puts("Yes");
		else     puts("No");
	}
	return 0;
}