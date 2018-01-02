#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace::std;

struct BinaryTreeNode {
	int data;
	BinaryTreeNode* leftChild;
	BinaryTreeNode* rightChild;
};

typedef BinaryTreeNode* BinaryTree;

/*
比较笨的方法构建二叉树
*/
BinaryTreeNode* CreateBinaryTreeNode(int data)
{
	BinaryTreeNode* pNode = new BinaryTreeNode();
	pNode->data = data;
	pNode->leftChild = nullptr;
	pNode->rightChild = nullptr;

	return pNode;
}

void ConnectTreeNodes(
	BinaryTreeNode* parent,
	BinaryTreeNode* leftChild,
	BinaryTreeNode* rightChild)
{
	if (parent != nullptr) {
		parent->leftChild = leftChild;
		parent->rightChild = rightChild;
	}
}

void printFromTopToBottom(BinaryTreeNode* pRoot)
{
	if (!pRoot)
		return;

	queue<BinaryTreeNode*> queueTreeNode;
	queueTreeNode.push(pRoot);

	while (!queueTreeNode.empty()) {
		BinaryTreeNode* temp = queueTreeNode.front();
		queueTreeNode.pop();
		cout << temp->data << ' ';

		if (temp->leftChild)
			queueTreeNode.push(temp->leftChild);
		if (temp->rightChild)
			queueTreeNode.push(temp->rightChild);
	}
}


int main()
{
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode14 = CreateBinaryTreeNode(14);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
	BinaryTreeNode* pNode16 = CreateBinaryTreeNode(16);

	ConnectTreeNodes(pNode10, pNode6, pNode14);
	ConnectTreeNodes(pNode6, pNode4, pNode8);
	ConnectTreeNodes(pNode14, pNode12, pNode16);

	printf("The nodes from top to bottom, from left to right are: \n");
	printFromTopToBottom(pNode10);

	printf("\n\n");

	return 0;
}