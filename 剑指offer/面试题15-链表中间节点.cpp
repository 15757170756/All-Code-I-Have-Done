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

void printList(linkList pHead)
{
	while (pHead != nullptr) {
		cout << pHead->data << ' ';
		pHead = pHead->next;
	}
}

listNode* midNode(listNode *pHead)
{
	if (pHead == nullptr)
		return nullptr;

	listNode *slowNode = pHead;
	listNode *fastNode = pHead;

	if (slowNode->next == nullptr)
		return slowNode;

	while (fastNode != nullptr) {
		slowNode = slowNode->next;
		fastNode = fastNode->next;
		if (fastNode != nullptr)
			fastNode = fastNode->next;
		if (fastNode == nullptr
			|| fastNode->next == nullptr)
			return slowNode;

	}
	return slowNode;
}

void test1()
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

	cout << midNode(pHead)->data << endl;
}

void test2()
{
	linkList pHead = nullptr;
	push_front(&pHead, 1);
	push_front(&pHead, 2);
	push_front(&pHead, 3);
	push_front(&pHead, 4);
	push_front(&pHead, 5);
	printList(pHead);
	cout << endl;

	cout << midNode(pHead)->data << endl;
}

void test3()
{
	linkList pHead = nullptr;
	push_front(&pHead, 1);
	push_front(&pHead, 2);
	push_front(&pHead, 3);
	printList(pHead);
	cout << endl;

	cout << midNode(pHead)->data << endl;
}

int main(int argc, char* argv[])
{
	test1();
	test2();
	test3();

	return 0;
}




