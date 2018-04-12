/*
给一个包含n个整数元素的集合a，一个包含m个整数元素的集合b。
定义magic操作为，从一个集合中取出一个元素，
放到另一个集合里，切操作过后每个集合的平均值都大于操作前。
注意一下两点：

不可以把一个集合的元素取空，这样就没有平均值了
值为x的元素从集合b取出放入集合a，
但集合a中已经有值为x的元素，
则a的平均值不变(因为集合元素不会重复)，b的平均值可能会改变(因为x被取出了)
问最多可以进行多少次magic操作？
输入描述：
第一行为两个整数n，m
第二行n个整数，表示集合a中的元素
第三行m个整数，表示集合b中的元素
对于100%的数据，1<n,m<1000000<a[i],b[i]<100000000，
集合a中元素互不相同，集合b中的元素互不相同。

输出描述：
输出一个整数，表示最多可以进行的操作次数。

样例
in:
3 5
1 2 5
2 3 4 5 6
out:
2
*/



#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <queue>
#include <set>

using namespace::std;



int main()
{
	for (int n, m; cin >> n >> m;) {
		set<int> A, B;
		double aveA = 0, aveB = 0;
		for (int i = 0, x; i < n;
			A.insert((cin >> x, x)), aveA += x, ++i){
		}
		for (int i = 0, x; i < m;
			B.insert((cin >> x, x)), aveB += x, ++i){
		}

		if (aveA / n < aveB / m) {
			A.swap(B);
			swap(aveA, aveB);
			swap(n, m);
		}

		int cnt = 0;
		for (auto iter = A.begin();
			iter != A.end() && *iter * 1.0 < aveA / n; ++iter) {
			if (B.find(*iter) != B.end())
				continue;
			if (*iter > aveB / m) {
				aveA -= *iter, aveB += *iter;
				--n, ++m;
				++cnt;
			}
		}
	}

	return 0;
}