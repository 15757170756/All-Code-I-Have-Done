/*
http://blog.csdn.net/acdreamers/article/details/24244643
*/
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;
const int N = 100005;

int a[N];

void swap(int a[], int x, int y)
{
	a[x] ^= a[y];
	a[y] ^= a[x];
	a[x] ^= a[y];
}

void Reverse(int a[], int x, int y)
{
	while (x < y)
		swap(a, x++, y--);
}

void Convert(int a[], int L, int M, int R)
{
	Reverse(a, L, M);
	Reverse(a, M + 1, R);
	Reverse(a, L, R);
}

void Merge(int a[], int L, int M, int R)
{
	int i = L;
	int j = M + 1;
	while (i < j && j <= R)
	{
		while (i < j && a[i] <= a[j])
			i++;
		int index = j;
		while (j <= R && a[j] < a[i])
			j++;
		Convert(a, i, index - 1, j - 1);
		i += j - index;
	}
}

void Merge_Sort(int a[], int L, int R)
{
	if (L < R)
	{
		int M = L + (R - L) / 2;
		Merge_Sort(a, L, M);
		Merge_Sort(a, M + 1, R);
		Merge(a, L, M, R);
	}
}

int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		Merge_Sort(a, 0, n - 1);
		for (int i = 0; i < n; i++)
			printf("%d%c", a[i], i == n - 1 ? '\n' : ' ');
	}
	return 0;
}
