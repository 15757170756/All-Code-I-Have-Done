/*
链接：https://www.nowcoder.com/acm/contest/7/C
来源：牛客网

景区路线规划
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
美团旅行团队最近打算推出一项新服务，为景区的各个景点规划游览路线，提升游客满意度。其中一个重要的问题是对于一个景区道路网，求出游客的满意度的期望值。基于用户的喜好差异，我们需要对男性游客和女性游客的满意度分别计算。
景区被描述成一张n个点、m条边的无向图（无重边，无自环）。每个点代表一个景点，第i个景点游览需要耗费ci分钟，会让男性游客和女性游客的满意度分别增加h1i和h2i（满意度初始值都为0）。每条边代表一条路，第i条边连接编号为xi,yi的两个景点，从景点xi走到yi和从yi走到xi的时间都是ti分钟。
每个游客在景区中最长可以游览k分钟，最开始会随机的通过不同大门进入到一个景点开始游览，每游览完一个项目，游客会等概率随机选择一个可以从当前景点直达且来得及游览的景点作为下一个游览目标（已经游览过的景点也会因为有各种新活动而让游客再次考虑，所以我们这里不区分景点是否已经游览过）。如果游览完一个景点后，周围没有来得及游览的景点，本次游玩就结束了。
请你分别计算小y和妹子在游玩结束后开心度的期望。
输入描述:
第一行给出三个空格隔开的整数，分别表示n, m, k(0 < n ≤ 100, 1 * 60 ≤ k ≤ 8 * 60)
接下来的n行，每行三个空格隔开的整数，分别表示ci, h1i, h2i (10 ≤ ci ≤ 60，0 < h1i, h2i ≤ 100)
接下来的m行，每行三个空格隔开的整数，分别表示xi, yi, ti (0 < ti ≤ 15)
输出描述:
两个用空格隔开的实数，分表表示小y和妹子开心度的期望，精确到小数点后5位。
示例1
输入
复制
5 4 60
25 12 83
30 38 90
16 13 70
22 15 63
50 72 18
2 1 7
3 1 7
4 3 1
5 3 10
输出
复制
39.20000 114.40000
*/


#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 105
#define eps 0.00000001
#define For(i,l,r) for(int i=l;i<=r;i++)
#define Dor(i,r,l) for(int i=r;i>=l;i--)
int n,m,K;
int pt[maxn],h1[maxn],h2[maxn];
int son[maxn],Next[maxn*maxn/2],ed[maxn*maxn/2],wt[maxn*maxn/2],cnt;
double f[60*8+5][maxn];
double Doit(int *h){
    double result=0;
    For(t,0,K) For(now,1,n) f[t][now]=0;
    For(now,1,n) f[pt[now]][now]=1.0/n;
        For(t,0,K){
            For(now,1,n) result+=f[t][now]*h[now];
            For(now,1,n){
            int num=0;

            for(int i=son[now];i;i=Next[i])
            if(K-t>=wt[i]+pt[ed[i]]) num++;

            if(num==0) continue;

            for(int i=son[now];i;i=Next[i])
            if(K-t>=wt[i]+pt[ed[i]])
                f[t+wt[i]+pt[ed[i]]][ed[i]] += f[t][now]/num;
            }
        }
        return result;
}
int main(){

    cin >> n >> m >> K;
    For(i,1,n) cin >> pt[i] >> h1[i] >> h2[i];
    For(i,1,m){
        int x, y, t;
        cin >> x >> y >> t;
        Next[++cnt]=son[x]; son[x]=cnt; ed[cnt]=y; wt[cnt]=t;
        Next[++cnt]=son[y]; son[y]=cnt; ed[cnt]=x; wt[cnt]=t;
    }
    printf("%.5lf %.5lf\n",Doit(h1),Doit(h2));
}