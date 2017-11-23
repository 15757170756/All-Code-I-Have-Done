#if 1

#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace::std;

typedef struct ListNode {
	int m_nValue;
	struct ListNode* m_pNext;
}ListNode, *linkedList;

void addToTail(linkedList* pHead, int value);
/*************************************
�ҵ���һ��ֵΪvalue�Ľ�㣬��ɾ��
*************************************/
void removeFirstFindNode(linkedList* pHead, int value);
/*************************************
�ҵ���һ��ֵΪvalue�Ľ�㣬��ɾ��
����ָoffer�ṩ�Ľ��
*************************************/
void RemoveNode(ListNode** pHead, int value);

void printList(ListNode* pHead);

void printListReverse(ListNode* pHead);

void printListReverseRecurse(ListNode* pHead);

void clearList(ListNode* pHead);

void test1();
void test2();
void test3();


int main()
{
	test1();
	printf("\n");
	test2();
	printf("\n");
	test3();
	printf("\n");

	return 0;
}


/*************************************
�ҵ���һ��ֵΪvalue�Ľ�㣬��ɾ��
*************************************/
void removeFirstFindNode(linkedList* pHead, int value)
{
	if (pHead == NULL || (*pHead) == NULL)
		return;

	ListNode* currentNode = *pHead, *preNode;

	/*���ͷ�����Ԫ�ص�ֵΪvalue*/
	if (currentNode->m_nValue == value) {
		(*pHead) = (*pHead)->m_pNext;
		free(currentNode);
		return;
	}

	while (currentNode != NULL && currentNode->m_nValue != value) {
		preNode = currentNode;
		currentNode = currentNode->m_pNext;
	}
	if (currentNode == NULL) {
		printf("don't find the value node!\n");
		return;
	}
	else {
		//ListNode* temp = currentNode;
		preNode->m_pNext = currentNode->m_pNext;
		free(currentNode);
		currentNode = nullptr;
	}
}

void addToTail(linkedList* pHead, int value)
{
	ListNode* addNode = (ListNode*)malloc(sizeof(ListNode));
	addNode->m_nValue = value;
	addNode->m_pNext = NULL;

	/*���ͷ���Ϊ��*/
	if ((*pHead) == NULL)
		(*pHead) = addNode;
	else {
		ListNode* temp = (*pHead);
		while (temp->m_pNext != NULL)
			temp = temp->m_pNext;
		temp->m_pNext = addNode;
	}
}


/*************************************
�ҵ���һ��ֵΪvalue�Ľ�㣬��ɾ��
����ָoffer�ṩ�Ľ��
*************************************/
void RemoveNode(ListNode** pHead, int value)
{
	if (pHead == nullptr || *pHead == nullptr)
		return;

	ListNode* pToBeDeleted = nullptr;
	if ((*pHead)->m_nValue == value) {
		pToBeDeleted = *pHead;
		*pHead = (*pHead)->m_pNext;
	}
	else {
		ListNode* pNode = *pHead;
		while (pNode->m_pNext != nullptr && pNode->m_pNext->m_nValue != value)
			pNode = pNode->m_pNext;

		if (pNode->m_pNext != nullptr && pNode->m_pNext->m_nValue == value) {
			pToBeDeleted = pNode->m_pNext;
			pNode->m_pNext = pNode->m_pNext->m_pNext;
		}
	}

	if (pToBeDeleted != nullptr) {
		free(pToBeDeleted);
		pToBeDeleted = nullptr;
	}
}

void printListReverse(ListNode* pHead)
{
	stack<ListNode*> nodes;

	ListNode* pNode = pHead;
	while (pNode != nullptr) {
		nodes.push(pNode);
		pNode = pNode->m_pNext;
	}

	while (!nodes.empty()) {
		pNode = nodes.top();
		printf("%d ", pNode->m_nValue);
		nodes.pop();
	}
}

void printListReverseRecurse(ListNode* pHead)
{
	if (pHead != nullptr) {
		if (pHead->m_pNext != nullptr)
			printListReverseRecurse(pHead->m_pNext);
		printf("%d ", pHead->m_nValue);
	}
}

void clearList(ListNode* pHead)
{
	ListNode* tempNode = pHead;
	while (tempNode != nullptr) {
		pHead = pHead->m_pNext;
		free(tempNode);
		tempNode = pHead;
	}
}


void printList(ListNode* pHead)
{
	ListNode* currNode = pHead;
	while (currNode != nullptr) {
		printf("%d ", currNode->m_nValue);
		currNode = currNode->m_pNext;
	}
}

/*������*/
void test1()
{
	ListNode* pHead = nullptr;
	printList(pHead);
	printListReverse(pHead);
	printListReverseRecurse(pHead);
	clearList(pHead);
}

/*����һ��Ԫ������*/
void test2()
{
	ListNode* pHead = nullptr;
	addToTail(&pHead, 1);
	printList(pHead);
	printListReverse(pHead);
	printListReverseRecurse(pHead);
	clearList(pHead);
}

/*���ж��Ԫ������*/
void test3()
{
	ListNode* pHead = nullptr;
	for (int i = 0; i < 10; i += 2)
		addToTail(&pHead, i);
	printList(pHead);
	printListReverse(pHead);
	printListReverseRecurse(pHead);
	clearList(pHead);
}

#endif