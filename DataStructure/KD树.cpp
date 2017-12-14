#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <stack>
#include <queue>

using namespace::std;
using namespace::chrono;

const int k = 2;

struct Node {
	int point[k];
	Node* leftChild;
	Node* rightChild;
};

// A method to create a node of K D tree
Node* newNode(int arr[])
{
	Node* temp = new Node;

	for (int i = 0; i < k; i++)
		temp->point[i] = arr[i];

	temp->leftChild = temp->rightChild = nullptr;
	return temp;
}

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
Node* insertRec(Node* root, int point[], unsigned int depth)
{

#if 0
	if (root == nullptr)
		return newNode(point);

	// Calculate current dimension (cd) of comparison
	unsigned int cd = depth % k;

	// Compare the new point with root on current dimension 'cd'
	// and decide the left or right subtree
	if (point[cd] < (root->point[cd]))
		root->leftChild = insertRec(root->leftChild, point, depth + 1);
	else
		root->rightChild = insertRec(root->rightChild, point, depth + 1);

	return root;
#endif


#if 1
	//非递归插入元素
	if (root == nullptr)
		return newNode(point);

	Node* temp = newNode(point);
	unsigned int cd;
	Node* currentNode = root;
	Node* preNode = nullptr;
	while (currentNode) {
		cd = depth % k;
		preNode = currentNode;
		if (point[cd] < (currentNode->point[cd]))
			currentNode = currentNode->leftChild;
		else
			currentNode = currentNode->rightChild;
		++depth;
	}
	cd = (--depth) % k;
	if (point[cd] < (preNode->point[cd]))
		preNode->leftChild = temp;
	else
		preNode->rightChild = temp;

	return root;
#endif
}

// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
Node* insert(Node* root, int point[])
{
	return insertRec(root, point, 0);
}

// A utility method to determine if two Points are same
// in K Dimensional space
bool isPointSame(int point1[], int point2[])
{
	for (int i = 0; i < k; ++i)
		if (point1[i] != point2[i])
			return false;

	return true;
}

// Searches a Point represented by "point[]" in the K D tree.
// The parameter depth is used to determine current axis.
bool searchRec(Node* root, int point[], unsigned int depth)
{

#if 0
	if (root == nullptr)
		return false;
	if (isPointSame(root->point, point))
		return true;

	// Current dimension is computed using current depth and total
	// dimensions (k)
	unsigned int cd = depth % k;
	if (point[cd] < root->point[cd])
		return searchRec(root->leftChild, point, depth + 1);

	return searchRec(root->rightChild, point, depth + 1);
#endif


#if 1
	//非递归搜索
	if (root == nullptr)
		return false;

	unsigned int cd;
	Node* currentNode = root;

	while (currentNode) {
		cd = depth % k;
		if (isPointSame(currentNode->point, point))
			return true;

		else if (point[cd] < (currentNode->point[cd]))
			currentNode = currentNode->leftChild;
		else
			currentNode = currentNode->rightChild;
		++depth;
	}

	if (currentNode == nullptr)
		return false;
#endif
}

// Searches a Point in the K D tree. It mainly uses
// searchRec()
bool search(Node* root, int point[])
{
	// Pass current depth as 0
	return searchRec(root, point, 0);
}

// A utility function to find minimum of three integers
int min(int x, int y)
{
	return (x < y ? x : y);
}

int min(int x, int y, int z)
{
	return min(x, min(y, z));
}

// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
/*
To find minimum we traverse nodes starting from root.
If dimension of current level is same as given dimension,
then required minimum lies on left side if there is left child.
This is same as Binary Search Tree Minimum.
Above is simple, what to do when current level’s
dimension is different.When dimension of
current level is different, minimum may be either
in left subtree or right subtree or current node
may also be minimum.So we take minimum of three
and return.This is different from Binary Search tree.
*/
int findMinRec(Node* root, int d, unsigned int depth)
{
	if (root == nullptr)
		return INT_MAX;

	// Current dimension is computed using current depth and total
	// dimensions (k)
	unsigned cd = depth % k;

	// Compare point with root with respect to cd (Current dimension)
	if (cd == d) {
		if (root->leftChild == nullptr)
			return root->point[d];
		return findMinRec(root->leftChild, d, depth + 1);
	}

	// If current dimension is different then minimum can be anywhere
	// in this subtree
	return min(root->point[d],
		findMinRec(root->leftChild, d, depth + 1),
		findMinRec(root->rightChild, d, depth + 1));
}

