/*
链接：https://www.nowcoder.com/acm/contest/6/E
来源：牛客网

数列互质
时间限制：C/C++ 6秒，其他语言12秒
空间限制：C/C++ 524288K，其他语言1048576K
64bit IO Format: %lld
题目描述 
给出一个长度为 n 的数列 { a[1] , a[2] , a[3] , ... , a[n] }，
以及 m 组询问 ( l[i] , r[i] , k[i])。
求数列下标区间在 [ l[i] , r[i] ] 中有多少数在该区间中的出现次数与 
k[i] 互质（最大公约数为1）。
输入描述:
第一行，两个正整数 n , m (1 ≤ n, m ≤ 50000)。
第二行，n 个正整数 a[i] (1 ≤ a[i] ≤ n)描述这个数列。
接下来 m 行，每行三个正整数 l[i] , r[i] , k[i] (1 ≤ l[i] ≤ r[i] ≤ n,
 1 ≤ k[i] ≤ n)，描述一次询问。
输出描述:
输出 m 行，即每次询问的答案。
示例1
输入
复制
10 5
1 1 1 1 1 2 2 2 2 2
4 7 2
4 7 3
4 8 2
4 8 3
3 8 3
输出
复制
0
2
1
1
0
*/


/*
作者：张晴川 loj.ac
链接：https://www.nowcoder.com/discuss/28582
来源：牛客网

数列互质
对于在整个序列中出现次数超过 sqrt(n)的数，
最多只有 sqrt(n)种，那么对于这些数，
很容易用一个数组做前缀和维护，
可以在每次询问中直接求出它们的出现次数并 gcd 判断。
剩下的数的出现次数不超过 sqrt(n)，
那么可以对它出现恰好 w 次的区间左右端点写出一个范围约束，
这样的约束只总共只有 nsqrt(n)对，
把左端点和右端点看成笛卡尔坐标系上的 x,y坐标，
约束就可以看成一个矩形，
问题转化为求询问点被多少矩形覆盖到，
可以用扫描线来离线对所有询问计算。
一个 trick case，k=1 是需要注意 gcd(1,0)=1 的问题。
代码:
*/


#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>
#define L 100
using namespace std;
int n,m,S,Sn,i,j,k,w,l,r,u,v,ul,vr,c;
int a[50005],sum[50000/L+5][50005],ans[50005],t[50005];
int ql[50005],qr[50005],qk[50005];
vector<int> V[100005];
vector<pair<int,int> > Ins[L+5][50005],Del[L+5][50005];
vector<int> query[50005];
int main()
{
  scanf("%d%d",&n,&m);S=min((int)sqrt(n),100);
  for(i=1;i<=n;++i)scanf("%d",&a[i]),V[a[i]].push_back(i);
  
  for(i=1;i<=n;++i)
  if(V[i].size()>=S)
  {
    ++Sn;
    for(k=V[i].size(),j=0;j<k;++j)++sum[Sn][V[i][j]];
    for(j=1;j<=n;++j)sum[Sn][j]+=sum[Sn][j-1];
  }
  else
  {
    c=V[i].size();
    for(j=0;j<c;++j)
    {
      u=V[i][j];
      if(j)ul=V[i][j-1]+1;else ul=1;
      for(k=j,l=1;k<c;++k,++l)
      {
        v=V[i][k];
        if(k<c-1)vr=V[i][k+1]-1;else vr=n;
        Ins[l][ul].push_back(make_pair(v,vr));
        Del[l][u].push_back(make_pair(v,vr));
      }
    }
  }
  
  for(i=1;i<=m;++i)
  {
    scanf("%d%d%d",&ql[i],&qr[i],&qk[i]);
    l=ql[i];r=qr[i];
    query[l].push_back(i);
    for(j=1;j<=Sn;++j)if(sum[j][r]-sum[j][l-1]>0&&__gcd(sum[j][r]-sum[j][l-1],qk[i])==1)++ans[i];
  }
  
  for(i=1;i<S;++i)
  for(j=1;j<=n;++j)
  {
    for(k=Ins[i][j].size()-1;k>=0;--k)
    {
      l=Ins[i][j][k].first;
      r=Ins[i][j][k].second;
      for(w=l;w<=n;w+=w&-w)++t[w];
      for(w=r+1;w<=n;w+=w&-w)--t[w];
    }
    for(k=query[j].size()-1;k>=0;--k)
    {
      l=query[j][k];
      u=qr[l];v=qk[l];
      if(__gcd(v,i)!=1)continue;
      for(w=u;w;w-=w&-w)ans[l]+=t[w];
    }
    for(k=Del[i][j].size()-1;k>=0;--k)
    {
      l=Del[i][j][k].first;
      r=Del[i][j][k].second;
      for(w=l;w<=n;w+=w&-w)--t[w];
      for(w=r+1;w<=n;w+=w&-w)++t[w];
    }
  }
  
  for(i=1;i<=m;++i)printf("%d\n",ans[i]);
}