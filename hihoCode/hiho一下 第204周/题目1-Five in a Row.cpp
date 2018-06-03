/*
题目1 : Five in a Row
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
Five in a Row is a game played on a 15x15 go board. Black and White take turns to place a stone of their color in an empty spot. The winner is the first player to get an unbroken row of five successive stones horizontally, vertically, or diagonally.

Given a Five in a Row game board, your task is to work out which color wins. Note that the input board may not be valid. It is possible that none or both colors have five successive stones.

输入
The first line contains an integer T, the number of test cases. (1 <= T <= 10)

For each test case there is an 15x15 matrix denoting the board. 'B' indicates a black stone, 'W' indicates a white stone and '.' indicates and empty spot.

输出
For each test case output "Black", "White", "None" or "Both" in a separate line denoting which color(s) have five successive stones.

样例输入
2
...............
...............
...............
...............
........B......
......BWW......
.....BWBW......
.....WBBW......
....WBBBBW.....
...W...BW......
......WWB......
......B........
...............
...............
...............
...............
.W.............
..W............
...W...B.......
....W.B........
.....B.........
....B.W........
...B...W.......
........W......
.........W.....
..........W....
...........W...
...............
...............
...............
样例输出
White  
Both 
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
#include <climits>

using namespace std;

char board[16][16];
int t;
int numB, numW;
int dire[8][2] = { { -1, -1 }, { -1, 0 },
{ -1, 1 }, { 0, 1 }, { 1, 1 },
{ 1, 0 }, { -1, -1 }, { 0, -1 } };

void dfs(char ch)
{

}

bool check(int x, int y) 
{
	if (x >= 0 && x < 15
		&& y >= 0 && y < 15)
		return true;
	else
		return false;
}

void work()
{
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			scanf("%c", &board[i][j]);
		}
		getchar();
	}
	//getchar();
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			if (board[i][j] == 'B') {
				for (int k = 0; k < 8; ++k) {
					numB = 1;
					int x = i + dire[k][0];
					int y = j + dire[k][1];
					while (check(x, y) && board[x][y] == 'B') {
						x = x + dire[k][0];
						y = y + dire[k][1];
						++numB;
						if (numB == 5)
							goto anothers;
					}
					
				}
			}
		}
	}
anothers:
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			if (board[i][j] == 'W') {
				for (int k = 0; k < 8; ++k) {
					numW = 1;
					int x = i + dire[k][0];
					int y = j + dire[k][1];
					while (check(x, y) && board[x][y] == 'W') {
						x = x + dire[k][0];
						y = y + dire[k][1];
						++numW;
						if (numW == 5)
							goto resultJudge;
					}
					
				}
			}
		}
	}
resultJudge:
	if (numB == 5 && numW != 5) {
		printf("Black\n");
		return;
	}
	if (numW == 5 && numB != 5) {
		printf("White\n");
		return;
	}
	if (numB == 5 && numW == 5) {
		printf("Both\n");
		return;
	}
	if (numB != 5 && numW != 5) {
		printf("None\n");
		return;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	scanf("%d", &t);
	getchar();
	while (t--) {
		numB = 0;
		numW = 0;
		work();
	}

	return 0;
}
/*
结果:Accepted
得分:100 / 100
*/