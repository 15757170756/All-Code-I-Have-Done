/*
时间限制：1秒

空间限制：32768K

如果一个整数只能被1和自己整除,就称这个数是素数。
如果一个数正着反着都是一样,就称为这个数是回文数。例如:6, 66, 606, 6666
如果一个数字既是素数也是回文数,就称这个数是回文素数
牛牛现在给定一个区间[L, R],希望你能求出在这个区间内有多少个回文素数。
输入描述:
输入包括一行,一行中有两个整数(1 ≤ L ≤ R ≤ 1000)


输出描述:
输出一个整数,表示区间内回文素数个数。

输入例子1:
100 150

输出例子1:
2
*/

#include <iostream>
#include <cmath>
#include <string>

using namespace::std;

bool isPrime(int num)
{
	int i, k = sqrt(double(num));
	if (2 == num)
		return true;
	for (i = 2; i <= k; ++i) {
		if (num % i == 0)
			return false;
	}
	if (i > k && num != 1)
		return true;
	else
		return false;
}

bool isPalindrome(int num)
{
	string s = to_string(num);
	int cnt = 0;
	for (int i = 0, j = s.size() - 1;
		i < s.size() / 2; ++i, --j) {
		if (s[i] == s[j])
			++cnt;
	}

	if (cnt == s.size() / 2)
		return true;
	else
		return false;
}

int main()
{
	int L, R;
	cin >> L >> R;
	int cnt = 0;
	for (int i = L; i <= R; ++i) {
		if (isPrime(i) && isPalindrome(i))
			++cnt;
	}
	cout << cnt << endl;
}

/*
您的代码已保存
答案正确:恭喜！您提交的程序通过了所有的测试用例
*/