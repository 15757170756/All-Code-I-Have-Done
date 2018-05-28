/*
题意：给定一个包含N(N<=3000)个正整数的序列，
每个数不超过5000，对它们两两相加得到的N*(N-1)/2个和，求出其中前M大的数
(M<=1000)并按从大到小的顺序排列。
*/

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

int a[3005], count[10005];
bool b[10005];

int main()
{
	int i, j, m, n;
	while (~scanf("%d%d", &n, &m))
	{
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);
		memset(b, 0, sizeof(b));
		memset(count, 0, sizeof(count));
		for (i = 0; i < n; i++)
		{
			for (j = i + 1; j < n; j++)
			{
				b[a[i] + a[j]] = 1;
				count[a[i] + a[j]]++;
			}
		}
		for (i = 10000; m >= 1; i--)
		{
			if (b[i])
			{
				while (count[i]--)
				{
					printf("%d", i);
					if (m > 1) printf(" ");
					else    puts("");
					m--;
					if (m < 1) break;
				}
			}
		}
	}
	return 0;
}
