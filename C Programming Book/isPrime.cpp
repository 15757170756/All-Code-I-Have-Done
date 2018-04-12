/***************************************
�ж��Ƿ�Ϊ����
O(N)������ɸѡ����ŷ������
http://blog.csdn.net/Dream_you_to_life/article/details/43883367
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
			printf("��������Ȼ�������ڵ���1��������\n");
			scanf("%d", &n);
		}
		if (isPrimNum(n) == 1)
			printf("%d������\n", n);
		else if (isPrimNum(n) == 0)
			printf("%d�Ǻ���\n", n);
		else
			printf("%d�Ȳ�������Ҳ���Ǻ���\n", n);
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

bool isPrimNum2(int n)
{
	if (n < 2)
		return false;
	int k = (int)sqrt((double)n);
	for (int i = 2; i <= k; ++i)
		if (n % i == 0)
			return false;

	return true;
}