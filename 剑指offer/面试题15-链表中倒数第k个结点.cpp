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
不够鲁棒性的代码
*/
listNode* findKthToTail1(linkList pHead, unsigned int k)
{
	listNode* pAhead = pHead;
	listNode* pBehind = nullptr;
	while (k - 1) {
		pAhead = pAhead->next;
		--k;
	}
	pBehind = pHead;
	while (pAhead->next != nullptr) {
		pBehind = pBehind->next;
		pAhead = pAhead->next;
	}
	return pBehind;
}


/*
判断很多边界条件
*/
listNode* findKthToTail2(linkList pHead, unsigned int k)
{
	if (!pHead || k <= 0)
		return nullptr;

	listNode* pAhead = pHead;
	listNode* pBehind = nullptr;
	while (k - 1) {
		if (pAhead->next != nullptr)
			pAhead = pAhead->next;
		else
			return nullptr;
		--k;
	}
	pBehind = pHead;
	while (pAhead->next != nullptr) {
		pBehind = pBehind->next;
		pAhead = pAhead->next;
	}
	return pBehind;
}

int main()
{
	linkList pHead = nullptr;
	push_front(&pHead, 1);
	push_front(&pHead, 2);
	push_front(&pHead, 1);
	push_front(&pHead, 4);
	push_front(&pHead, 5);
	push_front(&pHead, 1);
	printList(pHead);
	cout << endl;

	listNode* Kth = findKthToTail2(pHead, 3);
	if (Kth == nullptr)
		cout << "输入错误\n";
	else
		cout << Kth->data << endl;

	return 0;
}