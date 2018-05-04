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

bool isCircle(listNode *pHead)
{
	if (pHead == nullptr)
		return false;
	if (pHead->next == pHead)
		return true;

	listNode *slowNode = pHead;
	listNode *fastNode = pHead;

	slowNode = slowNode->next;
	bool flag = false;
	while (slowNode != fastNode) {
		if (flag == false) {
			flag = true;
			fastNode = fastNode->next;
			if (fastNode != nullptr)
				fastNode = fastNode->next;
			else
				return false;
		}

		else {
			slowNode = slowNode->next;
			fastNode = fastNode->next;
			if (fastNode != nullptr)
				fastNode = fastNode->next;
		}
		if (slowNode->next == nullptr
			|| fastNode == nullptr
			|| fastNode->next == nullptr)
			return false;
	}
	if (slowNode == fastNode)
		return true;
	else
		return false;
}

bool isCircle2(listNode *pHead)
{
	if (pHead == nullptr)
		return false;

	listNode *pSlow = pHead->next;
	if (pSlow == nullptr)
		return false;

	listNode *pFast = pSlow->next;
	while (pFast != nullptr 
		&& pSlow != nullptr) {
		if (pFast == pSlow)
			return true;
		pSlow = pSlow->next;
		pFast = pFast->next;
		if (pFast != nullptr)
			pFast = pFast->next;
	}

	return false;
}

//单向链表，没有环测试
void test1()
{
	linkList pHead = nullptr;
	push_front(&pHead, 1);
	//push_front(&pHead, 2);
	//push_front(&pHead, 1);
	//push_front(&pHead, 4);
	//push_front(&pHead, 5);
	//push_front(&pHead, 1);
	printList(pHead);
	cout << endl;

	cout << isCircle2(pHead) << endl;
}

//循环链表有环 测试
void test2()
{
	listNode *p1 = new listNode(1);
	listNode *p2 = new listNode(2);
	listNode *p3 = new listNode(3);
	listNode *p4 = new listNode(4);
	linkListNode(p1, p2);
	linkListNode(p2, p1);
	//linkListNode(p2, p3);
	//linkListNode(p3, p4);
	//linkListNode(p4, p2);
	//printList(p1);
	//cout << endl;

	//listNode *p = nullptr;
	cout << isCircle2(p1) << endl;
}

void test3()
{
	listNode *p1 = new listNode(1);
	listNode *p2 = new listNode(2);
	listNode *p3 = new listNode(3);
	listNode *p4 = new listNode(4);
	linkListNode(p1, p2);
	//linkListNode(p2, p1);
	linkListNode(p2, p3);
	linkListNode(p3, p4);
	linkListNode(p4, p4);


	//listNode *p = nullptr;
	cout << isCircle2(p1) << endl;
}

int main(int argc, char* argv[])
{
	test1();
	test2();
	test3();

	return 0;
}




