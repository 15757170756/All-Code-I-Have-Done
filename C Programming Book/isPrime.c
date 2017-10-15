/***************************************
判断是否为素数
****************************************/

#include <stdio.h>
#include <math.h>

int isPrimNum(int n);

int main()
{
	int n;
	while (1) {
		scanf("%d", &n);
		if (n < 1) {
			printf("请输入自然数（大于等于1的整数）\n");
			scanf("%d", &n);
		}
		if (isPrimNum(n) == 1)
			printf("%d是素数\n", n);
		else if (isPrimNum(n) == 0)
			printf("%d是合数\n", n);
		else
			printf("%d既不是素数也不是合数\n", n);
	}
}

int isPrimNum(int n) {
	int i;
	int k = sqrt((double)n);
	for (i = 2; i <= k; ++i) {
		if (n % i == 0)
			return 0;
	}
	if ((i > k) && (n != 1))
		return 1;
	else
		return 2;
}