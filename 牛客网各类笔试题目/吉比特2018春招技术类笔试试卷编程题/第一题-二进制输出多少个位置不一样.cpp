/*
题目
判断两个数，换成二进制格式，输出多少个位置不一样
*/

#include <bits/stdc++.h>

using namespace std;

int main()
{
	for (int n1, n2; cin >> n1 >> n2;) {
		int ans = 0;
		int n_1 = n1, n_2 = n2;
		for (int i = 0; i < 32; i++) {
			ans += (n_1 & 1) ^ (n_2 & 1);
			n_1 >>= 1;
			n_2 >>= 1;
		}
		cout << ans << endl;
	}
	return 0;
}