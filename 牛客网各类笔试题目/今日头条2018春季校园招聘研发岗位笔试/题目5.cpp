/*
第五题：
题目：
小T最近迷上一款跳板小游戏
已知空中有N个高度互不相同的跳板，
小T刚开始在高度为0的地方，
每次跳跃可以选择与自己高度绝对值小于等于H的跳板，
跳跃过后到达以跳板为轴的镜像位置，
问小T在最多跳K次的情况下最高能跳多高？(任意时刻，高度不能为负)

输入描述：
第一行三个整数N，K，H
以下N行，每行一个整数Ti，表示第i个跳板的离地高度

输出描述：
一个整数，表示最高能跳到的高度。

样例
in:
3 3 2
1
3
6
out:
8
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
	for (int n, k, h; cin >> n >> k >> h;) {
		vector<int> height;
		for (int i = 0, x; i < n; height.push_back((cin >> x, x)), ++i) {}

		int TOP = *max_element(height.begin(), height.end()) + h + 1;
		vector<bool> used(TOP, false);
		queue<pair<int, int> > que;
		used[0] = true;
		que.emplace(0, 0);
		int ans = 0;
		for (; !que.empty();) {
			auto now = que.front();
			que.pop();

			ans = max(now.first, ans);

			for (auto it = height.begin(); it != height.end(); ++it) {
				if (abs(now.first - *it) <= h &&
					(2 * *it - now.first > 0 && 2 * *it - now.first < TOP) &&
					!used[2 * *it - now.first] && now.second < k) {
					used[2 * *it - now.first] = true;
					que.emplace(2 * *it - now.first, now.second + 1);
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}