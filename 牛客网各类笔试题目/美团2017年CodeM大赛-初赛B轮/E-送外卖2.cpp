/*
链接：https://www.nowcoder.com/acm/contest/7/E
来源：牛客网

送外卖2
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
美团外卖日订单数已经超过1200万，实时调度系统是背后的重要技术支撑，
其中涉及很多复杂的算法。下面的题目是某类场景的抽象。

一张 n 个点 m 条有向边的图上，有 q 个配送需求，
需求的描述形式为( s_i , t_i , l_i , r_i )，
即需要从点 s_i 送到 t_i， 
在时刻 l_i 之后（包括 l_i）可以在 s_i 领取货物，
需要在时刻 r_i 之前（包括 r_i）送达 t_i ，
每个任务只需完成一次。 图上的每一条边均有边权，
权值代表外卖配送员通过这条边消耗的时间。
在时刻 0 有一个配送员在 点 1 上，求他最多能完成多少个配送任务。
在整个过程中，我们忽略了取餐与最后给用户递餐的时间
（实际场景中这两个时间是无法省略的），
只考虑花费在路程上的时间。另外，允许在一个点逗留。
输入描述:
第一行，三个正整数 n , m , q (2 ≤ n ≤ 0, 1 ≤ m ≤ 400, 1 ≤ q ≤ 10)。
接下来 m 行，每行三个正整数 u_i , v_i , c_i (1 ≤ u_i,v_i ≤ n, 1 ≤ c_i ≤ 20000)，
表示有一条从 u_i 到 v_i 耗时为 c_i 的有向边。
接下来 q 行，每行四个正整数 
s_i , t_i , l_i , r_i (1 ≤ s_i,t_i ≤ n, 1 ≤ l_i ≤ r_i ≤ 10^6)，
描述一个配送任务。
输出描述:
一个整数，表示最多能完成的任务数量。
示例1
输入
复制
5 4 3
1 2 1
2 3 1
3 4 1
4 5 1
1 2 3 4
2 3 1 2
3 4 3 4
输出
复制
2
*/




/*
作者：NotDeep
链接：https://www.nowcoder.com/discuss/29146
来源：牛客网

送外卖 2
思路
3^q 状压每个货物的(未领、已领、已到)状态，
对于每层状态，保存现在在点 i 的最 早到达时间，
每一层用 dijkstra 暴力更新最早时间 O(n^2+m)。
复杂度 O(3^q(n^2+m))
如果将图缩减为一个不超过 2q 个点的完全图(只留下订单涉及的点)，
两点之间的边长 为原图最短路，复杂度可以优化为 O(q(n^2+m) + 3^q q^2)。
*/

#include <stdio.h>
#include <stdlib.h>
#define inf 1000000005
using namespace std;

int n,m,q,Q,i,j,k,u,v,c,ans;
int s[15],t[15],l[15],r[15],w[15],p[15];
int son[25],Next[405],ed[405],cost[405],tot;
int f[60005][25];
bool vis[25];

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(;m;--m)
    {
        scanf("%d%d%d",&u,&v,&c);
        ++tot;Next[tot]=son[u];son[u]=tot;ed[tot]=v;cost[tot]=c;
    }
    for(i=Q=1;i<=q;++i,Q*=3)
    	scanf("%d%d%d%d",&s[i],&t[i],&l[i],&r[i]),p[i]=Q;
    for(i=0;i<Q;++i)
    for(j=1;j<=n;++j)
    f[i][j]=inf;
    f[0][1]=0;
    for(i=0;i<Q;++i)
    {
        for(j=1;j<=n;++j)vis[j]=false;
        for(j=1;j<=n;++j)
        {
            for(u=0,k=1;k<=n;++k)
            	if(!vis[k]&&(!u||f[i][k]<f[i][u]))
            		u=k;
            for(k=son[u],vis[u]=true;k;k=Next[k])
            	if(f[i][u]+cost[k]<f[i][ed[k]])
            		f[i][ed[k]]=f[i][u]+cost[k];
        }
        for(j=1,k=i;j<=q;++j,k/=3)w[j]=k%3;
        for(v=0,j=1;j<=q;++j)
        {
            if(w[j]==0&&f[i][s[j]]<inf)
            {
                if(f[i][s[j]]>l[j])
                	u=f[i][s[j]];
                else
                 u=l[j];
                if(u<f[i+p[j]][s[j]])
                	f[i+p[j]][s[j]]=u;
            }
            if(w[j]==1&&f[i][t[j]]<=r[j])
            {
                u=f[i][t[j]];
                if(u<f[i+p[j]][t[j]])
                	f[i+p[j]][t[j]]=u;
            }
            if(w[j]==2)++v;
        }
        for(j=1;j<=n;++j)
        	if(f[i][j]<inf&&v>ans)
        		ans=v;
    }
    printf("%d\n",ans);
}