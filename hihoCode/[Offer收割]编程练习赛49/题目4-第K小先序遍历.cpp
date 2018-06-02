/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
有一棵包含N个节点的二叉树，节点编号是1~N。

现在我们知道它的中序遍历结果A1, A2, ... AN。

只有中序遍历显然不能确定一棵二叉树的形态，可能有很多棵不同的二叉树符合给定的中序遍历。

那么你能从中找出先序遍历结果字典序第K小的二叉树吗？

设先序遍历结果是P1, P2, ... PN。字典序最小指首先P1应尽量小，其次P2尽量小，再次P3尽量小…… 以此类推。

输入
第一行包含两个整数N和K。

以下N行每行包含一个整数Ai。

对于30%的数据，1 ≤ N ≤ 12

对于100%的数据，1 ≤ N ≤ 30 1 ≤ K ≤ 合法的二叉树总数 1 ≤ Ai ≤ N

输出
输出N行，依次是P1, P2, ... PN。代表第K小的先序遍历结果。

样例输入
5 2
5
4
1
3
2
样例输出
1
4
5
3
2
*/

#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
ll c[31], k;
int a[31], n;
void dfs(int l, int r, ll k)
{
	if (l > r) return;
	vector<pii> v;
	for (int i = l; i <= r; i++) 
		v.push_back(pii(a[i], i));
	sort(v.begin(), v.end());
	ll tmp = 0, newk = 0;
	int i = 0;
	while (tmp < k)
	{
		int pos = v[i++].second - l + 1;
		newk = k - tmp;
		tmp += c[pos - 1] * c[v.size() - pos];
	}
	int root = v[i - 1].second;
	cout << a[root] << endl;
	ll lc = c[root - l], rc = c[r - root];
	ll lk = (newk + rc - 1) / rc;
	ll rk = (newk % rc == 0 ? rc : newk % rc);
	dfs(l, root - 1, lk); dfs(root + 1, r, rk);
}
int main()
{
	c[0] = c[1] = 1;
	for (int i = 2; i <= 30; i++)
	{
		for (int j = 0; j < i; j++)
		{
			c[i] += c[j] * c[i - j - 1];
		}
	}
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	dfs(1, n, k);
	return 0;
}

/*
结果:Accepted
*/





#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int MAXN = 31;
int a[MAXN], tmp[MAXN], rk[MAXN];
ll f[MAXN], k;

vector<int> ans;

void construct(int l, int r, ll c) {
	if (l > r) return;
	int n = r - l + 1;
	memcpy(tmp, a + l, n * sizeof(int));
	sort(tmp, tmp + n);
	for (int i = l; i <= r; i++) {
		int r = lower_bound(tmp, tmp + n, a[i]) - tmp + 1;
		rk[r] = i;
	}
	int root = -1;
	for (int i = 1; i <= n; i++) {
		int pos = rk[i];
		ll cnt = f[pos - l] * f[r - pos] * c;
		if (cnt >= k) {
			root = pos;
			break;
		}
		k -= cnt;
	}
	ans.push_back(a[root]);
	construct(l, root - 1, c * f[r - root]);
	construct(root + 1, r, c);
}

int main() {
	ios::sync_with_stdio(false);
	f[0] = 1;
	for (int i = 1; i <= 30; i++)
		for (int j = 1; j <= i; j++) f[i] += f[j - 1] * f[i - j];
	int n;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	construct(1, n, 1);
	for (auto i : ans) cout << i << endl;
	return 0;
}