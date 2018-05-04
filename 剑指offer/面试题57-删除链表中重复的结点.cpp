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

void deleteDuplication(listNode **pHead)
{
	if (pHead == nullptr || *pHead == nullptr)
		return;

	listNode *preNode = nullptr;
	listNode *curNode = *pHead;
	while (curNode != nullptr) {
		listNode *nextNode = curNode->next;
		bool needDelete = false;
		if (nextNode != nullptr
			&& curNode->data == nextNode->data)
			needDelete = true;

		if (!needDelete) {
			preNode = curNode;
			curNode = curNode->next;
		}

		else {
			int value = curNode->data;
			listNode *pToBeDel = curNode;
			while (pToBeDel != nullptr
				&& pToBeDel->data == value) {
				nextNode = pToBeDel->next;
				delete pToBeDel;
				pToBeDel = nullptr;
				pToBeDel = nextNode;
			}

			if (preNode == nullptr)
				*pHead = nextNode;
			else
				preNode->next = nextNode;
			curNode = nextNode;
		}
	}
}

void test1()
{
	listNode *p1 = new listNode(1);
	listNode *p2 = new listNode(2);
	listNode *p31 = new listNode(3);
	listNode *p32 = new listNode(3);
	listNode *p41 = new listNode(4);
	listNode *p42 = new listNode(4);
	listNode *p5 = new listNode(5);
	listNode *p61 = new listNode(6);
	listNode *p62 = new listNode(6);
	linkListNode(p1, p2);
	linkListNode(p2, p31);
	linkListNode(p31, p32);
	linkListNode(p32, p41);
	linkListNode(p41, p42);
	linkListNode(p42, p5);
	linkListNode(p5, p61);
	linkListNode(p61, p62);
	//linkListNode(p31, p32);
	printList(p1);
	cout << endl;
	deleteDuplication(&p1);
	printList(p1);
	cout << endl;
}

int main(int argc, char* argv[])
{
	test1();

	return 0;
}