// A wrapper over findMinRec(). Returns minimum of d'th dimension
int findMin(Node* root, int d)
{
	// Pass current level or depth as 0
	return findMinRec(root, d, 0);
}


/*
返回的不是具体的值，而是含有该值的结点
*/
// A utility function to find minimum of three integers
Node* minNode(Node* x, Node* y, Node* z, int d)
{
	Node* res = x;
	if (y != nullptr && y->point[d] < res->point[d])
		res = y;
	if (z != nullptr && z->point[d] < res->point[d])
		res = z;

	return res;
}

// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
Node* findMinRecNode(Node* root, int d, unsigned int depth)
{
	if (root == nullptr)
		return nullptr;

	// Current dimension is computed using current depth and total
	// dimensions (k)
	unsigned cd = depth % k;

	// Compare point with root with respect to cd (Current dimension)
	if (cd == d) {
		if (root->leftChild == nullptr)
			return root;
		return findMinRecNode(root->leftChild, d, depth + 1);
	}

	// If current dimension is different then minimum can be anywhere
	// in this subtree
	return minNode(root,
		findMinRecNode(root->leftChild, d, depth + 1),
		findMinRecNode(root->rightChild, d, depth + 1), d);
}

// A wrapper over findMinRec(). Returns minimum of d'th dimension
Node* findMinNode(Node* root, int d)
{
	// Pass current level or depth as 0
	return findMinRecNode(root, d, 0);
}


// Copies point p2 to p1
void copyPoint(int p1[], int p2[])
{
	for (int i = 0; i < k; ++i)
		p1[i] = p2[i];
}
/*
Like Binary Search Tree Delete, we recursively traverse down and
search for the point to be deleted.Below are steps are followed for every node visited.

1) If current node contains the point to be deleted

If node to be deleted is a leaf node, simply delete it(Same as BST Delete)
If node to be deleted has right child as not NULL(Different from BST)
Find minimum of current node’s dimension in right subtree.
Replace the node with above found minimum and recursively delete minimum in right subtree.
Else If node to be deleted has left child as not NULL(Different from BST)
Find minimum of current node’s dimension in left subtree.
Replace the node with above found minimum and recursively delete minimum in left subtree.
Make new left subtree as right child of current node.
2) If current doesn’t contain the point to be deleted

If node to be deleted is smaller than current node on current dimension, recur for left subtree.
Else recur for right subtree.
Why 1.b and 1.c are different from BST ?
In BST delete, if a node’s left child is empty and right is not empty,
we replace the node with right child.In K D Tree,
doing this would violate the KD tree property as dimension of right child of
node is different from node’s dimension.For example,
if node divides point by x axis values.then its children divide by y axis,
so we can’t simply replace node with right child.Same is true for the case
when right child is not empty and left child is empty.

Why 1.c doesn’t find max in left subtree and recur for max like 1.b ?
Doing this violates the property that all equal values are in right subtree.
For example, if we delete (!0, 10) in below subtree and replace if with

Wrong Way(Equal key in left subtree after deletion)
(5, 6)                             (4, 10)
/               Delete(5, 6)       /
(4, 10  )------------ >           (4, 20)
\
(4, 20)

Right way(Equal key in right subtree after deletion)
(5, 6)                          (4, 10)
/            Delete(5, 6)         \
(4, 10)         ------------ >      (4, 20)
\
(4, 20)
*/


// Function to delete a given point 'point[]' from tree with root
// as 'root'.  depth is current depth and passed as 0 initially.
// Returns root of the modified tree.
Node* deleteNodeRec(Node* root, int point[], int depth)
{
	// Given point is not present
	if (root == nullptr)
		return nullptr;

	// Find dimension of current node
	int cd = depth % k;

	// If the point to be deleted is present at root
	if (isPointSame(root->point, point)) {
		// 2.b) If right child is not NULL
		if (root->rightChild != nullptr)  {
			// Find minimum of root's dimension in right subtree
			Node* min = findMinNode(root->rightChild, cd);

			// Copy the minimum to root
			copyPoint(root->point, min->point);

			// Recursively delete the minimum
			root->rightChild = deleteNodeRec(root->rightChild, min->point, depth + 1);
		}
		else if (root->leftChild != nullptr) { // same as above
			Node* min = findMinNode(root->leftChild, cd);
			copyPoint(root->point, min->point);
			root->leftChild = deleteNodeRec(root->leftChild, min->point, depth + 1);
		}
		else { // If node to be deleted is leaf node
			delete root;
			return nullptr;
		}

		return root;
	}

	// 2) If current node doesn't contain point, search downward
	if (point[cd] < root->point[cd])
		root->leftChild = deleteNodeRec(root->leftChild, point, depth + 1);
	else
		root->rightChild = deleteNodeRec(root->rightChild, point, depth + 1);

	return root;
}

