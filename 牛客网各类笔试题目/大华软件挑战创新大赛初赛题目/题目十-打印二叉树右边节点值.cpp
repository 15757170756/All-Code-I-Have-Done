/*
"假设你站在一棵二叉树的右边，从上往下，请输出你看到的节点。比如：
5         <---
/ \
2   3       <---
/   / \
4   6   8     <---
返回 538。"

"输入的第一行指定用例数量T；
用例的第一行输入二叉树(以先序序列的方式输入，
比如题目的二叉树可以用""524###36##8##"")；"

输出从上往下看到的节点序列

输入字符串长度<1000

Input:
1
524###36##8##

Output:
538

*/



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
#include <functional>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <unordered_map>

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

BinaryTreeNode* getRightNode(char **str)
{
	if (**str == '#') {
		++(*str);
		return nullptr;
	}
	int num = (**str) - '0';
	++(*str);
	BinaryTreeNode *pRoot = new BinaryTreeNode(num);
	if (**str == '\0')
		return pRoot;
	pRoot->left = getRightNode(str);
	pRoot->right = getRightNode(str);

	return pRoot;
}

void preorder(BinaryTreeNode *pRoot)
{
	if (pRoot != nullptr) {
		cout << pRoot->data << ' ';
		preorder(pRoot->left);
		preorder(pRoot->right);
	}
}

BinaryTreeNode* getRightNode(char *str)
{
	if (str == nullptr)
		return nullptr;
	return getRightNode(&str);
}

void printRight(BinaryTreeNode *pRoot)
{
	if (pRoot == nullptr)
		return;
	queue<BinaryTreeNode*> q1, q2;
	q1.push(pRoot);
	while (!(q1.empty() && q2.empty())) {
		while (!q1.empty()) {
			BinaryTreeNode *frontNode = q1.front();
			q1.pop();
			if (frontNode->left != nullptr)
				q2.push(frontNode->left);
			if (frontNode->right != nullptr)
				q2.push(frontNode->right);

			if (q1.empty())
				cout << frontNode->data;
		}

		while (!q2.empty()) {
			BinaryTreeNode *frontNode = q2.front();
			q2.pop();
			if (frontNode->left != nullptr)
				q1.push(frontNode->left);
			if (frontNode->right != nullptr)
				q1.push(frontNode->right);

			if (q2.empty())
				cout << frontNode->data;
		}
	}
}

void test1()
{
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	while (t--) {
		char s[1000];
		cin >> s;
		BinaryTreeNode *pRoot = getRightNode(s);
		//preorder(pRoot);
		printRight(pRoot);
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
	test1();

}