#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace::std;

const int lowercaseCnt = 26;

typedef struct TrieNode {
	int count;
	struct TrieNode* next[lowercaseCnt];
	bool exist;
}TrieNode, *TrieTree;

TrieNode* creatTrieNode()
{
	TrieNode* node = new TrieNode();
	node->count = 0;
	node->exist = false;
	memset(node->next, 0, sizeof(node->next));

	return node;
}

void insert(TrieTree root, char* word)
{
	TrieNode* node = root;
	char* p = word;
	int id;
	while (*p) {
		id = *p - 'a';
		if (nullptr == node->next[id])
			node->next[id] = creatTrieNode();

		node = node->next[id];
		++p;
		node->count += 1;
	}
	node->exist = true;
}

void search(TrieNode* root, char* str)
{
	if (nullptr == root || '\0' == *str) {
		cout << "trie is empty or str is null \n";
		return;
	}

	char*p = str;
	TrieNode* t = root;
	while (*p != '\0') {
		int id = *p - 'a';
		if (t->next[id] != nullptr) {
			t = t->next[id];
			++p;
		}
		else break;
	}

	if (*p == '\0') {
		if (0 == t->count)
			cout << "���ַ�������trie���У����Ǹô���ĳ�����ʵ�ǰ׺\n";
		else
			cout << "���ַ����ڸ�trie����\n";
	}
	else
		cout << "���ַ������ڸ�trie����\n";
}

int main()
{
	const int n = 6;
	char* str[n] = { "inn", "int", "at", "age", "adv", "ant" };
	TrieNode* root = creatTrieNode();
	for (int i = 0; i < n; ++i) {
		insert(root, str[i]);
	}
	char* findStr = "agt";
	search(root, findStr);

	return 0;
}