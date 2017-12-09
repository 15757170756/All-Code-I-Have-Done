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

/*
链表的各类基本操作
*/


void push_back(linkList* pHead, int value)
{
	listNode* newNode = new listNode();
	newNode->data = value;
	newNode->next = nullptr;

	if (*pHead == nullptr) {
		*pHead = newNode;
		return;
	}
	else {
		/*
		这样写有错误，因为最后把newNode
		赋值给lastNode，而不是
		lastNode->next;
		*/
		//listNode* lastNode = *pHead;
		//while (lastNode != nullptr)
		//	lastNode = lastNode->next;
		//lastNode = newNode;

		listNode* lastNode = *pHead;
		while (lastNode->next != nullptr)
			lastNode = lastNode->next;
		lastNode->next = newNode;
	}
}

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
删除链表中的某一个结点
O(n)复杂度
*/
void deleteNodeOn(linkList* pHead, listNode* pToBeDeleted)
{
	if (!pHead || !pToBeDeleted)
		return;

	listNode* currentNode = *pHead;
	listNode* preNode;
	if (currentNode->data == pToBeDeleted->data) {
		(*pHead) = (*pHead)->next;
		delete currentNode;
		return;
	}
	else {
		while (currentNode->data != pToBeDeleted->data &&
			currentNode->next != nullptr) {
			preNode = currentNode;
			currentNode = currentNode->next;
		}
		if (currentNode->next == nullptr &&
			currentNode->data != pToBeDeleted->data) {
			cout << "没有该结点\n";
			return;
		}
		else {
			preNode->next = currentNode->next;
			delete currentNode;
		}
	}
}

void insert(linkList* pHead, int index, int value)
{
	if (!pHead || index <= 0)
		return;

	listNode* newNode = new listNode();
	newNode->data = value;

	if (index == 1) {
		newNode->next = (*pHead);
		(*pHead) = newNode;
	}
	else {
		listNode* currentNode = (*pHead);
		while (index > 2 && currentNode->next != nullptr) {
			currentNode = currentNode->next;
			--index;
		}

		newNode->next = currentNode->next;
		currentNode->next = newNode;
	}
}

/*
删除所有值为key的结点，
不是删除单个
*/
void deleteKey(linkList* pHead, int key)
{
	if (!pHead)
		return;

	listNode* currentNode = *pHead, *preNode;
	while (currentNode != nullptr && currentNode->data == key) {
		*pHead = currentNode->next;
		delete currentNode;
		currentNode = *pHead;
	}

	while (currentNode != nullptr) {
		while (currentNode != nullptr && currentNode->data != key) {
			preNode = currentNode;
			currentNode = currentNode->next;
		}

		if (currentNode == nullptr)
			return;
		preNode->next = currentNode->next;
		delete currentNode;
		currentNode = preNode->next;
	}
}

int main()
{
	linkList pHead = nullptr;
	push_back(&pHead, 1);
	push_back(&pHead, 2);
	push_back(&pHead, 1);
	push_back(&pHead, 4);
	push_front(&pHead, 5);
	insert(&pHead, 1, 9);
	insert(&pHead, 4, 90);
	push_front(&pHead, 1);
	printList(pHead);
	cout << endl;

	deleteKey(&pHead, 1);
	printList(pHead);
	cout << endl;

	listNode* deletedNode = new listNode();
	deletedNode->data = 4;
	deletedNode->next = nullptr;
	deleteNodeOn(&pHead, deletedNode);
	printList(pHead);


	return 0;
}