/*
Given a n-ary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

For example, given a 3-ary tree:

 

We should return its max depth, which is 3.

 

Note:

The depth of the tree is at most 1000.
The total number of nodes is at most 5000.
Accepted
26,465
Submissions
41,569
Seen this question in a real interview before?
*/


/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
public:
	int maxDepth(Node* root) 
	{
		int res = 0;
        if (!root)
			return res;
		queue<Node*> qNode;
		qNode.push(root);
		while (!qNode.empty()) {
			queue<Node*> tempNode;
			while (!qNode.empty()) {
				Node* frontNode = qNode.front();
				qNode.pop();
				for (int i = 0;
					i < frontNode->children.size(); ++i) {
					if (frontNode->children[i])
						tempNode.push(frontNode->children[i]);
				}
			}
			++res;
			qNode = tempNode;
		}
		return res;
	}
};
/*
Runtime: 68 ms, faster than 49.20% of C++ online submissions
 for Maximum Depth of N-ary Tree.
*/


//官方给的答案 DFS
// Definition for a Node.
class Node {
	public:
	int val;
	vector<Node*> children;

	Node() {}

	Node(int _val, vector<Node*> _children) {
		val = _val;
		children = _children;
	}
};


class Solution {
public:
	int maxDepth(Node* root) 
	{
		if (!root)
			return 0;
		else if (!root->children.size())
			return 1;
		else {
			vector<int> heights;
			for (Node* item : root->children)
				heights.push_back(maxDepth(item));
			return *max_element(heights.begin(), heights.end()) + 1;
		}
	}
};








class Solution {
public:
	int maxDepth(Node* root) 
	{
		queue<pair<Node*, int>> sta;
		if (root)
			sta.emplace(root, 1);
		int depth = 0;
		while (!sta.empty()) {
			pair<Node*, int> current = sta.front();
			sta.pop();
			root = current.first;
			int current_depth = current.second;
			if (root) {
				depth = max(depth, current_depth);
				for (Node* c : root->children)
					sta.emplace(c, current_depth + 1);
			}
		}
		return depth;
	}
};