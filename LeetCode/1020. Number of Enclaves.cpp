/*
https://leetcode.com/problems/number-of-enclaves/

1020. Number of Enclaves
Medium

75

11

Favorite

Share
Given a 2D array A, each cell is 0 (representing sea) or 1 (representing land)

A move consists of walking from one land square 4-directionally to another land square, or off the boundary of the grid.

Return the number of land squares in the grid for which we cannot walk off the boundary of the grid in any number of moves.

 

Example 1:

Input: [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
Output: 3
Explanation: 
There are three 1s that are enclosed by 0s, and one 1 that isn't enclosed because its on the boundary.
Example 2:

Input: [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
Output: 0
Explanation: 
All 1s are either on the boundary or can reach the boundary.
 

Note:

1 <= A.length <= 500
1 <= A[i].length <= 500
0 <= A[i][j] <= 1
All rows have the same size.
Accepted
6.2K
Submissions
11.4K
Seen this question in a real interview before?

Yes

No
Contributor
joyxian

*/

class Solution {
public:
	int res = 0;
	int dx[4] = { 0, -1, 1, 0 };
	int dy[4] = { -1, 0, 0, 1 };
	void dfs(int i, int j, int rows, int cols,
		vector<vector<int>>& A, vector<vector<int>>& isTravel)
	{
		if (i < 0 || i > rows - 1
			|| j < 0 || j > cols - 1
			|| A[i][j] == 0 || isTravel[i][j])
			return;
		isTravel[i][j] = 1;
		++res;
		for (int k = 0; k < 4; ++k)
			dfs(i + dx[k], j + dy[k], rows, cols, A, isTravel);
	}

	int numEnclaves(vector<vector<int>>& A) {
		int rows = A.size();
		int cols = A[0].size();
		int oneNo = 0;
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < cols; ++j)
				if (A[i][j] == 1)
					++oneNo;

		vector<vector<int>> isTravel(rows, vector<int>(cols, 0));
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (A[i][j] == 0)
					continue;
				else if (A[i][j] == 1 
					&&(i == 0 || i == rows - 1
						|| j == 0 || j == cols - 1)
					&& !isTravel[i][j])
					dfs(i, j, rows, cols, A, isTravel);
			}
		}
		return oneNo - res;
	}
};

/*
Success
Details 
Runtime: 56 ms, faster than 94.22% of C++ online submissions for Number of Enclaves.
Memory Usage: 17 MB, less than 100.00% of C++ online submissions for Number of Enclaves.
*/