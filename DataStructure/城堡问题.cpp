/*
(图 1)

# = Wall
| = No wall
- = No wall

图1是一个城堡的地形图。请你编写一个程序，计算城堡一共有多少房间，最大的房间有多大。
城堡被分割成m*n(m≤50，n≤50)个方块，每个方块可以有0~4面墙。

输入
程序从标准输入设备读入数据。第一行是两个整数，分别是南北向、东西向的方块数。
在接下来的输入行里，每个方块用一个数字(0≤p≤50)描述。
用一个数字表示方块周围的墙，1表示西墙，2表示北墙，4表示东墙，8表示南墙。
每个方块用代表其周围墙的数字之和表示。
城堡的内墙被计算两次，方块(1,1)的南墙同时也是方块(2,1)的北墙。
输入的数据保证城堡至少有两个房间。

输出
城堡的房间数、城堡中最大房间所包括的方块数。结果显示在标准输出设备上。

样例输入
4
7
11 6 11 6 3 10 6
7 9 6 13 5 15 5
1 10 12 7 13 7 5
13 11 10 8 10 12 13

样例输出
5
9
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

using namespace::std;

int rows, cols;
int rooms[60][60];
int color[60][60];
int maxRoomArea = 0, roomNum = 0;
int roomArea;

struct Room {
	int row, col;
	Room(int row, int col) :row(row), col(col){}
};

void dfs(int row, int col)
{
	if (color[row][col])
		return;
	++roomArea;
	color[row][col] = roomNum;
	if ((rooms[row][col] & 1) == 0) dfs(row, col - 1);//往西走
	if ((rooms[row][col] & 2) == 0) dfs(row - 1, col);//向北
	if ((rooms[row][col] & 4) == 0) dfs(row, col + 1);//向东
	if ((rooms[row][col] & 8) == 0) dfs(row + 1, col);//向南
}

void dfsByStack(int row, int col)
{
	stack<Room> stackRoom;
	stackRoom.emplace(row, col);
	while (!stackRoom.empty()) {
		Room tempRoom = stackRoom.top();
		int curRow = tempRoom.row;
		int curCol = tempRoom.col;
		if (color[curRow][curCol]) stackRoom.pop();
		else {
			++roomArea;
			color[curRow][curCol] = roomNum;
			if ((rooms[curRow][curCol] & 1) == 0) stackRoom.emplace(curRow, curCol - 1);//往西走
			if ((rooms[curRow][curCol] & 2) == 0) stackRoom.emplace(curRow - 1, curCol);//向北
			if ((rooms[curRow][curCol] & 4) == 0) stackRoom.emplace(curRow, curCol + 1);//向东
			if ((rooms[curRow][curCol] & 8) == 0) stackRoom.emplace(curRow + 1, curCol);//向南
		}
	}
}

void test1()
{
	freopen("input.txt", "r", stdin);
	cin >> rows >> cols;
	for (int i = 1; i <= rows; ++i)
		for (int k = 1; k <= cols; ++k)
			cin >> rooms[i][k];
	memset(color, 0, sizeof(color));
	for (int i = 1; i <= rows; ++i)
		for (int k = 1; k <= cols; ++k) {
			if (!color[i][k]) {
				++roomNum; roomArea = 0;
				dfsByStack(i, k);
				maxRoomArea = max(roomArea, maxRoomArea);
			}
		}
	cout << roomNum << endl;
	cout << maxRoomArea << endl;
}




int main(int argc, char* argv[])
{
	test1();

	return 0;
}