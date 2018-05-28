#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <stack>
#include <queue>
#include <functional>

using namespace::std;

struct linkListNode
{
	int value;
	linkListNode *next;
	linkListNode(int value) :value(value), next(nullptr){}
};

linkListNode* copy(linkListNode *pHead)
{
	if (pHead == NULL)
		return NULL;
	linkListNode *curNode = pHead;

	linkListNode *newHead = new linkListNode(curNode->value);
	linkListNode *preNode = newHead;
	while (curNode->next != NULL) {
		curNode = curNode->next;
		linkListNode *addNode = new linkListNode(curNode->value);
		preNode->next = addNode;
		preNode = preNode->next;
	}

	return newHead;
}


void addToTail(linkListNode **pHead, int value)
{
	linkListNode *pNew = new linkListNode(value);
	if (*pHead == nullptr)
		*pHead = pNew;

	else {
		linkListNode *pNode = *pHead;
		while (pNode->next != nullptr)
			pNode = pNode->next;
		pNode->next = pNew;
	}
}

void printList(linkListNode *pHead)
{
	linkListNode *curNode = pHead;
	while (curNode != nullptr) {
		cout << curNode->value << ' ';
		curNode = curNode->next;
	}
	cout << endl;
}

void test1()
{
	linkListNode *pHead = new linkListNode(2);
	addToTail(&pHead, 3);
	addToTail(&pHead, 6);
	addToTail(&pHead, 1);
	addToTail(&pHead, 4);
	addToTail(&pHead, 8);
	addToTail(&pHead, 9);

	printList(pHead);

	printList(copy(pHead));
}

int main(int argc, char* argv[])
{
	test1();

}

