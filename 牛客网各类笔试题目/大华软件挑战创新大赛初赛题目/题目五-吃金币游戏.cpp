/*
"有一个吃金币游戏：
1.地图中有N个城堡（编号分别为0~N-1），每个城堡中挂着一面旗子；
2.某些城堡之间是连通的，在其连通的路上，分散着若干个金币（个数可能相同，也可能不同）；
3.玩家走过存在金币的路之后，可以获得这条路上的所有金币，同一条路走多次，
只有第一次可获得金币；

游戏规则：
1.玩家可以从任意一个城堡出发；
2.玩家必须拿到所有城堡的旗子；
3.玩家走过的所有路，不能存在环路；
4.一定存在至少一条能让玩家拿到所有旗子的路线；

请设计一个算法，计算在遵守以上游戏规则的的前提下，最多能获取到的金币个数。

补充规则中对环路的说明：
1、环路就是最终走过的路径中存在圈，实例如下：
非环路：                  环路：1-2-5-4-1则成为环路
1----2    3              1----2----3
     |    |              |    |
     |    |              |    |
4----5----6              4----5----6
|    |    |              |    |
|    |    |              |    |
7    8    9              7    8----9

2、如说明1中的路径，玩家走1-2-5-4-7-4-5，虽然无圈，
但是4-7、5-4中的路径金币只能吃一次，
重复走第二次金币不可以获取"


"输入的第一行指定用例数量T；
用例的第一行输入指定城堡个数N；
用例的第二行输入指定城堡间连通的路的数量M；
用例的后续行输入指定城堡之间的金币数量，
包括三个参数： 出发点城堡编号 目标城堡编号 金币数量，使用空格隔开；"

最多能获取到的金币个数

"N > 1
M >= N
保证所有城堡间存在连通道路
M<30"

"// 记录城堡间路上金币信息的结构体
// 从城堡castle_from到城堡castle_to的路上有coins个金币
struct road{
int castle_from;
int castle_to;
int coins;
};

// 计算最多能获取到的金币个数
// 参数：roads         路径和金币信息数组
// 参数：roads_count   roads数量
// 参数：castles_count 城堡个数
// 返回值：获取到的金币个数
int max_coin(const road roads[], int roads_count, int castles_count);


Input:
1
7
9
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4
1 4 3
3 5 3
4 6 9
5 6 7

Output:
50"

*/


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>
#include <unordered_set>
#include <sstream>
#include <map>
#include <iterator>
#include <set>
#include <stack>
#include <deque>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <unordered_map>

using namespace::std;

const int maxN = 30;

struct Road
{
	int castle_from;
	int castle_to;
	int coins;
};

Road roads[maxN];

int ran[maxN];
int uset[maxN];

bool cmp(Road &a, Road &b)
{
	return a.coins > b.coins;
}

void makeSet(int n)
{
	for (int i = 1; i <= n; ++i)
		uset[i] = i, ran[i] = 0;
}

int find(int x)
{
	int r = x, t;
	while (r != uset[r])
		r = uset[r];
	while (x != r) {
		t = uset[x];
		uset[x] = r;
		x = t;
	}
	return x;
}

void unionSet(int x, int y)
{
	int a = find(x), b = find(y);
	if (a == b)
		return;
	if (ran[a] > ran[b])
		uset[b] = a;
	else {
		if (ran[a] == ran[b])
			++ran[b];
		uset[a] = b;
	}
}

int Kruskal(int castles_count, int roads_count)
{
	int i, nedge = 0;
	int res = 0;
	sort(roads + 1, roads + 1 + roads_count, cmp);
	for (int i = 1; i <= roads_count
		&& nedge != castles_count - 1; ++i) {
		if (find(roads[i].castle_from)
			!= find(roads[i].castle_to)) {
			unionSet(roads[i].castle_from, roads[i].castle_to);
			res += roads[i].coins;
			++nedge;
		}
	}
	if (nedge < castles_count - 1)
		res = -1;
	return res;
}

void test1()
{
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	while (t--) {
		int castles_count, roads_count;
		int ans = 0;
		cin >> castles_count >> roads_count;
		for (int i = 1; i <= roads_count; ++i) {
			cin >> roads[i].castle_from;
			cin >> roads[i].castle_to;
			cin >> roads[i].coins;
		}
		makeSet(castles_count);
		ans = Kruskal(castles_count, roads_count);
		cout << ans << endl;
	}
}


int main(int argc, char* argv[])
{
	test1();
	return 0;
}










#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>
#include <unordered_set>
#include <sstream>
#include <map>
#include <iterator>
#include <set>
#include <stack>
#include <deque>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <unordered_map>

using namespace std;

typedef pair<int, int>P;
const int maxn = 100;
const int INF = 0x3f3f3f3f;
struct Edge{
	int to, len;
	Edge(int to_ = 0, int len_ = 0)
	{
		to = to_;
		len = len_;
	}
};
vector<Edge> G[maxn];
int dis[maxn];
bool vis[maxn];
int n, m;
void init()
{
	for (int i = 0; i < n; i++)
		G[i].clear();
}
void Add(int from, int to, int len)
{
	G[from].push_back(Edge(to, len));
	G[to].push_back(Edge(from, len));
}
int prime(int s)
{
	fill(dis, dis + n, INF);
	dis[s] = 0;
	memset(vis, false, sizeof(vis));
	priority_queue<P, vector<P>, greater<P>> que;
	int u, v, i, len, cnt = 0, ans = 0;
	Edge e;
	P p;
	que.push(P(0, s));
	while (!que.empty())
	{
		p = que.top();
		que.pop();
		u = p.second;
		if (vis[u])
			continue;
		vis[u] = true;
		cnt++;
		ans += dis[u];
		len = G[u].size();
		for (int i = 0; i<len; i++)
		{
			e = G[u][i];
			v = e.to;
			if (!vis[v] && dis[v]>e.len)
			{
				dis[v] = e.len;
				que.push(P(dis[v], v));
			}
		}
	}
	/*if (cnt != n)
	return -1;*/
	return -ans;
}
int main()
{
	//freopen("input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		init();
		for (int i = 0; i < m; i++)
		{
			int u, v, len;
			scanf("%d%d%d", &u, &v, &len);
			Add(u, v, -len);
		}
		printf("%d\n", prime(0));

	}
}





















//终于对了
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int Max_n = 1e3 + 10;
const int Max_m = 1e5 + 10;

struct edge{
	int from, to, cost;
	bool operator<(const edge& e)const{
		return cost > e.cost;
	}
}e[Max_m];
int N, M;
int par[Max_n];

int Find(int x){
	if (par[x] == x)
		return x;
	return par[x] = Find(par[x]);
}

int Kruskal(){
	for (int i = 0; i < N; i++)
		par[i] = i;
	int ans = 0, sum = 0;
	sort(e, e + M);
	for (int i = 0; i < M; i++){
		int x = Find(e[i].from);
		int y = Find(e[i].to);
		if (x != y){
			ans++; sum += e[i].cost;
			par[x] = y;
		}
		if (ans == N - 1)break;
	}
	if (ans < N - 1)return -1;
	return sum;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &N, &M);
		int a, b, c;
		for (int i = 0; i < M; i++){
			scanf("%d%d%d", &a, &b, &c);
			e[i].from = a; e[i].to = b;
			e[i].cost = c;
		}
		int f = Kruskal();
		if (f == -1)printf("-1\n");
		else printf("%d\n", f);
	}
	return 0;
}