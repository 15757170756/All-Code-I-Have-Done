/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定N个整数A1, A2, ... AN，小Hi希望从中选出M个整数，
使得任意两个选出的整数的差都是K的倍数。

请你计算有多少种不同的选法。由于选法可能非常多，
你只需要输出对1000000009取模的结果。

输入
第一行包含三个整数N、M和K。

第二行包含N个整数A1, A2, ... AN。

对于30%的数据，2 ≤ M ≤ N ≤ 10

对于100%的数据，2 ≤ M ≤ N ≤ 100 1 ≤ K, Ai ≤ 100

输出
一个整数表示答案。

样例输入
5 3 2
1 2 3 4 5
样例输出
1
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <climits>
#include <algorithm>
#include <cassert>

using namespace::std;

template<typename T>
void combinations(const vector<T> &v, size_t count, vector<vector<int>> &resultVec);

int main()
{
	int N, M, K;
	cin >> N >> M >> K;
	vector<int> vec(N);
	for (int &e : vec)
		cin >> e;
	int cntResult = 0;
	vector<vector<int>> resultVec;
	combinations(vec, M, resultVec);
	for (int i = 0; i < resultVec.size(); ++i) {
		int cnt = 0;
		vector<int> &temp = resultVec[i];
		for (int j = 0; j < temp.size() - 1; ++j)
			if (abs(temp[j] - temp[j + 1]) % K == 0)
				++cnt;
		if (cnt == temp.size() - 1)
			++cntResult;
	}
	cout << cntResult % 1000000009 << endl;
}

template<typename T>
void combinations(const vector<T> &v, size_t count, vector<vector<int>> &resultVec)
{
	assert(count <= v.size());
	vector<bool> bitset(v.size() - count, 0);
	bitset.resize(v.size(), 1);
	do {
		vector<int> temp;
		temp.clear();
		for (size_t i = 0; i != v.size(); ++i) {
			if (bitset[i]) {
				temp.push_back(v[i]);
			}
		}
		resultVec.push_back(temp);
	} while (next_permutation(bitset.begin(), bitset.end()));
}

/*
结果:Memory Limit Exceeded
得分:50 / 100
*/











#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;
const int maxh = 17;
const int lim = 100000;
const int mod = 1000000009;
typedef long long ll;

int n, m, k;

int cnt[maxn];

int cc[maxn][maxn];
int main()
{
	cc[0][0] = 1;
	for (int i = 1; i < maxn; i++)
	{
		cc[i][0] = 1;
		for (int j = 1; j <= i; j++)
		{
			cc[i][j] = (cc[i - 1][j - 1] + cc[i - 1][j]) % mod;
		}
	}
	cin >> n >> m >> k;
	int x;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		cnt[x % k]++;
	}
	int res = 0;
	for (int i = 0; i < k; i++)
	{
		if (cnt[i] >= m)
		{
			res = (res + cc[cnt[i]][m]) % mod;
		}
	}
	cout << res << endl;
}
