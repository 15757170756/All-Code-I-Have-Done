/*
大端模式，是指数据的高字节保存在内存的低地址中，
而数据的低字节保存在内存的高地址中，
这样的存储模式有点儿类似于把数据当作字符串顺序处理：地址由小向大增加，
而数据从高位往低位放；这和我们的阅读习惯一致。

小端模式，是指数据的高字节保存在内存的高地址中，
而数据的低字节保存在内存的低地址中，
这种存储模式将地址的高低和数据位权有效地结合起来，
高地址部分权值高，低地址部分权值低。
*/



#include <iostream>
#include <cstring>

using namespace::std;

int myStrlen(char *s)
{
	int cnt = 0;
	while (*s != '\0') {
		++s;
		++cnt;
	}

	return cnt;
}

void getChar(char *p)
{
	p = (char *)malloc(100);
	strcpy(p, "hello world");
}

void bigEndOrSmallEnd1()
{
	unsigned int a = 0x12345678;
	unsigned char *b = reinterpret_cast<unsigned char*>(&a);
	cout << a << endl;
	printf("%x\n", b[1]);
	if (b[0] == 0x12)
		cout << "big\n";
	if (b[0] == 0x78)
		cout << "small\n";

}

void bigEndOrSmallEnd2()
{
	short int x;
	char x0, x1;
	x = 0x1122;
	x0 = ((char*)&x)[0]; //低地址单元
	x1 = ((char*)&x)[1]; //高地址单元
	if (x0 == 0x11)
		cout << "big\n";
	if (x0 == 0x22)
		cout << "small\n";

}

void bigEndOrSmallEnd3()
{

	static union {
		char c[4];
		unsigned long l;
	}endian_test = { { 'l', '?', '?', 'b' } };
#define ENDIANNESS ((char)endian_test.l)
	if (ENDIANNESS == 'b')
		cout << "big\n";
	if (ENDIANNESS == '1')
		cout << "small\n";

}

int main(int argc, char* argv[])
{
	char s[] = "00";
	cout << strlen("\0") << endl;
	cout << sizeof("\0") << endl;

	cout << strlen(s) << endl;
	cout << sizeof(s) << endl;

	cout << myStrlen(s) << endl;

	//char a;
	//char *str = &a;
	//strcpy(str, "hello");
	//printf("%s\n", str);

	char *strp = nullptr;
	getChar(strp);
	printf("%s\n", strp);

	bigEndOrSmallEnd1();

	return 0;
}
