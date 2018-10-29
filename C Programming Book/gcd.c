//求两个数的最大公约数和最小公倍数
//一般方法
#include<stdio.h>
int main()
{
	int n, m, gbs, gys;
	scanf("%d%d", &n, &m);
	for (gbs = m; gbs % m != 0 || gbs % n != 0; gbs += m); //O(n)
	gys = n * m / gbs;
	printf("最小公倍数%d\n最大公约数%d\n", gbs, gys);
}


//辗转相除法 O(lgn)
int fun(int a, int b)	/* 2个数的公约数 */
{
	int t;
	while (b)
	{
		t = a%b;
		a = b;
		b = t;
	}
	return a;
}


//递归辗转相除法
long long gcd(long long x, long long y){
	if (y == 0)
		return x;
	else 
		return gcd(y, x%y);
}


//设两数为a、b(a > b)，求a和b最大公约数(a，b)的步骤如下：用a除以b，
//得a÷b = q......r1(0≤r1)。若r1 = 0，则(a，b) = b；若r1≠0，则再用b除以r1，
//得b÷r1 = q......r2(0≤r2）.若r2 = 0，则(a，b) = r1，若r2≠0，则继续用r1除以r2，
//……如此下去，直到能整除为止。其最后一个余数为0的被除数的除数即为(a, b)的最大公约数。