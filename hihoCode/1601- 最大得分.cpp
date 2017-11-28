/*时间限制:10000ms
单点时限 : 1000ms
内存限制 : 256MB
描述
小Hi和小Ho在玩一个游戏。给定一个数组A = [A1, A2, ... AN]，小Hi可以指定M个不同的值S1，S2, S3 ... SM，
这样他的总得分是 ΣSi × count(Si)。（count(Si)是数组中与Si相等的元素的个数)。
为了增加难度，小Ho要求小Hi选择的S1..SM其中任意两个Si和Sj都满足 | Si - Sj | > 1。
你能帮助小Hi算出他最大得分是多少吗？
输入
第一行包含两个整数N和M。
第二行包含N个整数A1, A2, ... AN。
对于30%的数据，1 ≤ M ≤ N ≤ 10
对于100%的数据，1 ≤ M ≤ N ≤ 1000 1 ≤ Ai ≤ 100000
输出
最大得分
样例输入
5 2
1 2 1 2 3
样例输出
5
*/

/*
自己写的
超时了
*/


#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace::std;

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
				//cout << v[i] << " ";
			}
		}
		sort(temp.begin(), temp.end());
		int count = 0;
		for (int i = 0; i < temp.size() - 1; ++i) {
			if (abs(temp[i] - temp[i + 1]) > 1)
				++count;
		}
		if (count == temp.size() - 1)
			resultVec.push_back(temp);
		//cout << endl;
		//for (int i = 0; i < bitset.size(); ++i)
		//	cout << bitset[i] << " ";
		//cout << endl;
	} while (next_permutation(bitset.begin(), bitset.end()));

	auto last = unique(resultVec.begin(), resultVec.end());
	resultVec.erase(last, resultVec.end());
}


int main()
{
	int N, M;
	cin >> N >> M;
	vector<int> v;
	int temp;
	for (int i = 0; i < N; ++i) {
		cin >> temp;
		v.push_back(temp);
	}
	vector<vector<int>> combiResultVec;
	combinations(v, M, combiResultVec);
	for (int i = 0; i < combiResultVec.size(); ++i) {
		//cout << i + 1 << ":\t";
		vector<int> temp = combiResultVec[i];
		for (int j = 0; j < temp.size(); ++j) {
			//cout << temp[j] << " ";
		}
		//cout << endl;
	}

	int currSum = 0;
	int sum = 0;
	for (int i = 0; i < combiResultVec.size(); ++i) {
		vector<int> temp = combiResultVec[i];
		currSum = 0;
		for (int j = 0; j < temp.size(); ++j) {
			int countNum = std::count(v.begin(), v.end(), temp[j]);
			//cout << countNum << endl;
			currSum += temp[j] * countNum;
		}
		if (currSum > sum)
			sum = currSum;
	}

	cout << sum << endl;
}



/*
网上查的
AC的
*/
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<memory>
#include<cstring>
using namespace std;
const int maxn = 1010;
long long  a[maxn], b[maxn], c[maxn];
long long  dp[maxn][maxn], Max;
int main()
{
	long long  n, i, j, k, m, cnt = 0;
	scanf("%lld%lld", &n, &m);
	for (i = 1; i <= n; i++) scanf("%lld", &a[i]);
	sort(a + 1, a + n + 1);
	for (i = 1; i <= n; i++){
		if (a[i] != a[i - 1]) {
			b[++cnt] = a[i];
			c[cnt] = 1;
		}
		else  c[cnt]++;
	}
	memset(dp, -1, sizeof(dp));
	for (i = 0; i <= cnt; i++) dp[i][0] = 0;
	dp[1][1] = b[1] * c[1];
	Max = dp[1][1];
	for (i = 2; i <= cnt; i++)
		for (j = 1; j <= m; j++){
			dp[i][j] = dp[i - 1][j];//不用第i个
			if (b[i] - b[i - 1] > 1) 
				dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + b[i] * c[i]);//要第i个，前一个也要
			else
				dp[i][j] = max(dp[i][j], dp[i - 2][j - 1] + b[i] * c[i]);//要第i个，而前一个不要
			Max = max(Max, dp[i][j]);
		}
	printf("%lld\n", Max);
	return 0;
}