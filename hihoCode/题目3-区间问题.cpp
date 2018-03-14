/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定N个区间[Ai, Bi]，请你找到包含元素最少的整数集合S，使得每个区间都至少有两个整数在S中。

例如给定三个区间[1, 3], [1, 4], [2, 5]，则S={2, 3}。

输入
第一行包含一个整数N。

以下N行每行包含两个整数Ai, Bi。

对于30%的数据，1 ≤ N ≤ 1000

对于100%的数据， 1 ≤ N ≤ 100000 1 ≤ Ai < Bi ≤ 1000000

输出
输出一个整数代表S的大小。

样例输入
3
1 3
1 4
2 5
样例输出
2
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
const int maxn = 1e5 + 4;
const int maxm = 1e6 + 4;
inline long long rule(long long x){ return (x %= MOD) += x < 0 ? MOD : 0; }

struct Seg{
	int l, r;
	bool operator < (const Seg& rhs) const{
		if (r != rhs.r) return r < rhs.r;
		else return l > rhs.l;
	}
}seg[maxn];
int n;
bool in[maxm];
int b[maxm];
void add(int pos){
	for (int i = pos; i < maxm; i += i&(-i))
		b[i]++;
}
int query(int pos){
	int ret = 0;
	for (int i = pos; i > 0; i -= i&(-i))
		ret += b[i];
	return ret;
}
int sum(int l, int r){
	return query(r) - query(l - 1);
}
int main(){
	int ik, i, j, k, kase;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i){
		scanf("%d%d", &seg[i].l, &seg[i].r);
	}
	sort(seg, seg + n);
	int ans = 0;
	for (int i = 0; i < n; ++i){
		int j = seg[i].r;
		while (sum(seg[i].l, seg[i].r) < 2){
			while (in[j]) j--;
			in[j] = true;
			add(j);
		}
	}
	cout << sum(1, 1000000) << endl;
	return 0;
}
