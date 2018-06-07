/*
链接：https://www.nowcoder.com/acm/contest/5/D
来源：牛客网

送外卖
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
n 个小区排成一列，编号为从 0 到 n-1 。一开始，
美团外卖员在第0号小区，目标为位于第 n-1 个小区的配送站。
给定两个整数数列 a[0]~a[n-1] 和 b[0]~b[n-1] ，
在每个小区 i 里你有两种选择：
1) 选择a：向前 a[i] 个小区。
2) 选择b：向前 b[i] 个小区。

把每步的选择写成一个关于字符 ‘a’ 和 ‘b’ 的字符串。
求到达小区n-1的方案中，
字典序最小的字符串。如果做出某个选择时，
你跳出了这n个小区的范围，则这个选择不合法。 
• 当没有合法的选择序列时，输出 “No solution!”。
• 当字典序最小的字符串无限长时，输出 “Infinity!”。
• 否则，输出这个选择字符串。

字典序定义如下：串s和串t，如果串 s 字典序比串 t 小，则
• 存在整数 i ≥ -1，使得∀j，0 ≤ j ≤ i，
满足s[j] = t[j] 且 s[i+1] < t[i+1]。
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




/*
作者：toraoh
链接：https://www.nowcoder.com/discuss/28562
来源：牛客网

Prob D：有没有解比较，简单：构建反向图（本来是3能到6的，我加一条6到3的边），
从n出发，广度优先搜索（bfs）一遍，能到1就有解。
同时记录下哪些点被经过了，这在原图中，就是能到n的点。
有人问了，那什么时候会是无穷长的解？
看下图：

注意我们要字典序最小，而不是长度最小
那么在3这个位置上，我们要不停地选a，而不能选b，否则，字典序上来讲：
aaba......在aaaa.......之后
这里的处理也比较简单：
1、从1出发，每个点贪心选择：如果走a，这个点能到n，那就走a，否则走b。
2、但如果走回到之前走过的点，那说明答案是Infinity。
*/



#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
 
vector<int> G[100005];
int a[100005],b[100005];
int n;
bool vis[100005];
bool vis2[100005];
char str[100005];
 
void rev_bfs(int p){
    queue<int> q;
    vis[p]=1;
    q.push(p);
    while(!q.empty()){
        int x=q.front();q.pop();
        for(int i=0;i<G[x].size();i++){
            if(!vis[G[x][i]]){
                vis[G[x][i]]=1;
                q.push(G[x][i]);
            }
        }
    }
}
 
void input(int* a){
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        int tmp=i+a[i];
        if(tmp>=1&&tmp<=n)
            G[i+a[i]].push_back(i);
    }
}
 
int main(){
    scanf("%d",&n);
    input(a);
    input(b);
    rev_bfs(n);
    if(!vis[1]){
        puts("No solution!");
        return 0;
    }
    int p=0;
    vis2[1]=1;
    bool infflag=0;
    for(int x=1;x!=n&&!infflag;){
        int nxt=x+a[x];
        if(nxt>=1&&nxt<=n&&vis[nxt]){
            if(!vis2[nxt]){
                vis2[nxt]=1;
                str[p++]='a';
            }else{
                infflag=1;
            }
            x=nxt;
        }else{
            nxt=x+b[x];
            if(nxt>=1&&nxt<=n&&vis[nxt]){
                if(!vis2[nxt]){
                    vis2[nxt]=1;
                    str[p++]='b';
                }else{
                    infflag=1;
                }
            }else{
                puts("No solution!");
                return 0;
            }
            x=nxt;
        }
    }
    puts(infflag?"Infinity!":str);
    return 0;
}