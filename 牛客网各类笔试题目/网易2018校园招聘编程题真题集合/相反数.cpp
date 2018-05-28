/*
时间限制：1秒

空间限制：32768K

为了得到一个数的"相反数",我们将这个数的数字顺序颠倒,
然后再加上原先的数得到"相反数"。例如,为了得到1325的"相反数",
首先我们将该数的数字顺序颠倒,我们得到5231,之后再加上原先的数,
我们得到5231+1325=6556.如果颠倒之后的数字有前缀零,前缀零将会被忽略。
例如n = 100, 颠倒之后是1.
输入描述:
输入包括一个整数n,(1 ≤ n ≤ 10^5)


输出描述:
输出一个整数,表示n的相反数

输入例子1:
1325

输出例子1:
6556
*/


#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace::std;

int main()
{
	int n;
	cin >> n;
	string str;
	int temp = n;
	while (temp) {
		char lastDigit = temp % 10 + '0';
		str.push_back(lastDigit);
		temp /= 10;
	}
	int inverseDigit = stoi(str);
	cout << n + inverseDigit << endl;

	return 0;
}


/*
您的代码已保存
答案正确:恭喜！您提交的程序通过了所有的测试用例
*/