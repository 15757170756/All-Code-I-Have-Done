/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定n个数，令符号[l, r, t]表示第l个数到第r个数中第t大的值。

对于给定的len、y和k，求多重集{[l,r,(r-l+1)/len*y] | (r-l+1) mod len=0}中的第k大值

具体来说，这个多重集包含：

每个长度是len的区间中第y大的值，

每个长度是2len的区间中第2y大的值，

每个长度是3len的区间中第3y大的值，

……

以此类推。

对于下面的样例，这个多重集是{2, 3, 3, 4}

输入
第一行四个数，n, len, y, k (n ≤ 100000, y ≤ len ≤ n, k ≤ 长度为len倍数的区间个数)

第二行n个，每个数 ≤ n

输出
输出一个数表示答案

样例输入
4 2 1 3
2 1 3 4
样例输出
3
*/



#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <set>

using namespace std;

const int maxn = 1e5 + 10, mod = 1e9 + 7, inf = 0x3f3f3f3f;
int n, m, k, t, a[maxn];
priority_queue<int, vector<int>, greater<int> >pq;
int main()
{
	int i, j;
	int len, y;
	long long k;
	scanf("%d%d%d%lld", &n, &len, &y, &k);
	for (i = 1; i <= n; i++)scanf("%d", &a[i]);
	for (int i = len, cnt = y; i <= n; i += len, cnt += y)
	{
		multiset<int>tmp1, tmp2;
		for (j = 1; j <= i; j++)
		{
			tmp1.insert(a[j]);
			if (tmp1.size() > cnt)
			{
				tmp2.insert(*tmp1.begin());
				tmp1.erase(tmp1.begin());
			}
		}
		for (j = i + 1; j <= n + 1; j++)
		{
			pq.push(*tmp1.begin());
			if (pq.size() > k)pq.pop();
			if (tmp2.find(a[j - i]) != tmp2.end())
			{
				tmp2.erase(tmp2.lower_bound(a[j - i]));
			}
			else
			{
				tmp1.erase(tmp1.lower_bound(a[j - i]));
				if (tmp2.size() > 0)
				{
					tmp1.insert(*--tmp2.end());
					tmp2.erase(--tmp2.end());
				}
			}
			tmp1.insert(a[j]);
			if (tmp1.size() > cnt)
			{
				tmp2.insert(*tmp1.begin());
				tmp1.erase(tmp1.begin());
			}
		}
	}
	printf("%d\n", pq.top());
	return 0;
}

