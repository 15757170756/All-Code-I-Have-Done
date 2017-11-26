/***************************************
题目描述

某餐馆有n张桌子，每张桌子有一个参数：a可容纳的最大人数；有m批客人，每批客人有两个参数：b人数、c预计消费金额。在不允许拼桌的情况下，请实现一个算法选择其中一部分客人，使得总预计消费金额最大。

输入描述

输入包括m+2行。
第一行包括2个整数n(1<=n<=50000)，m(1<=m<=50000);
第二行为n个参数a，即每个桌子可容纳的最大人数，以空格分隔，范围均在32位int范围内;
接下来m行，每行两个参数b和c，分别表示第i批客人的人数和预计消费金额，
以空格分隔，范围均在32位int范围内。
输出描述

输出一个整数，表示最大的总预计消费金额。
输入例子

3 5
2 4 2
1 3
3 5
3 7
5 9
1 10
输出例子

20

分析:

贪心法。先把顾客进行消费金额降序,人数升序排序。 
然后枚举每波顾客去二分当前最适合的 桌子的容量，
维护答案即可,注意答案可能爆int。这题裸暴力过不了。
不能拆桌。时间复杂度：O(mlogm + nlogm)
注意: 结果需要使用long long(相应printf的格式控制为%lld), 
如果忘了用long long, 样例只会通过50%！
****************************************/
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct node{
	int b, c;
};
int comp(node x, node y){
	if (x.c == y.c) {
		return x.b < y.b;
	}
	return x.c > y.c;
}
int n, m;
long long ans;
std::vector<node> v;
std::multimap<int, int> mp;
int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++){
		int x; scanf("%d", &x);
		mp.insert(std::pair<int, int>(x, 1));
	}
	for (int i = 0; i < m; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		node tmp;
		tmp.b = x, tmp.c = y;
		v.push_back(tmp);
	}
	sort(v.begin(), v.end(), comp);
	for (int i = 0; i < m; i++){
		std::map<int, int>::iterator it = mp.lower_bound(v[i].b);
		if (it != mp.end()) {
			mp.erase(it);
			ans += v[i].c;
		}
	}
	printf("%lld\n", ans);
}