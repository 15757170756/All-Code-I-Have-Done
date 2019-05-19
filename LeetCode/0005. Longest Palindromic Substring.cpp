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





class Solution {
public:
	string longestPalindrome(string s)
	{
		string manaStr = "$#";
		for (int i = 0; i < s.size(); i++)
			//首先构造出新的字符串
		{
			manaStr += s[i];
			manaStr += '#';
		}
		vector<int> rd(manaStr.size(), 0);
		//用一个辅助数组来记录最大的回文串长度，
		//注意这里记录的是新串的长度，原串的长度要减去1
		int pos = 0, mx = 0;
		int start = 0, maxLen = 0;
		for (int i = 1; i < manaStr.size(); i++)
		{
			rd[i] = i < mx ? 
				min(rd[2 * pos - i], mx - i) : 1;
			while (i + rd[i] < manaStr.size() && 
				i - rd[i]>0 &&
				manaStr[i + rd[i]] == manaStr[i - rd[i]])//这里要注意数组越界的判断，源代码没有注意，release下没有报错
				rd[i]++;
			if (i + rd[i] > mx) 
				//如果新计算的最右侧端点大于mx,
				//则更新pos和mx
			{
				pos = i;
				mx = i + rd[i];
			}
			if (rd[i] - 1 > maxLen)
			{
				start = (i - rd[i]) / 2;
				maxLen = rd[i] - 1;
			}
		}
		return s.substr(start, maxLen);
	}
};
/*
https://www.cnblogs.com/mini-coconut/p/9074315.html
https://www.cnblogs.com/grandyang/p/4475985.html

Success
Details 
Runtime: 8 ms, faster than 98.53% of C++ online submissions for Longest Palindromic Substring.
Memory Usage: 9.5 MB, less than 67.34% of C++ online submissions for Longest Palindromic Substring.
*/









class Solution {
public:
	int expandAroundCenter(string s, int left, int right)
	{
		int l = left, r = right;
		while (l >= 0 && r < s.size() &&
			s[l] == s[r]) {
			--l;
			++r;
		}
		return r - l - 1;
	}
	string longestPalindrome(string s)
	{
		if (s.size() < 2)
			return s;
		int start = 0, end = 0;
		for (int i = 0; i < s.size(); ++i) {
			int len1 = expandAroundCenter(s, i, i);
			int len2 = expandAroundCenter(s, i, i + 1);
			int len = max(len1, len2);
			if (len > end - start) {
				start = i - (len - 1) / 2;
				end = i + len / 2;
			}
		}
		return s.substr(start, end - start + 1);
	}
};
/*
Success
Details 
Runtime: 68 ms, faster than 56.83% of C++ online submissions for Longest Palindromic Substring.
Memory Usage: 103.9 MB, less than 25.44% of C++ online submissions for Longest Palindromic Substring.
*/