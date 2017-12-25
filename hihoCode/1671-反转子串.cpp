/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定一个只包含括号和小写字母的字符串S，例如S="a(bc(de)fg)hijk"。

其中括号表示将里面的字符串翻转。(注意括号可能嵌套)

请你输出翻转之后的字符串。

输入
字符串S。

对于50%的数据，|S| ≤ 1000

对于100%的数据, |S| ≤ 5000000

输出
输出反转后的字符串(不带括号)。

样例输入
a(bc(de)fg)hijk
样例输出
agfdecbhijk
*/

/*
说说我的思路，这题目其实本质上是括号匹配问题
只要找到括号匹配的对应位置，从内向外一次翻转
字符串就可以了， 然后光有这个思想，编程中会遇到
各种各样的细节问题，所以还是有些麻烦的
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <stack>

using namespace::std;

void reverseString(string& s)
{
	/*
	我这里其实只考虑了括号内嵌的情况
	难怪像(ab)(cd)这样的会出错
	*/
	stack<int> rightParenthesis;
	int cnt = count(s.begin(), s.end(), '(');
	for (int i = 0; i < s.size(); ++i)
		if (s[i] == ')')
			rightParenthesis.push(i);

	int firstLeftParenthesis = s.find('(');
	int* parenthesis = new int[2 * cnt];
	for (int i = 0; i < cnt; ++i) {
		parenthesis[2 * i] = s.find('(', firstLeftParenthesis);
		parenthesis[2 * i + 1] = rightParenthesis.top();
		firstLeftParenthesis = parenthesis[2 * i] + 1;
		rightParenthesis.pop();
	}
	//for (int i = 0; i < cnt; ++i){
	//	cout << parenthesis[2 * i] << ' ' << parenthesis[2 * i + 1] << endl;
	//}
	for (int i = cnt - 1; i >= 0; --i) {
		int startPos = parenthesis[2 * i];
		int endPos = parenthesis[2 * i + 1];// -startPos;
		for (int j = startPos, k = endPos;
			j <= startPos + (endPos - startPos) / 2; ++j, --k) {
			char temp = s[j];
			s[j] = s[k];
			s[k] = temp;
		}
		//cout << s << endl;
	}

	s.erase(remove(s.begin(), s.end(), '('), s.end());
	s.erase(remove(s.begin(), s.end(), ')'), s.end());
	delete[] parenthesis;
}


int main()
{
	string s = "(ab)(cd)";
	//cin >> s;
	reverseString(s);
	cout << s << endl;

	return 0;
}

















/*
稍微改了一下，其实还是蛮简单的
但还是花了蛮多时间来想的
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>

using namespace::std;

void reverseString(string& s)
{
	int cnt = count(s.begin(), s.end(), '(');
	int* parenthesis = new int[2 * cnt];
	//vector<int> parenthesis;
	stack<int> leftParenthesis;
	for (int i = 0, j = 0; i < s.size(); ++i) {
		if (s[i] == '(')
			leftParenthesis.push(i);
		else if (s[i] == ')') {
			int temp = leftParenthesis.top();
			leftParenthesis.pop();
			parenthesis[j++] = (temp);
			parenthesis[j++] = (i);
		}
	}

	/*for (int i = 0; i < parenthesis.size() / 2; ++i)
	cout << parenthesis[2 * i] << ' ' << parenthesis[2 * i + 1] << endl;*/

	for (int i = 0; i < cnt; ++i) {
		int startPos = parenthesis[2 * i];
		int endPos = parenthesis[2 * i + 1];// -startPos;
		for (int j = startPos, k = endPos;
			j <= startPos + (endPos - startPos) / 2; ++j, --k) {
			char temp = s[j];
			s[j] = s[k];
			s[k] = temp;
		}
		//cout << s << endl;
	}

	s.erase(remove(s.begin(), s.end(), '('), s.end());
	s.erase(remove(s.begin(), s.end(), ')'), s.end());
	delete[] parenthesis;
}


int main()
{
	string s1 = "((ab)(cd))";
	string s2 = "a(bc(de)fg)hijk";
	//cin >> s;
	reverseString(s1);
	cout << s1 << endl;

	reverseString(s2);
	cout << s2 << endl;

	return 0;
}
/*
cdab
agfdecbhijk
*/

/*
Time Limit Exceededo(╥﹏╥)o
*/


















/*
自己写了简单的栈并且都用c语言的模式
写的，把函数调用改成直接在main函数中
但是还是超时了，感觉是算法问题，
整体思路还有待调整
*/

#include <cstring>
#include <cstdio>

using namespace::std;

char S[5000000];

class MyStack {
private:
	int arr[1000000];
	int topPos;
public:
	MyStack()
	{
		memset(arr, 0, sizeof(arr));
		topPos = -1;
	}
	void push(const int& data)
	{
		arr[++topPos] = data;
	}

	int& top() { return arr[topPos]; }

	void pop()
	{
		--topPos;
	}
};

MyStack leftParenthesis;

int main()
{
	scanf("%s", S);
	int strLength = strlen(S);
	int cnt = 0;
	for (int i = 0; i < strLength; ++i)
		if (S[i] == '(')
			++cnt;
	int* parenthesis = new int[2 * cnt];
	//stack<int> leftParenthesis;
	for (int i = 0, j = 0; i < strLength; ++i) {
		if (S[i] == '(')
			leftParenthesis.push(i);
		else if (S[i] == ')') {
			int temp = leftParenthesis.top();
			leftParenthesis.pop();
			parenthesis[j++] = (temp);
			parenthesis[j++] = (i);
		}
	}

	for (int i = 0; i < cnt; ++i) {
		int startPos = parenthesis[2 * i];
		int endPos = parenthesis[2 * i + 1];// -startPos;
		for (int j = startPos, k = endPos;
			j <= startPos + (endPos - startPos) / 2; ++j, --k) {
			char temp = S[j];
			S[j] = S[k];
			S[k] = temp;
		}
		//cout << s << endl;
	}
	for (int i = 0; i < strLength; ++i)
		if (S[i] != '(' && S[i] != ')')
			printf("%c", S[i]);

	delete[] parenthesis;

	return 0;
}