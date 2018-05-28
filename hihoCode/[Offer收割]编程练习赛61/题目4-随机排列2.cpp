/*
题目4 : 随机排列2
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
一个长度为n的排列p[1..n]的价值是这样定义的：一开始你有一个数x，x的值一开始为0，
然后对于1 ≤ i ≤ n，如果p[i] > x，则令x=p[i]；排列p[1..n]的价值就是x的值的改变次数。

求对于所有长度为n的[1,2…n]的排列，他们的价值之和，答案对109+7取模。

输入
第一行一个正整数n.  (1 ≤ n ≤ 106)。

输出
输出一个非负整数，表示答案。

样例解释
对于排列[1,2,3]，x的值会依次变成1,2,3，所以价值为3.

对于排列[1,3,2]，x的值会依次变成1,3，所以价值为2.

对于排列[2,1,3]，x的值会依次变成2,3，所以价值为2.

对于排列[2,3,1]，x的值会依次变成2,3，所以价值为2.

对于排列[3,1,2]，x的值会依次变成3，所以价值为1.

对于排列[3,2,1]，x的值会依次变成3，所以价值为1.

所以所有长度为 3 的排列的价值之和为11.

样例输入
3
样例输出
11
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

int n;
long long b[1000111], MOD = 1000000007;


void work() {
	scanf("%d", &n);
	b[1] = 1;
	b[2] = 3;
	for (int i = 3; i <= n; ++i) {
		b[i] = b[i - 1] * (i * 2 - 1) % MOD - b[i - 2] * (i - 1) % MOD*(i - 1) % MOD;
		b[i] = (b[i] % MOD + MOD) % MOD;
	}
	printf("%lld\n", b[n]);
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







#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
const long long M = 1000000007;
long long f[1000001] = { 0 };
int main()
{
	int n;
	cin >> n;
	f[1] = 1;
	long long p = 1;
	for (int i = 2; i <= n; i++) {
		p = (p*(i - 1)) % M;
		f[i] = (p + f[i - 1] * i) % M;
	}
	cout << f[n] << endl;
	cin.get();
	cin.ignore();
	return 0;
}