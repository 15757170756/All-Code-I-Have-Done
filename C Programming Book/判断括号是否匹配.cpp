/*
Check for balanced parentheses in an expression
Given an expression string exp ,
write a program to examine whether the pairs and
the orders of “{“,”}”,”(“,”)”,”[“,”]”
are correct in exp. For example, the program should
print true for exp = “[()]{}{[()()]()}”
and false for exp = “[(])”
*/
#include <stack>
#include <iostream>

using namespace std;

// function to check if paranthesis are balanced
bool areParanthesisBalanced(char expr[])
{
	stack<char> s;
	char a, b, c;

	// Traversing the Expression
	for (int i = 0; i < strlen(expr); i++)
	{
		if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{')
		{
			// Push the element in the stack
			s.push(expr[i]);
		}
		else
		{
			switch (expr[i])
			{
			case ')':

				// Store the top element in a
				a = s.top();
				s.pop();
				if (a == '{' || a == '[') {
					//cout << "Not Balancedn";
					return false;
				}
				break;
			case '}':

				// Store the top element in b
				b = s.top();
				s.pop();
				if (b == '(' || b == '['){
					//cout << "Not Balancedn";
					return false;
				}
				break;
			case ']':

				// Store the top element in c
				c = s.top();
				s.pop();
				if (c == '(' || c == '{'){
					//cout << "Not Balancedn";
					return false;
				}
				break;
			}
		}
	}

	// Check Empty Stack
	if (s.empty())
		return true;
	else
		return false;
}

// Driver program to test above function
int main()
{
	char expr[] = "{(}[]";

	if (areParanthesisBalanced(expr))
		cout << "Balanced";
	else
		cout << "Not Balanced";
	return 0;
}

















/*
判断括号是否合法
*/
#include <iostream>
#include <cstring>

using namespace::std;

bool isParanthesLegal(char expr[])
{
	//比价直接的方法判断括号是否合法
	int leftParenthesis = 0;
	int rightParenthesis = 0;
	for (int i = 0; i < strlen(expr); ++i) {
		if (expr[i] == '(')
			++leftParenthesis;
		else
			++rightParenthesis;
	}

	if (leftParenthesis == rightParenthesis
		&& expr[0] == '(')
		return true;
	else
		return false;

}

int main()
{
	char expr[] = "(())";
	if (isParanthesLegal(expr))
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	return 0;
}

