#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <limits>
#include <climits>
#include <stack>

using namespace::std;

struct TreeNode
{
	int data;
	TreeNode *left;
	TreeNode *right;
	TreeNode() :data(0), left(nullptr), right(nullptr){}
	TreeNode(int value) :data(value), left(nullptr), right(nullptr){}
};

TreeNode* createNode(int value)
{
	TreeNode *newNode = new TreeNode(value);
	return newNode;
}

TreeNode* connectNode(TreeNode *parent,
	TreeNode *leftChild, TreeNode *rightChild)
{
	parent->left = leftChild;
	parent->right = rightChild;
	return parent;
}

bool isBalanceAux(TreeNode *root, int *pDepth)
{
	if (root == nullptr) {
		*pDepth = 0;
		return true;
	}
	int left, right;
	if (isBalanceAux(root->left, &left)
		&& isBalanceAux(root->right, &right)) {
		int diff = left - right;
		if (diff <= 1 && diff >= -1) {
			*pDepth = 1 + (left > right ? left : right);
			return true;
		}
	}

	return false;
}

bool isBalance(TreeNode *root)
{
	int pDepth = 0;
	return isBalanceAux(root, &pDepth);
}

void inorder(TreeNode *root, vector<int> &vec)
{
	if (root == nullptr)
		return;
	inorder(root->left, vec);
	vec.push_back(root->data);
	inorder(root->right, vec);
}

void inorderIterator(TreeNode *root, vector<int> &vec)
{
	if (root == nullptr)
		return;

	TreeNode *currnetNode = root;
	stack<TreeNode*> stackNode;

	while (!stackNode.empty()
		|| currnetNode != nullptr) {
		while (currnetNode != nullptr) {
			stackNode.push(currnetNode);
			currnetNode = currnetNode->left;

		}
		//if (!stackNode.empty()) {
		currnetNode = stackNode.top();
		stackNode.pop();
		vec.push_back(currnetNode->data);
		currnetNode = currnetNode->right;
		//}
	}
}

bool isBST(TreeNode *root)
{
	vector<int> vec;
	inorderIterator(root, vec);
	vector<int> temp = vec;
	sort(temp.begin(), temp.end());
	if (temp == vec && vec.size() > 0)
		return true;
	else
		return false;
}

bool isAVL(TreeNode *root)
{
	return isBalance(root) && isBST(root);
}

void test1()
{
	TreeNode *p10 = new TreeNode(10);
	TreeNode *p6 = new TreeNode(6);
	TreeNode *p3 = new TreeNode(3);
	TreeNode *p7 = new TreeNode(7);
	TreeNode *p14 = new TreeNode(14);
	TreeNode *p12 = new TreeNode(12);
	TreeNode *p15 = new TreeNode(15);

	TreeNode *p2 = new TreeNode(2);
	TreeNode *p1 = new TreeNode(1);

	connectNode(p10, p6, p14);
	connectNode(p6, p3, p7);
	connectNode(p14, p12, p15);
	connectNode(p3, p2, nullptr);
	connectNode(p2, p1, nullptr);

	cout << boolalpha << isBalance(p10) << endl
		<< isBST(p10) << endl
		<< isAVL(p10) << noboolalpha << endl;
}

int main()
{
	test1();
}