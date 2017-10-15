/***************************************
����n��ѧϰС���Ա��������Ա��Ϣ����
ѧ�š�������4�ſγɼ�����ÿ����Ա��ƽ���ɼ�
�Լ��ҳ�ƽ���ɼ���ߵĳ�Ա��Ϣ��
****************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stuInfo {
	char num[20];
	char name[20];
	int score[4];
} stuInfo;

typedef struct Node {
	stuInfo stu;
	struct Node* next;
}listNode, *linkList;

void push_ahead(linkList* plist, stuInfo stu);
void push_back(linkList* plist, stuInfo stu);
void getAveScore(linkList* plist);
//listNode* reverseList(listNode* plist);
void reverseList(linkList* plist);

int main(int argc, char* argv[])
{
	stuInfo stu;
	char input[20];

	printf("������ѧ����Ϣ��˳��Ϊѧ�š�������4�ſγɼ���ÿ��ѧ���Իس����������һCrtl+Z ���س�������\n");

	listNode* headNode = (listNode*)malloc(sizeof(listNode));
	headNode->next = NULL;
	int scanfReturnValue = scanf("%s", input);
	if (scanfReturnValue == EOF) {
		printf("û�����룬�����Զ���ֹ��\n");
		return 0;
	}
	strcpy(stu.num, input);
	scanf("%s", input);
	strcpy(stu.name, input);
	for (int i = 0; i < 4; ++i)
		scanf("%d", &stu.score[i]);
	headNode->stu = stu;

	while (scanf("%s", input) != EOF && input[0] != '\0') {
		strcpy(stu.num, input);
		scanf("%s", input);
		strcpy(stu.name, input);
		for (int i = 0; i < 4; ++i)
			scanf("%d", &stu.score[i]);
		push_back(&headNode, stu);
	}

	//reverseList(&headNode);

	getAveScore(&headNode);

	return 0;
}

void push_ahead(linkList* plist, stuInfo stu)
{
	listNode* newNode = (listNode*)malloc(sizeof(listNode));
	newNode->stu = stu;
	newNode->next = (*plist);
	(*plist) = newNode;
}

void push_back(linkList* plist, stuInfo stu)
{
	listNode* newNode = (listNode*)malloc(sizeof(listNode));
	newNode->stu = stu;
	listNode* endNode = (*plist);

	while (endNode->next != NULL)
		endNode = endNode->next;

	endNode->next = newNode;
	newNode->next = NULL;
}

void getAveScore(linkList* plist)
{
	listNode* currentNode = *plist;
	double aveScore;
	double maxAveScore = 0;
	char maxAveScoreStuNum[20];
	while (currentNode != NULL) {
		aveScore = 0.0;
		for (int i = 0; i < 4; ++i)
			aveScore += currentNode->stu.score[i];
		aveScore /= 4;
		printf("ѧ��Ϊ%s��ѧ����ƽ���ɼ�Ϊ��%.1f\n", currentNode->stu.num, aveScore);
		if (aveScore > maxAveScore) {
			maxAveScore = aveScore;
			strcpy(maxAveScoreStuNum, currentNode->stu.num);
		}
		currentNode = currentNode->next;
	}

	currentNode = *plist;
	while (currentNode != NULL && strcmp(maxAveScoreStuNum, currentNode->stu.num))
		currentNode = currentNode->next;
	if (!strcmp(maxAveScoreStuNum, currentNode->stu.num)) {
		printf("ƽ���ɼ���ߵ�ѧ����ϢΪ��%s %s", currentNode->stu.num, currentNode->stu.name);
		for (int i = 0; i < 4; ++i)
			printf(" %d ", currentNode->stu.score[i]);
	}
	printf("\n");
}

//listNode* reverseList(listNode* headNode)
//{
//	listNode* reversedHead = NULL;
//	listNode* currentNode = headNode;
//	listNode* preNode = NULL;
//
//	while (currentNode != NULL) {
//		listNode* currentNextNode = currentNode->next;
//
//		if (currentNextNode == NULL)
//			reversedHead = currentNode;
//
//		currentNode->next = preNode;
//		preNode = currentNode;
//		currentNode = currentNextNode;
//	}
//	
//	return reversedHead;
//}

void reverseList(linkList* headNode)
{
	listNode* currentNode = *headNode;
	listNode* preNode = NULL;

	while (currentNode != NULL) {
		listNode* currentNextNode = currentNode->next;

		if (currentNextNode == NULL)
			*headNode = currentNode;

		currentNode->next = preNode;
		preNode = currentNode;
		currentNode = currentNextNode;
	}
}