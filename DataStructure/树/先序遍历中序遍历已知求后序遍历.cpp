#include <iostream>  
#include <vector>  
#include <string>

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
	string preorderStr = "CABEFDHG";
	string inorderStr = "BAFECHDG";
	vector<char> preorder;// = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
	vector<char> inorder;// = { 'c', 'b', 'a', 'e', 'f', 'd', 'i', 'h', 'j', 'g' };
	for (int i = 0; i < preorderStr.size(); ++i) {
		preorder.emplace_back(preorderStr[i]);
		inorder.emplace_back(inorderStr[i]);
	}

	Solution<char> sol;
	TreeNode *root;
	root = sol.buildTree(preorder, inorder);
	// PostTraverse(root);
	PostTraverse(root);

	return 0;
}