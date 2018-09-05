/*
时间限制：1秒

空间限制：32768K

在一个N*N的数组中寻找所有横，竖，左上到右下，右上到左下，
四种方向的直线连续D个数字的和里面最大的值
输入描述:
每个测试输入包含1个测试用例，第一行包括两个整数 N 和 D :
3 <= N <= 100
1 <= D <= N
接下来有N行，每行N个数字d:
0 <= d <= 100


输出描述:
输出一个整数，表示找到的和的最大值

输入例子1:
4 2
87 98 79 61
10 27 95 70
20 64 73 29
71 65 15 0

输出例子1:
193
*/


#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdint>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <sstream>

using namespace::std;

const int maxn = 105;

int maxSum = -1;
int curSum = 0;

int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int n, d;
int vec[maxn][maxn];

void dfs(int x, int y)
{
	for (int i = 0; i < 8; ++i) {
		curSum = 0;
		curSum += vec[x][y];
		int cnt = d;
		int new_x = x + dx[i];
		int new_y = y + dy[i];
		while (new_x >= 0 && new_x < n &&
			new_y >= 0 && new_y < n 
			&& (--cnt)) {
			curSum += vec[new_x][new_y];
			new_x = new_x + dx[i];
			new_y = new_y + dy[i];
		}
		maxSum = max(maxSum, curSum);
	}
}

int main(int argc, char *argv[])
{
	freopen("input.txt", "r", stdin);
	cin >> n >> d;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> vec[i][j];
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			
			dfs(i, j);
		}
	}
	cout << maxSum << endl;
	return 0;
}

/*
您的代码已保存
答案错误:您提交的程序没有通过所有的测试用例
case通过率为99.00%
*/
