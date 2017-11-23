#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>

using namespace std;

int native_string_matcher(char* mainStr, char* subStr);
int* compute_prefix_function(char* patten);
int KMP_match(char* text, char* patten);


int main(int argc, char* argv[])
{
	char* mainStr = "abcabcabcd";
	char* subStr = "abc";
	int idx = native_string_matcher(mainStr, subStr);
	cout << idx << endl;

	idx = KMP_match(mainStr, subStr);
	cout << idx << endl;
	return 0;
}


int native_string_matcher(char* mainStr, char* subStr)
{
	int mainStrLen = strlen(mainStr);
	int subStrLen = strlen(subStr);
	int end = mainStrLen - subStrLen;
	for (int i = 0, j; i <= end; ++i) {
		for (j = 0; j < subStrLen;) {
			if (subStr[j] == mainStr[i + j]) {
				j++;
			}
			else
				break;
		}
		if (j == subStrLen) {
			return i;
		}
	}

	return -1;
}


/*
构建next数组
ababaca的next数组为：
0012302
当前字符与前面字符组合
的最长前缀与后缀匹配
*/
int* compute_prefix_function(char* patten)
{
	int m = strlen(patten);
	int* next = (int*)malloc(m*sizeof(int));
	next[0] = 0;
	int k = 0;
	for (int q = 1; q < m; ++q) {
		while (k > 0 && patten[k] != patten[q])
			k = next[k - 1];
		if (patten[k] == patten[q])
			k++;
		next[q] = k;
	}
	return next;
}

int KMP_match(char* text, char* patten)
{
	int n = strlen(text);
	int m = strlen(patten);
	int* next = compute_prefix_function(patten);
	int q = 0;
	for (int i = 0; i < n; ++i) {
		while (q > 0 && patten[q] != text[i])
			q = next[q - 1];
		if (patten[q] == text[i])
			q++;
		if (q == m) {
			free(next);
			next = NULL;
			return i + 1 - m;
		}
	}
	return -1;
}