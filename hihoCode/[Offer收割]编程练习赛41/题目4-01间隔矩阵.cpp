/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定一个N × M的01矩阵，小Hi希望从中找到一个01间隔的子矩阵，并且子矩阵的面积越大越好。

例如对于

0101010

1000101

0101010

1010101

0101010

在右侧有一个5 × 4的01间隔子矩阵，在下方有一个3 × 7的01间隔子矩阵。

输入
第一行包含两个整数N和M。

以下N行M列包含一个N × M的01矩阵。
对于30%的数据，1 ≤ N, M ≤ 250
对于100%的数据，1 ≤ N, M ≤ 2000

输出
输出最大的01间隔子矩阵的面积。

样例输入
5 7
0101010
1000101
0101010
1010101
0101010
样例输出
21
*/

/*
Thank you for your hacking.
Hope you high rating.
*/
#include <bits/stdc++.h>

using namespace std;

#define pr(x) cerr << #x << " = " << x << endl;
#define bug cerr << "bugbug" << endl;
#define ppr(x, y) printf("(%d, %d)\n", x, y);
#define mst(a,b) memset(a,b,sizeof(a))
#define clr(a) mst(a,0)
#define sqr(a) ((a)*(a))
#define PCUT puts("\n---------------")


typedef complex<double> dcomplex;
typedef long long ll;
typedef double DBL;
typedef pair<int, int> P;
typedef unsigned int uint;
const double pi = acos(-1.0);
const double eps = 1e-12;
const int MOD = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int maxn = 2e3 + 4;
const int maxm = 1e3 + 4;
inline long long rule(long long x){ return (x %= MOD) += x < 0 ? MOD : 0; }


char s[maxn][maxn];
int cnt[maxn][maxn];
int main()
{
	int ik, i, j, k, kase;
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%s", s[i] + 1);
	for (int i = n; i > 0; --i)
		for (int j = m; j > 0; --j) {
			if (j == m) 
				cnt[i][j] = 1;
			else if (s[i][j] != s[i][j + 1]) 
				cnt[i][j] = cnt[i][j + 1] + 1;
			else 
				cnt[i][j] = 1;
		}
	int ans = 0;
	for (int i = 1; i <= m; ++i) {
		vector<P> v;
		for (int j = 1; j <= n; ++j) {
			if (j == 1 || s[j][i] == s[j - 1][i]) v.clear();
			int beg = j;
			while (v.size() != 0 && v.back().second >= cnt[j][i]){
				beg = v.back().first;
				v.pop_back();
			}
			v.push_back(P(beg, cnt[j][i]));
			int t = 0;
			for (int k = 0; k < v.size(); ++k)
				t = max(v[k].second*(j - v[k].first + 1), t);
			ans = max(ans, t);
			//			if (j == 3 && i == 1){
			//				for (int k = 0; k < v.size(); ++k)
			//					ppr(v[k].first, v[k].second);
			//			}
			//			cout << j << ' ' << i << ' ' << t <<  ' ' << v.size() << endl;
		}
	}
	//	while(true);
	cout << ans << endl;
	return 0;
}
