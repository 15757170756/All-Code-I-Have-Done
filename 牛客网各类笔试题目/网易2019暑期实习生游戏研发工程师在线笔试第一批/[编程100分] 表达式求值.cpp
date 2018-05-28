/*
[编程|100分] 表达式求值
时间限制：C/C++ 1秒，其他语言 2秒
空间限制：C/C++ 65536K，其他语言 131072K
语言限定：C/C++(clang++ 3.9), Java(javac 1.8)
题目描述
给定一个表达式，该表达式由以下规则生成：

1. "0"和"1"是合法表达式；
2. 如果x是一个合法表达式，那么"(!x)"是一个合法表达式；
3. 如果x和y是合法表达式，那么"(x|y)"和"(x&y)"都是合法表达式
其中，!是逻辑非操作符，|和&分别是与运算符和或运算符。

给定一个合法表达式，求该表达式最终的值。

输入描述:
第一行是一个正整数T（T <= 20）。接下来T行，每一行是一个表达式。
表达式不含空格，且输入保证该表达式是一个合法表达式。
对于30%的数据，表达式的长度不超过500; 对于100%的数据，表达式的长度不超过150000。
输出描述:
T行，每一行表示相应表达式的值。
示例1
输入
3
(!0)
(0|(1&0))
(0|(1&(!0)))
输出
1
0
1
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <stack>
#include <deque>

using namespace::std;

int main(int argc, char* argv[])
{
	ifstream in("input.txt");
	int t;
	in >> t;
	//vector<int> vec;
	while (t--) {
		string s;
		in >> s;
		int result, Num = 0;;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == '(')
				++Num;
		}
		//cout << Num << endl;
		for (int i = 0; i < Num; ++i) {
			for (int j = 1; j < s.size(); ++j) {
				if (s[j] == '&') {
					bool isGo1 = (s[j - 1] == '1' || s[j - 1] == '0')
						&& (s[j + 1] == '1' || s[j + 1] == '0');
					if (isGo1 == true) {
						int a = s[j - 1] - '0';
						int b = s[j + 1] - '0';
						result = a&b;
						string strTmp = to_string(result);
						s.replace(j - 2, 5, strTmp); 
						//我去，这里j-2弄错了，不然应该可以ACE的
						break;
					}
					/*		else
					break;*/
				}

				else if (s[j] == '|') {
					bool isGo2 = (s[j - 1] == '1' || s[j - 1] == '0')
						&& (s[j + 1] == '1' || s[j + 1] == '0');
					if (isGo2 == true) {
						int a = s[j - 1] - '0';
						int b = s[j + 1] - '0';
						result = a | b;
						string strTmp = to_string(result);
						s.replace(j - 2, 5, strTmp);
						//if ()
						break;
					}
					//else
					//	break;
				}

				else if (s[j] == '!') {
					bool isGo3 = (s[j - 1] == '(') &&
						(s[j + 1] == '1' || s[j + 1] == '0');
					if (isGo3 == true) {
						int b = s[j + 1] - '0';
						result = !b;
						string strTmp = to_string(result);
						s.replace(j - 1, 4, strTmp);
						break;
					}
					//else
					//	break;
				}
				else
					continue;
			}
		}
		cout << result << endl;
		//vec.push_back(result);
	}

	return 0;
}