/*
221. Maximal Square
DescriptionHintsSubmissionsDiscussSolution
Given a 2D binary matrix filled with 0's and 1's, 
find the largest square containing only 1's and return its area.

Example:

Input: 

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Output: 4
Seen this question in a real interview before?  

*/

class Solution {
public:
	int maximalRectangle(vector<vector<char>>& matrix) {
		int rows = matrix.size();
		if (rows < 1)
			return 0;
		int cols = matrix[0].size();
		int ans = -1;
		vector<vector<int>> dp(rows, vector<int>(cols, 0));
		for (int i = 0; i < cols; ++i) {
			dp[0][i] = matrix[0][i] - '0';
			ans = max(ans, dp[0][i]);
		}
		for (int i = 0; i < rows; ++i) {
			dp[i][0] = matrix[i][0] - '0';
			ans = max(ans, dp[i][0]);
		}
		for (int i = 1; i < rows; ++i) {
			for (int j = 1; j < cols; ++j) {
				if (matrix[i][j] == '1') 
					dp[i][j] = min(min(dp[i - 1][j - 1], dp[i - 1][j]),
						dp[i][j - 1]) + 1;
				ans = max(ans, dp[i][j]);
			}
		}

		return ans*ans;
	}
};
