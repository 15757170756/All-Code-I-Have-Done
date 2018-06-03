/*
题目3 : 质数
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
众所周知，一个正整数x一定可以写成若干个质数的乘积，
我们称一个数是好的数，当且仅当他可以写成质数个质数的乘积。

现在给定l,r，求[l,r]内有几个好的数。

输入
第一行两个正整数l,r，满足1 ≤ l ≤ r ≤ 109，且0 ≤ r-l ≤ 106。

输出
输出[l,r]内有几个好的数。

样例解释
4=2*2，所以4是好的数。

6=2*3，所以6是好的数。

8=2*2*2，所以8是好的数。

9=3*3，所以9是好的数。

样例输入
1 9
样例输出
4
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

void prim2(int m, vector<int>& resultVec)
{
	int n = 2;
	while (m > n) {
		while (m % n != 0)
			++n;
		m /= n;
		resultVec.push_back(n);
	}
}

bool isPrime(int n)
{
	int k = (int)sqrt((double)n);
	if (n == 1)
		return false;
	if (n == 2)
		return true;
	int i;
	for (i = 2; i <= k; ++i) {
		if (n % i == 0)
			return false;
	}
	if (i > k)
		return true;
	else
		return false;
}

int main(int argc, char* argv[])
{
	int l, r;
	cin >> l >> r;
	int cnt = 0;
	for (int i = l; i <= r; ++i) {
		vector<int> vec;
		prim2(i, vec);
		if (isPrime(vec.size()))
			++cnt;
	}
	cout << cnt << endl;
}

/*
结果:Time Limit Exceeded
得分:0 / 100

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

int n, p[41111], v[41111], a[1000111], ans, ct[1000111], l, r;

void work() {
	scanf("%d%d", &l, &r);
	for (int i = l; i <= r; ++i) {
		a[i - l] = i;
	}

	v[1] = v[0] = true;
	for (int i = 2; i <= 40000; ++i) {
		if (!v[i]) {
			p[n++] = i;
			for (int j = i + i; j <= 40000; j += i) {
				v[j] = true;
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		int x = p[i];
		int j = l / x;
		if (l % x != 0) ++j;
		j *= x;
		for (; j <= r; j += x) {
			while (a[j - l] % x == 0) {
				a[j - l] /= x;
				ct[j - l] += 1;
			}
		}
	}
	for (int i = l; i <= r; ++i) {
		if (a[i - l] != 1) {
			ct[i - l] += 1;
		}
		if (!v[ct[i - l]]) ans += 1;
	}

	printf("%d\n", ans);
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
