/***************************************
删除链表成员中与x值相等的（x由键盘输入）的
所有结点
****************************************/


// C Program to delete all occurrences of a given key in linked list
#include <stdio.h>
#include <stdlib.h>

// A linked list node
typedef struct Node
{
	int charData;
	struct Node *next;
}listNode, *LinkList;

/* Given a reference (pointer to pointer) to the head of a list
and an int, inserts a new node on the front of the list. */
void push_ahead(LinkList* headNode, char newChar)
{
	listNode* newNode = (listNode*)malloc(sizeof(listNode));
	newNode->charData = newChar;
	newNode->next = (*headNode);
	(*headNode) = newNode;
}

/* Given a reference (pointer to pointer) to the head of a list and
a key, deletes all occurrence of the given key in linked list */
void deleteKey(LinkList* headNode, char key)
{
	// Store head node
	listNode* currentNode = *headNode, *prevNode;

	// If head node itself holds the key or multiple occurrences of key
	while (currentNode != NULL && currentNode->charData == key)
	{
		*headNode = currentNode->next;   // Changed head
		free(currentNode);               // free old head
		currentNode = *headNode;         // Change Temp
	}

	// Delete occurrences other than head
	while (currentNode != NULL)
	{
		// Search for the key to be deleted, keep track of the
		// previous node as we need to change 'prev->next'
		while (currentNode != NULL && currentNode->charData != key)
		{
			prevNode = currentNode;
			currentNode = currentNode->next;
		}

		// If key was not present in linked list
		if (currentNode == NULL) return;

		// Unlink the node from linked list
		prevNode->next = currentNode->next;

		free(currentNode);  // Free memory

		//Update Temp for next iteration of outer loop
		currentNode = prevNode->next;
	}
}

// This function prints contents of linked list starting from
// the given node
void printList(listNode* headNode)
{
	if (headNode == NULL) {
		printf("the list is NULL.\n");
		return;
	}
	while (headNode != NULL)
	{
		printf("%c", headNode->charData);
		headNode = headNode->next;
	}
	printf("\n");
}

/* Drier program to test above functions*/
int main()
{
	/* Start with the empty list */
	listNode* headNode = NULL;
	char inputChar;
	printf("Please input a string and quit with Enter:\n");
	while ((inputChar = getchar()) != '\n')
		push_ahead(&headNode, inputChar);

	char key;// key to delete

	puts("Created Linked List: ");
	printList(headNode);

	printf("Please input the char you want to delete and quit with Enter:\n");
	scanf("%c", &key);

	deleteKey(&headNode, key);
	puts("Linked List after deletion: ");

	printList(headNode);

	return 0;
}