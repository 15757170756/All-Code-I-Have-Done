/*
https://www.cnblogs.com/chty/p/5953493.html

【描述】
在3×3的棋盘上，摆有八个棋子，每个棋子上标有1至8的某一数字。棋盘中留有一个空格，空格用0来表示。

空格周围的棋子可以移到空格中。

要求解的问题是：给出一种初始布局（初始状态）和目标布局（为了使题目简单,设目标状态为123804765），
找到一种最少步骤的移动方法，实现从初始布局到目标布局的转变。
*/


/*
【题解】

搜索经典题目，网上各种搞法，于是我就写个A*水一下。。。

主要说一下启发函数的写法：

首先定义一个dis[10][10]数组，记录偏移距离，我们把地图中的点按行标号，则dis[i][j]表示从第i个点到第j个点至少移动的步数。

举个栗子：

点的编号：1 2 3

　　　   　4 5 6

	   　　　   　7 8 9

			  那么显然dis[1][2]=1,dis[2][9]=3,dis[3][4]=3

			  这个dis数组可通过预处理完成，应该是这个样子：

			  0 1 2 1 2 3 2 3 4
			  1 0 1 2 1 2 3 2 3
			  2 1 0 3 2 1 4 3 2
			  1 2 3 0 1 2 1 2 3
			  2 1 2 1 0 1 2 1 2
			  3 2 1 2 1 0 3 2 1
			  2 3 4 1 2 3 0 1 2
			  3 2 3 2 1 2 1 0 1
			  4 3 2 3 2 1 2 1 0

			  接着定义一个p[10]数组，p[i]表示数字i在目标状态中的位置，也可以通过预处理完成，

			  const int p[10]={5,1,2,3,6,9,8,7,4};

			  然后定义一个r[10]数组，r[i]表示数字i在当前状态中的位置，这个需要动态维护。

			  那么估价函数的值当然就是数字0-8 的偏移量之和了。
*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<algorithm>
using namespace std;
const int dx[5] = { 1, 0, -1, 0 };
const int dy[5] = { 0, 1, 0, -1 };
const int p[10] = { 5, 1, 2, 3, 6, 9, 8, 7, 4 };
int s, flag, r[10], a[5][5], map[5][5], dis[10][10];
bool check()  { for (int i = 1; i <= 9; i++)if (r[i] != p[i])return 0; return 1; }
int get()  { int t = 0; for (int i = 1; i <= 9; i++)t += dis[r[i]][p[i]]; return t; }
int jue(int a, int b){ int t = a - b;  return t < 0 ? -t : t; }
int calx(int i){ return (i - 1) / 3 + 1; }
int caly(int i){ return i % 3 == 0 ? 3 : i % 3; }
void dfs(int depth, int x, int y)
{
	if (depth + get() > s)  return;
	if (check())  { flag = 1;  return; }
	for (int i = 0; i < 4; i++)
	{
		int xx = x + dx[i], yy = y + dy[i];
		if (xx < 1 || yy < 1 || xx>3 || yy>3)  continue;
		swap(a[x][y], a[xx][yy]);  swap(r[a[x][y]], r[a[xx][yy]]);
		dfs(depth + 1, xx, yy);
		swap(a[x][y], a[xx][yy]);  swap(r[a[x][y]], r[a[xx][yy]]);
	}
}
void pre()
{
	for (int i = 1; i <= 9; i++)
		for (int j = i + 1; j <= 9; j++)
			dis[i][j] = dis[j][i] = calx(j) - calx(i) + jue(caly(i), caly(j));
}
int main()
{
	//freopen("cin.in","r",stdin);
	//freopen("cout.out","w",stdout);
	pre();
	int sx, sy;
	for (int i = 1; i <= 9; i++)
	{
		char ch = getchar();  int x = calx(i), y = caly(i);
		map[x][y] = ch - '0';  r[ch - '0'] = i;
		if (ch == '0')  sx = x, sy = y;
	}
	for (s = 0;; s++)
	{
		memcpy(a, map, sizeof(map));  dfs(0, sx, sy);
		if (flag)  { printf("%d\n", s);  break; }
	}
	return 0;
}