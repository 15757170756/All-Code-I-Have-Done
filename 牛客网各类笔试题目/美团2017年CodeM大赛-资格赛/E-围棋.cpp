/*
链接：https://www.nowcoder.com/acm/contest/5/E
来源：牛客网

围棋
时间限制：C/C++ 2秒，其他语言4秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
围棋是起源于中国有悠久历史的策略性棋类游戏。它的规则如下：
1. 棋盘19*19。
2. 棋子分黑白两色，双方各执一色。
3. 下法：每次黑或白着一子于棋盘的空点上。棋子下定后，不再向其他点移动。
4. 棋子的气：一个棋子在棋盘上，
与它相邻的空点是这个棋子的“气”（这里相邻是指两个点有公共边）。 
相邻的点上如果有同色棋子存在，这些棋子就相互连接成一个不可分割的整体，气合并计算。
相邻的点上如果有异色棋子存在，此处的气便不存在。
如果棋子所在的连通块失去所有的气，即为无气之子，不能在棋盘上存在。
5. 提子：把无气之子清理出棋盘的手段叫“提子”。提子有二种：
1) 着子后，对方棋子无气，应立即提取对方无气之子。
2) 着子后，双方棋子都呈无气状态，应立即提取对方无气之子。
6. 禁着点：棋盘上的任何一空点，如果某方在此下子，会使该子立即呈无气状态，
同时又不能提取对方的棋子，这个点叫做“禁着点”，该方不能在此下子。
7. 禁止全局同形：无论哪一方，在成功进行了着子、提子操作后，棋盘局面不能和任何之前的局面相同。

你要做的是：输入一些操作，从空棋盘开始模拟这些操作。
对于每一步，若结果不正确，则输出对应的miss并且忽略这个操作，并在最后输出棋盘的局面。
输入描述:
第一行，测试数据组数≤100

第二行，每组测试数据，执行的步数 n ≤ 2000 

然后 n 行 

B x y 

W x y 

(1 ≤ x ≤ 19,1 ≤ y ≤ 19)
其中，二元组 x,y 表示围棋棋盘上第 x 行第 y 列对应的点。
输入数据保证是黑白轮流下的。
输出描述:
多行
对于miss的情况，输出是哪一种错误格式，其中：
miss 1 表示下的位置已经有棋了
miss 2 表示违反规则6
miss 3 表示违反规则7
对于正常的操作，不用输出。
最后输出最终盘面。“B表示黑子，W表示白子，如果是空点的话，就输出'.'字符。”
示例1
输入
">复制
1
12
B 1 3
W 1 2
B 2 4
W 2 1
B 1 1
W 2 3
B 3 3
W 3 2
B 1 1
W 2 3
B 2 2
W 2 3

对应的棋形是这样的：

输出
复制
miss 2
miss 2
miss 1
miss 3
.WB................
WB.B...............
.WB................
...................
...................
...................
...................
...................
...................
...................
...................
...................
...................
...................
...................
...................
...................
...................
...................
*/







/*
作者：toraoh
链接：https://www.nowcoder.com/discuss/28562
来源：牛客网

Prob F:
实现题。开个数组表示棋盘。
3类miss情况，放了子不能再放的miss 1很简单，不赘述。
miss 2，放下去以后自己没气的话，先考虑把对手的、没气的提掉，再检查自己有没有气，没气的话记得还原棋盘。
miss 3，出现重复情况的处理的话，骚年，hash都说得很熟练的话，不妨把这个棋盘也hash起来，用hash来高效查重啊？
反正这题就慢慢写吧~我写+调整了78分钟，红q写+调整了89分钟
（这题有点卡常数，大家要注意自己写出来的代码的效率，我TLE了3发，调了好几下才过……）
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <unordered_set>
using namespace std;
typedef unsigned int ull;
 
const int di[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
 
struct Point{
    int x,y;
    Point(int a=0,int b=0):x(a),y(b){}
    Point go(int i)const {
        return Point(x+di[i][0],y+di[i][1]);
    }
    bool check()const {
        return x>=1&&x<=19&&y>=1&&y<=19;
    }
};
 
struct Board{
    int a[21][21];
    unordered_set<ull> state;
     
    void init(){
        memset(a,0,sizeof(a));
        state.clear();
    }
    void output(){
        char tmp[20]="\0";
        for(int i=1;i<=19;i++){
            for(int j=1;j<=19;j++){
                if(a[i][j]==0)
                    tmp[j-1]='.';
                else if(a[i][j]==1)
                    tmp[j-1]='B';
                else if(a[i][j]==2)
                    tmp[j-1]='W';
            }
            puts(tmp);
        }
    }
    ull hash(){
        ull ans=0;
        for(int i=1;i<=19;i++){
            for(int j=1;j<=19;j++){
                ans*=3;
                ans+=a[i][j];
                ans%=(int)(1e9+7);
            }
        }
        return ans;
    }
    int& ref(const Point& p){
        return a[p.x][p.y];
    }
}board,backup;
 
bool vis[21][21],vis2[21][21];
bool chi(const Point& p,bool vis[21][21]){
    bool alive=false;
    int chess=board.ref(p);
    queue<Point> q;
    q.push(p);
    vis[p.x][p.y]=1;
    while(!q.empty()){
        Point x=q.front();q.pop();
        for(int i=0;i<4;i++){
            Point y=x.go(i);
            if(!y.check())continue;
            if(board.ref(y)==0)alive=true;
            if(board.ref(y)==chess&&!vis[y.x][y.y]){
                vis[y.x][y.y]=1;
                q.push(y);
            }
        }
    }
    return alive;
}
 
int put(int type,const Point& p){
    int& place=board.ref(p);
    if(place!=0) return 1;
     
    backup=board;
    place=type;
    memset(vis,0,sizeof(vis));
    memset(vis2,0,sizeof(vis2));
    for(int direct=0;direct<4;direct++){
        Point x=p.go(direct);
        if(!x.check())continue;
        int i=x.x,j=x.y;
        if(!vis[i][j] && board.a[i][j]==3-type){
            if(!chi(Point(i,j),vis)){
                chi(Point(i,j),vis2);
            }
        }
    }
     
    for(int i=1;i<=19;i++){
        for(int j=1;j<=19;j++){
            if(vis2[i][j]){
                board.a[i][j]=0;
            }
        }
    }
     
    if(!chi(p,vis)){
        board=backup;
        return 2;
    }
     
    ull hash_val=board.hash();
    unordered_set<ull>::iterator it=board.state.find(hash_val);
    if(it!=board.state.end()){
        board=backup;
        return 3;
    }
    board.state.insert(hash_val);
    return 0;
}
 
template <class T>
inline void scan(T &ret) {
    char c; ret=0;
    while((c=getchar())<'0'||c>'9');
    while(c>='0'&&c<='9') ret=ret*10+(c-'0'),c=getchar();
}
 
template <class T>
inline void scan_c(T &c) {
    while((c=getchar()),!isalnum(c));
}
 
int main(){
    int T,n;
    for(scan(T);T--;){
        board.init();
        for(scan(n);n--;){
            char tmp[2];
            Point x;
            scan_c(tmp[0]);
            scan(x.x);scan(x.y);
            int ret=put(tmp[0]=='B'?1:2,x);
            if(ret){
                printf("miss %d\n",ret);
            }
        }
        board.output();
    }
    return 0;
}