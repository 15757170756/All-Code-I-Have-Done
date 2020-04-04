/*
https://leetcode-cn.com/problems/middle-of-the-linked-list/
876. 链表的中间结点
给定一个带有头结点 head 的非空单链表，返回链表的中间结点。

如果有两个中间结点，则返回第二个中间结点。

示例 1：

输入：[1,2,3,4,5]
输出：此列表中的结点 3 (序列化形式：[3,4,5])
返回的结点值为 3 。 (测评系统对该结点序列化表述是 [3,4,5])。
注意，我们返回了一个 ListNode 类型的对象 ans，这样：
ans.val = 3, ans.next.val = 4, ans.next.next.val = 5, 以及 ans.next.next.next = NULL.
示例 2：

输入：[1,2,3,4,5,6]
输出：此列表中的结点 4 (序列化形式：[4,5,6])
由于该列表有两个中间结点，值分别为 3 和 4，我们返回第二个结点。

提示：

给定链表的结点数介于 1 和 100 之间。
通过次数54,508提交次数79,388
在真实的面试中遇到过这道题？
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* middleNode(ListNode* head) {
		int num = 0;
		ListNode* headaux = head;
		while (head->next != nullptr) {
			++num;
			head = head->next;
		}
		++num;
		int mid = num / 2;
		//mid += (num % 2 == 0 ? 1 : 0);
		while (headaux->next != nullptr && mid) {
			--mid;
			headaux = headaux->next;
		}
		return headaux;
	}
};


/*
执行结果：
通过
显示详情
执行用时 :
0 ms
, 在所有 C++ 提交中击败了
100.00%
的用户
内存消耗 :
6.3 MB
, 在所有 C++ 提交中击败了
100.00%
的用户
炫耀一下:

写题解，分享我的解题思路
进行下一个挑战：
两数相加
中等
有序链表转换二叉搜索树
中等
分割链表
中等
提交时间
提交结果
执行用时
内存消耗
语言
几秒前	通过	0 ms	6.3 MB
*/



//快慢指针，会更快一点
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* middleNode(ListNode* head) {
		ListNode* fastNode = head;
		while (fastNode && fastNode->next) {
			head = head->next;
			fastNode = fastNode->next->next;
		}
		return head;
	}
};

/*
执行结果：
通过
显示详情
执行用时 :
0 ms
, 在所有 C++ 提交中击败了
100.00%
的用户
内存消耗 :
6.8 MB
, 在所有 C++ 提交中击败了
100.00%
的用户
炫耀一下:


*/