/*
http://blog.csdn.net/acdreamers/article/details/8989048
题意：

给你n个整数，请按从大到小的顺序输出其中前m大的数。
每组测试数据有两行，第一行有两个数n,m(0<n,m<1000000)，第二行包含n
个各不相同，且都处于区间[-500000,500000]的整数。
*/

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

const int N = 1000005;

int a[N];

int main()
{
	int t, i, m, n;
	while (~scanf("%d%d", &n, &m))
	{
		memset(a, 0, sizeof(a));
		for (i = 0; i < n; i++)
		{
			scanf("%d", &t);
			a[500000 + t] = 1;
		}
		for (i = 1000000; m >= 1; i--)
		{
			if (a[i])
			{
				printf("%d", i - 500000);
				if (m > 1) printf(" ");
				else    puts("");
				m--;
			}
		}
	}
	return 0;
}
