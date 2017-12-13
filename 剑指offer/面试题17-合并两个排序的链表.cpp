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
删除所有值为key的结点，
不是删除单个
*/
void deleteKey(linkList* pHead, int key)
{
	if (!pHead)
		return;

	listNode* currentNode = *pHead, *preNode;
	//处理头结点要被删除
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

/*
会把传进来的头指针破坏掉
*/
listNode* reverseList(listNode* pHead)
{
	if (!pHead)
		return nullptr;

	listNode* pReverseHead = pHead;
	pHead = pHead->next;
	pReverseHead->next = nullptr;

	while (pHead) {
		listNode* nextNode = pHead->next;
		pHead->next = pReverseHead;
		pReverseHead = pHead;
		pHead = nextNode;
	}

	return pReverseHead;
}

void reverseList(linkList* pHead)
{
	if (!pHead)
		return;

	//listNode* pReverseHead = nullptr;
	listNode* preNode = nullptr;
	listNode* currentNode = (*pHead);

	while (currentNode != nullptr) {
		listNode* nextNode = currentNode->next;
		if (nextNode == nullptr)
			*pHead = currentNode;

		currentNode->next = preNode;
		preNode = currentNode;
		currentNode = nextNode;
	}
}

/*
递归解法
*/
listNode* mergeList(listNode* list1, listNode* list2)
{
	if (list1 == nullptr)
		return list2;
	else if (list2 == nullptr)
		return list1;

	listNode* pMergedHead = nullptr;
	if (list1->data < list2->data) {
		pMergedHead = list1;
		pMergedHead->next = mergeList(list1->next, list2);
	}
	else {
		pMergedHead = list2;
		pMergedHead->next = mergeList(list1, list2->next);
	}

	return pMergedHead;

}

/*
非递归解法
仿照归并排序
*/
listNode* mergeListNonRecursive(listNode* list1, listNode* list2)
{
	if (list1 == nullptr)
		return list2;
	else if (list2 == nullptr)
		return list1;

	listNode* pMergedHead = nullptr;
	listNode* currentNode = nullptr;
	while (list1 != nullptr && list2 != nullptr) {
		if (list1->data < list2->data) {
			if (pMergedHead == nullptr)
				pMergedHead = currentNode = list1;
			else {
				currentNode->next = list1;
				currentNode = currentNode->next;
			}
			list1 = list1->next;
		}
		else {
			if (pMergedHead == nullptr)
				pMergedHead = currentNode = list2;
			else {
				currentNode->next = list2;
				currentNode = currentNode->next;
			}
			list2 = list2->next;
		}
	}
	if (list1 == nullptr)
		currentNode->next = list2;
	else
		currentNode->next = list1;

	return pMergedHead;

}

int main()
{
	linkList pHead = nullptr;
	push_back(&pHead, 1);

	printList(pHead);
	cout << endl;


	linkList list2 = nullptr;
	push_back(&list2, 2);

	linkList mergedList = mergeListNonRecursive(pHead, list2);
	printList(mergedList);


	return 0;
}
