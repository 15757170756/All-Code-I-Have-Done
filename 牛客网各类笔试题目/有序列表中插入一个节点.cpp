/*
在有序列表中插入一个节点 
struct LinkNode { 　　
int val; 　　
struct LinkNode * next; }; 
struct LinkNode * insert( LinkNode * head, LinkNode * node );
*/
struct LinkNode {
	int val;
	struct LinkNode * next;
};
struct LinkNode *insert(LinkNode * head, LinkNode * node)
{
	assert(head != nullptr && node != nullptr);
	LinkNode *currendNode = head;
	LinkNode *preNode = nullptr;
	bool isDizeng;
	if (currendNode->val > currendNode->next->val)
		isDizeng = false;
	else
		isDizeng = true;

	if (isDizeng == true) {
		while (node->val > currendNode->val
			&& currendNode != nullptr) {
			preNode = currendNode;
			currendNode = currendNode->next;
		}
		node->next = currendNode;
		preNode->next = node;
	}
	else {
		while (node->val < currendNode->val &&
			currendNode != nullptr) {
			preNode = currendNode;
			currendNode = currendNode->next;
		}
		node->next = currendNode;
		preNode->next = node;
	}

	return head;
}

/*
首先做聊表和二叉树的题目，就要考虑指针问题，如指向null指针。
考虑链表为空，或者只有一个节点，然后插入的结点如果是头部，或者尾部之类的。

这里有些瑕疵currendNode->val > currendNode->next->val，默认是有两个结点的
所以看似简单，实则考虑的要蛮多的，还得看中基础编程能力。

*/

struct LinkNode {
	int val;
	LinkNode *next;
	LinkNode(int value) :val(value), next(nullptr) {}
	LinkNode(){}
};
struct LinkNode *insert(LinkNode * head, LinkNode * node)
{
	assert(head != nullptr && node != nullptr);
	LinkNode *currendNode = head;
	LinkNode *preNode = nullptr;

	if (head->next == nullptr) {
		head->next = node;
		return head;
	}

	bool isDizeng;
	if (currendNode->val > currendNode->next->val)
		isDizeng = false;
	else
		isDizeng = true;

	if (isDizeng == true) {
		if (node->val <= head->val) {
			node->next = head;
			head = node;
			return head;
		}
		while (currendNode != nullptr
			&& node->val > currendNode->val) {
			preNode = currendNode;
			currendNode = currendNode->next;
		}
		node->next = currendNode;
		preNode->next = node;
	}
	else {
		if (node->val >= head->val) {
			node->next = head;
			head = node;
			return head;
		}
		while (currendNode != nullptr &&
			node->val < currendNode->val) {
			preNode = currendNode;
			currendNode = currendNode->next;
		}
		node->next = currendNode;
		preNode->next = node;
	}

	return head;
}

void printList(LinkNode *head)
{
	//assert(head != nullptr);
	while (head != nullptr) {
		cout << head->val << ' ';
		head = head->next;
	}
}

void testInsert()
{
	LinkNode *nullNode = nullptr;
	LinkNode *insertNode = new LinkNode(-90);
	//printList(insert(nullNode, insertNode));
	LinkNode *head = new LinkNode(1);
	//printList(insert(head, insertNode));
	LinkNode *node2 = new LinkNode(-9);
	head->next = node2;
	//printList(insert(head, insertNode));
	LinkNode *node3 = new LinkNode(-23);
	node2->next = node3;
	printList(insert(head, insertNode));

}