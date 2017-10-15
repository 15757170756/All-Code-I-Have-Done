/**************************************
将字符串中的”*“全部移动到字符串的尾部
***************************************/

#include <stdio.h>
#include <string.h>

void fun(char ch[]);

int main()
{
	char ch[] = "***a**bbc****";
	fun(ch);

	return 0;
}

void fun(char ch[])
{
	char* temp = ch;
	int count = 0;
	size_t len = strlen(ch);
	for (int i = 0, j = 0; i < len; ++i) {
		if (ch[i] == '*')
			count++;
		else
			temp[j++] = ch[i];
	}

	for (int i = len - count; i < len; ++i) {
		temp[i] = '*';
	}
	puts(ch);
}