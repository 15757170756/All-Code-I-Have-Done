/*
八卦阵相传是由诸葛亮创设的一种战斗队形和兵力部署，由八种阵势组成。为了方便，采用矩阵来描述一个八卦阵，它由八个单阵组成，每个单阵由多个兵力区域组成形成一种阵势，如下图所示，其中数字为一个兵力区域的士兵个数。假设单阵与单阵之间兵力区域不会相邻，且单阵中每个兵力区域至少存在一个相邻兵力区域（注：相邻是指在其左上，正上，右上，右方，右下，正下，左下，左方与其相邻），请用最快的速度计算出八个单阵中的兵力（士兵个数）的最大值和最小值。


编译器版本: gcc 4.8.4
请使用标准输入输出(stdin，stdout) ；请把所有程序写在一个文件里，勿使用已禁用图形、文件、网络、系统相关的头文件和操作，如sys/stat.h , unistd.h , curl/curl.h , process.h
时间限制: 1S (C/C++以外的语言为: 3 S) 内存限制: 128M (C/C++以外的语言为: 640 M)
输入:
输入描述，例如：
第一行输入是八阵图的行数。
第二行输入是八阵图的列数。
后续行输入每个区域兵力。每一行的数据中间使用空格分开，当前一行输入完成后回车输入下一行数据。
输出:
输出描述，例如：
输出八个单阵中兵力最大值和最小值。
输入范例:
20
20
34 0 0 0 0 0 0 0 0 0 0 0 0 0 0 10 0 0 0 30
0 23 10 5 5 0 0 0 5 5 5 5 5 0 0 0 30 0 40 0
0 9 0 0 5 0 0 0 4 4 4 4 4 0 0 0 0 30 0 0
0 8 7 7 0 5 0 0 3 3 3 3 0 0 0 0 7 0 9 0
0 9 0 0 5 0 5 0 0 12 12 0 0 0 0 10 0 0 0 9
0 0 0 0 5 0 0 5 0 12 12 0 0 5 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 12 12 0 0 5 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 5 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 5 0 0 0 0 0 0
40 30 3 6 6 0 0 0 0 0 0 0 0 5 5 0 0 0 10 0
0 0 20 0 0 6 6 0 0 0 0 0 0 0 5 6 5 10 10 0
40 30 3 7 6 0 0 0 0 0 0 0 0 0 0 6 0 0 10 0
0 0 0 0 0 0 0 17 0 0 0 0 17 0 0 6 5 7 7 0
0 0 0 0 0 0 0 0 7 0 0 7 0 0 0 0 0 0 0 0
0 20 0 0 7 0 0 0 0 4 4 0 0 0 0 0 10 0 0 0
0 20 0 0 7 0 0 0 0 4 4 0 0 0 0 0 10 0 0 0
0 20 0 0 7 0 0 0 0 4 4 0 0 0 0 0 10 0 0 0
0 30 0 7 0 0 0 0 0 5 5 0 0 0 0 0 0 10 0 50
0 40 7 0 0 0 0 0 0 5 5 0 0 0 0 0 0 0 50 0
43 30 25 10 50 0 0 0 6 6 6 6 0 0 0 0 0 50 0 0
输出范例:
323
116
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>
#include <unordered_set>
#include <sstream>
#include <map>
#include <iterator>
#include <set>
#include <stack>
#include <deque>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <unordered_map>
#include <iterator>

using namespace std;

int maxNum = -1;
int minNum = 0x7fff;

int curSum = 0;

const int maxN = 100;

int matrix[maxN][maxN];
int visited[maxN][maxN];
int rows, cols;

void dfs(int x, int y)
{
	if (visited[x][y] || matrix[x][y] == 0)
		return;
	visited[x][y] = true;
	curSum += matrix[x][y];
	if (x - 1 >= 0 && y - 1 >= 0 &&
		matrix[x - 1][y - 1] > 0) dfs(x - 1, y - 1);

	if (x - 1 >= 0 &&
		matrix[x - 1][y] > 0) dfs(x - 1, y);

	if (x - 1 >= 0 && y + 1 < cols &&
		matrix[x - 1][y + 1] > 0) dfs(x - 1, y + 1);

	if (y + 1 < cols &&
		matrix[x][y + 1] > 0) dfs(x, y + 1);

	if (x + 1 < rows && y + 1 < cols &&
		matrix[x + 1][y + 1] > 0) dfs(x + 1, y + 1);

	if (x + 1 < rows &&
		matrix[x + 1][y] > 0) dfs(x + 1, y);

	if (x + 1 < rows && y - 1 >= 0 &&
		matrix[x + 1][y - 1] > 0) dfs(x + 1, y - 1);

	if (y - 1 >= 0 &&
		matrix[x][y - 1] > 0) dfs(x, y - 1);
}

int main(int argc, char* argv[])
{
	//freopen("input.txt", "r", stdin);

	cin >> rows >> cols;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cin >> matrix[i][j];
			visited[i][j] = false;
		}
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (matrix[i][j] > 0 && !visited[i][j]) {
				dfs(i, j);
				maxNum = max(maxNum, curSum);
				minNum = min(minNum, curSum);
				curSum = 0;
			}
		}
	}
	cout << maxNum << endl;
	cout << minNum << endl;
}
