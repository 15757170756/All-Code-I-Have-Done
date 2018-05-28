/*
去掉0个或多个字符
是字符串编程回文串
的总方案数。
例子：
输入：XXY
输出：4
输入：ABA
输出：5
*/

#include<bits/stdc++.h>
using namespace std;
long long dp[55][55];
char s[55];
int main(){
	char s[55];
	scanf("%s", s);
	int n = strlen(s);
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= i; j++){
			if (i == j) 
				dp[i][j] = 2;
			else 
				dp[i][j] = 1;
		}
	for (int l = 2; l <= n; l++){
		for (int i = 0; i + l - 1 < n; i++){
			int j = i + l - 1;
			dp[i][j] = dp[i + 1][j] + dp[i][j - 1];
			if (s[i] != s[j]) 
				dp[i][j] -= dp[i + 1][j - 1];
		}
	}
	printf("%lld\n", dp[0][n - 1] - 1);
	return 0;
}