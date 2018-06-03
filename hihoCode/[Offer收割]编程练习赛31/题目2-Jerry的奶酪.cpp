/*
题目2 : Jerry的奶酪
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
Jerry是一只聪明的老鼠，正身处一个N × M的2D迷宫中。
迷宫的每个格子或者是'0'表示Jerry可以走上去，
或者是'1'表示格子上有障碍物，不能走上去。

迷宫中有K个格子上放着一块奶酪。Jerry一开始在左上角(0, 0)的位置，
它希望收集所有的奶酪，之后再到达右下角(N-1, M-1)的出口。

已知每一秒Jerry可以移动到上下左右四个相邻的没有障碍的格子。
你能求出Jerry最快多少秒之后能收集完奶酪并走出迷宫吗？

输入
第一行包含三个整数N, M和K。

之后N行包含一个N × M的01矩阵，表示迷宫。

再之后K行，每行两个整数(x, y)表示奶酪的位置。

对于30%的数据，1 ≤ N, M ≤ 10, 0 ≤ K ≤ 3

对于60%的数据，1 ≤ N, M ≤ 100, 0 ≤ K ≤ 5

对于100%的数据，1 ≤ N, M ≤ 300, 0 ≤ K ≤ 10

输出
走出迷宫最少花费的时间。如果Jerry无法收集到所有的奶酪，或者无法到达出口，输出-1。

样例输入
5 5 3
01000
01010
00010
01010
00000
0 4
2 2
4 0
样例输出
16
*/

#include <map>
#include <cmath>
#include <queue>
#include <ctime>
#include <string>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, K, dist[311][311], f[5000][15], X[20], Y[20], d[20][20], S;
char a[311][311];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
queue<pair<int, int> > q;

void bfs(int sx, int sy) {

	memset(dist, -1, sizeof(dist));
	dist[sx][sy] = 0;
	while (!q.empty()) q.pop();
	q.push(make_pair(sx, sy));
	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();
		int x = now.first, y = now.second;
		for (int i = 0; i < 4; ++i) {
			int xx = x + dx[i], yy = y + dy[i];
			if (xx < 0 || yy < 0 || xx >= n || yy >= m || a[xx][yy] == '1') continue;
			if (dist[xx][yy] == -1) {
				dist[xx][yy] = dist[x][y] + 1;
				q.push(make_pair(xx, yy));
			}
		}
	}
}

void work() {
	scanf("%d%d%d", &n, &m, &K);
	for (int i = 0; i < n; ++i) {
		scanf("%s", a[i]);
	}
	for (int i = 0; i < K; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		X[i] = x, Y[i] = y;
	}
	X[K] = 0, Y[K++] = 0;
	X[K] = n - 1, Y[K++] = m - 1;
	for (int i = 0; i < K; ++i) {
		bfs(X[i], Y[i]);
		for (int j = 0; j < K; ++j) {
			d[i][j] = dist[X[j]][Y[j]];
		}
	}

	S = (1 << K);
	memset(f, -1, sizeof(f));
	f[0][K - 2] = 0;
	for (int i = 0; i < S; ++i) {
		for (int j = 0; j < K; ++j) {
			if (f[i][j] == -1) continue;
			for (int k = 0; k < K; ++k) {
				int s = i | (1 << k);
				if (d[j][k] != -1 && (f[s][k] == -1 || f[s][k] > f[i][j] + d[j][k])) {
					f[s][k] = f[i][j] + d[j][k];
				}

			}
		}
	}
	printf("%d\n", f[S - 1][K - 1]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	int TestCase = 1;
	//scanf("%d", &TestCase);
	while (TestCase--) {
		work();
	}
	return 0;
}
