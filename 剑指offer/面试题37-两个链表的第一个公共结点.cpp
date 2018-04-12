#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>

using namespace::std;

struct ListNode
{
	int value;
	ListNode *next;
	ListNode(int value)
		:value(value), next(nullptr){}

};

size_t getListLength(ListNode *pHead)
{
	size_t length = 0;
	ListNode *pNode = pHead;
	while (pNode != nullptr){
		++length;
		pNode = pNode->next;
	}

	return length;
}

ListNode* findFirstCommondNode(ListNode *list1, ListNode *list2)
{
	size_t list1Len = getListLength(list1);
	size_t list2Len = getListLength(list2);
	int diff = list1Len - list2Len;
	ListNode *listHeadLong = list1;
	ListNode *listHeadShort = list2;

	if (list2Len > list1Len) {
		listHeadLong = list2;
		listHeadShort = list1;
		diff = list2Len - list1Len;
	}

	for (int i = 0; i < diff; ++i)
		listHeadLong = listHeadLong->next;

	while (listHeadLong != nullptr
		&& listHeadShort != nullptr
		&& listHeadLong != listHeadShort) {
		listHeadLong = listHeadLong->next;
		listHeadShort = listHeadShort->next;
	}
	ListNode *pFirstCommondNode = listHeadLong;

	return pFirstCommondNode;
}

ListNode* CreateListNode(int value)
{
	ListNode* pNode = new ListNode(value);
	return pNode;
}

void ConnectListNodes(ListNode* pCurrent, ListNode* pNext)
{
	if (pCurrent == NULL)
	{
		printf("Error to connect two nodes.\n");
		exit(1);
	}

	pCurrent->next = pNext;
}

void PrintListNode(ListNode* pNode)
{
	if (pNode == NULL)
	{
		printf("The node is NULL\n");
	}
	else
	{
		printf("The key in node is %d.\n", pNode->value);
	}
}

void PrintList(ListNode* pHead)
{
	printf("PrintList starts.\n");

	ListNode* pNode = pHead;
	while (pNode != NULL)
	{
		printf("%d\t", pNode->value);
		pNode = pNode->next;
	}

	printf("\nPrintList ends.\n");
}

void Test(char* testName, ListNode* pHead1, ListNode* pHead2, ListNode* pExpected)
{
	if (testName != NULL)
		printf("%s begins: ", testName);

	ListNode* pResult = findFirstCommondNode(pHead1, pHead2);
	if (pResult == pExpected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 第一个公共结点在链表中间
// 1 - 2 - 3 \
//            6 - 7
//     4 - 5 /
void Test1()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);
	ListNode* pNode6 = CreateListNode(6);
	ListNode* pNode7 = CreateListNode(7);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode6);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	Test("Test1", pNode1, pNode4, pNode6);

}

// 没有公共结点
// 1 - 2 - 3 - 4
//            
// 5 - 6 - 7
void Test2()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);
	ListNode* pNode6 = CreateListNode(6);
	ListNode* pNode7 = CreateListNode(7);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	Test("Test2", pNode1, pNode5, NULL);

}

// 公共结点是最后一个结点
// 1 - 2 - 3 - 4 \
//                7
//         5 - 6 /
void Test3()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);
	ListNode* pNode6 = CreateListNode(6);
	ListNode* pNode7 = CreateListNode(7);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode7);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	Test("Test3", pNode1, pNode5, pNode7);
}

// 公共结点是第一个结点
// 1 - 2 - 3 - 4 - 5
// 两个链表完全重合   
void Test4()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	Test("Test4", pNode1, pNode1, pNode1);
}

// 输入的两个链表有一个空链表
void Test5()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	Test("Test5", NULL, pNode1, NULL);

}

// 输入的两个链表有一个空链表
void Test6()
{
	Test("Test6", NULL, NULL, NULL);
}

int main(int argc, char* argv[])
{
	//freopen("input.txt", "r", stdin);
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}


