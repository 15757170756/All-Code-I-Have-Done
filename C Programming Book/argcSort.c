/**************************************
对数组A从小到大进行连续编号，输出各个元素的
编号。要求不能改变数组A中元素的顺序，且相同的
整数要具有相同的编号。例如：
A = (5, 3, 4, 7, 3, 5, 6) 
output: (3, 1, 2, 5, 1, 3, 4)
***************************************/

#include <stdio.h>
#define N 10

int main()
{
	int a[N] = { 5, 4, 4, 7, 3, 5, 6, 6, 4, 3 };
	int b[N] = { 0 };
	int count, i, j;
	for (i = 0; i < N; i++)
		for (j = i + 1; j < N; j++)
			if (a[i] == a[j]) b[i]++;

	for (i = 0; i < N; i++) {
		count = 1;
		for (j = 0; j < N; j++)
			if (b[j] == 0 && a[i] > a[j]) count++;
		printf("%d ", count);
	}
	return 0;
}
//输出3 2 2 5 1 3 4 4 2 1

int main()
{
	int a[N] = { 5, 4, 4, 7, 3, 5, 6, 6, 4, 3 };
	int b[N] = { 0 };
	int count, i, j;

	for (i = 0; i < N; i++) {
		count = 1;
		for (j = 0; j < N; j++)
			if (a[i] > a[j]) count++;
		b[i] = count;
	}

	for (i = 0; i < N; ++i) {
		printf("%d ", b[i]);
	}
	return 0;
}
//输出6 3 3 10 1 6 8 8 3 1
