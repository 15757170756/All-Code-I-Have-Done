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
#include <stack>
#include <deque>

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

void printTree(BinaryTreeNode *pRoot)
{
	if (pRoot == nullptr)
		return;

	stack<BinaryTreeNode*> levels[2];
	int current = 0;
	int next = 1;
	levels[current].push(pRoot);
	while (!levels[0].empty() || !levels[1].empty()) {
		BinaryTreeNode *topNode = levels[current].top();
		levels[current].pop();

		printf("%d ", topNode->data);

		if (0 == current) {
			if (topNode->left != nullptr)
				levels[next].push(topNode->left);
			if (topNode->right != nullptr)
				levels[next].push(topNode->right);
		}
		else {
			if (topNode->right != nullptr)
				levels[next].push(topNode->right);
			if (topNode->left != nullptr)
				levels[next].push(topNode->left);
		}

		if (levels[current].empty()) {
			printf("\n");
			current = 1 - current;
			next = 1 - next;
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

	printTree(p10);
}

int main(int argc, char* argv[])
{
	test1();

	return 0;
}