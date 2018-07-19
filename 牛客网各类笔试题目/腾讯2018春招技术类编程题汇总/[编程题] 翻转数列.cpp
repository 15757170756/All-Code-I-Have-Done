/*
[编程题] 翻转数列
时间限制：1秒

空间限制：32768K

小Q定义了一种数列称为翻转数列:
给定整数n和m, 满足n能被2m整除。对于一串连续递增整数数列1, 2, 3, 4..., 每隔m个符号翻转一次, 最初符号为'-';。
例如n = 8, m = 2, 数列就是: -1, -2, +3, +4, -5, -6, +7, +8.
而n = 4, m = 1, 数列就是: -1, +2, -3, + 4.
小Q现在希望你能帮他算算前n项和为多少。 
输入描述:
输入包括两个整数n和m(2 <= n <= 109, 1 <= m), 并且满足n能被2m整除。


输出描述:
输出一个整数, 表示前n项和。

输入例子1:
8 2

输出例子1:
8
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>

using namespace::std;

int main()
{
	long long n, m;
	scanf("%lld%lld", &n, &m);
	long long result = n*m / 2;
	printf("%lld\n", result);
	return 0;
}

/*
您的代码已保存
答案正确:恭喜！您提交的程序通过了所有的测试用例
*/
