/*
定义两个字符串变量：s和m，再定义两种操作，
　
 第一种操作：

 m = s;
 s = s + s;
 第二种操作：

 s = s + m;
 　
  假设s, m初始化如下：

  s = "a";
  m = s;
  求最小的操作步骤数，可以将s拼接到长度等于n

  输入描述：
  一个整数n，表明我们需要得到s字符长度，0<n<10000
  输出描述：
  一个整数，表明总共操作次数

  样例
  in:
  6
  out:
  3
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









#include <bits/stdc++.h>

using namespace std;

struct Node {
	int s, m, cnt;
	Node() {}
	Node(int s, int m, int cnt) : s(s), m(m), cnt(cnt) {}
};

#define MAX_SIZE 10000

int main()
{
	vector<int> ans(MAX_SIZE, -1);
	queue<Node> que;
	que.emplace(1, 1, 0);
	while (!que.empty()) {
		auto now = que.front();
		que.pop();

		if (ans[now.s] == -1)
			ans[now.s] = now.cnt;

		if (now.s * 2 < MAX_SIZE)
			que.emplace(now.s * 2, now.s, now.cnt + 1);
		if (now.s + now.m < MAX_SIZE)
			que.emplace(now.s + now.m, now.m, now.cnt + 1);
	}
	for (int n; cin >> n; cout << ans[n] << endl) {}
	return 0;
}