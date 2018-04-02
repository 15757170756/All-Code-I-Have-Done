/*
[编程题] 矩形重叠
时间限制：1秒

空间限制：32768K

平面内有n个矩形, 第i个矩形的左下角坐标为(x1[i], y1[i]), 右上角坐标为(x2[i], y2[i])。

如果两个或者多个矩形有公共区域则认为它们是相互重叠的(不考虑边界和角落)。

请你计算出平面内重叠矩形数量最多的地方,有多少个矩形相互重叠。


输入描述:
输入包括五行。
第一行包括一个整数n(2 <= n <= 50), 表示矩形的个数。
第二行包括n个整数x1[i](-10^9 <= x1[i] <= 10^9),表示左下角的横坐标。
第三行包括n个整数y1[i](-10^9 <= y1[i] <= 10^9),表示左下角的纵坐标。
第四行包括n个整数x2[i](-10^9 <= x2[i] <= 10^9),表示右上角的横坐标。
第五行包括n个整数y2[i](-10^9 <= y2[i] <= 10^9),表示右上角的纵坐标。


输出描述:
输出一个正整数, 表示最多的地方有多少个矩形相互重叠,如果矩形都不互相重叠,输出1。

输入例子1:
2
0 90
0 90
100 200
100 200

输出例子1:
2
*/


/*
作者：NotDeep
链接：https ://www.nowcoder.com/discuss/70736
来源：牛客网

分析
分别枚举所有的横纵坐标,挨着判断每个矩形是否符合条件，计数维护最大即可。

时间复杂度
O(n^3)
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 50 + 5;
int X1[maxn], Y1[maxn];
int X2[maxn], Y2[maxn];
set<int> xx, yy;
int main() 
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> X1[i];
		xx.insert(X1[i]);
	}
	for (int i = 0; i < n; i++) {
		cin >> Y1[i];
		yy.insert(Y1[i]);
	}
	for (int i = 0; i < n; i++) {
		cin >> X2[i];
		xx.insert(X2[i]);
	}
	for (int i = 0; i < n; i++) {
		cin >> Y2[i];
		yy.insert(Y2[i]);
	}
	int ans = 0;
	for (int x : xx) {
		for (int y : yy) {
			int cnt = 0;
			for (int i = 0; i < n; i++) {
				if (X1[i] <= x && Y1[i] <= y && X2[i] > x && Y2[i] > y) 
					cnt++;
			}
			ans = max(ans, cnt);
		}
	}
	cout << ans << endl;
	return 0;
}