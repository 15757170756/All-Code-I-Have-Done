/*
Description

A rooted tree is a well-known data structure in computer science and engineering. An example is shown below:

In the figure, each node is labeled with an integer from {1, 2,...,16}. Node 8 is the root of the tree. Node x is an ancestor of node y if node x is in the path between the root and node y. For example, node 4 is an ancestor of node 16. Node 10 is also an ancestor of node 16. As a matter of fact, nodes 8, 4, 10, and 16 are the ancestors of node 16. Remember that a node is an ancestor of itself. Nodes 8, 4, 6, and 7 are the ancestors of node 7. A node x is called a common ancestor of two different nodes y and z if node x is an ancestor of node y and an ancestor of node z. Thus, nodes 8 and 4 are the common ancestors of nodes 16 and 7. A node x is called the nearest common ancestor of nodes y and z if x is a common ancestor of y and z and nearest to y and z among their common ancestors. Hence, the nearest common ancestor of nodes 16 and 7 is node 4. Node 4 is nearer to nodes 16 and 7 than node 8 is.

For other examples, the nearest common ancestor of nodes 2 and 3 is node 10, the nearest common ancestor of nodes 6 and 13 is node 8, and the nearest common ancestor of nodes 4 and 12 is node 4. In the last example, if y is an ancestor of z, then the nearest common ancestor of y and z is y.

Write a program that finds the nearest common ancestor of two distinct nodes in a tree.

Input
The input consists of T test cases. 
The number of test cases (T) is given in the first line of the input file.
Each test case starts with a line containing an integer N , 
the number of nodes in a tree, 2<=N<=10,000. 
The nodes are labeled with integers 1, 2,..., N. 
Each of the next N -1 lines contains a pair of integers that represent an edge 
--the first integer is the parent node of the second integer. 
Note that a tree with N nodes has exactly N - 1 edges. 
The last line of each test case contains two distinct integers whose nearest common 
ancestor is to be computed.
Output

Print exactly one line for each test case. The line should contain the integer that is the nearest common ancestor.
Sample Input

2
16
1 14
8 5
10 16
5 9
4 6
8 4
4 10
1 13
6 15
10 11
6 7
10 2
16 3
8 1
16 12
16 7
5
2 3
3 4
3 1
1 5
3 5
Sample Output

4
3
*/



#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>

using namespace std;
const int N = 10005;

int n;
vector<int> vec[N];
int pre[N];
bool vis[N];
bool root[N];
int u, v;

void Init()
{
	for (int i = 0; i < N; i++)
	{
		vec[i].clear();
		pre[i] = i;
		root[i] = true;
		vis[i] = false;
	}
}

void Import()
{
	scanf("%d", &n);
	Init();
	for (int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		vec[a].push_back(b);
		root[b] = false;
	}
	scanf("%d%d", &u, &v);
}

int Find(int x)
{
	if (pre[x] != x)
		pre[x] = Find(pre[x]);
	return pre[x];
}

void Union(int x, int y)
{
	x = Find(x);
	y = Find(y);
	if (x == y) return;
	pre[y] = x;
}

void LCA(int par)
{
	for (int i = 0; i < vec[par].size(); i++)
	{
		LCA(vec[par][i]);
		Union(par, vec[par][i]);
	}
	vis[par] = true;
	if (par == u && vis[v] == true)
	{
		printf("%d\n", Find(v));
		return;
	}
	if (par == v && vis[u] == true)
	{
		printf("%d\n", Find(u));
		return;
	}
}

void Work()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		Import();
		for (int i = 1; i <= n; i++)
		{
			if (root[i] == true)
			{
				LCA(i);
				break;
			}
		}
	}
}

int main()
{
	Work();
	return 0;
}
