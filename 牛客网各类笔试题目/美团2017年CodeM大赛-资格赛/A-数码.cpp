/*
链接：https://www.nowcoder.com/acm/contest/5/A
来源：牛客网

时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
给定两个整数 l 和 r ，对于所有满足1 ≤ l ≤ x ≤ r ≤ 10^9 的 x ，把 x 的所有约数全部写下来。对于每个写下来的数，只保留最高位的那个数码。求1～9每个数码出现的次数。
输入描述:
一行，两个整数 l 和 r (1 ≤ l ≤ r ≤ 10^9)。
输出描述:
输出9行。

第 i 行，输出数码 i 出现的次数。
示例1
输入
复制
1 4
输出
复制
4
2
1
1
0
0
0
0
0
*/


#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=1005;
const int INF=0x3f3f3f3f;
int a[MAXN],b[MAXN];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    int m;
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&b[i]);
    int res=INF;
    for(int i=0;i+n<=m;i++)
    {
        int now=0;
        for(int j=1;j<=n;j++)
            now+=(a[j]-b[i+j])*(a[j]-b[i+j]);
        res=min(res,now);
    }
    printf("%d\n",res);
    return 0;
}
