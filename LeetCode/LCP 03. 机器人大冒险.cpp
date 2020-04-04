/*
https://leetcode-cn.com/problems/programmable-robot/

LCP 03. 机器人大冒险
力扣团队买了一个可编程机器人，机器人初始位置在原点(0, 0)。小伙伴事先给机器人输入一串指令command，机器人就会无限循环这条指令的步骤进行移动。指令有两种：

U: 向y轴正方向移动一格
R: 向x轴正方向移动一格。
不幸的是，在 xy 平面上还有一些障碍物，他们的坐标用obstacles表示。机器人一旦碰到障碍物就会被损毁。

给定终点坐标(x, y)，返回机器人能否完好地到达终点。如果能，返回true；否则返回false。

 

示例 1：

输入：command = "URR", obstacles = [], x = 3, y = 2
输出：true
解释：U(0, 1) -> R(1, 1) -> R(2, 1) -> U(2, 2) -> R(3, 2)。
示例 2：

输入：command = "URR", obstacles = [[2, 2]], x = 3, y = 2
输出：false
解释：机器人在到达终点前会碰到(2, 2)的障碍物。
示例 3：

输入：command = "URR", obstacles = [[4, 2]], x = 3, y = 2
输出：true
解释：到达终点后，再碰到障碍物也不影响返回结果。
 

限制：

2 <= command的长度 <= 1000
command由U，R构成，且至少有一个U，至少有一个R
0 <= x <= 1e9, 0 <= y <= 1e9
0 <= obstacles的长度 <= 1000
obstacles[i]不为原点或者终点
通过次数5,783提交次数29,462
在真实的面试中遇到过这道题？

是

否
*/


class Solution {
public:
	bool isReachable(string command, int x, int y,
		int ups, int rights)
	{
		int len = command.size();
		int i = 0, x0 = 0, y0 = 0, temp1, temp2, minNum;
		temp1 = x / rights;
		temp2 = y / ups;
		if (temp1 != temp2 && temp1 != (temp2 + 1) &&
			temp1 != (temp2 - 1))
			return false;
		minNum = min(temp1, temp2);
		x = x - minNum * rights;
		y = y - minNum * ups;
		while (i < len) {
			if (x == x0 && y == y0)
				return true;
			if ('U' == command[i])
				++y0;
			else
				++x0;
			++i;
		}
		return false;
	}

	bool robot(string command, 
		vector<vector<int>>& obstacles, 
		int x, int y) 
	{
		int ups = 0, rights = 0, temp1, temp2, minNum;
		for (int i = 0; i < command.size(); ++i) {
			if ('U' == command[i])
				++ups;
			else
				++rights;
		}

		if (!isReachable(command, x, y, ups, rights))
			return false;

		for (int i = 0; i < obstacles.size(); ++i) {
			int x_ = obstacles[i][0];
			int y_ = obstacles[i][1];
			bool isReach = isReachable(command, x_, y_, ups, rights);
			if (x_ <= x && y_ <= y && isReach)
				return false;
		}
		return true;
	}
};

/*
执行结果：
通过
显示详情
执行用时 :
12 ms
, 在所有 C++ 提交中击败了
29.29%
的用户
内存消耗 :
10.7 MB
, 在所有 C++ 提交中击败了
16.67%
的用户
炫耀一下:


*/









class Solution {
public:
	bool isReachable(vector<vector<int>>& paths,
		int x, int y, int xStep, int yStep)
	{
		for (vector<int>& path : paths) {
			bool bo1 = (x - path[0]) % xStep == 0;
			bool bo2 = (y - path[1]) % yStep == 0;
			bool bo3 = (x - path[0]) / xStep == (y - path[1]) / yStep;
			if (bo1 && bo2 && bo3)
				return true;
		}
		return false;
	}

	bool robot(string command, 
		vector<vector<int>>& obstacles, 
		int x, int y) 
	{
		int len = command.size();
		vector<vector<int>> paths(len, vector<int>(2));
		int yStep = 0, xStep = 0;
		for (int i = 0; i < len; ++i) {
			if ('U' == command[i])
				++yStep;
			else
				++xStep;
			paths[i][0] = xStep;
			paths[i][1] = yStep;
		}

		for (vector<int>& obstacle : obstacles) {
			int obX = obstacle[0];
			int obY = obstacle[1];
			if(obX >= x && obY >= y)
				continue;
			if (isReachable(paths, obX, obY, xStep, yStep))
				return false;
		}

		return isReachable(paths, x, y, xStep, yStep);
	}
};


/*
执行结果：
通过
显示详情
执行用时 :
4 ms
, 在所有 C++ 提交中击败了
96.86%
的用户
内存消耗 :
8.2 MB
, 在所有 C++ 提交中击败了
100.00%
的用户
*/