/*
原题链接：http://poj.org/problem?id=3278

算法：bfs+队列+STL（C++）

PS：bfs入门题目，好高兴啊，终于会用bfs了。大笑

Catch That Cow
Time Limit: 2000MS	 	Memory Limit: 65536K
Total Submissions: 32679	 	Accepted: 10060
Description

Farmer John has been informed of the location of a fugitive cow 
and wants to catch her immediately. 
He starts at a point N (0 ≤ N ≤ 100,000) on a number line
 and the cow is at a point K (0 ≤ K ≤ 100,000) on the same number line. 
 Farmer John has two modes of transportation: walking and teleporting.

* Walking: FJ can move from any point X to the 
points X - 1 or X + 1 in a single minute
* Teleporting: FJ can move from any point X to 
the point 2 × X in a single minute.

If the cow, unaware of its pursuit, does not move at all, 
how long does it take for Farmer John to retrieve it?

Input

Line 1: Two space-separated integers: N and K
Output

Line 1: The least amount of time, in minutes, 
it takes for Farmer John to catch the fugitive cow.
Sample Input

5 17
Sample Output

4
Hint

The fastest way for Farmer John to reach the fugitive cow is
 to move along the following path: 5-10-9-18-17, which takes 4 minutes.
Source
*/

#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <cstring>

using namespace std;

int n, k;
const int maxn = 100000;
int visited[maxn + 10];
struct Step
{
	int x;
	int steps;
	Step(int xx, int s) :x(xx), steps(s){ }
};



int main(int argc, char* argv[])
{
	while (cin >> n >> k){
		memset(visited, 0, sizeof(visited));
		queue<Step> q;
		q.emplace(n, 0);
		visited[n] = 1;
		while (!q.empty()) {
			Step s = q.front();
			if (s.x == k) {
				cout << s.steps << endl;
				break;
				return 0;
			}
			else {
				if (s.x - 1 >= 0
					&& !visited[s.x - 1]) {
					q.emplace(s.x - 1, s.steps + 1);
					visited[s.x - 1] = 1;
				}
				if (s.x + 1 <= maxn
					&& !visited[s.x + 1]) {
					q.emplace(s.x + 1, s.steps + 1);
					visited[s.x + 1] = 1;
				}
				if (s.x * 2 <= maxn
					&& !visited[s.x * 2]) {
					q.emplace(s.x * 2, s.steps + 1);
					visited[s.x * 2] = 1;
				}
				q.pop();
			}
		}
	}

	return 0;
}
//注意输入是否为多组数据