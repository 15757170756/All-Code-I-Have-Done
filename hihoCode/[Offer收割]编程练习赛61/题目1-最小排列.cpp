/*
题目1 : 最小排列
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定一个长度为m的序列b[1..m]，再给定一个n，
求一个字典序最小的1~n的排列A，使得b是A的子序列。

一个序列a是序列c的子序列，当且仅当a可以由c中删除任意数量的数获得。

输入
第一行两个正整数n,m. 1 ≤ m ≤ n ≤ 105

接下来m行，第i行一个数表示b[i]

输出
输出n行，第i行一个数表示A[i]

保证答案一定存在

样例输入
5 3
1
4
2
样例输出
1
3
4
2
5
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
#include <cstring>

using namespace std;

const int maxn = 1e5 + 1;
int b[maxn];
int A[maxn];
int n, m;
map<int, int> mp;
set<int> st;
vector<int> vec;

int main(int argc, char* argv[])
{
	//freopen("input.txt", "r", stdin);
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int temp;
		cin >> temp;
		vec.push_back(temp);
	}

	for (int i = 1; i <= n; ++i) {
		if (find(vec.begin(), vec.end(), i) == vec.end()) {
			for (int j = 0; j < vec.size(); ++j) {
				if (vec[j] - i == 1) {
					vec.insert(vec.begin() + j, i);
					break;
				}
				if (i == n) {
					vec.push_back(n);
					break;
				}
			}
		}
	}
	for (int e : vec)
		cout << e << endl;
}

/*
结果:Wrong Answer
得分 : 0 / 100
*/









#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <ctime>
#include <string>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int a[101111], v[101111];

void work() {
	int n, m;
	scanf("%d%d", &n, &m);
	int j = 1;
	for (int i = 0; i < m; ++i) {
		scanf("%d", &a[i]);
		v[a[i]] = true;
	}
	for (int i = 0; i < m; ++i) {
		while (j <= a[i]) {
			if (!v[j]) printf("%d\n", j);
			++j;
		}
		printf("%d\n", a[i]);
	}
	while (j <= n) {
		if (!v[j]) {
			printf("%d\n", j);
		}
		++j;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	// freopen("input.txt", "r", stdin);
	int t = clock();
#endif
	int TestCase = 1, Case = 0;
	//scanf("%d", &TestCase);
	while (TestCase--) {
		Case++;
		//printf("Case #%d: ", Case);
		work();
	}
#ifndef ONLINE_JUDGE
	cerr << "time = " << clock() - t << " ms" << endl;
#endif
	return 0;
}
