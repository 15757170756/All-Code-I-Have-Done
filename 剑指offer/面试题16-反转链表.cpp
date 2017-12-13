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
��ת�����з���ֵ
��STL slist�Ͽ��Ĵ���
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
��ת�����з���ֵ
�ڽ�ָoffer�Ͽ��Ĵ���
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
��ת�����޷���ֵ
��
��ָoffer�Ͽ��Ĵ���
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
