/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
上回说到，小Ho得到了一棵二叉树玩具，这个玩具是由小球和木棍连接起来的，
而在拆拼它的过程中，小Ho发现他不仅仅可以拼凑成一棵二叉树！
还可以拼凑成一棵多叉树——好吧，其实就是更为平常的树而已。
但是不管怎么说，小Ho喜爱的玩具又升级换代了，
于是他更加爱不释手（其实说起来小球和木棍有什么好玩的是吧= =）。
小Ho手中的这棵玩具树现在由N个小球和N-1根木棍拼凑而成，
这N个小球都被小Ho标上了不同的数字，并且这些数字都是出于1..N的范围之内，
每根木棍都连接着两个不同的小球，
并且保证任意两个小球间都不存在两条不同的路径可以互相到达。
总而言之，是一个相当好玩的玩具啦！
但是小Hi瞧见小Ho这个样子，觉得他这样沉迷其中并不是一件好事，
于是寻思着再找点问题让他来思考思考——不过以小Hi的水准，自然是手到擒来啦！
于是这天食过早饭后，
小Hi便对着又拿着树玩具玩的不亦乐乎的小Ho道：“你说你天天玩这个东西，
我就问你一个问题，看看你可否知道？”
“不好！”小Ho想都不想的拒绝了。
“那你就继续玩吧，一会回国的时候我不叫上你了~”小Hi严肃道。
“诶！别别别，你说你说，我听着呢。”
一向习惯于开启跟随模式的小Ho忍不住了，马上喊道。
小Hi满意的点了点头，随即说道：“这才对嘛，我的问题很简单，
就是——你这棵树中哪两个结点之间的距离最长？
当然，这里的距离是指从一个结点走到另一个结点经过的木棍数。”。
“啊？”小Ho低头看了看手里的玩具树，困惑了。
提示一：路总有折点，路径也不例外！
输入
每个测试点（输入文件）有且仅有一组测试数据。
每组测试数据的第一行为一个整数N，意义如前文所述。

每组测试数据的第2~N行，每行分别描述一根木棍，
其中第i+1行为两个整数Ai，Bi，表示第i根木棍连接的两个小球的编号。

对于20%的数据，满足N<=10。

对于50%的数据，满足N<=10^3。

对于100%的数据，满足N<=10^5，1<=Ai<=N, 1<=Bi<=N

小Hi的Tip：那些用数组存储树边的记得要开两倍大小哦！

输出
对于每组测试数据，输出一个整数Ans，
表示给出的这棵树中距离最远的两个结点之间相隔的距离。

样例输入
8
1 2
1 3
1 4
4 5
3 6
6 7
7 8
样例输出
6
*/


#include <cstdio>
#include <cstring>
#include <queue>
#define MAXN 100010
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
int head[MAXN], tol;
struct Edge{
	int v, next;
}e[MAXN * 2];
void addEdge(int u, int v){
	e[tol].v = v; e[tol].next = head[u]; head[u] = tol++;
	e[tol].v = u; e[tol].next = head[v]; head[v] = tol++;
}
struct node{
	int u, dis;
	node(int u, int dis) :u(u), dis(dis){}
};
queue<node> q;
bool vis[MAXN];
int n;
int bfs(int u, int& ans){
	while (!q.empty()) 
		q.pop();

	q.push(node(u, 0));
	vis[u] = true;
	while (!q.empty()){
		node tmp = q.front(); q.pop();
		u = tmp.u;
		ans = tmp.dis;
		int v;
		for (int k = head[u]; k != -1; k = e[k].next){
			v = e[k].v;
			if (!vis[v]){
				vis[v] = true;
				q.push(node(v, tmp.dis + 1));
			}
		}
	}
	return u;
}
int main(){
	scanf("%d", &n);
	tol = 0; mem(head, -1);
	int u, v;
	for (int i = 1; i < n; ++i){ 
		scanf("%d%d", &u, &v); 
		addEdge(u, v); 
	}
	int ans;
	mem(vis, false);
	u = bfs(2, ans);
	mem(vis, false);
	bfs(u, ans);
	printf("%d\n", ans);
	return 0;
}

/*
结果:Accepted
*/