// Function to delete a given point from K D Tree with 'root'
Node* deleteNode(Node *root, int point[])
{
	// Pass depth as 0
	return deleteNodeRec(root, point, 0);
}

/*
先序遍历KD树
*/
void preorder(Node* root)
{
	if (root == nullptr)
		return;
	cout << "(" << root->point[0] << "," << root->point[1] << ")" << ' ';
	preorder(root->leftChild);
	preorder(root->rightChild);
}

/*
中序遍历KD树
*/
void inorder(Node* root)
{
	if (root == nullptr)
		return;
	inorder(root->leftChild);
	cout << "(" << root->point[0] << "," << root->point[1] << ")" << ' ';
	inorder(root->rightChild);
}

/*
后序遍历KD树
*/
void postorder(Node* root)
{
	if (root == nullptr)
		return;
	postorder(root->leftChild);
	postorder(root->rightChild);
	cout << "(" << root->point[0] << "," << root->point[1] << ")" << ' ';
}


/*
先序遍历KD树
迭代法，非递归
*/
/***************************************
二叉树的非递归前序遍历，前序遍历思想：
先让根进栈，只要栈不为空，就可以做弹出操作，
每次弹出一个结点，记得把它的左右结点都进栈，
记得右子树先进栈，这样可以保证右子树在栈中
总处于左子树的下面。
********************************************/
void preorderIterative(Node* root)
{
	if (root == nullptr)
		return;

	stack<Node*> stackNode;
	stackNode.push(root);

	while (!stackNode.empty()) {
		Node* topNode = stackNode.top();
		cout << "(" << topNode->point[0] << "," << topNode->point[1] << ")" << ' ';
		stackNode.pop();

		if (topNode->rightChild != nullptr)
			stackNode.push(topNode->rightChild);
		if (topNode->leftChild != nullptr)
			stackNode.push(topNode->leftChild);
	}
}

/*
中序遍历KD树
迭代法，非递归
*/

void inorderIterative(Node* root)
{
	if (root == nullptr)
		return;

	stack<Node*> stackNode;
	Node* currentTree = root;
	while (currentTree != nullptr || !stackNode.empty()) {
		//先一直遍历到最左叶节点
		while (currentTree != nullptr) {
			stackNode.push(currentTree);
			currentTree = currentTree->leftChild;
		}
		//然后依次pop，再另遍历右子树
		if (!stackNode.empty()) {
			currentTree = stackNode.top();
			stackNode.pop();
			cout << "(" << currentTree->point[0] << "," <<
				currentTree->point[1] << ")" << ' ';
			currentTree = currentTree->rightChild;
		}
	}
}

/*
中序遍历KD树
迭代法，非递归,非栈
*/
/* Function to traverse binary tree without recursion and
without stack */
void inorderIterativeNonStack(Node* root)
{
	Node* currentNode, *preNode;
	if (!root)
		return;

	currentNode = root;
	while (currentNode != nullptr) {
		if (currentNode->leftChild == nullptr) {
			cout << "(" << currentNode->point[0] << "," <<
				currentNode->point[1] << ")" << ' ';
			currentNode = currentNode->rightChild;
		}
		else {
			/* Find the inorder predecessor of current */
			preNode = currentNode->leftChild;
			while (preNode->rightChild != nullptr &&
				preNode->rightChild != currentNode)
				preNode = preNode->rightChild;

			/* Make current as right child of its inorder predecessor */
			if (preNode->rightChild == nullptr) {
				preNode->rightChild = currentNode;
				currentNode = currentNode->leftChild;
			}

			/* Revert the changes made in if part to restore the original
			tree i.e., fix the right child of predecssor */
			else {
				preNode->rightChild = nullptr;
				cout << "(" << currentNode->point[0] << "," <<
					currentNode->point[1] << ")" << ' ';
				currentNode = currentNode->rightChild;
			}
		}
	}
}

/*
后序遍历KD树
迭代法，非递归
*/
void postorderIterative(Node* root)
{
	if (root == nullptr)
		return;

	stack<Node*> stackNode;
	Node* currentTree = root;
	Node* preVisited = nullptr;

	while (currentTree != nullptr || !stackNode.empty()) {
		//这个和中序遍历一样，因为先要访问左子树
		while (currentTree != nullptr) {
			stackNode.push(currentTree);
			currentTree = currentTree->leftChild;
		}

		currentTree = stackNode.top();
		if (currentTree->rightChild == nullptr ||
			currentTree->rightChild == preVisited) {
			cout << "(" << currentTree->point[0] << "," << currentTree->point[1] << ")" << ' ';
			preVisited = currentTree;
			stackNode.pop();
			currentTree = nullptr;
		}
		else
			currentTree = currentTree->rightChild;
	}
}

