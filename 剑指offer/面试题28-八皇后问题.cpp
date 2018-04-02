/*
字符串全排列扩展----八皇后问题
题目：在8×8的国际象棋上摆放八个皇后，使其不能相互攻击，
即任意两个皇后不得处在同一行、同一列或者同一对角斜线上。
下图中的每个黑色格子表示一个皇后，这就是一种符合条件的摆放方法。
请求出总共有多少种摆法。
这就是有名的八皇后问题。解决这个问题通常需要用递归，而递归对编程能力的要求比较高。
因此有不少面试官青睐这个题目，用来考察应聘者的分析复杂问题的能力以及编程的能力。

由于八个皇后的任意两个不能处在同一行，那么这肯定是每一个皇后占据一行。
于是我们可以定义一个数组ColumnIndex[8]，数组中第i个数字表示位于第i行的皇后的列号。
先把ColumnIndex的八个数字分别用0-7初始化，接下来我们要做的事情就是对数组ColumnIndex做全排列。
由于我们是用不同的数字初始化数组中的数字，因此任意两个皇后肯定不同列。
我们只需要判断得到的每一个排列对应的八个皇后是不是在同一对角斜线上，
也就是数组的两个下标i和j，是不是i-j==ColumnIndex[i]-Column[j]或者j-i==ColumnIndex[i]-ColumnIndex[j]。

关于排列的详细讨论，详见上面的讲解。
接下来就是写代码了。思路想清楚之后，编码并不是很难的事情。下面是一段参考代码：
*/


#include<iostream>  
using namespace std;

int g_number = 0;
void Permutation(int *, int, int);
void Print(int *, int);

void EightQueen()
{
	const int queens = 8;
	int ColumnIndex[queens];
	for (int i = 0; i < queens; ++i)
		ColumnIndex[i] = i;    //初始化  
	Permutation(ColumnIndex, queens, 0);
}

bool Check(int ColumnIndex[], int length)
{
	int i, j;
	for (i = 0; i < length; ++i)
	{
		for (j = i + 1; j < length; ++j)
		{
			if (i - j == ColumnIndex[i] - ColumnIndex[j] || 
				j - i == ColumnIndex[i] - ColumnIndex[j])   //在正、副对角线上  
				return false;
		}
	}
	return true;
}
void Permutation(int ColumnIndex[], int length, int index)
{
	if (index == length)
	{
		if (Check(ColumnIndex, length))   //检测棋盘当前的状态是否合法  
		{
			++g_number;
			Print(ColumnIndex, length);
		}
	}
	else
	{
		for (int i = index; i < length; ++i)   //全排列  
		{
			swap(ColumnIndex[index], ColumnIndex[i]);
			Permutation(ColumnIndex, length, index + 1);
			swap(ColumnIndex[index], ColumnIndex[i]);
		}
	}
}

void Print(int ColumnIndex[], int length)
{
	printf("%d\n", g_number);
	for (int i = 0; i < length; ++i)
		printf("%d ", ColumnIndex[i]);
	printf("\n");
}

int main(void)
{
	EightQueen();
	return 0;
}