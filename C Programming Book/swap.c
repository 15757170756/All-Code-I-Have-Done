/***************************************
用三种方法交换两个数字，其中两种不使用
临时变量
****************************************/

#include <stdio.h>

void swap1(int* a, int* b);
void swap2(int* a, int* b);
void swap3(int* a, int* b);

int main()
{
	int a = 1, b = 0;
	printf("交换前a=%d, b=%d\n", a, b);
	swap1(&a, &b);
	printf("swap1函数交换后a=%d, b=%d\n", a, b);
	swap2(&a, &b);
	printf("swap2函数再次交换后a=%d, b=%d\n", a, b);
	swap3(&a, &b);
	printf("swap3函数再次交换后a=%d, b=%d\n", a, b);
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