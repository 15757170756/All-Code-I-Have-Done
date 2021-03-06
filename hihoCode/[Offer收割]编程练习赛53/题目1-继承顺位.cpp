/*
题目1 : 继承顺位
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
H国的国王有很多王子，这些王子各自也都有很多王孙，
王孙又各自有很多后代…… 总之，H国王族的族谱形成了一棵以国王为根的树形结构。

根据H国的法律，王族的继承顺位这样规定的：

假设A和B是两位王族

1. 如果其中一位是另一位的直系父亲、祖先，
则辈份高的王族继承顺位更高

2. 否则，假设C是A和B的最近公共祖先。
显然A和B一定是C的两位不同子嗣的后代。
其中C较年长的子嗣的后代的继承顺位更高

按时间顺序给出所有国王后代的出生和死亡记录，
请你计算所有还活着的后代的继承顺位。

输入
第一行包含一个整数N和一个只包含大写字母和数字的字符串，
分别代表记录的条数和国王的名字。

以下N行每行包含一条记录：

birth name1 name2 代表name1的儿子name2出生

death name 代表name死亡

1 <= N <= 10000

名字长度不超过20，并且没有重名的王族。

输出
按继承顺位从高到低输出每位王族的名字。(不包括国王)

每个名字一行。

样例输入
4 KING
birth KING ALI
birth KING BOB
birth ALI CARRO
death ALI
样例输出
CARRO
BOB
*/



#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>


using namespace::std;

class Offspring
{
public:
	Offspring() = default;
	Offspring(string name = "",
		bool isDead = false,
		int sunIdx = 0)
		: name(name), isDead(isDead), sunIdx(sunIdx) {}
	string name;
	//vector<string> sunName;
	vector<Offspring*> next;
	bool isDead;
	int sunIdx;
};

int main(int argc, char* argv[])
{
	ifstream in("input.txt");
	int n;
	string KingName;
	cin >> n;
	cin >> KingName;
	Offspring *root = new Offspring(KingName);
	while (n--) {
		string birOfde, dadName, sunName, deadName;
		cin >> birOfde;
		if (birOfde == "birth") {
			cin >> dadName >> sunName;
		}
	}

	return 0;
}





















#include<stdio.h>
#include<iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;

const int MAX_N = 11000;

//struct Edge {
//    int to, next;
//};
//
//int head[MAX_N], tot;
//Edge edge[MAX_N * 8];
//
//
//void add_edge(int a, int b) {
//    edge[tot].to = b;
//    edge[tot].next = head[a];
//    head[a] = tot++;
//    edge[tot].to = a;
//    edge[tot].next = head[b];
//    head[b] = tot++;
//}

vector<int> edge[MAX_N];
map<string, int> mp1;
map<int, string> mp2;
map<int, int> mp3;
int cnt = 0;
bool mark[MAX_N];

void dfs(int pos) {
	if (pos != 1 && mp3[pos] != 1) {
		cout << mp2[pos] << endl;
	}
	mark[pos] = true;
	for (int i = 0; i < edge[pos].size(); i++) {
		if (!mark[edge[pos][i]]) {
			dfs(edge[pos][i]);
		}
	}
}

int main()
{
	int N;
	string s;
	while (cin >> N >> s) {
		mp1.clear();
		mp2.clear();
		mp3.clear();
		cnt = 1;
		for (int i = 0; i < MAX_N; i++) {
			edge[i].clear();
		}
		mp1[s] = cnt;
		mp2[cnt] = s;
		cnt++;
		for (int i = 0; i < N; i++) {
			string temp;
			cin >> temp;
			if (temp == "birth") {
				string t1, t2;
				cin >> t1 >> t2;
				if (mp1[t1] == 0) {
					mp1[t1] = cnt;
					mp2[cnt] = t1;
					cnt++;
				}
				if (mp1[t2] == 0) {
					mp1[t2] = cnt;
					mp2[cnt] = t2;
					cnt++;
				}
				edge[mp1[t1]].push_back(mp1[t2]);
				edge[mp1[t2]].push_back(mp1[t1]);
			}
			else {
				string t1;
				cin >> t1;
				if (mp1[t1] == 0) {
					mp1[t1] = cnt;
					mp2[cnt] = t1;
					cnt++;
				}
				mp3[mp1[t1]] = 1;
			}
		}
		memset(mark, false, sizeof(mark));
		dfs(1);
	}
	return 0;
}












#include <bits/stdc++.h>
using namespace std;
vector<int> g[11111];
map<string, int> mp;
string name[11111];
int die[11111];

vector<int> ans;
void dfs(int x) {
	ans.push_back(x);
	for (int i = 0; i < g[x].size(); ++i){
		int to = g[x][i];
		dfs(to);
	}
}

int main(){
	string rt;
	int n, cnt = 1;
	scanf("%d", &n);
	cin >> rt;
	mp[rt] = 1;
	name[1] = rt;
	for (int i = 1; i <= n; i++){
		string op, a, b;
		cin >> op;
		if (op == "birth"){
			cin >> a >> b;
			if (mp.find(a) == mp.end()) mp[a] = ++cnt, name[cnt] = a;
			if (mp.find(b) == mp.end()) mp[b] = ++cnt, name[cnt] = b;
			g[mp[a]].push_back(mp[b]);
		}
		else{
			cin >> a;
			if (mp.find(a) == mp.end()) mp[a] = ++cnt, name[cnt] = a;
			die[mp[a]] = 1;
		}
	}
	dfs(1);
	for (int i = 1; i < ans.size(); ++i){
		if (!die[ans[i]]) cout << name[ans[i]] << endl;
	}
	return 0;
}
