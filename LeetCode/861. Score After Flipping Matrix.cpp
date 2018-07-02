/*
861. Score After Flipping Matrix
User Accepted: 606
User Tried: 691
Total Accepted: 615
Total Submissions: 973
Difficulty: Medium
We have a two dimensional matrix A where each value is 0 or 1.

A move consists of choosing any row or column, and toggling each value in that row or column: changing all 0s to 1s, and all 1s to 0s.

After making any number of moves, every row of this matrix is interpreted as a binary number, and the score of the matrix is the sum of these numbers.

Return the highest possible score.

 

Example 1:

Input: [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
Output: 39
Explanation:
Toggled to [[1,1,1,1],[1,0,0,1],[1,1,1,1]].
0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
 

Note:

1 <= A.length <= 20
1 <= A[0].length <= 20
A[i][j] is 0 or 1.
*/


class Solution {
	int matrixScore(vector<vector<int>>& A) {
		int R = A.size(), C = A[0].size();
		vector<int> colsums(C, 0);
		for (int r = 0; r < R; ++r)
			for (int c = 0; c < C; ++c)
				colsums[c] += A[r][c];

		int ans = 0;
		for (int state = 0; state < (1 << R); ++state) {
			// Toggle the rows so that after, 'state' represents
			// the toggled rows.
			if (state > 0) {
				int trans = state ^ (state - 1);
				for (int r = 0; r < R; ++r) {
					if (((trans >> r) & 1) > 0) {
						for (int c = 0; c < C; ++c) {
							colsums[c] += A[r][c] == 1 ? -1 : 1;
							A[r][c] ^= 1;
						}
					}
				}
			}

			// Calculate the score with the rows toggled by 'state'
			int score = 0;
			for (int c = 0; c < C; ++c)
				score += max(colsums[c], R - colsums[c]) * (1 << (C - 1 - c));
			ans = max(ans, score);
		}

		return ans;
	}
};

//暴力法Time Limit Exceeded





class Solution {
	int matrixScore(vector<vector<int>>& A) {
		int R = A.size(), C = A[0].size();
		int ans = 0;

		for (int c = 0; c < C; ++c) {
			int col = 0;
			for (int r = 0; r < R; ++r)
				col += A[r][c] ^ A[r][0];
			ans += max(col, R - col) * (1 << (C - 1 - c));
		}
		
		return ans;
	}
};