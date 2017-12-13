#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace::std;

struct listNode {
	int data;
	listNode* next;
};
typedef listNode* linkList;

void push_front(linkList* pHead, int value)
{
	listNode* newNode = new listNode();
	newNode->data = value;
	if ((*pHead) == nullptr) {
		(*pHead) = newNode;
		(*pHead)->next = nullptr;
		return;
	}
	else {
		newNode->next = (*pHead);
		(*pHead) = newNode;
	}
}

void printList(linkList pHead)
{
	while (pHead != nullptr) {
		cout << pHead->data << ' ';
		pHead = pHead->next;
	}
}

/*
反转链表，有返回值
在STL slist上看的代码
*/
listNode* reverseList1(linkList pHead)
{
	if (!pHead)
		return nullptr;

	listNode* pReservedHead = pHead;
	pReservedHead->next = nullptr;
	pHead = pHead->next;

	while (pHead) {
		listNode* nextNode = pHead->next;
		pHead->next = pReservedHead;
		pReservedHead = pHead;
		pHead = nextNode;
	}
	return pReservedHead;
}

/*
反转链表，有返回值
在剑指offer上看的代码
*/
listNode* reverseList2(linkList pHead)
{
	listNode* pReservedHead = nullptr;
	listNode* currentNode = pHead;
	listNode* preNode = nullptr;

	while (currentNode != nullptr) {
		listNode* nextNode = currentNode->next;
		if (nextNode == nullptr)
			pReservedHead = currentNode;

		currentNode->next = preNode;
		preNode = currentNode;
		currentNode = nextNode;
	}
	return pReservedHead;
}

/*
反转链表，无返回值
在
剑指offer上看的代码
*/
void reverseList3(linkList* pHead)
{
	listNode* currentNode = *pHead;
	listNode* preNode = nullptr;

	while (currentNode != nullptr) {
		listNode* nextNode = currentNode->next;
		if (nextNode == nullptr)
			(*pHead) = currentNode;

		currentNode->next = preNode;
		preNode = currentNode;
		currentNode = nextNode;
	}
}


int main()
{
	linkList pHead = nullptr;
	push_front(&pHead, 1);
	push_front(&pHead, 2);
	push_front(&pHead, 3);
	push_front(&pHead, 4);

	printList(pHead);
	cout << endl;

	listNode* newHead = reverseList2(pHead);
	printList(newHead);
	cout << endl;

	reverseList3(&newHead);
	printList(newHead);
	cout << endl;

	return 0;
}
