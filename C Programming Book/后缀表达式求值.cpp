/*
http://www.lxway.com/448111616.htm

二. 后缀表达式求值

对后缀表达式求值比直接对中缀表达式求值简单。在后缀表达式中，不需要括号，而且操作符的优先级也不再起作用了。您可以用如下算法对后缀表达式求值：

初始化一个空堆栈
从左到右读入后缀表达式
如果字符是一个操作数，把它压入堆栈。
如果字符是个操作符，弹出两个操作数，执行恰当操作，然后把结果压入堆栈。如果您不能够弹出两个操作数，后缀表达式的语法就不正确。
到后缀表达式末尾，从堆栈中弹出结果。若后缀表达式格式正确，那么堆栈应该为空。
好了，基本思路讨论完毕，我们开始动手写代码，此段代码假设表达式中的预算符只包括四大基本运算符+、-、*、/，为了简化代码，我们也假设表达式中的数字只包括1-9。

函数getPostfixExp用来将一个中缀表达式转换为后缀表达式(也就是逆波兰式).
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
			while (!operator_stack.empty() && isOperator(operator_stack.top()) && priority(operator_stack.top()) >= priority(p))
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


int main(int argc, char* argv[])
{

	string s;
	cin >> s;

	int num = postfixCalculate(getPostfixExp(s));
	cout << num << endl;


	return 0;
}

