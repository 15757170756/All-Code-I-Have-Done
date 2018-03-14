/*
时间限制:10000ms
单点时限 : 1000ms
内存限制 : 256MB
描述
小Hi和小Ho在玩一个游戏。给定一个数组A = [A1, A2, ... AN]，
小Hi可以指定M个不同的值S1，S2, S3 ... SM，
这样他的总得分是 ΣSi × count(Si)。（count(Si)是数组中与Si相等的元素的个数)。
为了增加难度，小Ho要求小Hi选择的S1..SM其中任意两个Si和Sj都满足 | Si - Sj | > 1。
你能帮助小Hi算出他最大得分是多少吗？
输入
第一行包含两个整数N和M。
第二行包含N个整数A1, A2, ... AN。
对于30%的数据，1 ≤ M ≤ N ≤ 10
对于100%的数据，1 ≤ M ≤ N ≤ 1000 1 ≤ Ai ≤ 100000
输出
最大得分
样例输入
5 2
1 2 1 2 3
样例输出
5
*/


#include<bits/stdc++.h>
using namespace std;

int n, m;
int a[1009];
int num[1009], t;
int dp[1009][1009];
int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i){
		scanf("%d", &a[i]);
	}
	sort(a, a + n);
	t = 0;
	for (int i = 0; i < n; ++i){
		if (a[i] == a[t]){
			++num[t];
		}
		else{
			a[++t] = a[i];
			num[t] = 1;
		}
	}
	++t;
	dp[0][1] = a[0] * num[0];
	for (int i = 1; i <= m; ++i)dp[0][i] = dp[0][1];
	dp[1][1] = max(a[0] * num[0], a[1] * num[1]);
	if (a[1] > a[0] + 1)dp[1][2] = a[0] * num[0] + a[1] * num[1];
	for (int i = 1; i <= m; ++i)dp[1][i] = max(dp[1][i], dp[1][i - 1]);
	for (int i = 2; i < t; ++i){
		int j = a[i] > a[i - 1] + 1 ? i - 1 : i - 2;
		for (int k = 1; k <= m; ++k){
			dp[i][k] = max(dp[i - 1][k], dp[j][k - 1] + a[i] * num[i]);
		}
	}
	printf("%d\n", dp[t - 1][m]);
	return 0;
}
