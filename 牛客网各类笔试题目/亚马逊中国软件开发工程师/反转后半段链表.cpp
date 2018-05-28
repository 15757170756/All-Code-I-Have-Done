#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <stack>
#include <queue>

using namespace::std;

struct linkListNode
{
	int value;
	linkListNode *next;
	linkListNode(int value) :value(value), next(nullptr){}
};

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

int getListLength(linkListNode *pList)
{
	int length = 0;
	linkListNode *curList = pList;
	while (curList != nullptr) {
		++length;
		curList = curList->next;
	}
	return length;
}

linkListNode* reverseTotalList(linkListNode *pList)
{
	linkListNode *curNode = pList;
	linkListNode *preNode = nullptr;

	linkListNode *pHead = nullptr;
	while (curNode != nullptr) {
		linkListNode *nextNode = curNode->next;

		if (nextNode == nullptr) {
			pHead = curNode;
			//return pHead;
		}
		curNode->next = preNode;
		preNode = curNode;
		curNode = nextNode;
		//curNode = curNode->next;
	}

	return pHead;
}

linkListNode* reverseLinkedList(linkListNode *pList)
{
	int length = getListLength(pList);
	if (length == 1 || length == 0)
		return pList;

	int index = (length + 1) / 2;
	if (length % 2 == 0)
		index += 1;

	linkListNode *curNode = pList;
	linkListNode *preNode = nullptr;
	while (--index) {
		preNode = curNode;
		curNode = curNode->next;
	}

	linkListNode *newHead = reverseTotalList(curNode);
	preNode->next = newHead;

	return pList;
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
	//addToTail(&pHead, 7);
	printList(pHead);

	//printList(reverseTotalList(&pHead));
	printList(reverseLinkedList(pHead));
}

int main(int argc, char* argv[])
{
	test1();
}

