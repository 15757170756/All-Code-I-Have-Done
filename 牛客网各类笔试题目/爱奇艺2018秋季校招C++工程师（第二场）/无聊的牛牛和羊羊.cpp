/*
[编程题] 无聊的牛牛和羊羊
时间限制：1秒

空间限制：32768K

牛牛和羊羊非常无聊.他们有n + m个共同朋友,
他们中有n个是无聊的,m个是不无聊的。
每个小时牛牛和羊羊随机选择两个不同的朋友A和B.
(如果存在多种可能的pair(A, B),任意一个被选到的概率相同。),
然后牛牛会和朋友A进行交谈,羊羊会和朋友B进行交谈。
在交谈之后,如果被选择的朋友之前不是无聊会变得无聊。
现在你需要计算让所有朋友变得无聊所需要的时间的期望值。
输入描述:
输入包括两个整数n 和 m(1 ≤ n, m ≤ 50)


输出描述:
输出一个实数,表示需要时间的期望值,四舍五入保留一位小数。

输入例子1:
2 1

输出例子1:
1.5
*/

#include <stack>
#include <algorithm>
#include <iostream>
#include <iomanip>
  
using namespace std;

#define maxn 55
float dp[maxn];
int n,m;
float p1(int x,float deno)
{
    return (n+x)*(m-x) / deno;
}
float p2(int x,float deno)
{
    return (m-x)*(m-x-1)/2.0f/deno;
}
float p3(int x,float deno)
{
    return (n+x)*(n+x-1)/2.0f/deno;
}
int main()
{
  
    while(cin >> n >> m){
        float deno = (n+m)*(n+m-1) / 2.0f;
        for(int i = 0;i < maxn;i ++){
            dp[i] = 0.0f;
        }
        for(int i = m-1;i >=0;i --){
            dp[i] += (dp[i+1]+1)*p1(i,deno) + p3(i,deno);
            if(i+2 <=m){
                dp[i] += p2(i,deno) * (dp[i+2] + 1);
            }
            dp[i] /= (1-p3(i,deno));
        }
        cout << setiosflags(ios::fixed) << setprecision(1) << dp[0] << endl;
    }
    return 0;
}