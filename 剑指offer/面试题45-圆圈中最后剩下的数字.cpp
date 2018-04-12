#include <iostream>
#include <list>
#include <algorithm>

using namespace::std;

int lastRemaining(unsigned int n, unsigned int m)
{
	if (n < 1 || m < 1)
		return -1;

	unsigned int i = 0;
	list<int> numbers;
	for (int i = 0; i < n; ++i)
		numbers.push_back(i);
	list<int>::const_iterator currentIter = numbers.begin();
	while (numbers.size() > 1) {
		for (int i = 1; i < m; ++i) {
			++currentIter;
			if (currentIter == numbers.end())
				currentIter = numbers.begin();
		}
		list<int>::const_iterator nextIter = ++currentIter;
		if (nextIter == numbers.end())
			nextIter = numbers.begin();

		--currentIter;
		numbers.erase(currentIter);
		currentIter = nextIter;
	}

	return *(currentIter);
}

int lastRemaining2(unsigned int n, unsigned int m)
{
	if (n < 1 || m < 1)
		return -1;
	int last = 0;
	for (int i = 2; i <= n; ++i)
		last = (last + m) % i;

	return last;
}


typedef struct Node {
	int data;
	struct Node *next;
}listNode, *linkList;

//头插法，建立循环链表
void push_ahead(linkList* headNode, int data)
{
	listNode *newNode = (listNode*)malloc(sizeof(listNode));
	listNode *endNode = *headNode;
	newNode->data = data;
	newNode->next = *headNode;

	if (*headNode != NULL) {
		while (endNode->next != *headNode)
			endNode = endNode->next;
		endNode->next = newNode;
	}
	else
		newNode->next = newNode;

	*headNode = newNode;
}

int JosephusProblem(linkList *headNode, int n, int m)
{
	listNode *currentNode = *headNode;
	listNode *preNode = NULL;
	while (n > 1) {
		if (m == 1) {
			listNode* temp = currentNode->next;
			free(currentNode);
			currentNode = temp;
		}
		else {
			for (int i = m - 1; i > 0; --i) {
				preNode = currentNode;
				currentNode = currentNode->next;
			}
			//delete currentNode
			preNode->next = currentNode->next;
			listNode* temp = currentNode->next;
			free(currentNode);
			currentNode = temp;
		}
		n--;
	}

	return currentNode->data;
}


int lastRemaining3(unsigned int n, unsigned int m)
{
	listNode *headNode = NULL;
	for (int i = n - 1; i >= 0; --i)
		push_ahead(&headNode, i);

	int result = JosephusProblem(&headNode, n, m);
	return result;
}



int main(int argc, char* argv[])
{
	unsigned int n = 100, m = 6;
	cout << lastRemaining(n, m) << endl;
	cout << lastRemaining2(n, m) << endl;
	cout << lastRemaining3(n, m) << endl;

	return 0;
}




