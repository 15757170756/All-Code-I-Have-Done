#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <string>
#include <stack>
#include <cmath>
#include <queue>
#include <list>
#include <set>
#include <cstring>
#include <functional>
#include <deque>
#include <cstdio>
#include <iomanip>
#include <numeric>
#include <limits>
#include <climits>

using namespace::std;

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

int main()
{
	vector<Node*> temp;
	Node* node1 = new Node(1, temp);
	Node* node2 = new Node(2, temp);
	Node* node3 = new Node(3, temp);
	Node* node4 = new Node(4, temp);
	Node* node5 = new Node(5, temp);
	Node* node6 = new Node(6, temp);
	node1->children.push_back(node3);
	node1->children.push_back(node2);
	node1->children.push_back(node4);
	node3->children.push_back(node5);
	node3->children.push_back(node6);

	Solution so;
	cout << so.maxDepth(node1) << endl;
}