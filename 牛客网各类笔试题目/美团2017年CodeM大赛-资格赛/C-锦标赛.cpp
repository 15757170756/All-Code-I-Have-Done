/*
链接：https://www.nowcoder.com/acm/contest/5/C
来源：牛客网

锦标赛
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
组委会正在为美团点评CodeM大赛的决赛设计新赛制。

比赛有 n 个人参加（其中 n 为2的幂），每个参赛者根据资格赛和预赛、复赛的成绩，会有不同的积分。比赛采取锦标赛赛制，分轮次进行，设某一轮有 m 个人参加，那么参赛者会被分为 m/2 组，每组恰好 2 人，m/2 组的人分别厮杀。我们假定积分高的人肯定获胜，若积分一样，则随机产生获胜者。获胜者获得参加下一轮的资格，输的人被淘汰。重复这个过程，直至决出冠军。

现在请问，参赛者小美最多可以活到第几轮（初始为第0轮）？
输入描述:
第一行一个整数 n (1≤n≤ 2^20)，表示参加比赛的总人数。

接下来 n 个数字（数字范围：-1000000…1000000），表示每个参赛者的积分。

小美是第一个参赛者。
输出描述:
小美最多参赛的轮次。
示例1
输入
复制
4
4 1 2 3
输出
复制
2
*/


#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
const int MAXN=100005;
int cnt[MAXN],la[MAXN];
int main()
{
    int m;
    scanf("%d",&m);
    set<int> mark;
    for(int i=1;i<=m;i++)
    {
        char ty[5];
        scanf("%s",ty);
        if(*ty!='?')
        {
            int x;
            scanf("%d",&x);
            cnt[x]+=(*ty=='I' ? 1 : -1);
            if(cnt[x]<0 || cnt[x]>1)
            {
                if(mark.lower_bound(la[x])==mark.end())
                    return 0*printf("%d\n",i);
                mark.erase(mark.lower_bound(la[x]));
                cnt[x]=min(max(cnt[x],0),1);
            }
            la[x]=i;
        }
        else mark.insert(i);
    }
    return 0*printf("-1\n");
}
