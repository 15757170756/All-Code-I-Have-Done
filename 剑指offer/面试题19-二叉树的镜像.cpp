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
BinaryTreeNode* creatBinaryTreeNode(int data)
{
	BinaryTreeNode* pNode = new BinaryTreeNode();
	pNode->data = data;
	pNode->leftChild = nullptr;
	pNode->rightChild = nullptr;

	return pNode;
}

void connectTreeNode(
	BinaryTreeNode* parent,
	BinaryTreeNode* leftChild,
	BinaryTreeNode* rightChild)
{
	if (parent != nullptr) {
		parent->leftChild = leftChild;
		parent->rightChild = rightChild;
	}
}

void mirrorTree(BinaryTreeNode* root)
{
	if (!root || (!root->leftChild &&
		!root->rightChild))
		return;

	//先看根节点的两个子节点
	BinaryTreeNode* pTemp = root->leftChild;
	root->leftChild = root->rightChild;
	root->rightChild = pTemp;

	if (root->leftChild)
		mirrorTree(root->leftChild);

	if (root->rightChild)
		mirrorTree(root->rightChild);

}

void levelTraverse(BinaryTreeNode* root)
{
	queue<BinaryTreeNode*> queueTree;
	BinaryTreeNode* currentNode = root;
	queueTree.push(currentNode);

	while (!queueTree.empty()){
		currentNode = queueTree.front();
		cout << currentNode->data << ' ';
		queueTree.pop();
		if (currentNode->leftChild)
			queueTree.push(currentNode->leftChild);
		if (currentNode->rightChild)
			queueTree.push(currentNode->rightChild);
	}
}

int main()
{
	BinaryTreeNode* pNodeA1 = creatBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = creatBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = creatBinaryTreeNode(7);
	BinaryTreeNode* pNodeA4 = creatBinaryTreeNode(9);
	BinaryTreeNode* pNodeA5 = creatBinaryTreeNode(2);
	BinaryTreeNode* pNodeA6 = creatBinaryTreeNode(4);
	BinaryTreeNode* pNodeA7 = creatBinaryTreeNode(7);
	connectTreeNode(pNodeA1, pNodeA2, pNodeA3);
	connectTreeNode(pNodeA2, pNodeA4, pNodeA5);
	connectTreeNode(pNodeA5, pNodeA6, pNodeA7);

	levelTraverse(pNodeA1);
	cout << endl;

	mirrorTree(pNodeA1);
	levelTraverse(pNodeA1);

	return 0;
}