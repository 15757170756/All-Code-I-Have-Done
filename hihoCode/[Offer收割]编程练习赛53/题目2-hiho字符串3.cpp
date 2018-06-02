/*
题目2 : hiho字符串3
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
我们定义第一代hiho字符串是"h"。

第N代hiho字符串是由第N-1代hiho字符串变化得到，
规则是在每一个h后插入i，i后插入o，o后插入h。

例如第二、三、四代hiho字符串分别是： "hi"、"hiio"和"hiioiooh"。

给定K，请你计算第100代hiho字符串中的第K个字符是什么。

输入
第一行包含一个整数T，代表测试数据的组数。 (1 ≤ T ≤ 10)

以下T行每行包含一个整数K。

对于50%的数据，1 ≤ K ≤ 1000000

对于100%的数据， 1 ≤ K ≤ 1000000000000000

输出
对于每组数据，输出一行，包含一个字符代表答案。

样例输入
2
3
7
样例输出
i
o
*/



#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
char dfs(ll k, int x = 100){
	if (x == 1 || k == 0) return 'h';
	if (k & 1){
		char c = dfs(k / 2, x - 1);
		if (c == 'h') return 'i';
		if (c == 'i') return 'o';
		if (c == 'o') return 'h';
	}
	return dfs(k / 2, x - 1);
}
int main(){
	//freopen("../input.txt", "r", stdin);
	int t; cin >> t;
	while (t--){
		ll k; cin >> k;
		cout << dfs(k - 1) << endl;
	}
	return 0;
}











#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF = 1e18;
// 0:h, 1:i, 2:o
LL dp[3][111];
char c[] = { 'h', 'i', 'o' };

int cal(LL k, int now, int step) {
	if (step == 0) {
		return now;
	}
	if (dp[now][step - 1] >= k) return cal(k, now, step - 1);
	return cal(k - dp[now][step - 1], (now + 1) % 3, step - 1);
}

int main(){
	dp[0][0] = dp[1][0] = dp[2][0] = 1;
	for (int i = 1; i <= 100; i++)
	{
		dp[0][i] = min(INF, dp[0][i - 1] + dp[1][i - 1]);
		dp[1][i] = min(INF, dp[1][i - 1] + dp[2][i - 1]);
		dp[2][i] = min(INF, dp[2][i - 1] + dp[1][i - 1]);
	}
	int T;
	scanf("%d", &T);
	while (T--){
		LL k;
		cin >> k;
		cout << c[cal(k, 0, 99)] << endl;
	}
	return 0;
}