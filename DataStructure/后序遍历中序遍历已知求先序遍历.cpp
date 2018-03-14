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
	TreeNode* buildTree(vector<T>& postorder, vector<T>& inorder) {
		return buildTree(begin(inorder), end(inorder),
			begin(postorder), end(postorder));
	}
	template<typename BidiIt>
	TreeNode* buildTree(BidiIt in_first, BidiIt in_last,
		BidiIt post_first, BidiIt post_last)
	{
		if (in_first == in_last) return nullptr;
		if (post_first == post_last) return nullptr;

		const auto val = *prev(post_last);
		TreeNode* root = new TreeNode(val);

		auto inRootPos = find(in_first, in_last, val);
		auto leftSize = distance(in_first, inRootPos);

		/*
		ע��end����ָ��ĵ����������һ��Ԫ�صĺ���һ��
		�������һ������Ļ����ͻ�ָ�����һ��Ԫ�ص�ָ�룬
		���Եݹ��ʱ��in_last��post_last��ʵ�ζ�Ҫ�ǵ�ǰ
		����in_last��post_last�ĺ�һ����������
		*/
		root->left = buildTree(in_first, inRootPos,
			post_first, next(post_first, leftSize));
		root->right = buildTree(next(inRootPos), in_last,
			next(post_first, leftSize), prev(post_last));
		return root;
	}
};

// ����Ϊ���Բ���  

void PreTraverse(TreeNode *pRoot)
{
	if (pRoot == NULL) return;
	cout << (char)pRoot->val << " "; // ���ʸ��ڵ�
	PreTraverse(pRoot->left); // ����������
	PreTraverse(pRoot->right); // ����������
}
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
	string preorderStr = "DEBFCA";
	string inorderStr = "DBEACF";
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
	PreTraverse(root);

	return 0;
}