/*
637. Average of Levels in Binary Tree
DescriptionHintsSubmissionsDiscussSolution
Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.
Example 1:
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
Note:
The range of node's value is in the range of 32-bit signed integer.
Seen this question in a real interview before?  

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
	vector<double> averageOfLevels(TreeNode *root) {
		vector<double> result;
		queue<TreeNode*> q1, q2;
		q1.push(root);
		while (!(q1.empty() && q2.empty())) {
			double sum = 0;
			int cnt = 0;
			while (!q1.empty()) {
				TreeNode *frontNode = q1.front();
				q1.pop();

				if (frontNode->left != nullptr)
					q2.push(frontNode->left);
				if (frontNode->right != nullptr)
					q2.push(frontNode->right);
				sum += frontNode->val;
				++cnt;
				if (q1.empty()) {
					sum = sum / cnt;
					result.push_back(sum);
				}
			}
			sum = 0;
			cnt = 0;
			while (!q2.empty()) {
				TreeNode *frontNode = q2.front();
				q2.pop();

				if (frontNode->left != nullptr)
					q1.push(frontNode->left);
				if (frontNode->right != nullptr)
					q1.push(frontNode->right);

				sum += frontNode->val;
				++cnt;
				if (q2.empty()) {
					sum = sum / cnt;
					result.push_back(sum);
				}
			}
		}

		return result;
	}
};

//Submission Result: Accepted 










#include <vector>
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
    vector<double> averageOfLevels(TreeNode* root) {
        
        std::vector<double> sum;
        std::vector<int> counts;

        helper(root, sum, counts, 0);

        std::vector<double> result;

        for (int i = 0; i < sum.size(); ++i) {
            result.push_back(sum[i] / counts[i]);
        }

        return result;

    }

    void helper(TreeNode* root, std::vector<double>& sum, 
    	std::vector<int>& counts, int level) {

        if (root == nullptr) {
            return;
        }

        if (level == sum.size() && level == counts.size()) {
            sum.push_back(root->val);
            counts.push_back(1);
        } else {
            sum[level] += root->val;
            counts[level] += 1;
        }
				
        helper(root->left, sum, counts, level + 1);
        helper(root->right, sum, counts, level + 1);
    }
};
