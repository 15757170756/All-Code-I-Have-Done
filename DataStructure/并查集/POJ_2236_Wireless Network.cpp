/*
Description

An earthquake takes place in Southeast Asia. 
The ACM (Asia Cooperated Medical team) have set up a wireless network with the lap computers,
but an unexpected aftershock attacked, all computers in the network were all broken.
The computers are repaired one by one, and the network gradually began to work again. 
Because of the hardware restricts, 
each computer can only directly communicate with the computers that are not farther than d meters from it. 
But every computer can be regarded as the intermediary of the communication between two other computers, 
that is to say computer A and computer B can communicate 
if computer A and computer B can communicate directly or
 there is a computer C that can communicate with both A and B.

In the process of repairing the network, workers can take two kinds of operations at every moment, 
repairing a computer, or testing if two computers can communicate. 
Your job is to answer all the testing operations.
Input

The first line contains two integers N and d (1 <= N <= 1001, 0 <= d <= 20000). 
Here N is the number of computers, which are numbered from 1 to N, 
and D is the maximum distance two computers can communicate directly. 
In the next N lines, each contains two integers xi, yi (0 <= xi, yi <= 10000), 
which is the coordinate of N computers. From the (N+1)-th line to the end of input, 
there are operations, which are carried out one by one. 
Each line contains an operation in one of following two formats:
1.	"O p" (1 <= p <= N), which means repairing computer p.
2.	"S p q" (1 <= p, q <= N),
 which means testing whether computer p and q can communicate.

The input will not exceed 300000 lines.
Output

For each Testing operation, 
print "SUCCESS" if the two computers can communicate, or "FAIL" if not.
Sample Input

4 1
0 1
0 2
0 3
0 4
O 1
O 2
O 4
S 1 4
O 3
S 1 4
Sample Output

FAIL
SUCCESS
*/


#include <iostream>
#include <string.h>
#include <stdio.h>

const int N = 1005;

struct Point
{
	int x, y;
};

Point p[N];
int repaired[N];
int pre[N], rank[N];

int dist(Point A, Point B)
{
	return (A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y);
}

void Init(int n)
{
	for (int i = 1; i <= n; i++)
	{
		pre[i] = i;
		rank[i] = 1;
	}
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
	if (rank[x] >= rank[y])
	{
		pre[y] = x;
		rank[x] += rank[y];
	}
	else
	{
		pre[x] = y;
		rank[y] += rank[x];
	}
}

int main()
{
	char ch[5];
	int n, d, x, y;
	scanf("%d%d", &n, &d);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &p[i].x, &p[i].y);
	int cnt = 0;
	Init(n);
	while (~scanf("%s", ch))
	{
		if (ch[0] == 'O')
		{
			scanf("%d", &x);
			for (int i = 0; i < cnt; i++)
			{
				if (dist(p[repaired[i]], p[x]) <= d*d)
					Union(repaired[i], x);
			}
			repaired[cnt++] = x;
		}
		else
		{
			scanf("%d%d", &x, &y);
			x = Find(x);
			y = Find(y);
			if (x == y) puts("SUCCESS");
			else       puts("FAIL");
		}
	}
	return 0;
}
