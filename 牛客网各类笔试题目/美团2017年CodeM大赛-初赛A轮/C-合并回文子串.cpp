/*
链接：https://www.nowcoder.com/acm/contest/6/C
来源：牛客网

合并回文子串
时间限制：C/C++ 2秒，其他语言4秒
空间限制：C/C++ 262144K，其他语言524288K
64bit IO Format: %lld
题目描述 
输入两个字符串A和B，合并成一个串C，
属于A和B的字符在C中顺序保持不变。
如"abc"和"xyz"可以被组合成"axbycz"或"abxcyz"等。
我们定义字符串的价值为其最长回文子串的长度
（回文串表示从正反两边看完全一致的字符串，如"aba"和"xyyx"）。
需要求出所有可能的C中价值最大的字符串，输出这个最大价值即可
输入描述:
第一行一个整数T(T ≤ 50)。
接下来2T行，每两行两个字符串分别代表A,B(|A|,|B| ≤ 50)，
A,B的字符集为全体小写字母。
输出描述:
对于每组数据输出一行一个整数表示价值最大的C的价值。
示例1
输入
复制
2
aa
bb
a
aaaabcaa
输出
复制
4
5
*/



/*
作者：张晴川 loj.ac
链接：https://www.nowcoder.com/discuss/28582
来源：牛客网

合并回文子串
考虑 c 中的回文子串，既然是子串，
就一定可以拆成 a, b 两串的两个子串的 combine。
不妨 设是 a[i, j]与 b[k, l]的 combine，
则可以考虑动态规划的状态 f[i][j][k][l]表示 
a[i, j]与 b[k, l]的 combine 能否组成回文子串。 
则可以匹配第一个字符和最后一个字符来转移，
根据第一个字符和最后一个字符分别来自 a 还是 b 共有四种转移:


边界情况：
当 j – i + 1 + l – k + 1 = 0 时答案是 true
当 j – i + 1 + l – k + 1 = 1 时答案是 true。
*/



#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int T;
int n,m;
char a[55],b[55];
bool f[55][55][55][55];
int main()
{
  for(scanf("%d",&T);T--;)
  {
    scanf("%s",a+1);n=strlen(a+1);
    scanf("%s",b+1);m=strlen(b+1);
    int ans=0;
    for(int d1=0;d1<=n;d1++)
      for(int d2=0;d2<=m;d2++)
        for(int i=1,j=d1;j<=n;i++,j++)
          for(int k=1,l=d2;l<=m;k++,l++)
          {
            if(d1+d2<=1)f[i][j][k][l]=1;
            else
            {
              f[i][j][k][l]=0;
              if(d1>1&&a[i]==a[j])f[i][j][k][l]|=f[i+1][j-1][k][l];
              if(d1&&d2&&a[i]==b[l])f[i][j][k][l]|=f[i+1][j][k][l-1];
              if(d1&&d2&&b[k]==a[j])f[i][j][k][l]|=f[i][j-1][k+1][l];
              if(d2>1&&b[k]==b[l])f[i][j][k][l]|=f[i][j][k+1][l-1];
            }
            if(f[i][j][k][l])ans=max(ans,d1+d2);
          }
    printf("%d\n",ans);
  }
  return 0;
}
