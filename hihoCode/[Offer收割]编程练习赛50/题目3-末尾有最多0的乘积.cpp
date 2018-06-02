/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定N个正整数A1, A2, ... AN。

小Hi希望你能从中选出M个整数，使得它们的乘积末尾有最多的0。

输入
第一行包含两个个整数N和M。

第二行包含N个整数A1, A2, ... AN。

对于30%的数据，1 ≤ M ≤ N ≤ 12

对于100%的数据，1 ≤ M ≤ N ≤ 100  1 ≤ Ai ≤ 1000000000

输出
末尾最多的0的个数

样例输入
4 2
8 25 30 40
样例输出
3
*/

#include<cmath>
#include<cstring>
#include<memory.h>
#include<bitset>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 110;
int t[maxn], f[maxn], ans;
int N, M;
int dp[102][102][902];
int main()
{
	int x, y, i, j, k, sum = 0;
	scanf("%d%d", &N, &M);
	for (i = 1; i <= N; i++){
		scanf("%d", &x); y = x;
		while (y % 5 == 0) {
			t[i]++; y /= 5;
			sum++;
		}
		while (x % 2 == 0){
			f[i]++; x /= 2;
		}
	}
	memset(dp, -1, sizeof(dp));
	dp[0][0][0] = 0;
	sum = min(sum, 900);
	for (i = 1; i <= N; i++)
		for (j = 0; j <= min(i, M); j++)
			for (k = 0; k <= sum; k++){
				dp[i][j][k] = dp[i - 1][j][k];
				if (k >= t[i] && j >= 1 && dp[i - 1][j - 1][k - t[i]] != -1) 
					dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 1][k - t[i]] + f[i]);
			}
	for (i = 1; i <= sum; i++) ans = max(ans, min(dp[N][M][i], i));
	printf("%d\n", ans);
	return 0;
}

/*
结果:Accepted
*/