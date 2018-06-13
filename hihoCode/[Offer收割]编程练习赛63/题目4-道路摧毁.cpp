/*
题目4 : 道路摧毁
时间限制:20000ms
单点时限:1000ms
内存限制:256MB
描述
A国一共有 n 个城市且有n-1条双向道路，且任意两个城市都可以通过道路互相到达。

现在 B 国给出了两个城市的集合X,Y，你需要摧毁若干条A国的道路，使得任意一个在X中的城市无法到达任何一个Y中的城市。

现在给定每条道路摧毁需要付出的代价，求一个代价之和最小的方案。

输入
第一行一个正整数n

第二行一个整数mX，表示|X|

第三行给出mX个互不相同的正整数，描述集合X

第四行一个整数mY，表示|Y|

第五行给出mY个互不相同的正整数，描述集合Y

接下来n-1行，每行三个正整数(u,v,w)，描述一条代价为w的双向道路(u,v)

1 ≤ n ≤ 2 × 105，1 ≤ w ≤ 109，保证集合X和集合Y的交集为空。

输出
输出一个整数，表示代价之和最小的方案的代价之和。

样例解释
摧毁道路(2,5),(1,3)

样例输入
6
1 
4
2 
5 6
1 2 5
2 4 4
2 5 1
1 3 2
3 6 7
样例输出
3
*/


#include <bits/stdc++.h>

using namespace std;
const long long INF = 1000000000000000LL;
const int maxn = 200005;
int h[maxn],mem;
int belong[maxn];
long long dp[maxn][3];
struct
{
    int v,w,next;
}e[maxn<<1];
void add(int u,int v,int w)
{
    e[mem].v=v;
    e[mem].w=w;
    e[mem].next=h[u];
    h[u]=mem++;
}
void dfs(int u,int fa)
{
    if(belong[u]){
        for(int i=0;i<3;i++)
            dp[u][i]=INF;
        dp[u][belong[u]]=0;
    }
    for(int i=h[u];i+1;i=e[i].next)
    {
        int v=e[i].v;
        if(v==fa) continue;
        dfs(v,u);
        dp[u][1] = min(min(min(dp[v][0],dp[v][1]),dp[v][2]+e[i].w) + dp[u][1],dp[u][0]+dp[v][1]);
        dp[u][2] = min(min(min(dp[v][0],dp[v][2]),dp[v][1]+e[i].w) + dp[u][2],dp[u][0]+dp[v][2]);
        dp[u][0] = min(dp[v][0],min(dp[v][1],dp[v][2])+e[i].w) + dp[u][0];
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    memset(belong,0,sizeof(belong));
    int x,y;
    scanf("%d",&x);
    mem=0;memset(h,-1,sizeof(h));
    for(int i=0;i<x;i++)
    {
        int val;
        scanf("%d",&val);
        belong[val]=1;
    }
    scanf("%d",&y);
    for(int i=0;i<y;i++)
    {
        int val;
        scanf("%d",&val);
        belong[val]=2;
    }
    for(int i=1;i<n;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        add(v,u,w);
    }
    dfs(1,1);
    printf("%lld\n",min(dp[1][0],min(dp[1][1],dp[1][2])));
    return 0;
}
