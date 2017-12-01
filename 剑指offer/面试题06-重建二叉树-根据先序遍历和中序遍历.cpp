#include <stdlib.h>
#include <stdio.h>
#include <exception>

using namespace::std;

typedef struct BinaryTreeNode
{
	int m_nValue;
	struct BinaryTreeNode* m_pLeft;
	struct BinaryTreeNode* m_pRight;
}BinaryTreeNode, *BinaryTree;

BinaryTree ConstructPreAndIn(int* preorder, int* inorder, int length);

BinaryTree ConstructCorePreAndIn(int* startPreorder, int* endPreorder,
	int* startInorder, int* endInorder);
void InTraverse(BinaryTreeNode *pRoot);


int main()
{
	int arrPreorder[] = { 1, 2, 4, 7, 3, 5, 6, 8 };
	int arrInorder[] = { 4, 7, 2, 1, 5, 3, 8, 6 };
	int length = sizeof(arrPreorder) / sizeof(int);
	BinaryTree root = ConstructPreAndIn(arrPreorder, arrInorder, length);
	InTraverse(root);

	return 0;
}

/*
����ǰ���������������ؽ�������
*/
BinaryTree ConstructPreAndIn(int* preorder, int* inorder, int length)
{
	if (preorder == nullptr || inorder == nullptr || length <= 0)
		return NULL;
	return ConstructCorePreAndIn(preorder, preorder + length - 1,
		inorder, inorder + length - 1);
}


BinaryTree ConstructCorePreAndIn(int* startPreorder, int* endPreorder,
	int* startInorder, int* endInorder)
{
	int rootValue = startPreorder[0];
	BinaryTree root = (BinaryTree)malloc(sizeof(BinaryTreeNode));
	root->m_nValue = rootValue;
	root->m_pLeft = root->m_pRight = nullptr;

	if (startPreorder == endPreorder) {
		if (startInorder == endInorder &&
			*startPreorder == *startInorder)
			return root;
		else
			throw exception("Invalid input.\n");
	}

	int* rootInorder = startInorder;
	while (rootInorder <= endInorder && *rootInorder != rootValue)
		++rootInorder;
	if (rootInorder == endInorder && *rootInorder != rootValue)
		throw exception("Invalid input.\n");

	int leftLenght = rootInorder - startInorder;
	int* leftPreorderEnd = startPreorder + leftLenght;

	if (leftLenght > 0)
		root->m_pLeft = ConstructCorePreAndIn(startPreorder + 1, leftPreorderEnd,
		startInorder, rootInorder - 1);

	if (leftLenght < endPreorder - startPreorder)
		root->m_pRight = ConstructCorePreAndIn(leftPreorderEnd + 1, endPreorder,
		rootInorder + 1, endInorder);

	return root;
}

void InTraverse(BinaryTreeNode *pRoot)
{
	if (pRoot == NULL) return;
	InTraverse(pRoot->m_pLeft); // ���������� 
	printf("%d ", pRoot->m_nValue); // ���ʸ��ڵ� 
	InTraverse(pRoot->m_pRight); // ����������    
}













#include <iostream>  
#include <vector>  

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/*
�������������һЩ
*/
class Solution {
public:
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		return buildTree(begin(preorder), end(preorder),
			begin(inorder), end(inorder));
	}
	template<typename InputIterator>
	TreeNode* buildTree(InputIterator pre_first, InputIterator pre_last,
		InputIterator in_first, InputIterator in_last)
	{
		if (pre_first == pre_last) return nullptr;
		if (in_first == in_last) return nullptr;

		TreeNode* root = new TreeNode(*pre_first);
		auto inRootPos = find(in_first, in_last, *pre_first);
		auto leftSize = distance(in_first, inRootPos);

		root->left = buildTree(next(pre_first), next(pre_first,
			leftSize + 1), in_first, next(in_first, leftSize));
		root->right = buildTree(next(pre_first, leftSize + 1), pre_last,
			next(inRootPos), in_last);
		return root;
	}
};

// ����Ϊ���Բ���  

void InTraverse(TreeNode *pRoot)
{
	if (pRoot == NULL) return;
	InTraverse(pRoot->left); // ����������
	cout << pRoot->val << " "; // ���ʸ��ڵ�
	InTraverse(pRoot->right); // ����������
}
void PostTraverse(TreeNode *pRoot)
{
	if (pRoot == NULL) return;
	PostTraverse(pRoot->left); // �������������
	PostTraverse(pRoot->right); // �������������
	cout << pRoot->val << " "; // ���ʸ��ڵ�
}

int main()
{
	vector<int> a = { 1, 3 };
	vector<int> b = { 1, 2 };

	Solution sol;
	TreeNode *root;
	root = sol.buildTree(a, b);
	// PostTraverse(root);
	InTraverse(root);

	return 0;
}












/*
�ĳ�ģ���࣬�Ժ����ֱ�����ˡ�����
*/
#include <iostream>  
#include <vector>  

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/*
�������������һЩ
*/
template<typename T>
class Solution {
public:
	TreeNode* buildTree(vector<T>& preorder, vector<T>& inorder) {
		return buildTree(begin(preorder), end(preorder),
			begin(inorder), end(inorder));
	}
	template<typename InputIterator>
	TreeNode* buildTree(InputIterator pre_first, InputIterator pre_last,
		InputIterator in_first, InputIterator in_last)
	{
		if (pre_first == pre_last) return nullptr;
		if (in_first == in_last) return nullptr;

		TreeNode* root = new TreeNode(*pre_first);
		auto inRootPos = find(in_first, in_last, *pre_first);
		auto leftSize = distance(in_first, inRootPos);

		root->left = buildTree(next(pre_first), next(pre_first,
			leftSize + 1), in_first, next(in_first, leftSize));
		root->right = buildTree(next(pre_first, leftSize + 1), pre_last,
			next(inRootPos), in_last);
		return root;
	}
};

// ����Ϊ���Բ���  

void InTraverse(TreeNode *pRoot)
{
	if (pRoot == NULL) return;
	InTraverse(pRoot->left); // ����������
	cout << pRoot->val << " "; // ���ʸ��ڵ�
	InTraverse(pRoot->right); // ����������
}
void PostTraverse(TreeNode *pRoot)
{
	if (pRoot == NULL) return;
	PostTraverse(pRoot->left); // �������������
	PostTraverse(pRoot->right); // �������������
	cout << char(pRoot->val) << " "; // ���ʸ��ڵ�
}

int main()
{
	vector<char> preorder = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
	vector<char> inorder = { 'c', 'b', 'a', 'e', 'f', 'd', 'i', 'h', 'j', 'g' };

	Solution<char> sol;
	TreeNode *root;
	root = sol.buildTree(preorder, inorder);
	// PostTraverse(root);
	PostTraverse(root);

	return 0;
}