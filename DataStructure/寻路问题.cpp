/*
Description
N cities named with numbers 1 … N are connected with one-way roads. Each road has two parameters associated with it : the road length and the toll that needs to be paid for the road (expressed in the number of coins).
Bob and Alice used to live in the city 1. After noticing that Alice was cheating in the card game they liked to play, Bob broke up with her and decided to move away - to the city N. He wants to get there as quickly as possible, but he is short on cash.

We want to help Bob to find the shortest path from the city 1 to the city N that he can afford with the amount of money he has.

N个城市，编号1到N。城市间有R条单向道路。
每条道路连接两个城市，有长度和过路费两个属性。
Bob只有K块钱，他想从城市1走到城市N。问最短共需要走多长的路。
如果到不了N，输出-1。

Input
The first line of the input contains the integer K, 0 <= K <= 10000, 
maximum number of coins that Bob can spend on his way.

The second line contains the integer N, 2 <= N <= 100, 
the total number of cities.

The third line contains the integer R, 1 <= R <= 10000,
the total number of roads.

Each of the following R lines describes one road by specifying integers S, D, L and T separated by single blank characters :
S is the source city, 1 <= S <= N
D is the destination city, 1 <= D <= N
L is the road length, 1 <= L <= 100
T is the toll (expressed in the number of coins), 0 <= T <=100

Notice that different roads may have the same source and destination cities.

Output
The first and the only line of the output should contain the total length of the shortest path from the city 1 to the city N whose total toll is less than or equal K coins.
If such path does not exist, only number -1 should be written to the output.

Sample Input
5
6
7
1 2 2 3
2 4 3 3
3 4 2 4
1 3 4 1
4 6 2 1
3 5 2 0
5 4 3 2

Sample Output
11
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

using namespace::std;

int K, N, R, S, D, L, T;
struct Road {
	int d, L, t;
};

vector<vector<Road>> cityMap(110);//连接表，cityMat[i]是从点i有路连到的城市集合
int minLen = 1 << 30;//当前找到的最优路径长度
int totalLen; //正在走的路径长度
int totalCost; //正在走的路径的花销
int visited[110]; //城市是否已经走过的标记
int minL[110][10100]; //min[i][j]表示从1到i点的花销为j的最短路径长度

void dfs(int s)
{
	if (s == N) {
		minLen = min(minLen, totalLen);
		return;
	}

	for (int i = 0; i < cityMap[s].size(); ++i) {
		int d = cityMap[s][i].d;
		if (!visited[d]) {
			int cost = totalCost + cityMap[s][i].t;
			if (cost > K)
				continue;
			if (totalLen + cityMap[s][i].L >= minLen
				|| totalLen + cityMap[s][i].L >= minL[d][cost])
				continue;
			totalCost += cityMap[s][i].t;
			totalLen += cityMap[s][i].L;
			minL[d][cost] = totalCost;
			visited[d] = 1;
			dfs(d);
			visited[d] = 0;
			totalCost -= cityMap[s][i].t;
			totalLen -= cityMap[s][i].L;
		}
	}
}

void test1()
{
	freopen("input.txt", "r", stdin);
	cin >> K >> N >> R;
	for (int i = 0; i < R; ++i) {
		int s;
		Road r;
		cin >> s >> r.d >> r.L >> r.t;
		if (s != r.d)
			cityMap[s].push_back(r);
	}
	for (int i = 0; i < 110; ++i)
		for (int j = 0; j < 10100; ++j)
			minL[i][j] = 1 << 30;

	memset(visited, 0, sizeof(visited));
	totalLen = 0;
	totalCost = 0;
	visited[1] = 1;

	minLen = 1 << 30;
	dfs(1);
	if (minLen < (1 << 30))
		cout << minLen << endl;
	else
		cout << "-1" << endl;
}

int main(int argc, char* argv[])
{
	test1();

	return 0;
}



