/*
链接：https://www.nowcoder.com/acm/contest/5/F
来源：牛客网

优惠券
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
美团点评上有很多餐馆优惠券，用户可以在美团点评App上购买。
每张优惠券有一个唯一的正整数编号。
当用户在相应餐馆就餐时，可以在餐馆使用优惠券进行消费。
优惠券的购买和使用按照时间顺序逐行记录在日志文件中，
运营人员会定期抽查日志文件看业务是否正确。
业务正确的定义为：一个优惠券必须先被购买，然后才能被使用。

某次抽查时，发现有硬盘故障，历史日志中有部分行损坏，
这些行的存在是已知的，但是行的内容读不出来。
假设损坏的行可以是任意的优惠券的购买或者使用。

现在问这次抽查中业务是否正确。
若有错，输出最早出现错误的那一行，即求出最大s，
使得记录1到s-1满足要求；若没有错误，输出-1。
输入描述:
m 分别表示 m (1 ≤ m ≤ 5 * 10^5) 条记录。

下面有m行，格式为：

I x （I为Input的缩写，表示购买优惠券x）；

O x（O为Output的缩写，表示使用优惠券x）；

? （表示这条记录不知道）。

这里x为正整数，且x ≤ 10^5 。
输出描述:
-1 或 x(1 ≤ x ≤ m) 其中x为使得1到x-1这些记录合法的最大行号。
示例1
输入
复制
0
1
O 1
2
？
O 1
3
I 1
？
O 1
2
I 2
O 1
输出
复制
-1
1
-1
-1
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
typedef unsigned long long ull;
const int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
char cur[25][25],nxt[25][25];
set<pair<ull,ull> > st;
inline void init()
{
    st.clear();
    for(int i=1;i<=19;i++)
        for(int j=1;j<=19;j++)
            cur[i][j]='.';
    for(int i=1;i<=19;i++)
        for(int j=1;j<=19;j++)
            nxt[i][j]='.';
}
inline void cop()
{
    for(int i=1;i<=19;i++)
        for(int j=1;j<=19;j++)
            nxt[i][j]=cur[i][j];
}
inline void pas()
{
    for(int i=1;i<=19;i++)
        for(int j=1;j<=19;j++)
            cur[i][j]=nxt[i][j];
}
inline bool check()
{
    ull has[2]={0,0};
    for(int i=1;i<=19;i++)
        for(int j=1;j<=19;j++)
        {
            has[0]=has[0]*131+nxt[i][j];
            has[1]=has[1]*137+nxt[i][j];
        }
    if(st.find(make_pair(has[0],has[1]))==st.end())
    {
        st.insert(make_pair(has[0],has[1]));
        return 1;
    }
    else return 0;
}
inline void show()
{
    for(int i=1;i<=19;i++)
        printf("%s\n",cur[i]+1);
}
int vis[25][25];
inline void fre()
{
    for(int i=1;i<=19;i++)
        for(int j=1;j<=19;j++)
            vis[i][j]=0;
}
bool dfs(int x,int y,char g)
{
    if(nxt[x][y]=='.')return 1;
    if(nxt[x][y]!=g)return 0;
    vis[x][y]=1;
    bool isok=0;
    for(int i=0;i<4;i++)
    {
        int tx=x+dir[i][0],ty=y+dir[i][1];
        if(!vis[tx][ty])
            isok|=dfs(tx,ty,g);
    }
    return isok;
}
void pick(int x,int y,char g)
{
    nxt[x][y]='.';
    for(int i=0;i<4;i++)
    {
        int tx=x+dir[i][0],ty=y+dir[i][1];
        if(nxt[tx][ty]==g)pick(tx,ty,g);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        init();
        check();
        for(int i=1;i<=n;i++)
        {
            char go[5];
            int x,y;
            scanf("%s%d%d",go,&x,&y);
            char a=go[0],b="BW"[a=='B'];
            if(cur[x][y]!='.')printf("miss 1\n");
            else
            {
                cop();
                nxt[x][y]=a;
                fre();
                bool isok=dfs(x,y,a);
                for(int i=0;i<4;i++)
                {
                    int tx=x+dir[i][0],ty=y+dir[i][1];
                    if(!vis[tx][ty] && nxt[tx][ty]==b && !dfs(tx,ty,b))
                    {
                        pick(tx,ty,b);
                        isok=1;
                    }
                }
                if(isok)
                {
                    if(check())pas();
                    else printf("miss 3\n");
                }
                else printf("miss 2\n");
            }
        }
        show();
    }
    return 0;
}
