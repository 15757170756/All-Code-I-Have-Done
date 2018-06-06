/*
链接：https://www.nowcoder.com/acm/contest/8/B
来源：牛客网

排列
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 262144K，其他语言524288K
64bit IO Format: %lld
题目描述 
n个二维点(a[i],b[i]), 其中1 ≤ i ≤ n，
询问有多少种排列p（答案对1e9+7取模）使得执行以下伪代码后留下的点是k，
即最后saved=k（其中1 ≤ k ≤ n）:
saved=p[1]
for x from 2 to n
    if a[p[x]] >= a[saved] and b[p[x]] >= b[saved]
        saved=p[x]
保证a[i]和b[i]分别为一个排列。
输入描述:
第一行一个整数n(n ≤ 100000)，接下来n行每行两个整数表示一个点。
输出描述:
n行每行一个整数表示留下的点为i的排列种数。
示例1
输入
复制
3
1 2
2 3
3 1
输出
复制
0
4
2
*/


#include<algorithm>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include  <stdio.h>
#include   <math.h>
#include   <time.h>
#include   <vector>
#include   <bitset>
#include    <queue>
#include      <set>
#include      <map>
using namespace std;

typedef long long LL;

const int N=100005,Mod=1e9+7;

int n,x[N],y[N],f[N],Num[N],s[N],inc[N],ans[N];

void Add(int x,int k)
{
    while(x<=n)
        s[x]=(s[x]+k)%Mod,x+=x&-x;
}

int Sum(int x)
{
    int ss=0;
    while(x)
        ss=(ss+s[x])%Mod,x-=x&-x;
    return ss;
}

int main()
{
    scanf("%d",&n);
    for(int i=1,a,b;i<=n;i++)
        scanf("%d%d",&a,&b),x[i]=a,y[a]=b;
    for(int i=n;i>=1;i--)
        Num[i]=n-i-Sum(y[i]),Add(y[i],1);
    inc[0]=inc[1]=1;
    int fac=1;
    for(int i=2;i<=n;i++)
        inc[i]=(Mod-(Mod/i)*(LL)inc[Mod%i]%Mod)%Mod,fac=fac*(LL)(i-1)%Mod;
    memset(s,0,sizeof s);
    int count=0;
    for(int i=1;i<=n;i++)
    {
        f[i]=(LL)(Sum(y[i])+1)*inc[Num[i]]%Mod;
        Add(y[i],f[i]);
        if(Num[i]==0)ans[i]=f[i]*(LL)fac%Mod,count++;
        else ans[i]=0;
    }
    for(int i=1;i<=n;++i)printf("%d\n",ans[x[i]]);
//    cout<<count<<endl;
    return 0;
}