/*
Print all combinations of balanced parentheses
3.9
Write a function to generate all possible n pairs of balanced parentheses.

For example,

Input : n=1
Output: {}

Input : n=2
Output:
{}{}
{{}}
Algorithm:
Keep track of counts of open and close brackets.

Initialize these counts as 0.
Recursively call the _printParenthesis() function 
until open bracket count is less than the given n.
If open bracket count becomes more than 
the close bracket count, then put a closing bracket and 
recursively call for the remaining brackets.
If open bracket count is less than n, 
then put an opening bracket and call _printParenthesis() 
for the remaining brackets.
*/

// C program to Print all combinations
// of balanced parentheses
# include<stdio.h>
# define MAX_SIZE 100

void _printParenthesis(int pos, int n, int open, int close);

// Wrapper over _printParenthesis()
void printParenthesis(int n)
{
	if (n > 0)
		_printParenthesis(0, n, 0, 0);
	return;
}

void _printParenthesis(int pos, int n, int open, int close)
{
	static char str[MAX_SIZE];

	if (close == n)
	{
		printf("%s \n", str);
		return;
	}
	else
	{
		if (open > close)
		{
			str[pos] = '}';
			_printParenthesis(pos + 1, n, open, close + 1);
		}

		if (open < n)
		{
			str[pos] = '{';
			_printParenthesis(pos + 1, n, open + 1, close);
		}
	}
}

// Driver program to test above functions
int main()
{
	int n = 3;
	printParenthesis(n);
	getchar();
	return 0;
}

/*
n = 3
output:
{}{}{}
{}{{}}
{{}}{}
{{}{}}
{{{}}}
*/


/*
һ��Ҫ����һ�£�ʹ֮Ϊ�����������ܹ�
�õ�ÿ���ַ����������Ǽ����
*/

#include <iostream>
#include <string>
#include <vector>

using namespace::std;

# define MAX_SIZE 100

void _getParenthesis(int pos, int n, int open, int close, vector<string>& resultVec);

// Wrapper over _printParenthesis()
void getParenthesis(int n, vector<string>& resultVec)
{
	if (n > 0)
		_getParenthesis(0, n, 0, 0, resultVec);
	return;
}

void _getParenthesis(int pos, int n, int open, int close, vector<string>& resultVec)
{
	static char str[MAX_SIZE];

	if (close == n)
	{
		resultVec.push_back(str);
		//printf("%s \n", str);
		return;
	}
	else
	{
		if (open > close)
		{
			str[pos] = '}';
			_getParenthesis(pos + 1, n, open, close + 1, resultVec);
		}

		if (open < n)
		{
			str[pos] = '{';
			_getParenthesis(pos + 1, n, open + 1, close, resultVec);
		}
	}
}

// Driver program to test above functions
int main()
{
	int n = 20;
	vector<string> vec;
	getParenthesis(n, vec);
	//for (int i = 0; i < vec.size(); ++i)
	//	cout << vec[i] << endl;
	cout << vec.size();
	return 0;
}
