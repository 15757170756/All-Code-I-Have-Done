/***************************************
判断是否为回文 当然少不了递归算法
****************************************/

#include<iostream>  
using namespace std;

//判断一个长度为length的字符串str是否为回文
bool isPalin(const char* str, int length)
{
	if (length <= 1)
		return true;
	if (str[0] != str[length - 1])
		return false;
	return isPalin(str + 1, length - 2);
}

int main(void)
{
	char *s = "abcba";
	int length = strlen(s);
	cout << isPalin(s, length) << endl;
}