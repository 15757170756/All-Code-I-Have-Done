/*
https://leetcode.com/problems/symmetric-tree/

101. Symmetric Tree
Easy

1772

36

Favorite

Share
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3
But the following [1,2,2,null,3,null,3] is not:
    1
   / \
  2   2
   \   \
   3    3
Note:
Bonus points if you could solve it both recursively and iteratively.

Accepted
338,914
Submissions
801,609
Seen this question in a real interview before?
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	bool aux_isSymmetric(TreeNode* root1,
		TreeNode* root2)
	{
		if (!root1 && !root2)
			return true;
		if ((!root1 && root2) || (root1 && !root2))
			return false;
		if (root1->val != root2->val)
			return false;
		return (aux_isSymmetric(root1->left, root2->right) &&
			aux_isSymmetric(root1->right, root2->left));
	}
	bool isSymmetric(TreeNode* root) {
		if (!root)
			return true;
		return aux_isSymmetric(root->left, root->right);
	}
};

/*
Success
Details 
Runtime: 8 ms, faster than 60.88% of C++ 
online submissions for Symmetric Tree.
*/