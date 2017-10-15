/***************************************
insert(s1,s2,pos),在字符串s1中的指定位置
pos处插入字符串s2.
****************************************/

#include <stdio.h>
#include <assert.h>
#include <string.h>

void insert(char s1[], char s2[], int pos);

int main()
{
	char s1[20] = "1234567";
	char s2[20] = "abc";
	insert(s1, s2, 0);
	puts(s1);
	return 0;
}

void insert(char s1[], char s2[], int pos)
{
	int s1Length = strlen(s1);
	int s2Length = strlen(s2);
	if (pos > s1Length) {
		printf("error:pos > s2's length\n");
		return;
	}

	char temp[20];
	int i, j;
	for (i = pos, j = 0; i < s1Length; ++i, ++j)
		temp[j] = s1[i];
	temp[j] = '\0';
	for (int i = pos, j = 0; j < s2Length; ++i, ++j)
		s1[i] = s2[j];
	for (int i = pos + s2Length, j = 0; i < s1Length + s2Length; ++i, ++j) {
		s1[i] = temp[j];
	}
}
