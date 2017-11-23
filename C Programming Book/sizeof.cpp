/***************************************
各类关于struct结构体或者class中求sizeof
的题目集锦
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
解析：如果使用Linux中g++编译的话输出为16 24
和Windows输出一样的；
int a;   4
short b; 2
int c;   4
char d;  1

double a; 8
short b;  2
int c;    4 
char d;   1
A中最大偏移为4，按照字节对齐应该为
int a;   4
short b; 4
int c;   4
char d;  4
所以sizeof为16
而B中最大偏移为8，
****************************************/