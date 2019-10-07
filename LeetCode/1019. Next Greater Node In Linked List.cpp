/*
https://leetcode.com/problems/next-greater-node-in-linked-list/

1019. Next Greater Node In Linked List
Medium

173

14

Favorite

Share
We are given a linked list with head as the first node.  Let's number the nodes in the list: node_1, node_2, node_3, ... etc.

Each node may have a next larger value: for node_i, next_larger(node_i) is the node_j.val such that j > i, node_j.val > node_i.val, and j is the smallest possible choice.  If such a j does not exist, the next larger value is 0.

Return an array of integers answer, where answer[i] = next_larger(node_{i+1}).

Note that in the example inputs (not outputs) below, arrays such as [2,1,5] represent the serialization of a linked list with a head node value of 2, second node value of 1, and third node value of 5.

 

Example 1:

Input: [2,1,5]
Output: [5,5,0]
Example 2:

Input: [2,7,4,3,5]
Output: [7,0,5,5,0]
Example 3:

Input: [1,7,5,1,9,2,5,1]
Output: [7,9,9,9,0,5,0,0]
 

Note:

1 <= node.val <= 10^9 for each node in the linked list.
The given list has length in the range [0, 10000].
Accepted
9,865
Submissions
17,462
*/



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	vector<int> nextLargerNodes(ListNode* head) {
		vector<int> headVec;
		ListNode *temp = head;
		while (temp) {
			headVec.push_back(temp->val);
			temp = temp->next;
		}
		vector<int> res(headVec.size());
		for (int i = 0; i < headVec.size(); ++i) {
			int curNum = headVec[i];
			int cnt = 0;
			for (int j = i + 1; j < headVec.size(); ++j) {
				if (headVec[j] > curNum) {
					res[i] = headVec[j];
					break;
				}
				else
					++cnt;
			}
			if (cnt == headVec.size() - i - 1)
				res[i] = 0;
		}

		return res;
	}
};

/*
Success
Details 
Runtime: 1088 ms, faster than 17.56% of C++ online submissions for Next Greater Node In Linked List.
Memory Usage: 25.6 MB, less than 58.72% of C++ online submissions for Next Greater Node In Linked List.
*/




class Solution {
public:
	vector<int> nextLargerNodes(ListNode* head) {
		vector<int> res, stack;
		for (ListNode *node = head; node; node = node->next) {
			while (stack.size() && res[stack.back()] < node->val) {
				res[stack.back()] = node->val;
				stack.pop_back();
			}
			stack.push_back(res.size());
			res.push_back(node->val);
		}
		for (int i : stack) res[i] = 0;
		return res;
	}
};



/*
Success
Details 
Runtime: 208 ms, faster than 95.20% of C++ online submissions for Next Greater Node In Linked List.
Memory Usage: 26.2 MB, less than 32.14% of C++ online submissions for Next Greater Node In Linked List.
*/