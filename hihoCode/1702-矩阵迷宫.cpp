/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定一个NxN的方格矩阵迷宫，每个格子中都有一个整数Aij。
最初小Hi位于迷宫左上角的格子A11，他每一步可以向右或向下移动，
目标是移动到迷宫的出口——右下角ANN。

小Hi需要支付的代价包括路径中经过的所有格子中的整数之和，
以及改变移动方向需要支付的代价。

小Hi第一次改变方向的代价是1，第二次的代价是2，第三次的代价是4，…… 第K次的代价是2K-1。

请你帮小Hi算出要离开迷宫代价最小的路径，并输出要支付的代价。

输入
第一行一个整数N。  (1 ≤ N ≤ 100)

以下N行每行N个整数，代表矩阵A。  (1 ≤ Aij ≤ 100)

输出
从左上角到右下角路径的最小的代价。

样例输入
3
1 3 5
1 1 2
5 1 1
样例输出
9
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <climits>
#include <algorithm>
#include <cassert>

using namespace::std;

struct Point
{
	bool operator ==(const Point &other) const
	{
		return x == other.x && y == other.y;
	}
	int x;
	int y;
};

int main()
{
	int n;
	cin >> n;
	vector<vector<int>> v2(n, vector<int>(n));
	vector<vector<int>> dp(n, vector<int>(n));
	for (int i = 0; i < v2.size(); ++i){
		for (int j = 0; j < v2[i].size(); ++j)
			cin >> v2[i][j];
	}
	dp[0][0] = v2[0][0];

	for (int i = 1; i < n; ++i) {
		dp[0][i] = dp[0][i - 1] + v2[0][i];
		dp[i][0] = dp[i - 1][0] + v2[i][0];
	}
	for (int i = 1; i < n; ++i) {
		for (int j = 1; j < n; ++j) {
			dp[i][j] = v2[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	/*
	上面是经典的动态规划。
	*/
	vector<Point> path;
	Point p;
	p.x = p.y = 0;
	path.push_back(p);
	for (int i = 1; i < n; ++i) {
		for (int j = 1; j < n; ++j) {
			if (dp[i][j - 1] < dp[i - 1][j]) {
				p.x = i;
				p.y = j - 1;
				path.push_back(p);
				break;
			}
			else if (dp[i][j - 1] > dp[i - 1][j]) {
				p.x = i - 1;
				p.y = j;
				path.push_back(p);
			}
			else {
				int XBefore = path[path.size() - 2].x;
				int YBefore = path[path.size() - 2].y;
				int s = (i - XBefore)*(j - 1 - YBefore);
				if (0 == s) {
					p.x = i;
					p.y = j - 1;
					path.push_back(p);
				}
				else {
					p.x = i - 1;
					p.y = j;
					path.push_back(p);
				}
			}
		}
	}
	p.x = p.y = n - 1;
	path.push_back(p);
	//for (int i = 0; i < path.size(); ++i)
	//	cout << path[i].x << ',' << path[i].y << endl;

	auto last = unique(path.begin(), path.end());
	path.erase(last, path.end());

	//for (int i = 0; i < path.size(); ++i)
	//	cout << path[i].x << ',' << path[i].y << endl;

	int cnt = 0;
	for (int i = 0; i < path.size() - 2; ++i) {
		int x1 = path[i].x;
		int y1 = path[i].y;
		int x2 = path[i + 2].x;
		int y2 = path[i + 2].y;

		if ((x1 - x2)*(y1 - y2) != 0){
			++cnt;
		}
	}
	//cout << dp[n - 1][n - 1] << endl;
	cout << dp[n - 1][n - 1] + static_cast<int>(pow(2, cnt - 1)) << endl;
	return 0;
}

/*
结果:Wrong Answer
就这个提示，提示太少了。测试用例是对的
然后自己构造了一个矩阵，应该也是对的。
4
1 3 5 2
1 1 2 4
5 1 1 3
1 2 3 4
dp输出
1 4 9 11
2 3 5 9
7 4 5 8
8 6 8 12
结果输出20 = 20 + 8
*/