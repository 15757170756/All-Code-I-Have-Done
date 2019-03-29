/*
863. All Nodes Distance K in Binary Tree
User Accepted: 827
User Tried: 1105
Total Accepted: 838
Total Submissions: 2572
Difficulty: Medium
We are given a binary tree (with root node root), a target node, and an integer value `K`.

Return a list of the values of all nodes that have a distance K from the target node.  The answer can be returned in any order.

 

Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2
Output: [7,4,1]
Explanation: 
The nodes that are a distance 2 from the target node (with value 5)
have values 7, 4, and 1.

Note that the inputs "root" and "target" are actually TreeNodes.
The descriptions of the inputs above are just serializations of these objects.

Note:

The given tree is non-empty.
Each node in the tree has unique values 0 <= node.val <= 500.
The target node is a node in the tree.
0 <= K <= 1000.
*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
	map<TreeNode*, TreeNode*> parent;
	set<TreeNode*> visited;
	vector<int> ans;

	void findParent(TreeNode* root)
	{
		if (!root)
			return;
		if (root->left) {
			parent[root->left] = root;
			findParent(root->left);
		}
		if (root->right) {
			parent[root->right] = root;
			findParent(root->right);
		}
	}

	void dfs(TreeNode* root, int K)
	{
		if (visited.find(root) != visited.end())
			return;
		visited.insert(root);
		if (K == 0) {
			ans.push_back(root->val);
			return;
		}
		if (root->left)
			dfs(root->left, K - 1);
		if (root->right)
			dfs(root->right, K - 1);
		TreeNode* p = parent[root];
		if (p)
			dfs(p, K - 1);
	}

	vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
		if (!root)
			return {};
		findParent(root);
		dfs(target, K);
		return ans;
	}
};