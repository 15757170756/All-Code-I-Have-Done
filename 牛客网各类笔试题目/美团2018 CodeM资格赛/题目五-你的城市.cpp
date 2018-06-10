/*
[编程|1000分] 你的城市
时间限制：C/C++ 1秒，其他语言 2秒
空间限制：C/C++ 262144K，其他语言 524288K
题目描述
2018年第一季度，美团旅行的酒店业务以5770万的订单总量，成为行业第一名。
与此同时，美团旅行也提供机票、火车票、船票等各种服务，不断开辟新的目的旅游城市。
最近新开的目的地，就包括对小A有特殊意义的偏僻小城C。
“我来到 你的城市 熟悉的那一条街。”小A哼着歌，从北京出发，要去C城。
这对他非常重要，必须当天到达，虽然交通并不是非常方便。
但是，错过火车并不是一个小概率事件。
为了保险起见，小A决定选择一个即使错过火车也存在补救措施的交通方案。
（即假使未赶上原方案中的任何一班火车，依然可以改乘其他的车次能够在当天到达C城，
但同时小A是一个乐观主义者，所以他认为改乘以后的所有车次都不会延误。）
当然了，在满足上述条件的情况下，小A希望花费的钱越少越好
（只考虑计划中的，不考虑发生意外时换乘带来的代价）。
城市及交通网可以看做一张n个点m条边的有向图。
每个点代表一个城市（1号点代表北京，n号点代表C城）。
每条边由一个五元组<x, y, c, ts, td>组成，表示存在一个车次，
由ts时刻从城市x出发，在td时刻到达城市y，且花费为c元。
为了简化问题，ts，td均为以半小时为基本单位（具体格式见样例及Hint）。
并假设每次中转最少需要花费半个小时，
且中转只能发生在同一城市（即到达一个城市距离再次从这个城市出发至少需要间隔半个小时），
注意，小 A 如果因为没赶上车次需要改乘，也需要半个小时的时间。
问小A到达C城最少需要花费多少钱（行程必须在这一天内完成，
可以在0:00上车，也可以在24:00到达）。
输入描述:
第一行，两个正整数n, m。n表示城市数量，m表示当天不同班次的火车数量。
接下来m行，每行3个整数x, y, c加两个字符串ts, td，均以空格作为分隔，
表示当天的某一班火车。其中x, y, c, ts, td的含义如前描述。
所有的车次都是当天的，没有隔夜的票。
2 <= n <= 500, m <= 15000, c <= 1000, ts < td，所有数均为正整数。
车次保证不过夜，时间范围0:00, 0:30, 1:00, … , 23:00, 23:30, 24:00，
可能存在重复车次。
输出描述:
一个整数，表示存在补救措施的前提下，小A到达C城的最小花费。
如果不存在这样的路径，则输出-1。
示例1
输入
3 5
1 3 800 18:00 21:00
1 2 650 13:30 14:00
2 3 100 14:00 18:00
2 3 300 14:30 19:00
2 3 200 15:00 19:30
输出
950
说明
选择第二个和第四个车次。
第三个车次由于中转时间太短无法选择。第五个车次由于没有可改乘的航班无法选择。
如果错过第二个车次，可以改乘第一个车次。如果错过第四个车次，可以改乘第五个车次。
示例2
输入
3 5
1 2 1000 0:00 12:00
1 2 100 0:30 14:00
1 2 100 0:30 15:00
2 3 300 16:00 24:00
2 3 200 16:30 24:00
输出
1300
说明
选择第一个和第四个车次。
不能选择第二个车次是因为，如果错过了0:30的车次2，
那么同样在0:30出发的车次3也是来不及改乘的。
示例3
输入
3 4
1 2 100 0:30 14:00
1 2 200 0:30 15:00
2 3 300 16:00 24:00
2 3 200 16:30 24:00
输出
-1
说明
和样例二类似，但是缺少了原先的车次一，所以没有换乘方案。
示例4
输入
3 4
1 2 100 0:30 14:00
1 2 200 1:00 16:00
2 3 300 16:00 24:00
2 3 200 16:30 24:00
输出
400
说明
选择第一个和第三个车次。
示例5
输入
3 4
1 2 100 0:30 14:00
1 2 200 1:00 16:30
2 3 300 16:00 24:00
2 3 200 16:30 24:00
输出
-1
说明
和样例四类似，但假如错过了第一个车次，
改乘车次二在16:30到达城市2是不足以赶上16:30出发的车次四的。
*/







/*

*/
#include<cstdio>
#include<cstdlib>
#include<string>
#include<algorithm>

#define For(i,l,r) for(int i=l;i<=r;i++)
#define Dor(i,r,l) for(int i=r;i>=l;i--)
#define timeMagicNumber 49
#define inf 100000000

using namespace std;

char convert_buffer[10];
int convert(char* buffer) {
	int a,b;
	sscanf(buffer,"%d:%d",&a,&b);
	return a*2 + b / 30;
}
char* convert(int num){
	sprintf(convert_buffer, "%d:%02d", num/2, (num&1)*30);
	return convert_buffer;
}

struct Edge{
	int x,y,co,s,t;
	void read(){
		scanf("%d%d%d",&x,&y,&co);
		scanf("%s",convert_buffer); s = convert(convert_buffer);
		scanf("%s",convert_buffer); t = convert(convert_buffer);
	}
}E[200005];

int n,m;
int cnt;
int son[200005],Next[500005],ed[500005],edge_cost[500005],edge_s[500005],edge_t[500005];

void graph_link(int x,int y,int c,int s,int t){
	Next[++cnt] = son[x]; son[x]=cnt; ed[cnt]=y;
	edge_cost[cnt] = c; edge_s[cnt] = s; edge_t[cnt] = t;
}

int f[2005][55],ff[200005];
int dist[2005][55];

int dfs(int u,int ut){
	if (f[u][ut] == 1) return 1;
	if (f[u][ut] == 0) return 0;
	if (ut == timeMagicNumber) return 0;

	f[u][ut] = 0;
	for(int i=son[u];i;i=Next[i])
	if(edge_s[i] == ut){
		f[u][ut] |= dfs(ed[i],edge_t[i]+1);
	}
	f[u][ut] |= dfs(u,ut+1);

	return f[u][ut];
}

void dfs(int u,int ut,int di){
	if (di >= dist[u][ut]) return;
	dist[u][ut] = di;
	if (u == n) return;
	if (ut == timeMagicNumber) return;
	if (ut >= ff[u]) return;

	dfs(u,ut+1,di);
	for(int i=son[u];i;i=Next[i])
	if(edge_s[i] == ut){
		dfs(ed[i],edge_t[i]+1,edge_cost[i]+di);
	}
}

int main(){
	scanf("%d%d",&n,&m);
	For(i,1,m) E[i].read();
	For(i,1,m) graph_link(E[i].x,E[i].y,E[i].co,E[i].s,E[i].t);

	For(i,1,n-1) For(t,0,timeMagicNumber) f[i][t] = -1,f[n][t] = 1;
	For(i,1,n-1) For(t,0,timeMagicNumber-1) dfs(i,t);

	For(i,1,n) For(t,0,timeMagicNumber) if(f[i][t] == 1) ff[i] = t;

	For(i,1,n) For(t,0,timeMagicNumber) dist[i][t] = inf;
	dfs(1,0,0);

	int ans = inf;
	For(nt,0,timeMagicNumber) ans = min(ans,dist[n][nt]);
	if (ans == inf) ans = -1;
	printf("%d\n",ans);
}