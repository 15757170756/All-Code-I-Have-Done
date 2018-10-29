/*
Problem Description
Humans have discovered a kind of new metal mineral on Mars 
which are distributed in point‐like with paths connecting each of them
which formed a tree. Now Humans launches k robots on Mars to collect them, 
and due to the unknown reasons, 
the landing site S of all robots is identified in advanced, 
in other word, all robot should start their job at point S.
Each robot can return to Earth anywhere, 
and of course they cannot go back to Mars. 
We have research the information of all paths on Mars, 
including its two endpoints x, y and energy cost w. 
To reduce the total energy cost,
we should make a optimal plan which cost minimal energy cost.
 

Input
There are multiple cases in the input. 
In each case: 
The first line specifies three integers N, S, K specifying the numbers of metal mineral, 
landing site and the number of robots. 
The next n‐1 lines will give three integers x, y, w in each line specifying 
there is a path connected point x and y which should cost w. 
1<=N<=10000, 1<=S<=N, 1<=k<=10, 1<=x, y<=N, 1<=w<=10000.
 

Output
For each cases output one line with the minimal energy cost.
 

Sample Input
3 1 1
1 2 1
1 3 1
3 1 2
1 2 1
1 3 1
 

Sample Output
3
2

Hint
In the first case: 1->2->1->3 the cost is 3;
In the second case: 1->2; 1->3 the cost is 2;


Source
The 36th ACM/ICPC Asia Regional Dalian Site —— Online Contest
 

Recommend
lcy




问题描述
人类在火星上发现了一种新的金属！这些金属分布在一些奇怪的地方，不妨叫它节点好了。一些节点之间有道路相连，所有的节点和道路形成了一棵树。一共有 n 个节点，这些节点被编号为 1~n 。人类将 k 个机器人送上了火星，目的是采集这些金属。这些机器人都被送到了一个指定的着落点， S 号节点。每个机器人在着落之后，必须沿着道路行走。当机器人到达一个节点时，它会采集这个节点蕴藏的所有金属矿。当机器人完成自己的任务之后，可以从任意一个节点返回地球。当然，回到地球的机器人就无法再到火星去了。我们已经提前测量出了每条道路的信息，包括它的两个端点
x 和 y，以及通过这条道路需要花费的能量 w 。我们想花费尽量少的能量采集所有节点的金属，这个任务就交给你了。
输入格式
第一行包含三个整数 n, S 和 k ，分别代表节点个数、着落点编号，和机器人个数。
接下来一共 n-1 行，每行描述一条道路。一行含有三个整数 x, y 和 w ，代表在 x 号节点和 y 号节点之间有一条道路，通过需要花费 w 个单位的能量。所有道路都可以双向通行。
输出格式
输出一个整数，代表采集所有节点的金属所需要的最少能量。
样例输入
6 1 3

1 2 1

2 3 1

2 4 1000

2 5 1000

1 6 1000
样例输出
3004
样例说明
所有机器人在 1 号节点着陆。
第一个机器人的行走路径为 1->6 ，在 6 号节点返回地球，花费能量为1000。
第二个机器人的行走路径为 1->2->3->2->4 ，在 4 号节点返回地球，花费能量为1003。
第一个机器人的行走路径为 1->2->5 ，在 5 号节点返回地球，花费能量为1001。
数据规模与约定
本题有10个测试点。
对于测试点 1~2 ， n <= 10 ， k <= 5 。
对于测试点 3 ， n <= 100000 ， k = 1 。
对于测试点 4 ， n <= 1000 ， k = 2 。
对于测试点 5~6 ， n <= 1000 ， k <= 10 。
对于测试点 7~10 ， n <= 100000 ， k <= 10 。
道路的能量 w 均为不超过 1000 的正整数。

dp[p][m]:表示在以p为根的子树中停留m个机器人的花费。把一棵子树看作是一个整体。
*/



#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
using namespace std;
#define N 100001
#define Max_M 11
#define inf 0xfffffff
struct SON
{
    int id,ans;
};
int vist[N],cost[N],dp[N][Max_M],M;
vector<SON> node[N];
int min(int a,int b)
{
    return a>b?b:a;
}
void dfs(int p)
{
    for(int m=M;m>=0;m--)
    dp[p][m]=0;
    vist[p]=1;
    for(int i=0; i<node[p].size(); i++)
    {
        int son=node[p][i].id;
        if(vist[son])continue;
        cost[son]=node[p][i].ans;
        dfs(son);

        for(int m=M; m>=0; m--)//这里要注意不能掉了0的情况
        {
            dp[p][m]+=(dp[son][0]+2*cost[son]);//子树son中没有停留机器人，那么意味全反回，
            //最少是去一个所以最少反回一个
            for(int raim=1; raim<=m; raim++)//在子树son中停raim个机器人的情况
                dp[p][m] = min(dp[p][m], dp[p][m-raim]+raim*cost[son]+dp[son][raim]);
        }
    }
}
int main()
{
    int n,s,a,b,c;
    SON son;
    scanf("%d%d%d",&n,&s,&M);

    for(int i=0; i<=n; i++)
        node[i].clear(),vist[i]=0;
    for(int i=1; i<n; i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        son.id=b;
        son.ans=c;
        node[a].push_back(son);
        son.id=a;
        son.ans=c;
        node[b].push_back(son);
    }

    dfs(s);
    printf("%d\n",dp[s][M]);

}