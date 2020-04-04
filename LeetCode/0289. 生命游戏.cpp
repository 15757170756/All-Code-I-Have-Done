/*
https://leetcode-cn.com/problems/game-of-life/
289. 生命游戏
根据 百度百科 ，生命游戏，简称为生命，是英国数学家约翰·何顿·康威在 1970 年发明的细胞自动机。

给定一个包含 m × n 个格子的面板，每一个格子都可以看成是一个细胞。每个细胞都具有一个初始状态：1 即为活细胞（live），或 0 即为死细胞（dead）。每个细胞与其八个相邻位置（水平，垂直，对角线）的细胞都遵循以下四条生存定律：

如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
如果死细胞周围正好有三个活细胞，则该位置死细胞复活；
根据当前状态，写一个函数来计算面板上所有细胞的下一个（一次更新后的）状态。下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是同时发生的。

 

示例：

输入： 
[
  [0,1,0],
  [0,0,1],
  [1,1,1],
  [0,0,0]
]
输出：
[
  [0,0,0],
  [1,0,1],
  [0,1,1],
  [0,1,0]
]
 

进阶：

你可以使用原地算法解决本题吗？请注意，面板上所有格子需要同时被更新：你不能先更新某些格子，然后使用它们的更新后的值再更新其他格子。
本题中，我们使用二维数组来表示面板。原则上，面板是无限的，但当活细胞侵占了面板边界时会造成问题。你将如何解决这些问题？
通过次数14,346提交次数20,234
*/

class Solution {
public:
	bool isInRange(int x, int y, int rows, int cols)
	{
		return (x >= 0 && x < cols && y >= 0 && y < rows);
	}
	void gameOfLife(vector<vector<int>>& board) {
		int dx[] = { -1, 0, 1, -1,1, -1,0,1 };
		int dy[] = { -1,-1,-1,  0, 0, 1, 1,1 };
		int rows = board.size();
		int cols = board[0].size();
		vector<vector<int>> tempBoard = board;
		for (int i = 0; i < rows; ++i) {
			vector<int>& rowsEle = board[i];
			for (int j = 0; j < cols; ++j) {
				int temp = rowsEle[j];
				int cnt = 0;
				for (int k = 0; k < 8; ++k) {
					int x = j + dx[k];
					int y = i + dy[k];
					if (isInRange(x, y, rows, cols) &&
						board[y][x] == 1)
						++cnt;
				}
				if (0 == temp) 
					if (cnt == 3)
						tempBoard[i][j] = 1;
	
				if (1 == temp) {
					if (cnt < 2)
						tempBoard[i][j] = 0;
					else if (cnt == 2 || cnt == 3) 
						tempBoard[i][j] = 1;
					else if(cnt > 3)
						tempBoard[i][j] = 0;
				}
			}
		}
		board = tempBoard;
	}
};

/*
执行结果：
通过
显示详情
执行用时 :
4 ms
, 在所有 C++ 提交中击败了
66.02%
的用户
内存消耗 :
7.1 MB
, 在所有 C++ 提交中击败了
100.00%
的用户
*/



//原地算法，用其他状态记录改变
class Solution {
public:
	bool isInRange(int x, int y, int rows, int cols)
	{
		return (x >= 0 && x < cols && y >= 0 && y < rows);
	}
	void gameOfLife(vector<vector<int>>& board) {
		int dx[] = { -1, 0, 1, -1,1, -1,0,1 };
		int dy[] = { -1,-1,-1,  0, 0, 1, 1,1 };
		int rows = board.size();
		int cols = board[0].size();
		//vector<vector<int>> tempBoard = board;
		for (int i = 0; i < rows; ++i) {
			vector<int>& rowsEle = board[i];
			for (int j = 0; j < cols; ++j) {
				int temp = rowsEle[j];
				int cnt = 0;
				for (int k = 0; k < 8; ++k) {
					int x = j + dx[k];
					int y = i + dy[k];
					if (isInRange(x, y, rows, cols) &&
						(1 == board[y][x] || 3 == board[y][x]))
						++cnt;
				}
				if ((0 == temp || 3 == temp ) 
					&& cnt == 3)
					board[i][j] = 2;
	
				else if ((1 == temp || 2 == temp) && 
					(cnt < 2 || cnt > 3)) 
					board[i][j] = 3;
			}
		}
		for (int i = 0; i < rows; ++i) {
			vector<int>& rowsEle = board[i];
			for (int j = 0; j < cols; ++j) {
				int& temp = rowsEle[j];
				if (2 == temp)
					temp = 1;
				else if (3 == temp)
					temp = 0;
			}
		}
	}
};
/*
执行用时 :
0 ms
, 在所有 C++ 提交中击败了
100.00%
的用户
内存消耗 :
7 MB
, 在所有 C++ 提交中击败了
100.00%
的用户
*/