/*
这题其实网上找个字符串表达式求值的，
把表达式值给求出来， 然后就好办了。
今日头条6周年周年庆就要开始啦。活动主办方请你帮忙制作一个小彩蛋。你的程序需要读取一个表达式，并输出用字符6拼出的计算结果。相邻数字使用两个英文句号"."间隔，如下是0123456789。

66666......6..66666..66666..6...6..66666..66666..66666..66666..66666
6...6......6......6......6..6...6..6......6..........6..6...6..6...6
6...6......6..66666..66666..66666..66666..66666......6..66666..66666
6...6......6..6..........6......6......6..6...6......6..6...6......6
66666......6..66666..66666......6..66666..66666......6..66666..66666
输入描述：
第一行为一个整数n
接下来n行，每一行为一个表达式
对于30%的数据，表达式仅包含'6', '+', '-'三种字符
对于100%的数据，表达式仅包含'6', '+', '-', '*'四种字符。1≤n≤100，表达式长度不超过100，其中'+', '-', '*'均为二元运算符，计算中间结果在[−263,263−1]之内，最终结果在[0,263−1]之内
输出描述：
对于每组数据输出用字符6拼出的计算结果。

样例
in:
2
6+6
6*6
out:
....6..66666
....6......6
....6..66666
....6..6....
....6..66666
66666..66666
....6..6....
66666..66666
....6..6...6
66666..66666
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <unordered_map>
#include <stack>

using namespace::std;


bool isOperator(char ch)
{
	switch (ch)
	{
	case'+':
	case'-':
	case'*':
	case'/':
		return true;
	default:
		return false;
	}
}

int priority(char a) {
	int temp;
	if (a == '*' || a == '/')
		temp = 2;
	else if (a == '+' || a == '-')
		temp = 1;
	return temp;
}

void getTwoNums(stack<int>& num_stack, int& first, int& second)
{
	second = num_stack.top();
	num_stack.pop();

	first = num_stack.top();
	num_stack.pop();
}

int postfixCalculate(string& postfix)
{
	int first, second;
	stack<int> num_stack;
	for (auto p : postfix)
	{
		switch (p)
		{
			//if the item is an operator (+, -, *, or /) then

			//      pop two numbers off the stack

			//      make a calculation:  the second number 
			//            popped-operator-first number

			//      push the result on the stack
		case '*':
			getTwoNums(num_stack, first, second);
			num_stack.push(first * second);
			break;
		case '/':
			getTwoNums(num_stack, first, second);
			num_stack.push(first / second);
			break;
		case '+':
			getTwoNums(num_stack, first, second);
			num_stack.push(first + second);
			break;
		case '-':
			getTwoNums(num_stack, first, second);
			num_stack.push(first - second);
			break;
		case ' ':
			break;
			//   if the item is a number push it on the stack
		default:
			num_stack.push(p - '0');
			break;
		}
	}
	int result = num_stack.top();
	num_stack.pop();
	return result;
}

string getPostfixExp(string& infix)
{
	stack<char> operator_stack;
	string postfix;
	for (auto p : infix)
	{
		if (isOperator(p))
		{
			while (!operator_stack.empty() && 
				isOperator(operator_stack.top()) && 
				priority(operator_stack.top()) >= priority(p))
			{
				postfix.push_back(operator_stack.top());
				postfix.push_back(' ');
				operator_stack.pop();
			}
			operator_stack.push(p);
		}
		else if (p == '(')
		{
			operator_stack.push(p);
		}
		else if (p == ')')
		{
			while (operator_stack.top() != '(')
			{
				postfix.push_back(operator_stack.top());
				postfix.push_back(' ');
				operator_stack.pop();
			}
			operator_stack.pop();
		}
		else
		{
			postfix.push_back(p);
			postfix.push_back(' ');
		}
	}
	while (!operator_stack.empty())
	{
		postfix.push_back(operator_stack.top());
		postfix.push_back(' ');
		operator_stack.pop();
	}
	postfix.pop_back();
	return postfix;
}


int fun(string s)
{
	return postfixCalculate(s);
}

char arr0[5][6] = { "66666",
"6...6", "6...6", "6...6", "66666" };

char arr1[5][6] = { "....6",
"....6", "....6", "....6", "....6" };

char arr2[5][6] = { "66666",
"....6", "66666", "6....", "66666" };

char arr3[5][6] = { "66666",
"....6", "66666", "....6", "66666" };

char arr4[5][6] = { "6...6",
"6...6", "66666", "....6", "....6" };

char arr5[5][6] = { "66666",
"6....", "66666", "....6", "66666" };

char arr6[5][6] = { "66666",
"6....", "66666", "6...6", "66666" };

char arr7[5][6] = { "66666",
"....6", "....6", "....6", "....6" };

char arr8[5][6] = { "66666",
"6...6", "66666", "6...6", "66666" };

char arr9[5][6] = { "66666",
"6...6", "66666", "....6", "66666" };

void print666(int num)
{
	vector<int> vec;
	while (num) {
		int temp = num % 10;
		vec.emplace_back(temp);
		num /= 10;
	}
	reverse(vec.begin(), vec.end());
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < vec.size(); ++j) {
			switch (vec[j]) {
			case 0:
				if (j != 0)
					cout << ".." << arr0[i];
				else
					cout << arr0[i];
				break;
			case 1:
				if (j != 0)
					cout << ".." << arr1[i];
				else
					cout << arr1[i];
				break;
			case 2:
				if (j != 0)
					cout << ".." << arr2[i];
				else
					cout << arr2[i];
				break;
			case 3:
				if (j != 0)
					cout << ".." << arr3[i];
				else
					cout << arr3[i];
				break;
			case 4:
				if (j != 0)
					cout << ".." << arr4[i];
				else
					cout << arr4[i];
				break;
			case 5:
				if (j != 0)
					cout << ".." << arr5[i];
				else
					cout << arr5[i];
				break;
			case 6:
				if (j != 0)
					cout << ".." << arr6[i];
				else
					cout << arr6[i];
				break;
			case 7:
				if (j != 0)
					cout << ".." << arr7[i];
				else
					cout << arr7[i];
				break;
			case 8:
				if (j != 0)
					cout << ".." << arr8[i];
				else
					cout << arr8[i];
				break;
			case 9:
				if (j != 0)
					cout << ".." << arr9[i];
				else
					cout << arr9[i];
				break;
			}

		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{

	string s;
	cin >> s;

	int num = postfixCalculate(getPostfixExp(s));

	print666(num);

	return 0;
}

