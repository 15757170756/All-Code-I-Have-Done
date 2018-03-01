#include <iostream>
using namespace::std;

struct ComplexListNode
{
	int data;
	ComplexListNode* next;
	ComplexListNode* sibling;
};

ComplexListNode* creatNode(int value)
{
	ComplexListNode* pNode = new ComplexListNode();
	pNode->data = value;
	pNode->next = nullptr;
	pNode->sibling = nullptr;
	return pNode;
}

void buildNodes(ComplexListNode* pNode,
	ComplexListNode* pNext,
	ComplexListNode* pSibding)
{
	if (pNode) {
		pNode->next = pNext;
		pNode->sibling = pSibding;
	}
}

void printList(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while (pNode) {
		cout << "The value of this node is: " << pNode->data << endl;
		if (pNode->sibling)
			cout << "The value of its sibling is: " <<
			pNode->sibling->data << endl;
		else
			cout << "This node does not have a sibling.\n";
		cout << endl;

		pNode = pNode->next;
	}
}

/*
这样其实不算复制，newNode的地址与pHead的地址
是一样的。。。
*/
/*
ComplexListNode* clone(ComplexListNode* pHead)
{
ComplexListNode* pNode = pHead;
ComplexListNode* newNode = new ComplexListNode();
newNode = pNode;
return newNode;
}
*/

void cloneNodes(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while (pNode) {
		ComplexListNode* newNode = new ComplexListNode();
		newNode->data = pNode->data;
		newNode->next = pNode->next;
		newNode->sibling = nullptr;

		pNode->next = newNode;
		pNode = newNode->next;
	}
}

void connectSiblingNode(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while (pNode) {
		ComplexListNode* pCloneNode = pNode->next;
		if (pNode->sibling)
			pCloneNode->sibling = pNode->sibling->next;

		pNode = pCloneNode->next;
	}
}

ComplexListNode* reconnectNodes(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	ComplexListNode* pClonedHead = nullptr;
	ComplexListNode* pClonedNode = nullptr;

	if (pNode) {
		pClonedHead = pClonedNode = pNode->next;
		pNode->next = pClonedNode->next;
		pNode = pNode->next;
	}

	while (pNode) {
		pClonedNode->next = pNode->next;
		pClonedNode = pClonedNode->next;
		pNode->next = pClonedNode->next;
		pNode = pNode->next;
	}

	return pClonedHead;
}

ComplexListNode* clone(ComplexListNode* pHead)
{
	cloneNodes(pHead);
	connectSiblingNode(pHead);
	return reconnectNodes(pHead);
}

int main()
{
	ComplexListNode* p1 = creatNode(1);
	ComplexListNode* p2 = creatNode(2);
	ComplexListNode* p3 = creatNode(3);
	ComplexListNode* p4 = creatNode(4);
	buildNodes(p1, p2, p4);
	buildNodes(p2, p3, p1);
	buildNodes(p3, p4, nullptr);
	buildNodes(p4, nullptr, p2);
	printList(p1);
	cout << endl << endl;

	ComplexListNode* pNew = clone(p1);
	printList(pNew);

	return 0;
}