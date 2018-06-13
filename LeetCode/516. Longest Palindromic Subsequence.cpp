/*
516. Longest Palindromic Subsequence
DescriptionHintsSubmissionsDiscussSolution
Given a string s, find the longest palindromic subsequence's length in s.
 You may assume that the maximum length of s is 1000.

Example 1:
Input:

"bbbab"
Output:
4
One possible longest palindromic subsequence is "bbbb".
Example 2:
Input:

"cbbd"
Output:
2
One possible longest palindromic subsequence is "bb".

*/

class Solution {
public:
	int longestPalindromeSubseq(string s) {
		int len = s.size();
		vector<vector<int>> dp(len, vector<int>(len));
		for (int i = len - 1; i >= 0; --i) {
			dp[i][i] = 1;
			for (int j = i + 1; j < len; ++j) {
				if (s[i] == s[j]) {
					dp[i][j] = dp[i + 1][j - 1] + 2;
				}
				else
					dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
			}
		}

		return dp[0][len - 1];
	}
};
//Submission Result: Accepted 