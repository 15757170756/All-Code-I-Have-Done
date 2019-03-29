/*

107. Binary Tree Level Order Traversal II
DescriptionHintsSubmissionsDiscussSolution
Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
]
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
 public class Solution {
    public List<List<Integer>> levelOrderBottom(TreeNode root) {
        Queue<TreeNode> queue = new LinkedList<TreeNode>();
        List<List<Integer>> wrapList = new LinkedList<List<Integer>>();
        
        if(root == null) return wrapList;
        
        queue.offer(root);
        while(!queue.isEmpty()){
            int levelNum = queue.size();
            List<Integer> subList = new LinkedList<Integer>();
            for(int i=0; i<levelNum; i++) {
                if(queue.peek().left != null) queue.offer(queue.peek().left);
                if(queue.peek().right != null) queue.offer(queue.peek().right);
                subList.add(queue.poll().val);
            }
            wrapList.add(0, subList);
        }
        return wrapList;
    }
}


public class Solution {
        public List<List<Integer>> levelOrderBottom(TreeNode root) {
            List<List<Integer>> wrapList = new LinkedList<List<Integer>>();
            levelMaker(wrapList, root, 0);
            return wrapList;
        }
        
        public void levelMaker(List<List<Integer>> list, TreeNode root, int level) {
            if(root == null) return;
            if(level >= list.size()) {
                list.add(0, new LinkedList<Integer>());
            }
            levelMaker(list, root.left, level+1);
            levelMaker(list, root.right, level+1);
            list.get(list.size()-level-1).add(root.val);
        }
    }





vector<vector<int> > levelOrder(TreeNode *root) {
	vector<vector<int> > retVal;

	levelOrder(root, retVal, 0);

	reverse(retVal.begin(), retVal.end());

	return retVal;
}

void levelOrder(TreeNode* root, vector<vector<int> > &v, int currLevel) {
	if (root == NULL) {
		return;
	}

	if (v.empty() || currLevel > (v.size() - 1)) {
		v.push_back(vector<int>());
	}

	v[currLevel].push_back(root->val);

	levelOrder(root->left, v, currLevel + 1);
	levelOrder(root->right, v, currLevel + 1);
}




vector<vector<int>> levelOrderBottom(TreeNode* root) {
    vector<vector<int>> res;
    if(!root)
        return res;
    vector<int> vlevel;
    queue<TreeNode*> q;
    q.push(root);
    int level1=1,level2=0;
    while(!q.empty()){
        TreeNode* front = q.front();
        q.pop();
        vlevel.push_back(front->val);
        if(front->left){
            q.push(front->left);
            ++level2;
        }
        if(front->right){
            q.push(front->right);
            ++level2;
        }
        
        
        if(--level1 == 0){//one level is over
            res.push_back(vlevel);
            level1 = level2;//next level
            level2=0;//next next level start
            vlevel.clear();
        }
        
    }
    reverse(res.begin(),res.end());
    return res;
}












class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        if (!root)
            return res;
        queue<TreeNode*> q1, q2;
        q1.push(root);
        while (!q1.empty() || !q2.empty()) {
            vector<int> temp1, temp2;
            while (!q1.empty()) {
                TreeNode *frontNode = q1.front();
                q1.pop();

                temp1.push_back(frontNode->val);
                if (frontNode->left)
                    q2.push(frontNode->left);
                if (frontNode->right)
                    q2.push(frontNode->right);
            }

            while (!q2.empty()) {
                TreeNode *frontNode = q2.front();
                q2.pop();
                temp2.push_back(frontNode->val);
                if (frontNode->left)
                    q1.push(frontNode->left);
                if (frontNode->right)
                    q1.push(frontNode->right);
            }
            if (temp1.size()) {
                res.push_back(temp1);
            }
            if (temp2.size())
                res.push_back(temp2);
        }

        reverse(res.begin(), res.end());
        return res;
    }
};
//Submission Result: Accepted 自己写的