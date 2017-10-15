#include <stdio.h>

void moveRecursion(int n, char x, char y, char z);
void moveNonRecursion(int n, char x, char y, char z);

int main()
{
	int h;
	printf("input number:\n");
	scanf("%d", &h);
	printf("the step to moving %2d diskes:\n", h);
	moveRecursion(h, 'a', 'b', 'c');

	return 0;
}

//递归实现汉诺塔问题
void moveRecursion(int n, char x, char y, char z)
{
	if (n == 1)
		printf("%c-->%c\n", x, z);
	else {
		move(n - 1, x, z, y);
		printf("%c-->%c\n", x, z);
		move(n - 1, y, x, z);
	}
}

//非递归实现汉诺塔问题
void moveNonRecursion(int n, char x, char y, char z)
{

}

