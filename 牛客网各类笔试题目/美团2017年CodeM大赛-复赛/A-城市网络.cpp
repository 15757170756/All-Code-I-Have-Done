/*
链接：https://www.nowcoder.com/acm/contest/8/A
来源：牛客网

城市网络
时间限制：C/C++ 2秒，其他语言4秒
空间限制：C/C++ 262144K，其他语言524288K
64bit IO Format: %lld
题目描述 
有一个树状的城市网络（即 n 个城市由 n-1 条道路连接的连通图），
首都为 1 号城市，每个城市售卖价值为 a_i 的珠宝。
你是一个珠宝商，现在安排有 q 次行程，
每次行程为从 u 号城市前往 v 号城市（走最短路径），
保证 v 在 u 前往首都的最短路径上。 在每次行程开始时，
你手上有价值为 c 的珠宝（每次行程可能不同），
并且每经过一个城市时（包括 u 和 v ），
假如那个城市中售卖的珠宝比你现在手上的每一种珠宝都要优秀（价值更高，即严格大于），
那么你就会选择购入。
现在你想要对每一次行程，求出会进行多少次购买事件。
输入描述:
第一行，两个正整数 n , q (2 ≤ n ≤ 10^5 , 1 ≤ q ≤ 10^5)。
第二行，n 个正整数 a_i (1 ≤ a_i ≤ 10^5) 描述每个城市售卖的珠宝的价值。
接下来 n-1 行，每行描述一条道路 x , y (1 ≤ x,y ≤ n)，表示有一条连接 x 和 y 的道路。
接下来 q 行，每行描述一次行程 u , v , c (1 ≤ u,v ≤ n , 1 ≤ c ≤ 10^5)。
输出描述:
对于每次行程输出一行，为所购买次数。
示例1
输入
复制
5 4
3 5 1 2 4
1 2
1 3
2 4
3 5
4 2 1
4 2 2
4 2 3
5 1 5
输出
复制
2
1
1
0
*/

/*
作者：NotDeep
链接：https://www.nowcoder.com/discuss/29150
来源：牛客网

城市网络
思路
考虑离线处理，可以对每个询问，建出一个新点，作为叶子挂在起点下面。
然后建一棵新树，对于每个点，求出它的祖先中，第一个比它权值大的，作为它在新树中 的父亲。
考虑在新树上处理询问，可以倍增找出需要跳多少点。
*/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int n,q,i,j,k,u,v,l,r,ans;
int a[200005],id[200005];
int tid[200005],t[200005][20],cnt;
int tfa[200005],fa[200005],deep[200005],aim[200005];
int son[200005],Next[400005],ed[400005],tot;
bool vis[200005];

int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
inline bool cmp(const int &x,const int &y){return a[x]<a[y];}

void dfs(int x)
{
    vis[x]=true;tid[++cnt]=x;
    for(int i=son[x];i;i=Next[i])
    if(!vis[ed[i]])
    {
        tfa[ed[i]]=x;
        deep[ed[i]]=deep[x]+1;
        dfs(ed[i]);
    }
}

int main()
{
    scanf("%d%d",&n,&q);
    for(i=1;i<=n;++i)scanf("%d",&a[i]);
    for(i=1;i<n;++i)
    {
        scanf("%d%d",&u,&v);
        ++tot;Next[tot]=son[u];son[u]=tot;ed[tot]=v;
        ++tot;Next[tot]=son[v];son[v]=tot;ed[tot]=u;
    }
    deep[1]=1;dfs(1);
    for(i=1;i<=q;++i)tid[++cnt]=n+i;
    for(i=1;i<=n+q;++i)fa[i]=id[i]=i;
    for(i=1;i<=q;++i)scanf("%d%d%d",&tfa[n+i],&aim[n+i],&a[n+i]),deep[n+i]=deep[tfa[n+i]]+1;
    sort(id+1,id+n+q+1,cmp);
    for(l=1;l<=n+q;l=r+1)
    {
        for(r=l;r<n+q&&a[id[r+1]]==a[id[l]];++r);
        for(i=l;i<=r;++i)u=id[i],fa[u]=tfa[u];
        for(i=l;i<=r;++i)u=id[i],t[u][0]=get(u);
    }
    for(i=1;i<=n+q;++i)
    {
        u=tid[i];
        for(j=0;t[u][j];++j)
        t[u][j+1]=t[t[u][j]][j];
    }
    for(i=n+1;i<=n+q;++i)
    {
        ans=0;u=i;
        for(j=18;j>=0;--j)
        if(deep[t[u][j]]>=deep[aim[i]])
        u=t[u][j],ans+=1<<j;
        printf("%d\n",ans);
    }
}