/*
892. Surface Area of 3D Shapes
DescriptionHintsSubmissionsDiscussSolution
On a N * N grid, we place some 1 * 1 * 1 cubes.

Each value v = grid[i][j] represents a tower of v cubes placed on top of grid cell (i, j).

Return the total surface area of the resulting shapes.

 

Example 1:

Input: [[2]]
Output: 10
Example 2:

Input: [[1,2],[3,4]]
Output: 34
Example 3:

Input: [[1,0],[0,2]]
Output: 16
Example 4:

Input: [[1,1,1],[1,0,1],[1,1,1]]
Output: 32
Example 5:

Input: [[2,2,2],[2,1,2],[2,2,2]]
Output: 46
 

Note:

1 <= N <= 50
0 <= grid[i][j] <= 50

*/



class Solution {
public:
	bool check(int x, int y, int n)
	{
		if (x >= 0 && x < n && y >= 0 && y < n)
			return true;
		else
			return false;
	}
	int surfaceArea(vector<vector<int>>& grid) {
		int dx[4] = { -1, 0, 1, 0 };
		int dy[4] = { 0, 1, 0, -1 };
		int n = grid.size();
		if (n == 1)
			return (2 + 4 * grid[0][0]);
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (((i == 0 && j == 0) || (i == 0 && j == n - 1)
					|| (i == n - 1 && j == 0) 
					|| (i == n - 1 && j == n - 1))
					&& grid[i][j] > 0) {
					cnt += (2 + 2 * grid[i][j]);
					for (int k = 0; k < 4; ++k) {
						int x = i + dx[k];
						int y = j + dy[k];
						if (check(x, y, n)) {
							if (grid[i][j] > grid[x][y]) {
								cnt += (grid[i][j] - grid[x][y]);
							}
						}
					}
				}

				else if ((i == 0 || j == 0
					|| i == n - 1 || j == n - 1)
					&& grid[i][j] > 0) {
					cnt += (2 + grid[i][j]);
					for (int k = 0; k < 4; ++k) {
						int x = i + dx[k];
						int y = j + dy[k];
						if (check(x, y, n)) {
							if (grid[i][j] > grid[x][y]) {
								cnt += (grid[i][j] - grid[x][y]);
							}
						}
					}
				}

				else if (grid[i][j] > 0) {
					cnt += 2;
					for (int k = 0; k < 4; ++k) {
						int x = i + dx[k];
						int y = j + dy[k];
						if (check(x, y, n)) {
							if (grid[i][j] > grid[x][y]) {
								cnt += (grid[i][j] - grid[x][y]);
							}
						}
					}
				}
			}
		}
		return cnt;
	}
};

//Submission Result: Accepted 
