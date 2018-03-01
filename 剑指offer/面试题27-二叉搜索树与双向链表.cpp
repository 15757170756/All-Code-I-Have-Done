#include <iostream>

using namespace::std;

struct BinaryTreeNode
{
	int data;
	BinaryTreeNode* leftChild;
	BinaryTreeNode* rightChild;
};

BinaryTreeNode* createBinaryTreeNode(int data)
{
	BinaryTreeNode* pNode = new BinaryTreeNode();
	pNode->data = data;
	pNode->leftChild = nullptr;
	pNode->rightChild = nullptr;

	return pNode;
}

void connectNodes(
	BinaryTreeNode* parent,
	BinaryTreeNode* leftChild,
	BinaryTreeNode* rightChild)
{
	if (parent) {
		parent->leftChild = leftChild;
		parent->rightChild = rightChild;
	}
}

void convertNode(BinaryTreeNode* pNode,
	BinaryTreeNode** pLastNodeInList);

BinaryTreeNode* convert(BinaryTreeNode* pRoot)
{
	BinaryTreeNode* pLastOfList = nullptr;
	convertNode(pRoot, &pLastOfList);

	BinaryTreeNode* pHeadOfList = pLastOfList;
	while (pHeadOfList && pHeadOfList->leftChild)
		pHeadOfList = pHeadOfList->leftChild;

	return pHeadOfList;
}

void convertNode(BinaryTreeNode* pNode,
	BinaryTreeNode** pLastNodeInList)
{
	if (!pNode)
		return;

	BinaryTreeNode* pCurrent = pNode;

	if (pCurrent->leftChild)
		convertNode(pCurrent->leftChild, pLastNodeInList);

	pCurrent->leftChild = *pLastNodeInList;
	if (*pLastNodeInList)
		(*pLastNodeInList)->rightChild = pCurrent;

	*pLastNodeInList = pCurrent;

	if (pCurrent->rightChild)
		convertNode(pCurrent->rightChild, pLastNodeInList);
}

void printDoubleLinkedList(BinaryTreeNode* pHead)
{
	BinaryTreeNode* pNode = pHead;
	while (pNode) {
		cout << pNode->data << ' ';
		if (!pNode->rightChild)
			break;
		pNode = pNode->rightChild;
	}
}

int main()
{
	BinaryTreeNode* pNode10 = createBinaryTreeNode(10);
	BinaryTreeNode* pNode6 = createBinaryTreeNode(6);
	BinaryTreeNode* pNode14 = createBinaryTreeNode(14);
	BinaryTreeNode* pNode4 = createBinaryTreeNode(4);
	BinaryTreeNode* pNode8 = createBinaryTreeNode(8);
	BinaryTreeNode* pNode12 = createBinaryTreeNode(12);
	BinaryTreeNode* pNode16 = createBinaryTreeNode(16);

	connectNodes(pNode10, pNode6, pNode14);
	connectNodes(pNode6, pNode4, pNode8);
	connectNodes(pNode14, pNode12, pNode16);

	printDoubleLinkedList(convert(pNode10));

	return 0;
}