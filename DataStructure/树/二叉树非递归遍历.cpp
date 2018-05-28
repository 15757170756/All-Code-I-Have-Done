#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <queue>
#include <stack>
#include <cassert>

using namespace::std;

struct Node
{
	Node *lc;
	Node *rc;
	int value;
	Node(int value = 0) :
		value(value), lc(nullptr), rc(nullptr){}
};

void preorder(Node *root)
{
	assert(root != nullptr);

	stack<Node*> stackNode;
	stackNode.push(root);
	while (!stackNode.empty()) {
		Node *topNode = stackNode.top();
		cout << topNode->value << endl;
		stackNode.pop();

		if (topNode->rc != nullptr)
			stackNode.push(topNode->rc);
		if (topNode->lc != nullptr)
			stackNode.push(topNode->lc);
	}
}

void inorder(Node *root)
{
	assert(root != nullptr);

	stack<Node*> stackNode;
	Node *currentNode = root;

	while (!stackNode.empty() || currentNode != nullptr) {
		while (currentNode != nullptr) {
			stackNode.push(currentNode);
			currentNode = currentNode->lc;
		}
		if (!stackNode.empty()) {
			currentNode = stackNode.top();
			stackNode.pop();
			cout << currentNode->value << endl;
			currentNode = currentNode->rc;
		}
	}
}

void postorder(Node *root)
{
	assert(root != nullptr);
	stack<Node*> stackNode;
	Node *currentNode = root;
	Node *preNode = nullptr;

	while (!stackNode.empty() || currentNode != nullptr) {
		while (currentNode != nullptr) {
			stackNode.push(currentNode);
			currentNode = currentNode->lc;
		}
		currentNode = stackNode.top();
		if (currentNode->rc == nullptr ||
			currentNode->rc == preNode) {
			cout << currentNode->value << endl;
			preNode = currentNode;
			stackNode.pop();
			currentNode = nullptr;
		}
		else
			currentNode = currentNode->rc;
	}
}
