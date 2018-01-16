/*
要求：
给定字符串，求它的回文子序列个数。
回文子序列反转字符顺序后仍然与原序列相同。
例如字符串aba中，回文子序列为"a", "a", "aa", "b", "aba"，共5个。
内容相同位置不同的子序列算不同的子序列。

思路：
动态规划思想

对于任意字符串，如果头尾字符不相等，
则字符串的回文子序列个数就等于去掉头的字符串的回文子序列个数+
去掉尾的字符串的回文子序列个数-去掉头尾的字符串的回文子序列个数；
如果头尾字符相等，那么除了上述的子序列个数之外，还要加上首尾相等时新增的子序列个数，
1+去掉头尾的字符串的回文子序列个数，1指的是加上头尾组成的回文子序列，如aa，bb等。
因此动态规划的状态转移方程为：
设字符串为str，长度为n，p[i][j]表示第i到第j个字符间的最长子序列的长度（i<=j），则：
状态初始条件：dp[i][i]=1 （i=0：n-1）
状态转移方程：dp[i][j]=dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1]  if（str[i]！=str[j]）
dp[i][j]=dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1]+dp[i+1][j-1]+1=dp[i+1][j] + dp[i][j-1]+1
if （str[i]==str[j]）
*/

#include <string>
#include <iostream>
#include <vector>

using namespace::std;

int numOfPalindromeSubSequence(string str)
{
	int strLen = str.size();
	vector<vector<int>> dp(strLen, vector<int>(strLen));

	for (int j = 0; j < strLen; ++j) {
		dp[j][j] = 1;
		for (int i = j - 1; i >= 0; --i) {
			dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
			if (str[i] == str[j])
				dp[i][j] += 1 + dp[i + 1][j - 1];
		}
	}

	return dp[0][strLen - 1];
}


int main()
{
	string str;
	int num;
	while (cin >> str) {
		num = numOfPalindromeSubSequence(str);
		cout << num << endl;
	}

	return 0;
}
