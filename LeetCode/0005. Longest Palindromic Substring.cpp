/*
https://leetcode.com/problems/longest-palindromic-substring/

5. Longest Palindromic Substring
Medium

3246

315

Favorite

Share
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: "cbbd"
Output: "bb"
Accepted
506,996
Submissions
1,888,149
*/

class Solution {
public:
	bool isPalindrome(string s)
	{
		int n = s.size();
		for (int i = 0, j = n - 1; i < n / 2; ++i, --j)
			if (s[i] != s[j])
				return false;
		return true;
	}
	string longestPalindrome(string s) {
		int n = s.size();
		int maxn = -1;
		string res;
		for (int i = 0; i < n; ++i) {
			for (int j = n; j > i; --j) {
				string temp = s.substr(i, j - i);
				if (isPalindrome(temp)) {
					if ((int)temp.size() > maxn) {
						maxn = temp.size();
						res = temp;
					}
				}
			}
		}
		return res;
	}
};

//Time Limit Exceeded Details 




class Solution {
public:
	string longestPalindrome(string s) {
		int len = s.size();
		if (len <= 1)
			return s;
		int longest = 1;
		int start = 0;
		vector<vector<int>> dp(len, vector<int>(len));
		for (int i = 0; i < len; ++i) {
			dp[i][i] = 1;
			if (i < len - 1 && 
				s[i] == s[i+1]) {
				dp[i][i + 1] = 1;
				start = i;
				longest = 2;
			}
		}

		for (int l = 3; l <= len; ++l) {
			for (int i = 0; i + l - 1 < len; ++i) {
				int j = l + i - 1;
				if (s[i] == s[j] && 
					dp[i + 1][j - 1] == 1) {
					dp[i][j] = 1;
					start = i;
					longest = l;
				}
			}
		}
		return s.substr(start, longest);
	}
};
/*
Success
Details 
Runtime: 208 ms, faster than 26.59% of C++ online submissions for Longest Palindromic Substring.
Memory Usage: 186.2 MB, less than 13.07% of C++ online submissions for Longest Palindromic Substring.
*/