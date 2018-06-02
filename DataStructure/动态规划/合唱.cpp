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
动态规划。
dp[i][j]表示小Q上一个演唱的音符是v[i],牛博士上一个演唱的音符是v[j]的最小难度和。
记忆化搜索一下就好了。
*/
#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 2000 + 5;
int v[maxn];
int n;
int dp[maxn][maxn];
int solve(int la, int lb)
{
    int now = max(la, lb) + 1;
    if(now == n + 1) return 0;
    if(dp[la][lb] != -1) return dp[la][lb];
    return dp[la][lb] = min(solve(now, lb) + (la ? abs(v[now] - v[la]) : 0), solve(la, now) + (lb ? abs(v[now] - v[lb]) : 0));
}
int main() 
{
    scanf("%d", &n);
    v[0] = -1;
    for(int i = 1; i <= n; i++) 
        scanf("%d", &v[i]);
    memset(dp, -1, sizeof(dp));
    printf("%d\n", solve(0, 0));
    return 0;
}

/*
您的代码已保存
答案正确:恭喜！您提交的程序通过了所有的测试用例
*/