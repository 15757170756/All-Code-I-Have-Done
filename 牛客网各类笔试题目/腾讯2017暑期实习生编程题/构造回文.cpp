/*
时间限制：1秒
空间限制：32768K
给定一个字符串s，你可以从中删除一些字符，
使得剩下的串是一个回文串。如何删除才能使得回文串最长呢？
输出需要删除的字符个数。
输入描述:
输入数据有多组，每组包含一个字符串s，且保证:1<=s.length<=1000.
输出描述:
对于每组数据，输出一个整数，代表最少需要删除的字符个数。
输入例子1:
abcda
google
输出例子1:
2
2
*/




#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace::std;

int longestPalindromeSubseq1(string s)
{
	int n = s.size();
	vector<vector<int>> dp(n, vector<int>(n));
	for (int i = n - 1; i >= 0; --i) {
		dp[i][i] = 1;
		for (int j = i + 1; j < n; ++j) {
			if (s[i] == s[j])
				dp[i][j] = dp[i + 1][j - 1] + 2;
			else
				dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
		}
	}

	//for (auto e1 : dp) {
	//	for (auto e2 : e1)
	//		cout << e2 << ' ';
	//	cout << endl;
	//}
	return dp[0][n - 1];
}

int longestPalindromeSubseq2(string s)
{
	int n = s.size(), res = 0;
	vector<int> dp(n, 1);
	for (int i = n - 1; i >= 0; --i) {
		int len = 0;
		for (int j = i + 1; j < n; ++j) {
			int t = dp[j];
			if (s[i] == s[j])
				dp[j] = len + 2;
			else
				len = max(len, t);
		}
	}
	for (int num : dp)
		res = max(res, num);

	return res;
}

int main()
{
	string s;
	while (cin >> s)
		cout << s.size() - longestPalindromeSubseq1(s) << endl;

	return 0;
}