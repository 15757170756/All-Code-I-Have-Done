/*
链接：https://www.nowcoder.com/acm/contest/8/D
来源：牛客网

神秘代号
时间限制：C/C++ 2秒，其他语言4秒
空间限制：C/C++ 262144K，其他语言524288K
64bit IO Format: %lld
题目描述 
有一个古老的帝国，这个帝国有 n 个城邦，
这些城邦由恰好 n 条道路连结（每条路连结两个不同的城邦，
保证任意两条道路连结的城邦组不同，即没有重边），所有城邦保证连通。
每个城邦有一个神秘的代号 x_i ，
每个 x_i 都是一个 [0,p-1] 范围内的非负整数，其中 p 为一个已知的质数。
由于年代过于久远，这些 x_i 已经不为人知了，
但是作为一个历史爱好者，你希望考证一下这些 x_i 的值。
幸运的是，你找到了一些线索，
对于每条道路你都得到了一个方程，
这个方程的形式为：设这条道路连结的两个城邦为 u , v ，
以及有三个参数 a , b , c，那么有 a*x_u + b*x_v = c (mod p)，
即这是一个在模质数 p 域下的方程。
现在你需要根据这些线索来求出一组满足条件的 x_i ，数据保证有解且解唯一。
输入描述:
第一行两个正整数 n , p ( 3 ≤ n ≤ 10^5 , 3 ≤ p ≤ 10^9 )。
接下来 n 行，每行五个整数 u , v , a , b , c 描述一条道路及其参数
 ( 1 ≤ u,v ≤ n , 1 ≤ a,b < p , 0 ≤ c < p )。
输出描述:
输出 n 行，依次为 x_i (0 ≤ x_i < p)。
示例1
输入
复制
6 5
1 4 3 1 0
4 3 1 3 2
4 2 1 3 4
2 6 1 1 2
3 5 1 2 3
2 3 3 4 0
输出
复制
0
3
4
0
2
4
*/

/*
作者：NotDeep
链接：https://www.nowcoder.com/discuss/29150
来源：牛客网

神秘代码
思路
N 个点N 条边的图一定是环套外向树。考虑将环上的所有方程都取出来(设共有x 个)，
那 么这些方程构成了一个x个方程x个变量且首尾相接的方程组。
考虑每次用第一个方程去 消，消去相同的一部分，
消完后将会得到一个仅关于第一个变量的方程。由于题目保证解 唯一，
所以最后的方程是ax ≡ b (mod p)的形式，通过求a的逆元就可以求得第一个变 量的值。
求得一个值后，通过bfs递推就可以得到剩余每个位置的xi 了。
*/

#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 300005
#define M 200005
#define seed 23333

using namespace std;
int i,j,m,n,p,k,vis[N],deg[N],Q[N],cy[N],x,y,fa[N],A[N];
long long a,b,c;
struct Node{
        long long a,b,c;
};
Node fx[N],E[N];
vector<pair<int,Node> >v[N];
void Find_Cycle()
{
        for (i=1;i<=n;++i) if (deg[i]==1) Q[++Q[0]]=i,vis[i]=1;
        int l;
        for (l=1;l<=Q[0];++l)
        {
                int p=Q[l]; 
                for (i=0;i<(int)v[p].size();++i)
                {
                        int k=v[p][i].fi; --deg[k];
                        if (!vis[k]) fa[p]=k,E[p]=v[p][i].se;
                        if (deg[k]==1)
                        {
                                Q[++Q[0]]=k; 
                                vis[k]=1;
                        }
                }
        }
        for (i=1;i<=n;++i) if (!vis[i]) break;
        for (;!vis[i];)
        {
                cy[++cy[0]]=i;
                vis[i]=1;
                for (j=0;j<(int)v[i].size();++j)
                {
                        int k=v[i][j].fi; 
                        if (!vis[k]) 
                        {
                            fx[cy[0]]=v[i][j].se;
                            i=k;
                            break;
                        }
                }
        }
}
int power(int x,int y)
{
        int sum=1;
        for (;y;y>>=1)
        {
                if (y&1) sum=1ll*sum*x%p;
                x=1ll*x*x%p;
        }
        return sum;
}
int main()
{
    scanf("%d%d",&n,&p);
    for (i=1;i<=n;++i)
    {
            scanf("%d%d%lld%lld%lld",&x,&y,&a,&b,&c);
            v[x].pb(mk(y,(Node){a,b,c}));
            v[y].pb(mk(x,(Node){b,a,c}));
            deg[x]++; deg[y]++;
    }
    Find_Cycle();
    Node now=fx[1];
    k=cy[cy[0]];
    for (i=0;i<(int)v[k].size();++i)
    {
             int p=v[k][i].fi;
             if (p==cy[1]) fx[cy[0]]=v[k][i].se;
    }
    for (i=2;i<=cy[0];++i)
    {
        now.a=(now.a*fx[i].a%p+p)%p;
        now.c=((now.c*fx[i].a-fx[i].c*now.b)%p+p)%p;
        now.b=((p-fx[i].b)*now.b%p+p)%p;
    }
    (now.a+=now.b)%=p;
    if (now.a==0) puts("cao"); else A[cy[1]]=1ll*now.c*power(now.a,p-2)%p;
    for (i=2;i<=cy[0];++i) A[cy[i]]=1ll*(fx[i-1].c-1ll*A[cy[i-1]]*fx[i-1].a%p+p)*power(fx[i-1].b,p-2)%p;
    for (i=Q[0];i;--i)
    {
            int k=Q[i];
            A[k]=1ll*(E[k].c-1ll*A[fa[k]]*E[k].b%p+p)*power(E[k].a,p-2)%p; 
    }
    for (i=1;i<=n;++i) printf("%d\n",A[i]);
}