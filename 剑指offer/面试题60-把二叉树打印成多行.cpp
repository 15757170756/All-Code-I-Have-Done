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

struct BinaryTreeNode
{
	int data;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
	BinaryTreeNode() :data(0), left(nullptr), right(nullptr){}
	BinaryTreeNode(int value) :data(value), left(nullptr), right(nullptr){}
};

BinaryTreeNode* createNode(int value)
{
	BinaryTreeNode *newNode = new BinaryTreeNode(value);
	return newNode;
}

BinaryTreeNode* connectNode(BinaryTreeNode *parent,
	BinaryTreeNode *leftChild, BinaryTreeNode *rightChild)
{
	parent->left = leftChild;
	parent->right = rightChild;
	return parent;
}

void printTreeMyself(BinaryTreeNode *pRoot)
{
	if (pRoot == nullptr)
		return;
	queue<BinaryTreeNode*> qNode, printQueue;
	BinaryTreeNode *curNode = pRoot;
	qNode.push(curNode);
	printQueue = qNode;
	while (!qNode.empty()) {
		while (!printQueue.empty()) {
			BinaryTreeNode *frontNode = printQueue.front();
			cout << frontNode->data << ' ';
			printQueue.pop();
		}
		cout << endl;
		while (!qNode.empty()) {
			curNode = qNode.front();
			qNode.pop();
			if (curNode->left != nullptr)
				printQueue.push(curNode->left);
			if (curNode->right != nullptr)
				printQueue.push(curNode->right);
		}
		qNode = printQueue;
	}
}

void printTree(BinaryTreeNode *pRoot)
{
	if (pRoot == nullptr)
		return;

	queue<BinaryTreeNode*> qNodes;
	qNodes.push(pRoot);
	int nextLevel = 0;
	int toBePrinted = 1;
	while (!qNodes.empty()) {
		BinaryTreeNode *frontNode = qNodes.front();
		cout << frontNode->data << ' ';

		if (frontNode->left != nullptr) {
			qNodes.push(frontNode->left);
			++nextLevel;
		}
		if (frontNode->right != nullptr) {
			qNodes.push(frontNode->right);
			++nextLevel;
		}
		qNodes.pop();
		--toBePrinted;
		if (0 == toBePrinted) {
			cout << endl;
			toBePrinted = nextLevel;
			nextLevel = 0;
		}
	}
}

void test1()
{
	BinaryTreeNode *p10 = new BinaryTreeNode(10);
	BinaryTreeNode *p6 = new BinaryTreeNode(6);
	BinaryTreeNode *p3 = new BinaryTreeNode(3);
	BinaryTreeNode *p7 = new BinaryTreeNode(7);
	BinaryTreeNode *p14 = new BinaryTreeNode(14);
	BinaryTreeNode *p12 = new BinaryTreeNode(12);
	BinaryTreeNode *p15 = new BinaryTreeNode(15);

	BinaryTreeNode *p2 = new BinaryTreeNode(2);
	BinaryTreeNode *p1 = new BinaryTreeNode(1);

	connectNode(p10, p6, p14);
	connectNode(p6, p3, p7);
	connectNode(p14, p12, p15);
	connectNode(p3, p2, nullptr);
	connectNode(p2, p1, nullptr);

	printTreeMyself(p10);
	cout << endl;
	printTree(p6);
}

int main(int argc, char* argv[])
{
	test1();

	return 0;
}


