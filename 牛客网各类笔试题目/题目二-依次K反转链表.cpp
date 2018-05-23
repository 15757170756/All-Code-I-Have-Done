/*
给定一个链表，实现一个函数，将链表中每k个节点进行翻转，
若最后一组节点数量不足k个，则按实际个数翻转。
例如：给定链表1->2->3->4->5->6->7->8->NULL，k=3，
翻转后输出3->2->1->6->5->4->8->7->NULL。
翻转函数reverse有两个参数，分别为链表头指针和翻转步长k。

"1<=T<=10
1<=N<=100
1<=K<=N"

"
Input:
1
8
1 2 2 4 5 6 7 8
4

Output:
4 2 2 1 8 7 6 5"


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

using namespace::std;

void reverseK(vector<int> &vec, int k)
{
	if (vec.size() <= 0 || k < 1)
		return;
	int times = vec.size() / k;
	for (int i = 0; i < times; ++i) {
		for (int j = (i + 1) * k - 1, m = 0; m < k; ++m, --j)
			cout << vec[j] << ' ';
	}
	for (int i = vec.size() - 1; i >= times*k; --i)
		cout << vec[i] << ' ';
	cout << endl;
}

void test1()
{
	freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> vec(n);
		for (int i = 0; i < n; ++i)
			cin >> vec[i];
		int k;
		cin >> k;
		reverseK(vec, k);
	}

}


int main(int argc, char* argv[])
{
	test1();
	return 0;
}















//上面是投机的，这才是真正的，但是其实也是蛮难的感觉
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
#include <iomanip>

using namespace::std;

struct listNode
{
	int data;
	listNode *next;
	listNode(int data) :data(data), next(nullptr){}
	listNode(){}
};

void push_back(listNode **pHead, int data)
{
	listNode *newNode = new listNode(data);
	if ((*pHead) == nullptr) {
		(*pHead) = newNode;
		return;
	}
	listNode *curNode = (*pHead);
	while (curNode->next != nullptr)
		curNode = curNode->next;
	curNode->next = newNode;
}

listNode* reverseK(listNode *pHead, unsigned int k)
{
	if (pHead == nullptr || k <= 1)
		return pHead;

	listNode *begin = pHead; //begin是当前段的开始
	listNode *end = begin; //end是下一段的开始
	listNode *newHead = begin; //新的链表头
	listNode *preNode = pHead; //是上一段最后的一个节点

	int flag = 0; //记录是第几段
	while (end != nullptr) {
		int count = 1;
		while (end->next != nullptr && count < k) {
			end = end->next;
			++count;
		}
		if (count == k) {

			if (flag == 0)
				newHead = end;
			++flag;
			if (flag > 1) {  //不是第一段时候就需要段与段之间的连接
				preNode->next = end;
				preNode = begin;
			}
			end = end->next; //下一段的开始
			listNode *prev = nullptr;
			int i = 0;
			while (i < k) { //本段链表反转
				listNode *nextNode = begin->next;
				begin->next = prev;
				prev = begin;
				begin = nextNode;
				++i;
			}
			begin = end;  //下一段的开始
			//preNode->next = end;
			/*
			如果else直接break的话，需要上面注释的语句，
			两个段之间连接，是为了避免下一段节点数不足k个，
			则不能使用第30行代码来连接段是为了避免下一段节点数不足k个，
			则不能使用第30行代码来连接段*/
		}
		else {
			listNode *curNode = begin;
			listNode *pre = nullptr;
			while (curNode != nullptr) {
				listNode *nextNode = curNode->next;
				curNode->next = pre;
				pre = curNode;
				curNode = nextNode;
			}
			preNode->next = end;
			break;
		}
	}

	return newHead;
}

void printList(listNode *pHead)
{
	while (pHead != nullptr) {
		cout << pHead->data << ' ';
		pHead = pHead->next;
	}
}

void test1()
{
	freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		listNode *pHead = nullptr;
		for (int i = 0; i < n; ++i) {
			int temp;
			cin >> temp;
			push_back(&pHead, temp);
		}
		//printList(pHead);
		//cout << endl;
		int k;
		cin >> k;
		printList(reverseK(pHead, k));

		cout << endl;
	}
}


int main()
{
	test1();

	return 0;
}
