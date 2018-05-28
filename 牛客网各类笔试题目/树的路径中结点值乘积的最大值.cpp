/*
输入：
int numNodes = 5;
int rootNode = 1;
vector<int> values = { 2, 4, 10, 20, 1 };
vector < vector<int>> edges = { { 1, 2 }, { 1, 3 }, { 2, 4 }, { 2, 5 } };

输出：160
因为：2*4*20 = 160
     1
   2  3
 4  5
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace::std;

class Node
{
public:
	Node() = default;
	Node(int index, int value)
	{
		this->index = index;
		this->value = value;
		muntiValue = 1;
		sons.clear();
	}

	void addSon(Node *son) { sons.push_back(son); }

public:
	int index;
	int value;
	vector<Node*> sons;
	int muntiValue;
};

Node* buildTree(int numOfNodes, int firstIndex,
	vector<int> &values, vector<vector<int>> &edges)
{
	vector<Node*> nodes(numOfNodes);
	for (int i = 0; i < numOfNodes; ++i)
		nodes[i] = new Node(i + 1, values[i]);
	for (int i = 0; i < edges.size(); ++i)
		nodes[edges[i][0] - 1]->addSon(nodes[edges[i][1] - 1]);

	return nodes[firstIndex - 1];
}

int dfs(Node *root, int parentValue, int maximum)
{
	if (root->sons.size() == 0)
		return root->muntiValue;
	for (Node *son : root->sons) {
		son->muntiValue = son->value* parentValue;
		maximum = max(maximum, dfs(son, son->muntiValue, maximum));
		son->muntiValue = parentValue;
	}

	return maximum;
}


int getMaxProducts(int numNodes, int rootNode,
	vector<int> &values, vector<vector<int>> &edges)
{
	Node* root = buildTree(numNodes, rootNode, values, edges);
	return dfs(root, root->value, INT_MIN);
}

int main()
{
	int numNodes = 5;
	int rootNode = 1;
	vector<int> values = { 2, 4, 10, 20, 1 };
	vector < vector<int>> edges = { { 1, 2 }, { 1, 3 }, { 2, 4 }, { 2, 5 } };
	cout << getMaxProducts(numNodes, rootNode, values, edges) << endl;
	return 0;
}