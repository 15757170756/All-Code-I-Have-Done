/***************************************
�������struct�ṹ�����class����sizeof
����Ŀ����
****************************************/
#include <iostream>

using namespace::std;

int main()
{
	class A
	{
		int a;
		short b;
		int c;
		char d;
	};
	class B
	{
		double a;
		short b;
		int c;
		char d;
	};

	cout << sizeof(A) << " " << sizeof(B) << endl;
	return 0;
}

/***************************************
���������ʹ��Linux��g++����Ļ����Ϊ16 24
��Windows���һ���ģ�
int a;   4
short b; 2
int c;   4
char d;  1

double a; 8
short b;  2
int c;    4 
char d;   1
A�����ƫ��Ϊ4�������ֽڶ���Ӧ��Ϊ
int a;   4
short b; 4
int c;   4
char d;  4
����sizeofΪ16
��B�����ƫ��Ϊ8��
****************************************/