/*
后序遍历KD树
迭代法，非递归
使用两个栈
*/
void postorderIterativeTwoStacks(Node* root)
{
	if (!root)
		return;

	stack<Node*> stackNode1, stackNode2;
	Node* currentNode;
	stackNode1.push(root);

	//利用先序遍历和后序遍历的遍历次序
	while (!stackNode1.empty()) {
		currentNode = stackNode1.top();
		stackNode1.pop();
		stackNode2.push(currentNode);

		//stack1的遍历顺序为根右左，
		//然后stack2正好是一个栈，与stack1逆序
		if (currentNode->leftChild)
			stackNode1.push(currentNode->leftChild);
		if (currentNode->rightChild)
			stackNode1.push(currentNode->rightChild);
	}

	while (!stackNode2.empty()) {
		cout << "(" << stackNode2.top()->point[0] << ","
			<< stackNode2.top()->point[1] << ")" << ' ';
		stackNode2.pop();
	}

}


/*
非递归层次遍历
使用队列
*/
void levelTraverse(Node* root)
{
	if (!root)
		return;

	queue<Node*> queueNode;
	Node* currentNode = root;

	queueNode.push(currentNode);

	//和先序遍历有些类似
	while (!queueNode.empty()) {
		currentNode = queueNode.front();
		cout << "(" << currentNode->point[0] << ","
			<< currentNode->point[1] << ")" << ' ';
		queueNode.pop();

		if (currentNode->leftChild)
			queueNode.push(currentNode->leftChild);
		if (currentNode->rightChild)
			queueNode.push(currentNode->rightChild);
	}

}

int main()
{
	auto startTime = system_clock::now();

	Node* root = nullptr;
	int points[][k] = { { 3, 6 }, { 17, 15 }, { 13, 15 },
	{ 6, 12 }, { 9, 1 }, { 2, 7 }, { 10, 19 } };

	int n = sizeof(points) / sizeof(points[0]);

	for (int i = 0; i < n; ++i)
		root = insert(root, points[i]);

	cout << "preorder:\n";
	preorder(root);
	cout << endl;
	cout << "preorderIterative:\n";
	preorderIterative(root);
	cout << endl << endl;

	cout << "inorder:\n";
	inorder(root);
	cout << endl;
	cout << "inorderIterative:\n";
	inorderIterative(root);
	cout << endl;
	cout << "inorderIterativeNonStack:\n";
	inorderIterativeNonStack(root);
	cout << endl << endl;

	cout << "postorder:\n";
	postorder(root);
	cout << endl;
	cout << "postorderIterative:\n";
	postorderIterative(root);
	cout << endl;
	cout << "postorderIterativeTwoStacks:\n";
	postorderIterativeTwoStacks(root);
	cout << endl << endl;

	cout << "levelTraverse:\n";
	levelTraverse(root);
	cout << endl << endl;

	int point0[] = { 3, 7 };
	cout << "search (3, 7) ";
	(search(root, point0)) ? cout << "Found\n" : cout << "Not Found\n";

	int point1[] = { 10, 19 };
	cout << "search (10, 19) ";
	(search(root, point1)) ? cout << "Found\n" : cout << "Not Found\n";

	cout << "search (12, 19) ";
	int point2[] = { 12, 19 };
	(search(root, point2)) ? cout << "Found\n" : cout << "Not Found\n";

	cout << "Minimum of 0'th dimension is " << findMin(root, 0) << endl;
	cout << "Minimum of 1'th dimension is " << findMin(root, 1) << endl;

	root = deleteNode(root, points[1]);
	cout << "Root after deletion of (3, 6)\n";
	cout << root->point[0] << ", " << root->point[1] << endl;

	cout << "after deleteNode:\n";
	cout << "preorder:\n";
	preorder(root);
	cout << endl;

	cout << "inorder:\n";
	inorder(root);
	cout << endl;

	auto endTime = system_clock::now();
	auto durationTime = duration_cast<microseconds>(endTime - startTime);

	cout << "花费了："
		<< double(durationTime.count()) * microseconds::period::num / microseconds::period::den
		<< "秒" << endl;
	return 0;     
}