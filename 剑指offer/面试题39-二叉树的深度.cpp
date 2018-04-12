#include <iostream>

using namespace::std;

struct BinaryTreeNode
{
	int data;
	BinaryTreeNode* leftChild;
	BinaryTreeNode* rightChild;
};

BinaryTreeNode* createBinaryTreeNode(int data)
{
	BinaryTreeNode* pNode = new BinaryTreeNode();
	pNode->data = data;
	pNode->leftChild = nullptr;
	pNode->rightChild = nullptr;

	return pNode;
}

void connectNodes(
	BinaryTreeNode* parent,
	BinaryTreeNode* leftChild,
	BinaryTreeNode* rightChild)
{
	if (parent) {
		parent->leftChild = leftChild;
		parent->rightChild = rightChild;
	}
}

int treeDepth(BinaryTreeNode *pRoot)
{
	if (pRoot == nullptr)
		return 0;
	int nLeft = treeDepth(pRoot->leftChild);
	int nRight = treeDepth(pRoot->rightChild);

	return (nLeft > nRight) ? (nLeft + 1) : (nRight + 1);
}

int main()
{
	BinaryTreeNode* pNode10 = createBinaryTreeNode(10);
	BinaryTreeNode* pNode6 = createBinaryTreeNode(6);
	BinaryTreeNode* pNode14 = createBinaryTreeNode(14);
	BinaryTreeNode* pNode4 = createBinaryTreeNode(4);
	BinaryTreeNode* pNode8 = createBinaryTreeNode(8);
	BinaryTreeNode* pNode12 = createBinaryTreeNode(12);
	BinaryTreeNode* pNode16 = createBinaryTreeNode(16);
	BinaryTreeNode* pNode3 = createBinaryTreeNode(3);

	connectNodes(pNode10, pNode6, pNode14);
	connectNodes(pNode6, pNode4, pNode8);
	connectNodes(pNode14, pNode12, pNode16);
	connectNodes(pNode4, pNode3, nullptr);

	cout << treeDepth(pNode10) << endl;
}









/*
另外方法

https://blog.csdn.net/fly_yr/article/details/52326917
*/


/*
* 题目：二叉树和为某一值的路径
* 描述：输入一颗二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。
* 路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int flag = INT_MIN;

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;

	TreeNode(int x) :val(x), left(NULL), right(NULL) {}
};


/*递归求二叉树高度*/
int depth(TreeNode *root)
{
	if (root == NULL)
		return 0;

	int leftDepth = depth(root->left);
	int rightDepth = depth(root->right);

	return max(leftDepth, rightDepth) + 1;
}

/*非递归求二叉树高度 -- 采用层序遍历的思想，记录树的层数*/
int depth2(TreeNode *root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 1;

	queue<TreeNode *> nodes;
	nodes.push(root);
	int d = 0;
	while (!nodes.empty())
	{
		queue<TreeNode *> q;

		while (!nodes.empty())
		{
			TreeNode *tmp = nodes.front();
			nodes.pop();

			if (tmp->left != NULL)
				q.push(tmp->left);

			if (tmp->right != NULL)
				q.push(tmp->right);
		}//while
		for (int i = 0; i < q.size(); ++i) {
			TreeNode *tmp = q.front();
		}
		++d;
		nodes = q;
	}//while
	return d;
}

//非递归求二叉树高度 -- 利用后序遍历思想
int depth3(TreeNode *root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 1;

	stack<TreeNode *> s;
	stack<int> tag;

	TreeNode *p = root;
	int d = 0;
	while (p != NULL || !s.empty())
	{
		while (p != NULL)
		{
			s.push(p);
			tag.push(0);

			p = p->left;
		}//while

		if (tag.top() == 1)
		{
			d = d > s.size() ? d : s.size();
			s.pop();

			tag.pop();

			p = NULL;
		}
		else {
			p = s.top();
			p = p->right;
			tag.pop();
			tag.push(1);
		}//else
	}//while
	return d;
}

TreeNode *generateTree(vector<int> &nums)
{
	if (nums.empty())
		return NULL;

	TreeNode *root = new TreeNode(nums[0]);
	queue<TreeNode *> que;
	que.push(root);
	//求出所给元素个数，对应二叉查找树节点个数
	int size = nums.size();
	for (int i = 1; i < size; i += 2)
	{
		//处理队首节点的左右子树
		TreeNode *tmp = que.front();
		TreeNode *left = NULL, *right = NULL;
		//定义非空左子树
		if (nums[i] != flag)
		{
			left = new TreeNode(nums[i]);
			que.push(left);
		}

		//定义非空右子树
		if (i + 1 < size && nums[i + 1] != flag)
		{
			right = new TreeNode(nums[i + 1]);
			que.push(right);
		}

		tmp->left = left;
		tmp->right = right;
		//弹出当前处理的节点
		que.pop();
	}
	return root;
}

int main()
{
	vector<int> v = { 10, 5, 12, 4, 7 };
	TreeNode *root = generateTree(v);

	cout << depth(root) << endl;
	cout << depth2(root) << endl;
	cout << depth3(root) << endl;
	system("pause");
	return 0;
}