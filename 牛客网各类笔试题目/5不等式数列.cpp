/*
时间限制：1秒

空间限制：32768K

度度熊最近对全排列特别感兴趣, 对于1到n的一个排列, 
度度熊发现可以在中间根据大小关系插入合适的大于和
小于符号(即 '>' 和 '<')使其成为一个合法的不等式数列。
但是现在度度熊手中只有k个小于符号即('<'')
和n-k-1个大于符号(即' > '),度度熊想知道对于1至n任意的
排列中有多少个排列可以使用这些符号使其为合法的不等式数列。 
输入描述:
输入包括一行, 包含两个整数n和k(k < n ≤ 1000)


输出描述 :
	 输出满足条件的排列数, 答案对2017取模。

 输入例子1 :
5 2

输出例子1 :
	  66
	*/

//自己写的程序
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int permutations(int n, int k)
{
	vector<int> v(n);
	for (int i = 0; i < n; ++i)
		v[i] = i + 1;
	vector<vector<int>> resultVec;
	sort(v.begin(), v.end());
	do {
		resultVec.push_back(v);
	} while (next_permutation(v.begin(), v.end()));

	int lessCnt, permutationCnt = 0;
	for (int i = 0; i < resultVec.size(); ++i) {
		vector<int> temp = resultVec[i];
		lessCnt = 0;
		for (int j = 0; j < temp.size() - 1; ++j) {
			if (temp[j] < temp[j + 1])
				++lessCnt;
		}
		if (lessCnt == k)
			++permutationCnt;
	}

	return permutationCnt;
}

int main()
{
	int n, k;
	cin >> n >> k;
	cout << permutations(n, k);

	return 0;
}

//您的代码已保存
//内存超限 : 您的程序使用了超过限制的内存
//	   case通过率为30.00%
//o(╥﹏╥)o

//看来稍微难一点的题目就一定要用到动态规划的


/*
dp[i][j] = (dp[i - 1][j - 1] * (i - j) + dp[i - 1][j] * (j + 1)) % 2017;
dp[i][j]表示有i个数字及j个小于号所能组成的数量(大于号数量当然是i - j - 1次，
	后面需要使用)
而加入第i + 1个数字时，分以下四种情况：
1.如果将i + 1插入当前序列的开头，即有了1 < 2，加入后成为3>1 < 2，
会发现等于同时加入了一个大于号！(此时可以无视1与2之间的关系，因为i + 1 > i)
2.如果将i + 1插入当前序列末尾, 即1 < 2变成了 1 < 2 < 3，
会发现等于同时加入了一个小于号！(此时可以无视1与2之间的关系，因为i + 1 > i)
3.如果将i + 1加入一个小于号之间，即已经有 1 < 2了，向中间加入3, 
会发现变成了1 < 3>2，等于同时加入了一个大于号！
4.如果将i + 1加入一个大于号中间，即有了2 > 1，变成了2 < 3>1，
等于同时加入了一个小于号！
综上所述，dp[i][j]等于以上四种情况之和：
dp[i - 1][j] 将i加在开头等于加入一个大于号，即要求i - 1个数时已经有了j个小于号
dp[i - 1][j - 1] 将i加在末尾等于加入一个小于号，
即要求i - 1个数时已经有了j - 1个小于号
dp[i - 1][j] * j 将i加在任意一个小于号之间，等于加入了一个大于号；
即要求i - 1个数时已经有了j个小于号，每个小于号都可以进行这样的一次插入
dp[i - 1][j - 1] * (i - j - 1) 将i加载任意一个大于号之间，
等于加入了一个小于号；即要求i - 1个数时有了j - 1个小于号，而此时共有
(i - 1) - (j - 1) - 1个大于号，每个大于号都要进行一次这样的操作合并同类项即为
dp[i][j] = (dp[i - 1][j - 1] * (i - j) + dp[i - 1][j] * (j + 1))
*/

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int dp[1001][1001];

int main()
{

	int n, k, d;
	scanf("%d%d", &n, &k);
	d = 0;
	memset(dp, 0, sizeof(dp));
	dp[1][0] = 1;
	for (int i = 2; i <= n; i++)
		for (int j = 0; j < n; j++) {
			if (j == 0)
				dp[i][j] = 1;
			else
				dp[i][j] = (dp[i - 1][j - 1] * (i - j) + dp[i - 1][j] * (j + 1)) % 2017;

		}
	printf("%d\n", dp[n][k]);

	return 0;
}