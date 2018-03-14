/*
题目1 : H星人社交网络
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
Handbook是H星人的一家社交网络。Handbook中共有N名用户，其中第i名用户的年龄是Ai。

根据H星人的文化传统，用户i不会给用户j发送好友请求当且仅当：

1. Aj < 1/8 * Ai + 8 或者

2. Aj > 8 * Ai + 8 或者

3. Ai < 88888 且 Aj > 88888

其他情况用户i都会给用户j发送好友请求。

你能求出Handbook总计会有多少好友请求吗？

输入
第一行一个整数N。

第二行N个整数A1, A2, ... AN。

对于30%的数据，1 ≤ N ≤ 100

对于100%的数据，1 ≤ N ≤ 100000, 1 ≤ Ai ≤ 100000

输出
输出Handbook中好友请求的总数

样例输入
2
10 80
样例输出
1
*/



#include <iostream>
#include <vector>

using namespace::std;

int friendRequest(vector<int> &ages);
bool isFriendRequest(int Ai, int Aj);

int main()
{
	int usersNum, userAge;
	cin >> usersNum;
	vector<int> ages;
	for (int i = 0; i < usersNum; ++i) {
		cin >> userAge;
		ages.push_back(userAge);
	}


	int result = friendRequest(ages);
	cout << result;

	return 0;
}

int friendRequest(vector<int> &ages)
{
	int numRequests = 0;
	for (int i = 0; i < ages.size(); ++i) {
		for (int j = 0; j < ages.size(); ++j) {
			if ((i != j) && (isFriendRequest(ages[i], ages[j])))
				numRequests++;
		}
	}

	return numRequests;
}

bool isFriendRequest(int Ai, int Aj)
{
	return (!((Aj < (1.0 / 8) * Ai + 8) ||
		(Aj > 8 * Ai + 8) ||
		((Ai < 88888) && (Aj > 88888))));
}

/*
结果:Time Limit Exceeded
得分:30 / 100
*/










#include <map>
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

long long ans;
int n, a[101111], head, tail;

void work() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	sort(a, a + n);
	for (int i = 0; i < n; ++i) {
		int l = a[i] / 8 + 8;
		if (a[i] % 8) l++;
		int r = a[i] * 8 + 8;
		if (a[i] < 88888) r = min(r, 88888);
		int ll = lower_bound(a, a + n, l) - a;
		int rr = upper_bound(a, a + n, r) - a;
		ans += rr - ll;
		if (ll <= i && i < rr) ans--;
	}
	printf("%lld\n", ans);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	int TestCase = 1;
	//scanf("%d", &TestCase);
	while (TestCase--) {
		work();
	}
	return 0;
}
