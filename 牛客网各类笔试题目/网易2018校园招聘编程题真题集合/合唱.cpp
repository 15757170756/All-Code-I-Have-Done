/*
时间限制：2秒

空间限制：131072K

小Q和牛博士合唱一首歌曲,这首歌曲由n个音调组成,每个音调由一个正整数表示。
对于每个音调要么由小Q演唱要么由牛博士演唱,
对于一系列音调演唱的难度等于所有相邻音调变化幅度之和,
例如一个音调序列是8, 8, 13, 12,
那么它的难度等于|8 - 8| + |13 - 8| + |12 - 13| = 6(其中||表示绝对值)。
现在要对把这n个音调分配给小Q或牛博士,
让他们演唱的难度之和最小,请你算算最小的难度和是多少。
如样例所示: 小Q选择演唱{5, 6}难度为1, 
牛博士选择演唱{1, 2, 1}难度为2,难度之和为3,这一个是最小难度和的方案了。
输入描述:
输入包括两行,第一行一个正整数n(1 ≤ n ≤ 2000) 
第二行n个整数v[i](1 ≤ v[i] ≤ 10^6), 表示每个音调。


输出描述:
输出一个整数,表示小Q和牛博士演唱最小的难度和是多少。

输入例子1:
5
1 5 6 2 1

输出例子1:
3
*/


/*
解题思路： DP。dp[i][j][0]表示在前i个人里选满足条件的j个人且最后一个人是i的最大值，
dp[i][j][1]为对应的最小值。

dp[i][j][0] = max(dp[i-k][j-1][l] * a[i]) 其中k = 1,2，..., D, 
和 l = 0,1。dp[i][j][1]有类似的转移方程。
*/

#include <bits/stdc++.h>
using namespace std;

const int imax_n = 55;

int a[imax_n];
long long dp[imax_n][15][2];
int n;
int K;
int D;

int main()
{
    while (scanf("%d", &n)!=-1)
    {
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &a[i]);
        }
        scanf("%d%d", &K, &D);
        dp[0][0][0] = dp[0][0][1] = 1LL;
        for (int i = 1; i <= n; ++i)
        {
            dp[i][0][0] = 1LL;
            dp[i][0][1] = 1LL;
            for (int j = 1; j <= K && j <= i; ++j)
            {
                for (int k = 1; k <= D && i >= k; ++k)
                {
                    for (int l = 0; l <= 1; ++l)
                    {
                        dp[i][j][0] = max(dp[i][j][0], dp[i-k][j-1][l] * a[i]);
                        dp[i][j][1] = min(dp[i][j][1], dp[i-k][j-1][l] * a[i]);
                    }
                }
            }
        }
        long long ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            ans = max(ans, dp[i][K][0]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}