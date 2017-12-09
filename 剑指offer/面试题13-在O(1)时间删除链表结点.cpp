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

void pushBack(linkList* pHead, int value)
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

/*
删除链表中的某一个结点
O(1)复杂度,
感觉和我之前写的代码有些不一样
这个要求把要删除的结点的指针地址知道的
而一般都是按data来删除的，所以并不是很
适用的
*/
void deleteNodeO1(linkList* pHead, listNode* pToBeDeleted)
{
	if (!pHead || !pToBeDeleted)
		return;

	if (pToBeDeleted->next != nullptr) {
		listNode* pNext = pToBeDeleted->next;
		pToBeDeleted->data = pNext->data;
		pToBeDeleted->next = pNext->next;

		delete pNext;
		pNext = nullptr;
	}

	else if (*pHead == pToBeDeleted) {
		delete pToBeDeleted;
		pToBeDeleted = nullptr;
		*pHead = nullptr;
	}

	else {
		listNode* pNode = *pHead;
		while (pNode->next != pToBeDeleted)
			pNode = pNode->next;

		pNode->next = nullptr;
		delete pToBeDeleted;
		pToBeDeleted = nullptr;
	}
}

int main()
{
	linkList pHead = nullptr;
	pushBack(&pHead, 1);
	pushBack(&pHead, 2);
	pushBack(&pHead, 3);
	pushBack(&pHead, 4);
	printList(pHead);
	cout << endl;

	listNode* deletedNode = new listNode();
	deletedNode->data = 4;
	deletedNode->next = nullptr;
	deleteNodeOn(&pHead, deletedNode);
	printList(pHead);


	return 0;
}