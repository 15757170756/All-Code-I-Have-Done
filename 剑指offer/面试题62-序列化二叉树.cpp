#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>
#include <unordered_set>
#include <sstream>
#include <map>
#include <iterator>
#include <set>
#include <stack>
#include <deque>

using namespace::std;

struct BinaryTreeNode
{
	int data;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
	BinaryTreeNode() :data(0), left(nullptr), right(nullptr){}
	BinaryTreeNode(int value) :data(value), left(nullptr), right(nullptr){}
};

BinaryTreeNode* createNode(int value)
{
	BinaryTreeNode *newNode = new BinaryTreeNode(value);
	return newNode;
}

BinaryTreeNode* connectNode(BinaryTreeNode *parent,
	BinaryTreeNode *leftChild, BinaryTreeNode *rightChild)
{
	parent->left = leftChild;
	parent->right = rightChild;
	return parent;
}

void serialize(BinaryTreeNode *pRoot)
{
	if (pRoot == nullptr) {
		printf("$,");
		return;
	}
	printf("%d,", pRoot->data);
	serialize(pRoot->left);
	serialize(pRoot->right);
}

bool isReadStream(istream &stream, int *number)
{
	return false;
}

void deserialize(BinaryTreeNode **pRoot, istream &stream)
{
	int number;
	if (isReadStream(stream, &number)) {
		*pRoot = new BinaryTreeNode(number);

		deserialize(&((*pRoot)->left), stream);
		deserialize(&((*pRoot)->right), stream);
	}
}

char* serialize2(BinaryTreeNode *pRoot)
{
	string s;
	stack<BinaryTreeNode*> stackNode;
	stackNode.push(pRoot);
	while (!stackNode.empty()) {
		BinaryTreeNode *topNode = stackNode.top();
		if (topNode != nullptr) {
			s.append(to_string(topNode->data));
			s.push_back(',');
		}
		else
			s.append("$,");
		stackNode.pop();
		if (topNode != nullptr)
			stackNode.push(topNode->right);
		if (topNode != nullptr)
			stackNode.push(topNode->left);
	}

	s.pop_back();

	char *result = new char[s.size() + 1];
	strcpy(result, s.c_str());
	return result;

}

BinaryTreeNode* deserialize(char **str)
{
	if (**str == '$'){
		++(*str);
		return nullptr;
	}
	int num = 0;
	while (**str != '\0' && **str != ',') {
		num = num * 10 + ((**str) - '0');
		++(*str);
	}
	BinaryTreeNode *pRoot = new BinaryTreeNode(num);
	if (**str == '\0')
		return pRoot;
	else
		++(*str);
	pRoot->left = deserialize(str);
	pRoot->right = deserialize(str);

	return pRoot;
}

BinaryTreeNode* deserialize(char *str)
{
	if (str == nullptr)
		return nullptr;

	return deserialize(&str);
}



void postorder(BinaryTreeNode *pRoot)
{
	if (pRoot == nullptr)
		return;
	postorder(pRoot->left);
	postorder(pRoot->right);
	printf("%d ", pRoot->data);
}

void test1()
{
	BinaryTreeNode *p10 = new BinaryTreeNode(10);
	BinaryTreeNode *p6 = new BinaryTreeNode(6);
	BinaryTreeNode *p3 = new BinaryTreeNode(3);
	BinaryTreeNode *p7 = new BinaryTreeNode(7);
	BinaryTreeNode *p14 = new BinaryTreeNode(14);
	BinaryTreeNode *p12 = new BinaryTreeNode(12);
	BinaryTreeNode *p15 = new BinaryTreeNode(15);

	BinaryTreeNode *p2 = new BinaryTreeNode(2);
	BinaryTreeNode *p1 = new BinaryTreeNode(1);

	connectNode(p10, p6, p14);
	connectNode(p6, p3, p7);
	connectNode(p14, p12, p15);
	connectNode(p3, p2, nullptr);
	connectNode(p2, p1, nullptr);

	printf("%s\n", serialize2(p10));
	char *str = "1,2,4,$,$,$,3,5,$,$,6,$,$";
	postorder(p10);
	printf("\n");
	postorder(deserialize(str));
	//printf("\n");
	//printf("%s\n",str);
	//	printf("%s\n", serialize2(deserialize(str)));

}



int main(int argc, char* argv[])
{
	test1();

	return 0;
}