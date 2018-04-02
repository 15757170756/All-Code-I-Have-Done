/*
作者：vegetableB
链接：https ://
www.nowcoder.com/discuss/70299
来源：牛客网

两种操作：
1：m=s
s=s+s;
2:s = s+m;
已知s = 'a',m=s;
求s长度为n时最少需要几步操作。
*/

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
map<pair<int, int>, int > mp;
int main()
{
	int n;
	scanf("%d", &n);
	queue<pii> q;
	q.push(make_pair(1, 1));
	mp[make_pair(1, 1)] = 0;
	while (!q.empty())
	{
		pii pr = q.front(); q.pop();
		//        printf("%d %d\n",pr.first, pr.second);
		if (pr.first == n)
		{
			printf("%d\n", mp[pr]);
			exit(0);
		}
		pii t = pr;
		t.second = t.first; t.first *= 2;
		if (!mp.count(t))
		{
			q.push(t);
			mp[t] = mp[pr] + 1;
		}
		t = pr;
		t.first = t.first + t.second;
		if (!mp.count(t))
		{
			q.push(t);
			mp[t] = mp[pr] + 1;
		}
	}
	return 0;
}