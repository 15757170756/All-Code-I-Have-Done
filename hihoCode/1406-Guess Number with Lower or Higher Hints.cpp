/*
题目1 : Guess Number with Lower or Higher Hints
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
There is a game about guessing number between 1 and N. 
This game is played by two people A and B. 
When A guesses a number(e.g. 5), 
he needs to pay that amount of dollars($5). 
Then B will give a hint whether A's guess is lower, 
higher or correct. B will choose the hint that forces to 
gain maximal amount of earning as long as it's not conlict with previous hints.

Assume they are both smart enough. 
What is the minimal amount that A needs to pay to finish this game?
 That is, there is only one number left and A will surely guess it right. 
 Careful: B does not have a fixed number in mind.  

输入
An integer N. (1 <= N <= 200)

输出
The minimal amount A needs to pay.

样例输入
5
样例输出
6
*/



//解答
/*
hiho一下206周《Guess Number with Lower or Higher Hints》分析
0
0
《Guess Number with Lower or Higher Hints》题目分析
本题是一道类似“石子合并”的动态规划题目。

我们用f[l][r]表示A从[l, r]的范围中猜中B想的数，需要支付的最小的代价。

面对范围[l, r]，A显然可以猜[l, r]的任意一个数，因为A足够聪明，所以他会选择其中代价最小的方案。

假设A猜的是k，那么他首先要支付$k。这时对于B，他显然不会说k就是答案(除非l=r=k)。
B为了让自己的收益最大，会考虑f[l][k-1]和f[k+1][r]哪个比较大。

如果前者比较大，B就会说A猜大了，从而让A从[l, k-1]的范围再猜，
代价是f[l][k-1]；反之B就会说A猜小了，让A从[k+1, r]的范围再猜，代价是f[k+1][r]。

总之，如果A猜k，那么他需要支付的代价是k + max{f[l][k-1], f[k+1][r]}。

因为A足够聪明，所以他会选择其中代价最小的方案。
也就是f[l][r] = min{k + max{f[l][k-1], f[k+1][r]} | k = l, l+1, ... r}。

于是我们按照以上转移方程进行动态规划即可。最后f[1][n]就是答案。

参考代码：

int main() {
        int n;
        cin >> n;

        vector<vector<int> > f(n + 1, vector<int>(n + 1, 0));
        for (int l = n; l > 0; l--)
                for (int r = l + 1; r <= n; r ++) {
                        f[l][r] = MAXINT;
                        for (int k = l; k <= r; k++) {
                                int s = 0;
                                if (k > l) s = max(s, f[l][k - 1]);
                                if (k < r) s = max(s, f[k + 1][r]);
                                f[l][r] = min(f[l][r], s + k);
                        }
                }
        cout << f[1][n] << endl;
        return 0;
}
*/


#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int main()
{
	int n;
	cin >> n;

	vector<vector<int> > f(n + 1, vector<int>(n + 1, 0));
	for (int l = n; l > 0; l--)
		for (int r = l + 1; r <= n; r++) {
			f[l][r] = INT_MAX;
			for (int k = l; k <= r; k++) {
				int s = 0;
				if (k > l) s = max(s, f[l][k - 1]);
				if (k < r) s = max(s, f[k + 1][r]);
				f[l][r] = min(f[l][r], s + k);
			}
		}

	cout << f[1][n] << endl;
	return 0;
}

/*
结果:Accepted 
得分:100 / 100
*/