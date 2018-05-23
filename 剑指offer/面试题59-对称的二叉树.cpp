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



struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {
	}
};
//只过了50%的数据
class Solution {
public:
	bool isSymmetrical(TreeNode* pRoot)
	{
		if (pRoot == nullptr)
			return true;
		deque<TreeNode*> q1, q2;
		q1.push_back(pRoot);
		while (!(q1.empty() && q2.empty())) {
			while (!q1.empty()) {
				TreeNode *frontNode = q1.front();
				q1.pop_front();
				if (frontNode->left != nullptr)
					q2.push_back(frontNode->left);
				if (frontNode->right != nullptr)
					q2.push_back(frontNode->right);
			}
			vector<TreeNode*> vec(q2.begin(), q2.end());
			for (int i = 0, j = vec.size() - 1;
				i < vec.size() / 2; ++i, --j) {
				if (vec[i]->val != vec[j]->val)
					return false;
			}
			while (!q2.empty()) {
				TreeNode *frontNode = q2.front();
				q2.pop_front();
				if (frontNode->left != nullptr)
					q1.push_back(frontNode->left);
				if (frontNode->right != nullptr)
					q1.push_back(frontNode->right);
			}
			vec.clear();
			vec.assign(q1.begin(), q1.end());
			for (int i = 0, j = vec.size() - 1;
				i < vec.size() / 2; ++i, --j) {
				if (vec[i]->val != vec[j]->val)
					return false;
			}
		}
		return true;
	}

};



//这个是对的
class Solution {
public:
	bool isSymmetric(TreeNode* root) {
		if (root == NULL) 
			return true;
		queue<TreeNode*> q1, q2;
		TreeNode *left, *right;
		q1.push(root->left);
		q2.push(root->right);
		while (!q1.empty() && !q2.empty())
		{
			left = q1.front();
			q1.pop();
			right = q2.front();
			q2.pop();
			//两边都是空
			if (NULL == left && NULL == right)
				continue;
			//只有一边是空
			if (NULL == left || NULL == right)
				return false;
			if (left->val != right->val)
				return false;
			q1.push(left->left);
			q1.push(left->right);
			q2.push(right->right);
			q2.push(right->left);
		}

		return true;

	}
};

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