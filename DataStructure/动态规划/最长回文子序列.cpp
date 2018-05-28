/*
动态规划思想
对于任意字符串，如果头尾字符相同，
那么字符串的最长子序列等于去掉首尾的字符串的最长子序列加上首尾；
如果首尾字符不同，
则最长子序列等于去掉头的字符串的最长子序列和去掉尾的字符串的最长子序列的较大者。
因此动态规划的状态转移方程为：
设字符串为str，长度为n，p[i][j]表示第i到第j个字符间的子序列的个数（i<=j），则：
状态初始条件：dp[i][i]=1 （i=0：n-1）
状态转移方程：dp[i][j]=dp[i+1][j-1] + 2  if（str[i]==str[j]）
dp[i][j]=max(dp[i+1][j],dp[i][j-1])  if （str[i]!=str[j]）
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
		cout << longestPalindromeSubseq1(s) << endl;

	return 0;
}