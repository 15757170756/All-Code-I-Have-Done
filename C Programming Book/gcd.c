//�������������Լ������С������
//һ�㷽��
#include<stdio.h>
int main()
{
	int n, m, gbs, gys;
	scanf("%d%d", &n, &m);
	for (gbs = m; gbs % m != 0 || gbs % n != 0; gbs += m); //O(n)
	gys = n * m / gbs;
	printf("��С������%d\n���Լ��%d\n", gbs, gys);
}


//շת����� O(lgn)
int fun(int a, int b)	/* 2�����Ĺ�Լ�� */
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


//�ݹ�շת�����
long long gcd(long long x, long long y){
	if (y == 0)
		return x;
	else 
		return gcd(y, x%y);
}


//������Ϊa��b(a > b)����a��b���Լ��(a��b)�Ĳ������£���a����b��
//��a��b = q......r1(0��r1)����r1 = 0����(a��b) = b����r1��0��������b����r1��
//��b��r1 = q......r2(0��r2��.��r2 = 0����(a��b) = r1����r2��0���������r1����r2��
//���������ȥ��ֱ��������Ϊֹ�������һ������Ϊ0�ı������ĳ�����Ϊ(a, b)�����Լ����