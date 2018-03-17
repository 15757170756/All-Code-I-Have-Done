/*
时间限制:10000ms
单点时限 : 1000ms
内存限制 : 256MB
描述
小Hi和小Ho在玩一个游戏。给定一个数组A = [A1, A2, ... AN]，
小Hi可以指定M个不同的值S1，S2, S3 ... SM，
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
题解：
先把输入的内容hash一下到一个vector里，
这个vector里每个点存一下Ai的值和出现的次数，
是按照Ai的值大小排序的。
然后对于每个Vector里的结点，想象成一个背包。
dp[i][j]是代表从前i个背包里取j个所能拿到的最大值
因为|Si-Sj| > 1，所以如果前一个背包和当前的背包值的大小刚好差了1，
那么就要跳过上一个背包来更新当前的值。
不然，就直接更新就好。
*/

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
using namespace std;
int T;
int x, y, a, b;
int N, M;
int A[1009];
int V[100009];
int dp[1009][1009];//前i个包里拿走j个
struct node{
	int V, C;
	node(){}
	node(int v, int c){
		V = v;
		C = c;
	}
};
int main(){
	cin >> N >> M;
	memset(V, 0, sizeof(V));
	int maxV = -1;
	for (int i = 0; i < N; i++){
		scanf("%d", &A[i]);
		V[A[i]]++;
		maxV = max(maxV, A[i]);
	}
	vector<node> nums;
	nums.push_back(node(0, 0));
	for (int i = 1; i <= maxV; i++){
		if (V[i] != 0)
			nums.push_back(node(i, V[i]));
	}
	int numOfBags = nums.size() - 1;
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= M; i++)
		dp[1][i] = nums[1].V*nums[1].C;

	for (int i = 2; i <= numOfBags; i++){
		for (int j = 1; j <= M; j++){
			if (nums[i].V - nums[i - 1].V>1){
				dp[i][j] = max(dp[i - 1][j - 1] + nums[i].V*nums[i].C, dp[i - 1][j]);
			}
			else{
				dp[i][j] = max(dp[i - 2][j - 1] + nums[i].V*nums[i].C, dp[i - 1][j]);
			}
		}
	}

	cout << dp[numOfBags][M] << endl;



	return 0;
}



//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永无BUG
//
//
//















#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
int a[1009];
int num[1009], t;
int dp[1009][1009];
int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i){
		scanf("%d", &a[i]);
	}
	sort(a, a + n);
	t = 0;
	for (int i = 0; i < n; ++i){
		if (a[i] == a[t]){
			++num[t];
		}
		else{
			a[++t] = a[i];
			num[t] = 1;
		}
	}
	++t;
	dp[0][1] = a[0] * num[0];
	for (int i = 1; i <= m; ++i)
		dp[0][i] = dp[0][1];

	dp[1][1] = max(a[0] * num[0], a[1] * num[1]);
	if (a[1] > a[0] + 1)
		dp[1][2] = a[0] * num[0] + a[1] * num[1];
	for (int i = 1; i <= m; ++i)
		dp[1][i] = max(dp[1][i], dp[1][i - 1]);

	for (int i = 2; i < t; ++i) {
		int j = a[i] > a[i - 1] + 1 ? i - 1 : i - 2;
		for (int k = 1; k <= m; ++k) {
			dp[i][k] = max(dp[i - 1][k], dp[j][k - 1] + a[i] * num[i]);
		}
	}
	printf("%d\n", dp[t - 1][m]);
	return 0;
}
