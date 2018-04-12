#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <stack>

using namespace::std;

struct BinaryTreeNode
{
	int data;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
	BinaryTreeNode *parent;
	BinaryTreeNode() :data(0), left(nullptr), right(nullptr), parent(nullptr){}
	BinaryTreeNode(int value) :data(value), left(nullptr), right(nullptr), parent(nullptr){}
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

	if (leftChild != nullptr)
		leftChild->parent = parent;
	if (rightChild != nullptr)
		rightChild->parent = parent;
	return parent;
}

BinaryTreeNode* LCABST(BinaryTreeNode *root, int data1, int data2)
{
	if (root == nullptr)
		return nullptr;
	if (root->data > data1 && root->data > data2)
		return LCABST(root->left, data1, data2);
	if (root->data < data1 && root->data < data2)
		return LCABST(root->right, data1, data2);

	return root;
}

void testBST()
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

	BinaryTreeNode *lca = LCABST(p10, 2, 7);
	cout << lca->data << endl;
}

int getNodeLength(BinaryTreeNode *node)
{
	int cnt = 0;
	while (node != nullptr) {
		++cnt;
		node = node->parent;
	}

	return cnt;
}

BinaryTreeNode* getFirstCommonNode(BinaryTreeNode *node1, BinaryTreeNode *node2)
{
	int node1L = getNodeLength(node1);
	int node2L = getNodeLength(node2);
	BinaryTreeNode *longerNode = node1;
	BinaryTreeNode *shorterNode = node2;
	int diff = node1L - node2L;
	if (node2L > node1L) {
		longerNode = node2;
		shorterNode = node1;
		diff = node2L - node1L;
	}
	for (int i = 0; i < diff; ++i)
		longerNode = longerNode->parent;

	while (longerNode != nullptr
		&& shorterNode != nullptr
		&& longerNode != shorterNode) {
		longerNode = longerNode->parent;
		shorterNode = shorterNode->parent;
	}

	return longerNode;
}

BinaryTreeNode* LCAHaveParentPointer(BinaryTreeNode *root, BinaryTreeNode *node1, BinaryTreeNode *node2)
{
	if (root == nullptr
		|| node1 == nullptr
		|| node2 == nullptr)
		return nullptr;

	return getFirstCommonNode(node1, node2);
}

void testHaveParentPointer()
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

	BinaryTreeNode *lca = LCAHaveParentPointer(p10, p2, p1);
	cout << lca->data << endl;
}



//Wrong TODO
bool getNodePath(BinaryTreeNode *pRoot, BinaryTreeNode *pNode,
	list<BinaryTreeNode*> &path)
{
	if (pRoot == pNode)
		return true;

	path.push_back(pRoot);
	bool found = false;

	//多叉树
	//vector<BinaryTreeNode*>::iterator i = pRoot->m_vChildren.begin();
	//while (!found && i < pRoot->m_vChildren.end()) {
	//	found = getNodePath(*i, pNode, path);
	//	++i;
	//}
	while (!found && pRoot != nullptr) {
		found = getNodePath(pRoot->left, pNode, path);
		//return found;
		found = getNodePath(pRoot->right, pNode, path);
		//return found;
	}

	if (!found)
		path.pop_back();

	return found;
}

BinaryTreeNode* getLastCommondNode(const list<BinaryTreeNode*> &path1,
	const list<BinaryTreeNode*> &path2)
{
	list<BinaryTreeNode*>::const_iterator iter1 = path1.begin();
	list<BinaryTreeNode*>::const_iterator iter2 = path2.begin();

	BinaryTreeNode *pLast = nullptr;
	while (iter1 != path1.end()
		&& iter2 != path2.end()) {
		if (*iter1 == *iter2)
			pLast = *iter1;
		++iter1, ++iter2;
	}

	return pLast;
}

BinaryTreeNode* LCAOrdinary(BinaryTreeNode *root,
	BinaryTreeNode *node1, BinaryTreeNode *node2)
{
	if (root == nullptr
		|| node1 == nullptr
		|| node2 == nullptr)
		return nullptr;

	list<BinaryTreeNode*> path1;
	getNodePath(root, node1, path1);

	list<BinaryTreeNode*> path2;
	getNodePath(root, node2, path2);

	return getLastCommondNode(path1, path2);
}

void testLCAOrdinaryBinaryTree()
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

	BinaryTreeNode *lca = LCAOrdinary(p10, p2, p1);
	cout << lca->data << endl;
}








struct TreeNode
{
	int                    m_nValue;
	std::vector<TreeNode*>    m_vChildren;
};

TreeNode* CreateTreeNode(int value)
{
	TreeNode* pNode = new TreeNode();
	pNode->m_nValue = value;

	return pNode;
}

void ConnectTreeNodes(TreeNode* pParent, TreeNode* pChild)
{
	if (pParent != NULL)
	{
		pParent->m_vChildren.push_back(pChild);
	}
}

bool getNodePath(TreeNode *pRoot, TreeNode *pNode,
	list<TreeNode*> &path)
{
	if (pRoot == pNode)
		return true;

	path.push_back(pRoot);
	bool found = false;

	//多叉树
	vector<TreeNode*>::iterator i = pRoot->m_vChildren.begin();
	while (!found && i < pRoot->m_vChildren.end()) {
		found = getNodePath(*i, pNode, path);
		++i;
	}

	if (!found)
		path.pop_back();

	return found;
}


