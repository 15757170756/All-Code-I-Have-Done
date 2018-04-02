/*

https://blog.csdn.net/flushhip/article/details/79660602

字符串距离
时间限制：C/C++语言 2000MS；其他语言 4000MS
内存限制：C/C++语言 65536KB；其他语言 589824KB
题目描述：
给出两个相同长度的由字符 a 和 b 构成的字符串，
定义它们的距离为对应位置不同的字符的数量。
如串”aab”与串”aba”的距离为 2；串”ba”与串”aa”的距离为 1；
串”baa”和串”baa”的距离为 0。
下面给出两个字符串 S 与 T，其中 S 的长度不小于 T 的长度。
我们用|S|代表 S 的长度，|T|代表 T 的长度，
那么在 S 中一共有|S|-|T|+1 个与 T 长度相同的子串，
现在你需要计算 T 串与这些|S|-|T|+1 个子串的距离的和。

输入
第一行包含一个字符串 S。

第二行包含一个字符串 T。

S 和 T 均由字符 a 和 b 组成，1 ≤ |T| ≤ |S| ≤105 。

输出
输出对应的答案。


样例输入
aab

aba

样例输出
2


Hint
Input Sample 2
aaabb
bab
Output Sample 2
5
在样例 2 中，”aaa”与”bab”的距离为 2，”aab”与”bab”的距离为 1，
”abb”与”bab”的距离为 2，
所以最后答案为 5。

*/

#include <iostream>
#include <string>
#include <vector>

using namespace::std;

int sameNumStr(string &s1, string &s2)
{
	int cnt = 0;
	for (size_t i = 0; i < s1.size(); ++i) {
		if (s1[i] != s2[i])
			++cnt;
	}
	return cnt;
}

int main()
{
	string s, t;
	cin >> s >> t;
	size_t sLength = s.size();
	size_t tLength = t.size();
	int diff = sLength - tLength + 1;
	int cnt = 0;
	for (size_t i = 0; i < diff; ++i) {
		string temp = s.substr(i, tLength);
		cnt += sameNumStr(temp, t);
	}
	cout << cnt << endl;

}
/*
case通过率为70%
*/




















#include <bits/stdc++.h>

using namespace std;

int main()
{
	for (string S, T; cin >> S >> T;) {
		int a = 0, b = 0;
		int lens = S.size(), lent = T.size();
		for (int i = 0; i < lens - lent + 1; i++)
			a += S[i] == 'a',
			b += S[i] == 'b';
		int ans = 0;
		for (int i = 0; i + lens - lent < lens; i++) {
			ans += T[i] == 'a' ? b : a;
			S[i] == 'a' ? --a : --b;
			S[i + lens - lent + 1] == 'a' ? ++a : ++b;
		}
		cout << ans << endl;
	}
	return 0;
}