/*

[编程题] 牛牛的背包问题
时间限制：1秒

空间限制：32768K

牛牛准备参加学校组织的春游, 出发前牛牛准备往背包里装入一些零食, 牛牛的背包容量为w。
牛牛家里一共有n袋零食, 第i袋零食体积为v[i]。
牛牛想知道在总体积不超过背包容量的情况下,他一共有多少种零食放法(总体积为0也算一种放法)。

输入描述:
输入包括两行
第一行为两个正整数n和w(1 <= n <= 30, 1 <= w <= 2 * 10^9),表示零食的数量和背包的容量。
第二行n个正整数v[i](0 <= v[i] <= 10^9),表示每袋零食的体积。


输出描述:
输出一个正整数, 表示牛牛一共有多少种零食放法。

输入例子1:
3 10
1 2 4

输出例子1:
8

例子说明1:
三种零食总体积小于10,于是每种零食有放入和不放入两种情况，一共有2*2*2 = 8种情况。
*/






/*
作者：NotDeep
链接：https ://www.nowcoder.com/discuss/70736?type=0&order=0&pos=17&page=1
来源：牛客网

作者：NotDeep
链接：https://www.nowcoder.com/discuss/70736?type=0&order=0&pos=17&page=1
来源：牛客网

分析
容量太大,没办法dp。
看到物品数量是30,直接爆搜也不行。。
于是对半分成两部分枚举之后,二分计算贡献。
当然用个map来做个map版本的背包也是兹磁的吧？

时间复杂度
O(2^(n/2) * log(2^(n/2)))
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
LL v[35];
vector<LL> val1, val2;
int n, w;
void calc(LL *item, int mx, vector<LL> &val){
	for (int i = 0; i < mx; i++){
		LL sum = 0;
		for (int j = 0; j < 20; j++){
			if (i & (1 << j)){
				sum += item[j];
				if (sum > w) break;
			}
		}
		if (sum <= w) val.push_back(sum);
	}
}
int main() {
	val1.clear();
	val2.clear();
	scanf("%d%d", &n, &w);
	for (int i = 0; i < n; i++) scanf("%lld", &v[i]);
	calc(v, 1 << (n / 2), val1);
	calc(&v[n - (n + 1) / 2], 1 << (n - n / 2), val2);
	sort(val2.begin(), val2.end());
	LL ans = 0;
	for (int i = 0; i < val1.size(); i++){
		ans += upper_bound(val2.begin(), val2.end(), w - val1[i]) - val2.begin();
	}
	printf("%lld\n", ans);
	return 0;
}