//TODO
void getNodePathIterator(TreeNode *pRoot, TreeNode *pNode,
	list<TreeNode*> &path)
{
	stack<TreeNode*> stackNode;
	//TreeNode *curNode = pRoot;
	stackNode.push(pRoot);

	while (!stackNode.empty()) {
		bool flag = false;
		TreeNode *topNode = stackNode.top();
		cout << topNode->m_nValue << endl;
		path.push_back(topNode);
		stackNode.pop();
		TreeNode *lastNode = path.back();
		if (lastNode->m_vChildren.size() == 0
			&& lastNode != pNode)
			path.pop_back();

		vector<TreeNode*>::const_iterator iter = topNode->m_vChildren.begin();
		while (iter != topNode->m_vChildren.end()
			&& *iter != nullptr) {
			if (*iter == pNode) {
				flag = true;
				break;
			}
			stackNode.push(*iter);
			++iter;
		}
		if (flag == true)
			break;
	}
}


TreeNode* getLastCommondNode(const list<TreeNode*> &path1,
	const list<TreeNode*> &path2)
{
	list<TreeNode*>::const_iterator iter1 = path1.begin();
	list<TreeNode*>::const_iterator iter2 = path2.begin();

	TreeNode *pLast = nullptr;
	while (iter1 != path1.end()
		&& iter2 != path2.end()) {
		if (*iter1 == *iter2)
			pLast = *iter1;
		++iter1, ++iter2;
	}

	return pLast;
}

TreeNode* LCAOrdinary(TreeNode *root,
	TreeNode *node1, TreeNode *node2)
{
	if (root == nullptr
		|| node1 == nullptr
		|| node2 == nullptr)
		return nullptr;

	list<TreeNode*> path1;
	getNodePath(root, node1, path1);

	list<TreeNode*> path2;
	getNodePath(root, node2, path2);

	return getLastCommondNode(path1, path2);
}

void Test(char* testName, TreeNode* pRoot, TreeNode* pNode1, TreeNode* pNode2, TreeNode* pExpected)
{
	if (testName != NULL)
		printf("%s begins: \n", testName);

	TreeNode* pResult = LCAOrdinary(pRoot, pNode1, pNode2);

	if ((pExpected == NULL && pResult == NULL)
		|| (pExpected != NULL && pResult != NULL
		&& pResult->m_nValue == pExpected->m_nValue))
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 形状普通的树
//              1
//            /   \
//           2     3
//        /     \
//       4       5
//     / \      / | \
//    6   7    8  9  10
void Test1()
{
	TreeNode* pNode1 = CreateTreeNode(1);
	TreeNode* pNode2 = CreateTreeNode(2);
	TreeNode* pNode3 = CreateTreeNode(3);
	TreeNode* pNode4 = CreateTreeNode(4);
	TreeNode* pNode5 = CreateTreeNode(5);
	TreeNode* pNode6 = CreateTreeNode(6);
	TreeNode* pNode7 = CreateTreeNode(7);
	TreeNode* pNode8 = CreateTreeNode(8);
	TreeNode* pNode9 = CreateTreeNode(9);
	TreeNode* pNode10 = CreateTreeNode(10);

	ConnectTreeNodes(pNode1, pNode2);
	ConnectTreeNodes(pNode1, pNode3);

	ConnectTreeNodes(pNode2, pNode4);
	ConnectTreeNodes(pNode2, pNode5);

	ConnectTreeNodes(pNode4, pNode6);
	ConnectTreeNodes(pNode4, pNode7);

	ConnectTreeNodes(pNode5, pNode8);
	ConnectTreeNodes(pNode5, pNode9);
	ConnectTreeNodes(pNode5, pNode10);

	//list<TreeNode*> path;
	//cout << endl;
	//getNodePathIterator(pNode1, pNode7, path);
	//cout << endl;
	//for (TreeNode *e : path)
	//	cout << e->m_nValue << ' ';
	//cout << endl;

	Test("Test1", pNode1, pNode6, pNode8, pNode2);
}

// 树退化成一个链表
//               1
//              /
//             2
//            /
//           3
//          /
//         4
//        /
//       5
void Test2()
{
	TreeNode* pNode1 = CreateTreeNode(1);
	TreeNode* pNode2 = CreateTreeNode(2);
	TreeNode* pNode3 = CreateTreeNode(3);
	TreeNode* pNode4 = CreateTreeNode(4);
	TreeNode* pNode5 = CreateTreeNode(5);

	ConnectTreeNodes(pNode1, pNode2);
	ConnectTreeNodes(pNode2, pNode3);
	ConnectTreeNodes(pNode3, pNode4);
	ConnectTreeNodes(pNode4, pNode5);

	Test("Test2", pNode1, pNode5, pNode4, pNode3);
}

// 树退化成一个链表，一个结点不在树中
//               1
//              /
//             2
//            /
//           3
//          /
//         4
//        /
//       5
void Test3()
{
	TreeNode* pNode1 = CreateTreeNode(1);
	TreeNode* pNode2 = CreateTreeNode(2);
	TreeNode* pNode3 = CreateTreeNode(3);
	TreeNode* pNode4 = CreateTreeNode(4);
	TreeNode* pNode5 = CreateTreeNode(5);

	ConnectTreeNodes(pNode1, pNode2);
	ConnectTreeNodes(pNode2, pNode3);
	ConnectTreeNodes(pNode3, pNode4);
	ConnectTreeNodes(pNode4, pNode5);

	TreeNode* pNode6 = CreateTreeNode(6);

	Test("Test3", pNode1, pNode5, pNode6, NULL);
}

// 输入NULL
void Test4()
{
	Test("Test4", NULL, NULL, NULL, NULL);
}

void testLCAOrdinary()
{
	Test1();
	Test2();
	Test3();
	Test4();
}

int main(int argc, char* argv[])
{
	testBST();
	testHaveParentPointer();
	testLCAOrdinary();
	testLCAOrdinaryBinaryTree();
}