/*
Sample Input
a
ahat
hat
hatword
hziee
word


Sample Output
ahat
hatword



题目意思是   给你一定的单词，
要你找出能够通过其他两个单词组成的单词，
数据有50000多，字典树了
*/

#include <iostream>  
#include <cstring>  
#include <cstdio>  
#include <algorithm>  
using namespace std;

typedef struct Trie {
	int flag;
	Trie* next[26];
} Trie;

Trie* root;
int flag;
char a[50000][50];

void Inti()//初始化  
{
	root = (Trie*)malloc(sizeof(Trie));
	root->flag = 0;
	for (int i = 0; i < 26; i++)
		root->next[i] = NULL;
}

void ChaRu(char *a)//建立字典树    插入单词  
{
	Trie* p = root, *q;
	int l = strlen(a);
	for (int i = 0; i < l; i++) {
		int id = a[i] - 'a';
		if (p->next[id] == NULL) {
			q = (Trie *)malloc(sizeof(Trie));
			q->flag = 0;
			for (int i = 0; i < 26; i++)
				q->next[i] = NULL;
			p->next[id] = q;
		}
		/* else if (p->next[id]->flag) {
		flag = 1;
		}*/
		p = p->next[id];
	}
	p->flag = 1;
}

int CZ(char *a)//查找单词  
{
	Trie *p = root;
	int len = strlen(a);
	for (int i = 0; i<len; i++)
	{
		int id = a[i] - 'a';
		p = p->next[id];
		if (p == NULL)
			return 0;
	}
	return p->flag;
}

int SF(Trie *p)//释放空间    这个题不用也可以过  
{
	//    Trie *p=root;  
	if (p == NULL)
		return 0;
	for (int i = 0; i<26; i++)
	{
		if (p->next[i] != NULL)
			SF(p->next[i]);
	}
	free(p);
	return 0;
}

int main()
{

	Inti();
	int n = 0;
	while (~scanf("%s", &a[n])) {
		// flag = 0;  
		//printf("%s",a[i]);  
		ChaRu(a[n]);
		n++;
	}

	for (int i = 0; i<n; i++)
	{
		int len = strlen(a[i]);
		for (int j = 0; j<len; j++)
		{
			char str1[50] = { '\0' }, str2[50] = { '\0' };//新建两个临时数组  
			strncpy(str1, a[i], j);                //把第i个单词进行拆分，分别放入两个临时数组里面  
			strncpy(str2, a[i] + j, len - j);
			if (CZ(str1) && CZ(str2))            //通过查找函数进行查找，如果两个返回都是1，代表能够组成  
			{
				printf("%s\n", a[i]);
				break;
			}
		}
	}
	SF(root);//释放内存（这个题可以不要）  
	return 0;
}