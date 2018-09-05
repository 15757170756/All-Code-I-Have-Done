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
这个程序更好理解一些
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
		注意end函数指向的迭代器是最后一个元素的后面一个
		而如果用一般数组的话，就会指向最后一个元素的指针，
		所以递归的时候in_last和post_last的实参都要是当前
		子树in_last和post_last的后一个迭代器。
		*/
		root->left = buildTree(in_first, inRootPos,
			post_first, next(post_first, leftSize));
		root->right = buildTree(next(inRootPos), in_last,
			next(post_first, leftSize), prev(post_last));
		return root;
	}
};

// 以下为测试部分  

void PreTraverse(TreeNode *pRoot)
{
	if (pRoot == NULL) return;
	cout << (char)pRoot->val << " "; // 访问根节点
	PreTraverse(pRoot->left); // 遍历左子树
	PreTraverse(pRoot->right); // 遍历右子树
}
void InTraverse(TreeNode *pRoot)
{
	if (pRoot == NULL) return;
	InTraverse(pRoot->left); // 遍历左子树
	cout << pRoot->val << " "; // 访问根节点
	InTraverse(pRoot->right); // 遍历右子树
}
void PostTraverse(TreeNode *pRoot)
{
	if (pRoot == NULL) return;
	PostTraverse(pRoot->left); // 后序遍历左子树
	PostTraverse(pRoot->right); // 后序遍历右子树
	cout << char(pRoot->val) << " "; // 访问根节点
}

int main()
{
	vector<char> postorder = { 'D', 'E', 'B', 'F', 'C', 'A' };
	vector<char> inorder = { 'D', 'B', 'E', 'A', 'C', 'F' };

	Solution<char> sol;
	TreeNode *root;

	root = sol.buildTree(postorder, inorder);
	// PostTraverse(root);
	PreTraverse(root);

	return 0;
}


