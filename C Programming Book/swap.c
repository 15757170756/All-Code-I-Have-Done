/***************************************
�����ַ��������������֣��������ֲ�ʹ��
��ʱ����
****************************************/

#include <stdio.h>

void swap1(int* a, int* b);
void swap2(int* a, int* b);
void swap3(int* a, int* b);

int main()
{
	int a = 1, b = 0;
	printf("����ǰa=%d, b=%d\n", a, b);
	swap1(&a, &b);
	printf("swap1����������a=%d, b=%d\n", a, b);
	swap2(&a, &b);
	printf("swap2�����ٴν�����a=%d, b=%d\n", a, b);
	swap3(&a, &b);
	printf("swap3�����ٴν�����a=%d, b=%d\n", a, b);
}

void swap1(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void swap2(int* a, int* b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}
void swap3(int* a, int* b)
{
	*a = *a^*b;
	*b = *a^*b;
	*a = *a^*b;
}