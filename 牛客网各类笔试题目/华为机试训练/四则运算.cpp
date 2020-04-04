/*
https://www.nowcoder.com/practice/9999764a61484d819056f807d2a91f1e?tpId=37&tqId=21273&tPage=3&rp=&ru=/ta/huawei&qru=/ta/huawei/question-ranking
时间限制：C/C++ 1秒，其他语言2秒 空间限制：C/C++ 32M，其他语言64M 热度指数：17184
 算法知识视频讲解
校招时部分企业笔试将禁止编程题跳出页面，为提前适应，练习时请使用在线自测，而非本地IDE。
题目描述
请实现如下接口

    /* 功能：四则运算

     * 输入：strExpression：字符串格式的算术表达式，如: "3+2*{1+2*[-4/(8-6)+7]}"

         * 返回：算术表达式的计算结果

     

    public static int calculate(String strExpression)

    {

        /* 请实现

        return 0;

    } 

约束：

pucExpression字符串中的有效字符包括[‘0’-‘9’],‘+’,‘-’, ‘*’,‘/’ ,‘(’， ‘)’,‘[’, ‘]’,‘{’ ,‘}’。

pucExpression算术表达式的有效性由调用者保证; 

 



输入描述:
输入一个算术表达式

输出描述:
得到计算结果

示例1
输入
复制
3+2*{1+2*[-4/(8-6)+7]}
输出
复制
25
*/


#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>
#include <vector>
#include <functional>
#include <string>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include <stack>

using namespace std;

string changeBracket(string exp);
int mid2post(string exp);
int calculate(int a, int b, char sym);

int main()
{
	//freopen("input.txt", "r", stdin);
	string s;
	while (cin >> s) {
		s = changeBracket(s);
		int res = mid2post(s);
		cout << res << endl;
	}

	return 0;
}

string changeBracket(string exp)
{
	for (int i = 0; i < exp.size(); ++i) {
		if ('{' == exp[i] || '[' == exp[i])
			exp[i] = '(';
		if ('}' == exp[i] || ']' == exp[i])
			exp[i] = ')';
	}

	return exp;
}

int mid2post(string exp)
{
	int flag = 0;
	stack<int> expPost;
	stack<char> symbol;
	for (int i = 0; i < exp.size(); ++i) {
		char temp;
		if (isdigit(exp[i])) {
			int j = i, num = 0;
			while (i + 1 < exp.length() && isdigit(exp[i + 1]))
				++i;
			string strNum = exp.substr(j, i - j + 1);
			for (int k = 0; k < strNum.size(); ++k)
				num = num * 10 + strNum[k] - '0';
			if (flag == 2)
				num = 0 - num;
			flag = 0;
			expPost.push(num);
		}
		else if (exp[i] == '*' || exp[i] == '/'
			|| exp[i] == '(')
			symbol.push(exp[i]);
		else if (exp[i] == '+' || exp[i] == '-') {
			if (!i || exp[i - 1] == '(') {
				if (exp[i] == '+')
					flag = 1;
				else
					flag = 2;
			}
			while (!flag && !symbol.empty() &&
				symbol.top() != '(') {
				int b = 0, a = 0;
				char sym_temp;
				b = expPost.top();
				expPost.pop();
				a = expPost.top();
				expPost.pop();
				sym_temp = symbol.top();
				symbol.pop();
				expPost.push(calculate(a, b, sym_temp));
			}
			if (!flag)
				symbol.push(exp[i]);
		}
		else if (')' == exp[i]) {
			while ('(' != symbol.top()) {
				int b = 0, a = 0;
				char sym_temp;
				b = expPost.top();
				expPost.pop();
				a = expPost.top();
				expPost.pop();
				sym_temp = symbol.top();
				symbol.pop();
				expPost.push(calculate(a, b, sym_temp));
			}
			symbol.pop();
		}
	}
	while (!symbol.empty()) {
		int b = 0, a = 0;
		char sym_temp;
		b = expPost.top();
		expPost.pop();
		a = expPost.top();
		expPost.pop();
		sym_temp = symbol.top();
		symbol.pop();
		expPost.push(calculate(a, b, sym_temp));
	}
	return expPost.top();
}

int calculate(int a, int b, char sym)
{
	switch (sym)
	{
	case '+':return a + b;
	case '-':return a - b;
	case '*':return a*b;
	case '/':return a / b;
	default:
		return 0;
		break;
	}
}

/*
恭喜你通过本题
运行时间：8ms

占用内存：484k
*/