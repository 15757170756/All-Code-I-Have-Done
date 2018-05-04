/*
题目1 : 卡片游戏
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Hi的面前摆放了N张卡片，每张卡片都有A和B两面。其中第i张卡片的A面写着一个整数Ai，B面写着一个整数Bi。

一开始所有卡片都是A面向上。现在小Hi必须选择一张卡片，将其翻成B面向上。

设N张卡片向上那一面的数字组成的集合是S，那么游戏的得分是：最小的不属于S的正整数。

例如S={1, 2, 4, 6, 7}，则得分是3。

你能算出小Hi最多能得多少分么？

输入
第一行包含一个整数N。

第二行包含N个整数Ai。

第三行包含N个整数Bi。

对于50%的数据，1 ≤ N ≤ 1000

对于100%的数据，1 ≤ N ≤ 100000 1 ≤ Ai, Bi ≤ 1000000

输出
输出最大得分

样例输入
5
1 2 3 5 6
3 4 3 4 4
样例输出
6
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

using namespace::std;

const int MAXN = 100000;

int Ai[MAXN], Bi[MAXN];

struct dataIdx
{
	int data;
	int idx;
	dataIdx(int data, int idx) : data(data), idx(idx){}
	dataIdx() :data(0), idx(0){}
	bool operator<(const dataIdx &others) const
	{
		return data < others.data;
	}

	bool operator>(const dataIdx &others) const
	{
		return data > others.data;
	}
};

//int findMaxScore(int *Ai, int *Bi, int n)
//{
//	vector<int> result;
//	for (int i = 0; i < n; ++i) {
//		swap(Ai[i], Bi[i]);
//		
//		for (int j = 0; j < n - 1; ++j) {
//			if (Ai[j + 1] - Ai[j] != 1) {
//				result.push_back(Ai[j] + 1);
//				break;
//			}
//		}
//
//		swap(Ai[i], Bi[i]);
//	}
//}

int main(int argc, char* argv[])
{
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;
	vector<int> result;
	vector<dataIdx> Ai(n);
	vector<dataIdx> Bi(n);
	for (int i = 0; i < n; ++i) {
		cin >> Ai[i].data;
		Ai[i].idx = i;
	}

	for (int i = 0; i < n; ++i) {
		cin >> Bi[i].data;
		Bi[i].idx = i;
	}

	sort(Ai.begin(), Ai.end());
	sort(Bi.begin(), Bi.end());
	for (int i = n - 1; i >= 0; --i) {
		int idx = Ai[i].idx;
		int BiMax;
		for (int j = 0; j < n; ++j)
			if (idx == j) {
				BiMax = Bi[j].data;
				break;
			}
		swap(Ai[i].data, BiMax);

		vector<int> auxVec(n);
		for (int j = 0; j < n; ++j) {
			auxVec[j] = Ai[j].data;
		}

		sort(auxVec.begin(), auxVec.end());
		int cnt = 0;
		for (int j = 0; j < n - 1; ++j) {
			if (auxVec[j + 1] - auxVec[j] != 1) {
				result.push_back(auxVec[j] + 1);
				break;
			}
			else
				++cnt;
		}
		if (cnt == n - 1)
			result.push_back(auxVec[n - 1] + 1);

		swap(Ai[i].data, BiMax);
	}

	sort(result.begin(), result.end());
	/*for (int i = 0; i < result.size(); ++i) {
	cout << result[i] << endl;
	}*/
	cout << result[result.size() - 1] << endl;

	return 0;
}
/*
通过30%
*/















#include <bits/stdc++.h>
using namespace std;
map<int, int> mp;
set<int> S;
const int maxn = 1e5 + 10;
int A[maxn], B[maxn];

int main()
{
	int N, ans = 1;
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) 
		scanf("%d", A + i), mp[A[i]]++;
	for (int i = 1; i <= N; ++i) 
		scanf("%d", B + i);
	for (int i = 1; i <= N + 1; ++i) 
		if (mp.find(i) == mp.end()) 
			S.insert(i);
	for (int i = 1; i <= N; ++i){
		mp[A[i]]--;
		if (mp[A[i]] == 0) 
			S.insert(A[i]);
		mp[B[i]]++;
		if (mp[B[i]] == 1 
			&& S.find(B[i]) != S.end()) 
			S.erase(B[i]);

		ans = max(ans, *S.begin());
		mp[B[i]]--;
		if (mp[B[i]] == 0) 
			S.insert(B[i]);
		mp[A[i]]++;

		if (mp[A[i]] == 1
			&& S.find(A[i]) != S.end()) 
			S.erase(A[i]);
	}
	printf("%d\n", ans);
	return 0;
}