/*
题目
n个三维空间点，判断最多多少个空间点在同一条直线上

这题尽量不要用斜率做，用向量做是最好的，那么问题就转化成了如何判断两个向量共线；

只要两个向量对应系数成比例，那么这两个向量就共线；

由于n达到了2000，那么三层for循环枚举三个点的算法是行不通的，因此，换一种思路，
假设两个向量共线，且这两个向量的起点是同一个点，那么这说明三点就共线了；

因此，我们把空间点排序，排序函数：

bool operator<(const Point &other) const {
if (x != other.x)
return x < other.x;
if (y != other.y)
return y < other.y;
if (z != other.z)
return z < other.z;
}
1
2
3
4
5
6
7
8
这样可以保证待会我们以一个点作为起点去构造其他向量的时候能保证向量都在第一卦限；

由于共线向量对应系数成比例，因此，我们直接把共线的向量统一化成最简的形式，
即三个分量没有除了1没有其他公约数，这样就可以用一个map来保存最简式，
最后求出共线最多的最简式的数量加一就是答案。

时间复杂度：O(n2logn)。
*/

#include <bits/stdc++.h>

using namespace std;

#define gcd __gcd

struct Point {
	int x, y, z;
	Point() {}
	Point(int x, int y, int z) : x(x), y(y), z(z) {}

	bool operator<(const Point &other) const {
		if (x != other.x)
			return x < other.x;
		if (y != other.y)
			return y < other.y;
		if (z != other.z)
			return z < other.z;
	}
};

typedef pair<pair<int, int>, int> Node;

int main()
{
	for (int n; cin >> n;) {
		vector<Point> points;
		for (int i = 0, x, y, z; i < n; i++)
			cin >> x >> y >> z, points.push_back(Point(x, y, z));
		sort(points.begin(), points.end());

		int ans = 0;
		for (int i = 0; i < n; i++) {
			map<Node, int> mp;
			for (int j = i + 1; j < n; j++) {
				int vx = points[j].x - points[i].x;
				int vy = points[j].y - points[i].y;
				int vz = points[j].z - points[i].z;
				int g = gcd(gcd(vx, vy), vz);
				mp[make_pair(make_pair(vx / g, vy / g), vz / g)]++;
			}
			int sum = 0;
			for (auto it = mp.begin(); it != mp.end(); ++it)
				sum = max(sum, it->second);
			ans = max(sum, ans);
		}
		cout << ans + 1 << endl;
	}
	return 0;
}