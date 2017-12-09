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
		����д�д�����Ϊ����newNode
		��ֵ��lastNode��������
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
ɾ�������е�ĳһ�����
O(n)���Ӷ�
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
			cout << "û�иý��\n";
			return;
		}
		else {
			preNode->next = currentNode->next;
			delete currentNode;
		}
	}
}

/*
ɾ�������е�ĳһ�����
O(1)���Ӷ�,
�о�����֮ǰд�Ĵ�����Щ��һ��
���Ҫ���Ҫɾ���Ľ���ָ���ַ֪����
��һ�㶼�ǰ�data��ɾ���ģ����Բ����Ǻ�
���õ�
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