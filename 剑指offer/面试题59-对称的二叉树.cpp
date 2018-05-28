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

//还是利用层序遍历，但是有特例会出错
bool isSymmetricalMyself(BinaryTreeNode *pRoot)
{
	if (pRoot == nullptr)
		return false;
	deque<BinaryTreeNode*> qNodes;
	qNodes.push_back(pRoot);
	int nextLevel = 0;
	int toBePrinted = 1;
	while (!qNodes.empty()) {
		BinaryTreeNode *frontNode = qNodes.front();
		//cout << frontNode->data << ' ';

		if (frontNode->left != nullptr) {
			qNodes.push_back(frontNode->left);
			++nextLevel;
		}
		if (frontNode->right != nullptr) {
			qNodes.push_back(frontNode->right);
			++nextLevel;
		}

		qNodes.pop_front();
		--toBePrinted;

		if (0 == toBePrinted) {
			vector<BinaryTreeNode*> vec(qNodes.begin(), qNodes.end());
			int len = vec.size();
			for (int i = 0, j = len - 1; i < len / 2; ++i, --j)
				if (vec[i]->data != vec[j]->data)
					return false;
			toBePrinted = nextLevel;
			nextLevel = 0;
		}
	}

	return true;
}

bool isSymmetrical(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2)
{
	if (pRoot1 == nullptr && pRoot2 == nullptr)
		return true;

	//左子树或者右子树为空
	if (pRoot1 == nullptr || pRoot2 == nullptr)
		return false;
	if (pRoot1->data != pRoot2->data)
		return false;

	return (isSymmetrical(pRoot1->left, pRoot2->right)
		&& isSymmetrical(pRoot1->right, pRoot2->left));
}

bool isSymmetrical(BinaryTreeNode *pRoot)
{
	return isSymmetrical(pRoot, pRoot);
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

	cout << isSymmetricalMyself(p10) << endl;
	cout << isSymmetrical(p10) << endl;
}

void test2()
{
	BinaryTreeNode *p10 = new BinaryTreeNode(10);
	BinaryTreeNode *p61 = new BinaryTreeNode(6);
	BinaryTreeNode *p62 = new BinaryTreeNode(6);
	BinaryTreeNode *p71 = new BinaryTreeNode(7);
	BinaryTreeNode *p72 = new BinaryTreeNode(7);
	BinaryTreeNode *p51 = new BinaryTreeNode(5);
	BinaryTreeNode *p52 = new BinaryTreeNode(5);

	connectNode(p10, p61, p62);
	connectNode(p61, p51, p71);
	connectNode(p62, p72, p51);

	cout << isSymmetricalMyself(p10) << endl;
	cout << isSymmetrical(p10) << endl;
}

int main(int argc, char* argv[])
{
	test1();
	test2();

	return 0;
}