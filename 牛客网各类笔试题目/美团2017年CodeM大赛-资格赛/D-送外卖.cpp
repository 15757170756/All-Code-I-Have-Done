/*
链接：https://www.nowcoder.com/acm/contest/5/D
来源：牛客网

送外卖
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
n 个小区排成一列，编号为从 0 到 n-1 。一开始，美团外卖员在第0号小区，目标为位于第 n-1 个小区的配送站。
给定两个整数数列 a[0]~a[n-1] 和 b[0]~b[n-1] ，在每个小区 i 里你有两种选择：
1) 选择a：向前 a[i] 个小区。
2) 选择b：向前 b[i] 个小区。

把每步的选择写成一个关于字符 ‘a’ 和 ‘b’ 的字符串。求到达小区n-1的方案中，字典序最小的字符串。如果做出某个选择时，你跳出了这n个小区的范围，则这个选择不合法。 
• 当没有合法的选择序列时，输出 “No solution!”。
• 当字典序最小的字符串无限长时，输出 “Infinity!”。
• 否则，输出这个选择字符串。

字典序定义如下：串s和串t，如果串 s 字典序比串 t 小，则
• 存在整数 i ≥ -1，使得∀j，0 ≤ j ≤ i，满足s[j] = t[j] 且 s[i+1] < t[i+1]。
• 其中，空字符 < ‘a’ < ‘b’。
输入描述:
输入有 3 行。

第一行输入一个整数 n (1 ≤ n ≤ 10^5)。

第二行输入 n 个整数，分别表示 a[i] 。

第三行输入 n 个整数，分别表示 b[i] 。

−n ≤ a[i], b[i] ≤ n
输出描述:
输出一行字符串表示答案。
示例1
输入
复制
7
5 -3 6 5 -5 -1 6
-6 1 4 -2 0 -2 0
输出
复制
abbbb
*/


#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=100005;
int ok[MAXN],vis[MAXN];
vector<int> go[MAXN],rg[MAXN];
void dfs1(int u)
{
    ok[u]=1;
    for(int i=0;i<(int)rg[u].size();i++)
    {
        int v=rg[u][i];
        if(!ok[v])dfs1(v);
    }
}
vector<int> res;
void dfs2(int u,int t)
{
    if(u==t)
    {
        for(int i=0;i<(int)res.size();i++)
            printf("%c",res[i]+'a');
        exit(0);
    }
    vis[u]=1;
    for(int i=0;i<(int)go[u].size();i++)
    {
        int v=go[u][i];
        if(v<0 || !ok[v])continue;
        if(vis[v])
        {
            printf("Infinity!\n");
            exit(0);
        }
        res.push_back(i);
        dfs2(v,t);
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int _=0;_<2;_++)
        for(int i=0;i<n;i++)
        {
            int a;
            scanf("%d",&a);
            int t=i+a;
            if(t>=0 && t<n)
            {
                go[i].push_back(t);
                rg[t].push_back(i);
            }
            else go[i].push_back(-1);
        }
    dfs1(n-1);
    if(!ok[0])return 0*printf("No solution!\n");
    dfs2(0,n-1);
    return 0;
}
