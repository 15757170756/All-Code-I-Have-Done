#include <stdio.h>

void num2strRecu(int n);

int main()
{
	int a = -912345;
	num2strRecu(a);

	return 0;
}

/***************************************
����������ҵĵݹ�汾���ŵ��ǱȽϼ��׶���
����ȱ����ֱ�Ӵ�ӡ�����ˣ�û�з���ֵ��
�����Ǵ��β��з��ء�
****************************************/
void num2strRecu(int n) {
	if (n < 0) {
		putchar('-');
		n *= (-1);
	}
	if (n / 10)
		num2strRecu(n / 10);
	putchar(n % 10 + '0');
}









#include <stdio.h>
#define MAX 20

int itoa(int n, char s[]);

int main()
{
	int a = -123;
	char s[MAX];
	int cont = itoa(a, s);
	printf("%d %s %d\n", cont, s, strlen(s));

	return 0;
}

/***************************************
����ݹ�����������ƣ����ص����ַ����ĳ��ȣ�
���б任����ַ�����
****************************************/
int itoa(int n, char s[]) {
	int i = 0;

	if (n < 0) {
		s[0] = '-';
		return 1 + itoa(-n, s + 1);
	}

	if (n / 10) {
		i = itoa(n / 10, s);
	}
	s[i] = n % 10 + '0';
	s[++i] = '\0';
	//putchar(s[i]);

	return i;
}






#include <stdio.h>
#define MAX 20

void stringReversed(char s[]);
void num2str(int n);

int main()
{
	int a = -9123621;
	char s[MAX];
	num2str(a, s);
	printf("%s\n", s);

	return 0;
}

/***************************************
�Լ�д��һ��ͨ�õķ�����������ת��Ϊ�ַ���
****************************************/
void num2str(int n, char s[])
{
	int i = 0;
	if (n < 0) {
		n *= (-1);
		putchar('-');
	}

	while (n > 0) {
		s[i] = n % 10 + '0';
		n /= 10;
		++i;
	}
	s[i] = '\0';
	stringReversed(s);
}

void stringReversed(char s[])
{
	int sLength = strlen(s);
	for (int i = 0, j = sLength; i < sLength / 2; ++i, --j) {
		char temp = s[i];
		s[i] = s[j - 1];
		s[j - 1] = temp;
	}
	s[sLength] = '\0';
}



