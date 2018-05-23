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

BinaryTreeNode* kthNodeCore(BinaryTreeNode *pRoot, unsigned int &k)
{
	BinaryTreeNode *target = nullptr;
	if (pRoot->left != nullptr)
		target = kthNodeCore(pRoot->left, k);

	if (target == nullptr) {
		if (1 == k)
			target = pRoot;
		--k;
	}

	if (target == nullptr && pRoot->right != nullptr)
		target = kthNodeCore(pRoot->right, k);

	return target;
}

BinaryTreeNode* kthNode(BinaryTreeNode *pRoot, unsigned int k)
{
	if (pRoot == nullptr || k == 0)
		return nullptr;
	return kthNodeCore(pRoot, k);
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

	int k = 3;
	printf("%d\n", kthNode(p10, k)->data);
}



int main(int argc, char* argv[])
{
	test1();

	return 0;
}










struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {
	}
};

class Solution {
public:
	//使用中序遍历存储结点
	void inorder(TreeNode *pRoot, vector<TreeNode*> &vec)
	{
		if (pRoot == nullptr)
			return;
		inorder(pRoot->left, vec);
		vec.emplace_back(pRoot);
		inorder(pRoot->right, vec);
	}
	TreeNode* KthNode(TreeNode* pRoot, int k)
	{
		if (pRoot == nullptr || k < 1)
			return nullptr;

		vector<TreeNode*> vec;
		inorder(pRoot, vec);


		if (vec.size() < k)
			return nullptr;
		return vec[k - 1];
	}
};