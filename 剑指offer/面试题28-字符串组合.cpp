/*
https://blog.csdn.net/x526967803/article/details/77718434
二、字符串的组合

题目：输入一个字符串，输出该字符串中字符的所有组合。
举个例子，如果输入abc，它的组合有a、b、c、ab、ac、bc、abc。

上面我们详细讨论了如何用递归的思路求字符串的排列。
同样，本题也可以用递归的思路来求字符串的组合。

假设我们想在长度为n的字符串中求m个字符的组合。
我们先从头扫描字符串的第一个字符。针对第一个字符，
我们有两种选择：第一是把这个字符放到组合中去，
接下来我们需要在剩下的n-1个字符中选取m-1个字符；
第二是不把这个字符放到组合中去，
接下来我们需要在剩下的n-1个字符中选择m个字符。
这两种选择都很容易用递归实现。下面是这种思路的参考代码：
*/

#include<iostream>  
#include<vector>  
#include<cstring>  
using namespace std;
#include<assert.h>  

void Combination(char *string, int number, vector<char> &result);

void Combination(char *string)
{
	assert(string != NULL);
	vector<char> result;
	int i, length = strlen(string);
	for (i = 1; i <= length; ++i)
		Combination(string, i, result);
}

void Combination(char *string, int number, vector<char> &result)
{
	assert(string != NULL);
	if (number == 0)
	{
		static int num = 1;
		printf("第%d个组合\t", num++);

		vector<char>::iterator iter = result.begin();
		for (; iter != result.end(); ++iter)
			printf("%c", *iter);
		printf("\n");
		return;
	}
	if (*string == '\0')
		return;
	result.push_back(*string);
	Combination(string + 1, number - 1, result);
	result.pop_back();
	Combination(string + 1, number, result);
}

int main(void)
{
	char str[] = "abc";
	Combination(str);
	return 0;
}