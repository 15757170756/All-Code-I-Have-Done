#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>
#include <unordered_set>
#include <sstream>
#include <map>
#include <iterator>
#include <set>

using namespace::std;

struct listNode
{
	int data;
	listNode *next;
	listNode(int data) :data(data), next(nullptr){}
};

typedef listNode* linkList;

void push_front(linkList *pHead, int value)
{
	listNode *newNode = new listNode(value);
	if (*pHead == nullptr) {
		(*pHead) = newNode;
		(*pHead)->next = nullptr;
		return;
	}
	else {
		newNode->next = (*pHead);
		(*pHead) = newNode;
	}

}

void linkListNode(listNode *pHead, listNode *addNode)
{
	pHead->next = addNode;
}

void printList(linkList pHead)
{
	while (pHead != nullptr) {
		cout << pHead->data << ' ';
		pHead = pHead->next;
	}
}

listNode* meetingNdoe(listNode *pHead)
{
	if (pHead == nullptr)
		return nullptr;
	listNode *pSlow = pHead->next;
	if (pSlow == nullptr)
		return nullptr;

	listNode *pFast = pSlow->next;
	while (pFast != nullptr
		&& pSlow != nullptr) {
		if (pFast == pSlow)
			return pFast;
		pSlow = pSlow->next;

		pFast = pFast->next;
		if (pFast != nullptr)
			pFast = pFast->next;
	}

	return nullptr;
}

listNode* entryNodeOfLoop(listNode *pHead)
{
	listNode *meetNode = meetingNdoe(pHead);
	if (meetNode == nullptr)
		return nullptr;
	int nodesInLoop = 1;
	listNode *pNode1 = meetNode;
	while (pNode1->next != meetNode) {
		++nodesInLoop;
		pNode1 = pNode1->next;
	}

	pNode1 = pHead;
	listNode *pNode2 = pHead;
	for (int i = 0; i < nodesInLoop; ++i)
		pNode1 = pNode1->next;
	while (pNode1 != pNode2) {
		pNode1 = pNode1->next;
		pNode2 = pNode2->next;
	}

	return pNode1;
}

//循环链表有环 测试
void test1()
{
	listNode *p1 = new listNode(1);
	listNode *p2 = new listNode(2);
	listNode *p3 = new listNode(3);
	listNode *p4 = new listNode(4);
	linkListNode(p1, p2);
	//linkListNode(p2, p1);
	linkListNode(p2, p3);
	linkListNode(p3, p4);
	linkListNode(p4, p2);
	cout << entryNodeOfLoop(p1)->data << endl;
}

int main(int argc, char* argv[])
{
	test1();

	return 0;
}


