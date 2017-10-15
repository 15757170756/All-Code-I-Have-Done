/***************************************
Josephus问题：n个人围坐一圈，现从第1个人开始
报数，顺时针数到m的人出列，然后从出列的下一个人
重新开始报数，数到m的人出列。。。如此反复，
直至最后剩下一人便是胜利者。
输入任意的n和m（m<n），输出第几个是胜利者。
****************************************/

/***************************************
解决方案：主要还是建立循环链表，依次删除满足的
结点，最后上下的就是那个胜利者
****************************************/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int data;
	struct Node *next;
}listNode, *linkList;

void push_ahead(linkList* headNode, int data);

int JosephusProblem(linkList* headNode, int n, int m);

int main()
{
	int n = 100, m = 67;
	listNode *headNode = NULL;
	for (int i = n; i > 0; --i)
		push_ahead(&headNode, i);

	int result = JosephusProblem(&headNode, n, m);

	printf("%d\n", result);
	return 0;
}

//头插法，建立循环链表
void push_ahead(linkList* headNode, int data)
{
	listNode *newNode = (listNode*)malloc(sizeof(listNode));
	listNode *endNode = *headNode;
	newNode->data = data;
	newNode->next = *headNode;

	if (*headNode != NULL) {
		while (endNode->next != *headNode)
			endNode = endNode->next;
		endNode->next = newNode;
	}
	else
		newNode->next = newNode;

	*headNode = newNode;
}


int JosephusProblem(linkList *headNode, int n, int m)
{
	listNode *currentNode = *headNode;
	listNode *preNode = NULL;
	while (n > 1) {
		if (m == 1) {
			listNode* temp = currentNode->next;
			free(currentNode);
			currentNode = temp;
		}
		else {
			for (int i = m - 1; i > 0; --i) {
				preNode = currentNode;
				currentNode = currentNode->next;
			}
			//delete currentNode
			preNode->next = currentNode->next;
			listNode* temp = currentNode->next;
			free(currentNode);
			currentNode = temp;
		}
		n--;
	}

	return currentNode->data;
}
