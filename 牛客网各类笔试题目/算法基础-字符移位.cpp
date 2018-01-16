/*
时间限制：1秒

空间限制：32768K

小Q最近遇到了一个难题：把一个字符串的大写字母放到字符串的后面，
各个字符的相对位置不变，且不能申请额外的空间。
你能帮帮小Q吗？


输入描述:

输入数据有多组，每组包含一个字符串s，且保证:1<=s.length<=1000.

输出描述:

对于每组数据，输出移位后的字符串。


输入例子1:
AkleBiCeilD

输出例子1:
kleieilABCD
*/


/*
看来刷剑指offer还是蛮有用的，
不过这个STL 的解法是看了陈硕的关于网络编程的
书后面，这本书虽然有些“不务正业”
但是对我等基础差的还是蛮好的。
*/
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string.h>

using namespace::std;

bool isUpper(char ch)
{
	return !(ch >= 'A' && ch <= 'Z');
}

int main()
{
	char str[1000];// = "AkleBiCeilD";
	while (cin >> str) {
		int strLen = strlen(str);
		stable_partition(str, str + strLen, isUpper);
		cout << str << endl;
	}

	return 0;
}