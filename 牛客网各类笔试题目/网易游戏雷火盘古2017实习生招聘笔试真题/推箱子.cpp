/*
时间限制：1秒

空间限制：32768K

大家一定玩过“推箱子”这个经典的游戏。
具体规则就是在一个N*M的地图上，
有1个玩家、1个箱子、1个目的地以及若干障碍，其余是空地。
玩家可以往上下左右4个方向移动，但是不能移动出地图或者移动到障碍里去。
如果往这个方向移动推到了箱子，箱子也会按这个方向移动一格，
当然，箱子也不能被推出地图或推到障碍里。当箱子被推到目的地以后，游戏目标达成。
现在告诉你游戏开始是初始的地图布局，请你求出玩家最少需要移动多少步才能够将游戏目标达成。
输入描述:
每个测试输入包含1个测试用例
第一行输入两个数字N，M表示地图的大小。其中0<N，M<=8。
接下来有N行，每行包含M个字符表示该行地图。
其中 . 表示空地、X表示玩家、*表示箱子、#表示障碍、@表示目的地。
每个地图必定包含1个玩家、1个箱子、1个目的地。


输出描述:
输出一个数字表示玩家最少需要移动多少步才能将游戏目标达成。
当无论如何达成不了的时候，输出-1。

输入例子1:
4 4
....
..*@
....
.X..
6 6
...#..
......
#*##..
..##.#
..X...
.@#...

输出例子1:
3
11
*/


#include<iostream>  
#include<queue>  
#include<string>  

using namespace std;

int state[10][10][10][10];//四维数组表示人和箱子的位置状态,开始全为0  

struct q
{
	int px, py, bx, by;
	q(int x, int y, int bx, int by) :px(x), py(y), bx(bx), by(by) {}
};
int moves[4][2] = { { 0, 1 }, { 0, -1 }, { -1, 0 }, { 1, 0 } };//四个方向  
char map[10][10];//地图数组  
int chx, chy, cbx, cby, ex, ey, n, m;

//分别表示当前人的位置，盒子的位置，终点位置，以及地图尺寸。  

bool bound(int x, int y)//边界检查，遇到不合理的位置返回真  
{
	if (x < 0 || y < 0 || x >= n || y >= m || map[x][y] == '#')
		return true;
	else
		return false;
}

//广度优先算法
int bfs()
{
	state[chx][chy][cbx][cby] = 1;//当前其实状态位置设步数为1  
	q temp(chx, chy, cbx, cby);
	queue<q> que; //状态队列  
	que.push(temp);//初始状态入栈  
	while (que.size()) //只要队列不为空就一直寻找  
	{
		temp = que.front();//获取首元素  
		que.pop();//首元素弹出  
		if (temp.bx == ex&&temp.by == ey)
			return state[temp.px][temp.py][temp.bx][temp.by] - 1;
			//如果箱子在终点，结束，返回步数  
		for (int i = 0; i < 4; i++)//四个方向开始搜索了  
		{
			//先更新人的位置  
			int px = temp.px + moves[i][0];
			int py = temp.py + moves[i][1];
			if (bound(px, py))
				continue;//如果这个位置非法，探寻其它方向  
			if (px == temp.bx&&py == temp.by)//如果此时人的位置与箱子的位置重合，说明人应当推动了箱子  
			{
				if (bound(temp.bx + moves[i][0], temp.by + moves[i][1]))
					continue;//如果箱子移动的位置不合法，则重新探寻其它方向  
				state[px][py][temp.bx + moves[i][0]][temp.by + moves[i][1]] =
					state[temp.px][temp.py][temp.bx][temp.by] + 1;//箱子推动，则人和箱子位置改变，记录新状态  
				que.push(q(px, py, temp.bx + moves[i][0], temp.by + moves[i][1]));//新状态入栈  

			}
			else//人没有推动箱子  
			{
				if (state[px][py][temp.bx][temp.by])//如果移动后的状态出现过，则重新搜索新方向  
					continue;
				state[px][py][temp.bx][temp.by] = state[temp.px][temp.py][temp.bx][temp.by] + 1;
				//没有走过这条路就走着试试  
				que.push(q(px, py, temp.bx, temp.by));//更新状态  


			}

		}
	}
	return -1;//如果所有位置都试过了，没有找到，说明不存在  

}


int main()
{
	//freopen("input.txt", "r", stdin);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		scanf("%s", map[i], m + 1);
	}
	
	for (int i = 0; i < n; i++)//初始化人，箱子，终点的位置  
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == '*')
			{
				cbx = i;
				cby = j;
			}
			else if (map[i][j] == 'X') {
				chx = i;
				chy = j;
			}
			else if (map[i][j] == '@')
			{
				ex = i;
				ey = j;
			}
		}
	}

	cout << bfs() << endl;
	return 0;
}