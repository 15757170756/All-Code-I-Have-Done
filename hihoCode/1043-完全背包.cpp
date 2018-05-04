/*
#1043 : 完全背包
时间限制:20000ms
单点时限:1000ms
内存限制:256MB
描述
且说之前的故事里，小Hi和小Ho费劲心思终于拿到了茫茫多的奖券！而现在，终于到了小Ho领取奖励的时刻了！

等等，这段故事为何似曾相识？这就要从平行宇宙理论说起了………总而言之，在另一个宇宙中，
小Ho面临的问题发生了细微的变化！

小Ho现在手上有M张奖券，而奖品区有N种奖品，分别标号为1到N，
其中第i种奖品需要need(i)张奖券进行兑换，并且可以兑换无数次，
为了使得辛苦得到的奖券不白白浪费，小Ho给每件奖品都评了分
，其中第i件奖品的评分值为value(i),表示他对这件奖品的喜好值。
现在他想知道，凭借他手上的这些奖券，可以换到哪些奖品，使得这些奖品的喜好值之和能够最大。

提示一： 切，不就是0~1变成了0~K么

提示二：强迫症患者总是会将状态转移方程优化一遍又一遍

提示三：同样不要忘了优化空间哦！

输入
每个测试点（输入文件）有且仅有一组测试数据。

每组测试数据的第一行为两个正整数N和M,表示奖品的种数，以及小Ho手中的奖券数。

接下来的n行描述每一行描述一种奖品，其中第i行为两个整数need(i)和value(i)，意义如前文所述。

测试数据保证

对于100%的数据，N的值不超过500，M的值不超过10^5

对于100%的数据，need(i)不超过2*10^5, value(i)不超过10^3

输出
对于每组测试数据，输出一个整数Ans，表示小Ho可以获得的总喜好值。

样例输入
5 1000
144 990
487 436
210 673
567 58
1056 897
样例输出
5940
*/


/*
因为我们要把当前物品i放入包内，因为物品i可以无限使用，
所以要用f[i][j-c[i]]；
如果我们用的是f[i-1][j-c[i]]，f[i-1][j-c[i]]的意思是说，
我们只有一件当前物品i，
所以我们在放入物品i的时候需要考虑到第i-1个物品的价值(f[i-1][j-c[i]])；
但是现在我们有无限件当前物品i，我们不用再考虑第i-1个物品了，
我们所要考虑的是在当前容量下是否再装入一个物品i，
而[j-c[i]]的意思是指要确保f[i][j]至少有一件第i件物品，
所以要预留c[i]的空间来存放一件第i种物品。总而言之，如果放当前物品i的话，
它的状态就是它自己"i"，而不是上一个"i-1"。
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace::std;

int knapsack(int Weight, vector<int> &weights,
	vector<int> &values, int num)
{
	vector<vector<int>> dp(num + 1, vector<int>(Weight + 1));
	for (int i = 0; i <= num; ++i) {
		for (int w = 0; w <= Weight; ++w) {
			if (i == 0 || w == 0)
				dp[i][w] == 0;
			else if (weights[i - 1] <= w)
				dp[i][w] = max(dp[i][w - weights[i - 1]] + values[i - 1],
				dp[i - 1][w]);
			else
				dp[i][w] = dp[i - 1][w];
		}
	}
	int maxValue = dp[num][Weight];
	return maxValue;
}

int main()
{
	ifstream in("input.txt");
	int n, Weight;
	in >> n >> Weight;
	vector<int> value, wt;
	for (int i = 0; i < n; ++i) {
		int tempValue, tempWt;
		in >> tempWt >> tempValue;
		wt.push_back(tempWt);
		value.push_back(tempValue);
	}

	//int n, Weight;
	//cin >> n >> Weight;
	//vector<int> value, wt;
	//for (int i = 0; i < n; ++i) {
	//	int tempValue, tempWt;
	//	cin >> tempWt >> tempValue;
	//	value.push_back(tempValue);
	//	wt.push_back(tempWt);
	//}

	cout << knapsack(Weight, wt, value, n) << endl;

	return 0;
}