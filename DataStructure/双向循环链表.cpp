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
#include <cstring>

using namespace std;

struct Node
{
	int data;
	Node *next;
	Node *prev;
	Node(int data, Node *next, Node *prev)
		:data(data), next(next), prev(prev) { }
	Node(int data) :data(data), next(nullptr), prev(nullptr) { }
};

void insertEnd(Node **start, int value)
{
	if (*start == nullptr) {
		Node *newNode = new Node(value);
		newNode->next = newNode->prev = newNode;
		*start = newNode;
		return;
	}
	Node *last = (*start)->prev;
	Node *newNode = new Node(value, *start, last);
	(*start)->prev = newNode;
	last->next = newNode;
}

void insertBegin(Node **start, int value)
{
	Node *last = (*start)->prev;
	Node *newNode = new Node(value, *start, last);
	last->next = (*start)->prev = newNode;
	*start = newNode;
}

void insertAfter(Node **start, int value1, int value2)
{
	Node *newNode = new Node(value1);
	Node *curNode = *start;
	while (curNode->data != value2)
		curNode = curNode->next;
	Node *next = curNode->next;

	curNode->next = newNode;
	newNode->prev = curNode;
	newNode->next = next;
	next->prev = newNode;
}

void display(Node *start)
{
	Node *curNode = start;
	printf("\nTraversal in forward direction \n");
	while (curNode->next != start) {
		printf("%d ", curNode->data);
		curNode = curNode->next;
	}
	printf("%d ", curNode->data);

	printf("\nTraversal in reverse direction \n");
	Node *last = start->prev;
	curNode = last;
	while (curNode->prev != last) {
		printf("%d ", curNode->data);
		curNode = curNode->prev;
	}
	printf("%d ", curNode->data);
}

void deleteNode(Node **start, int key)
{
	if (*start == nullptr)
		return;

	Node *curNode = *start, *prev1 = nullptr;
	while (curNode->data != key) {
		if (curNode->next == *start) {
			printf("\nList doesn't have node with value key\n");
			return;
		}
		prev1 = curNode;
		curNode = curNode->next;
	}
	if (curNode->next == *start && prev1 == nullptr) {
		(*start) = nullptr;
		delete curNode;
		return;
	}

	if (curNode == *start) {
		prev1 = (*start)->prev;
		*start = (*start)->next;
		prev1->next = *start;
		(*start)->prev = prev1;
		delete curNode;
	}
	else if (curNode->next == *start) {
		prev1->next = (*start);
		(*start)->prev = prev1;
		delete curNode;
	}
	else {
		Node *temp = curNode->next;
		prev1->next = temp;
		temp->prev = prev1;
		delete curNode;
	}
}

int main()
{
	// Start with the empty list
	struct Node *start = NULL;

	// Created linked list will be 4->5->6->7->8
	insertEnd(&start, 4);
	insertEnd(&start, 5);
	insertEnd(&start, 6);
	insertEnd(&start, 7);
	insertEnd(&start, 8);

	printf("List Before Deletion: ");
	display(start);

	// Delete the node which is not present in list
	deleteNode(&start, 9);
	printf("\nList After Deletion: ");
	display(start);

	// Delete the first node
	deleteNode(&start, 4);
	printf("\nList After Deleting %d: ", 4);
	display(start);

	// Delete the last node
	deleteNode(&start, 8);
	printf("\nList After Deleting %d: ", 8);
	display(start);

	// Delete the middle node
	deleteNode(&start, 6);
	printf("\nList After Deleting %d: ", 6);
	display(start);


	return 0;
}