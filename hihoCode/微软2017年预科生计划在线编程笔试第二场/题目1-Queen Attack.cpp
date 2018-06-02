/*
题目1 : Queen Attack
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
There are N queens in an infinite chessboard. 
We say two queens may attack each other 
if they are in the same vertical line, 
horizontal line or diagonal line even if there are other queens sitting between them.

Now given the positions of the queens, 
find out how many pairs may attack each other?

输入
The first line contains an integer N.

Then N lines follow. 
Each line contains 2 integers Ri and Ci indicating 
there is a queen in the Ri-th row and Ci-th column.

No two queens share the same position.

For 80% of the data, 1 <= N <= 1000

For 100% of the data, 1 <= N <= 100000, 0 <= Ri, Ci <= 1000000000

输出
One integer, the number of pairs may attack each other.

样例输入
5
1 1
2 2
3 3
1 3
3 1
样例输出
10
*/



#include<stdio.h>
#include<iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cstring>
#include <map>
#include <list>
using namespace std;

struct Point
{
	int x;
	int y;
	Point(int x = 0, int y = 0)
		:x(x), y(y){}
};

int main()
{
	//freopen("input.txt", "r", stdin);
	int n;
	cin >> n;
	vector<Point> points(n);
	for (int i = 0; i < n; ++i)
		cin >> points[i].x >> points[i].y;
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			Point p1 = points[i];
			Point p2 = points[j];
			int diffX = p1.x - p2.x;
			int diffY = p1.y - p2.y;
			if (abs(diffX) == abs(diffY)
				|| diffX == 0
				|| diffY == 0)
				++cnt;
		}
	}

	cout << cnt << endl;
	return 0;
}

/*
结果:Time Limit Exceeded
暴力法会超时
*/







#include<bits/stdc++.h>
using namespace std;

map<int, int > m1;
map<int, int > m2;
map<int, int > m3;
map<int, int > m4;
typedef long long LL;
int main()
{
	int n;
	LL ans = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		ans += m1[a];
		m1[a]++;
		ans += m2[b];
		m2[b]++;
		ans += m3[a + b];
		m3[a + b]++;
		ans += m4[b - a];
		m4[b - a]++;
	}
	cout << ans << endl;
	return 0;
}
/*
5
1 1
2 2
3 3
1 3
3 1
*/
