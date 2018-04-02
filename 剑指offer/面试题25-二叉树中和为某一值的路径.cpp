#include <iostream>
#include <vector>

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


void findPath(
	BinaryTree pRoot,
	int        expectedSum,
	vector<int>& path,
	int&        currentSum)
{
	currentSum += pRoot->data;
	path.push_back(pRoot->data);
	bool isLeaf = (pRoot->leftChild == nullptr
		&& pRoot->rightChild == nullptr);
	if (currentSum == expectedSum && isLeaf) {
		cout << "A path is found: ";
		vector<int>::const_iterator iter = path.begin();
		for (; iter != path.end(); ++iter)
			cout << *iter << '\t';
		cout << endl;
	}

	if (pRoot->leftChild != nullptr)
		findPath(pRoot->leftChild, expectedSum,
		path, currentSum);

	if (pRoot->rightChild != nullptr)
		findPath(pRoot->rightChild, expectedSum,
		path, currentSum);

	currentSum -= pRoot->data;
	path.pop_back();
}

void findPath(BinaryTree pRoot, int expectedSum)
{
	if (!pRoot)
		return;

	vector<int> path;
	int currentSum = 0;
	findPath(pRoot, expectedSum, path, currentSum);
}


int main()
{
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNode10, pNode5, pNode12);
	ConnectTreeNodes(pNode5, pNode4, pNode7);

	int sum = 22;
	findPath(pNode10, sum);

	return 0;
}