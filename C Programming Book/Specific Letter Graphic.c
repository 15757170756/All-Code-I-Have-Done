/*******************************
��д�������붥���ַ���ͼ�εĸߣ�
���һ��ͼ�Σ�
              A
			B   B 
		   C     C
		  D       D
		 E         E
		  D       D
		   C     C
		    B   B
			  A
********************************/


#include<stdio.h>

void main()
{
	int i, j, k, n, m;
	char c;
	printf("�����붥����ĸ��ͼ�εĸ�(�и�ֻ��Ϊ����)��\n");
	scanf("%c%d", &c, &n);
	n = n / 2;
	for (i = 1; i <= n + 1; i++)
	{
		for (j = 1; j <= n - i + 1; j++)
			printf(" ");
		printf("%c", c++);
		if (i != 1)
		{
			for (k = 1; k <= 2 * i - 3; k++)
			{
				printf(" ");
			}
			m = k - 1;
			printf("%c", c - 1);
		}
		printf("\n");
	}
	c--;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= i; j++)
			printf(" ");
		printf("%c", --c);
		if (i != n)
		{
			for (k = (m -= 2); k >= 1; k--)
				printf(" ");
			printf("%c", c);
		}
		printf("\n");
	}
}

//���������ҵ