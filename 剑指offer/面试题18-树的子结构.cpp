#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>

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

bool doseTreeHaveTree2(BinaryTreeNode* tree1,
	BinaryTreeNode* tree2)
{
	if (tree2 == nullptr)
		return true;
	if (tree1 == nullptr)
		return false;

	if (tree1->data != tree2->data)
		return false;

	return (doseTreeHaveTree2(tree1->leftChild, tree2->leftChild) &&
		doseTreeHaveTree2(tree1->rightChild, tree2->rightChild));
}

bool hasSubTree(BinaryTreeNode* tree1, BinaryTreeNode* tree2)
{
	bool result = false;

	if (!tree1 || !tree2)
		return false;

	if (tree1->data == tree2->data)
		result = doseTreeHaveTree2(tree1, tree2);

	if (!result)
		result = hasSubTree(tree1->leftChild, tree2);
	if (!result)
		result = hasSubTree(tree1->rightChild, tree2);
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

	BinaryTreeNode* pNodeB1 = creatBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = creatBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = creatBinaryTreeNode(4);
	connectTreeNode(pNodeB1, pNodeB2, pNodeB3);

	cout << boolalpha << hasSubTree(pNodeA1, pNodeB1) << noboolalpha << endl;

	return 0;
}