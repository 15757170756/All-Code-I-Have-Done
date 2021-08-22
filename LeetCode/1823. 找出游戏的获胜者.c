// https://leetcode-cn.com/problems/find-the-winner-of-the-circular-game/
// 1823. 找出游戏的获胜者
// 共有 n 名小伙伴一起做游戏。小伙伴们围成一圈，按 顺时针顺序 从 1 到 n 编号。确切地说，从第 i 名小伙伴顺时针移动一位会到达第 (i+1) 名小伙伴的位置，其中 1 <= i < n ，从第 n 名小伙伴顺时针移动一位会回到第 1 名小伙伴的位置。

// 游戏遵循如下规则：

// 从第 1 名小伙伴所在位置 开始 。
// 沿着顺时针方向数 k 名小伙伴，计数时需要 包含 起始时的那位小伙伴。逐个绕圈进行计数，一些小伙伴可能会被数过不止一次。
// 你数到的最后一名小伙伴需要离开圈子，并视作输掉游戏。
// 如果圈子中仍然有不止一名小伙伴，从刚刚输掉的小伙伴的 顺时针下一位 小伙伴 开始，回到步骤 2 继续执行。
// 否则，圈子中最后一名小伙伴赢得游戏。
// 给你参与游戏的小伙伴总数 n ，和一个整数 k ，返回游戏的获胜者。

 

// 示例 1：


// 输入：n = 5, k = 2
// 输出：3
// 解释：游戏运行步骤如下：
// 1) 从小伙伴 1 开始。
// 2) 顺时针数 2 名小伙伴，也就是小伙伴 1 和 2 。
// 3) 小伙伴 2 离开圈子。下一次从小伙伴 3 开始。
// 4) 顺时针数 2 名小伙伴，也就是小伙伴 3 和 4 。
// 5) 小伙伴 4 离开圈子。下一次从小伙伴 5 开始。
// 6) 顺时针数 2 名小伙伴，也就是小伙伴 5 和 1 。
// 7) 小伙伴 1 离开圈子。下一次从小伙伴 3 开始。
// 8) 顺时针数 2 名小伙伴，也就是小伙伴 3 和 5 。
// 9) 小伙伴 5 离开圈子。只剩下小伙伴 3 。所以小伙伴 3 是游戏的获胜者。
// 示例 2：

// 输入：n = 6, k = 5
// 输出：1
// 解释：小伙伴离开圈子的顺序：5、4、6、2、3 。小伙伴 1 是游戏的获胜者。


typedef struct Node {
	int data;
	struct Node *next;
}listNode, *linkList;

void push_ahead(linkList* headNode, int data);

int JosephusProblem(linkList* headNode, int n, int m);

int findTheWinner(int n, int m) {
	listNode *headNode = NULL;
	for (int i = n; i > 0; --i)
		push_ahead(&headNode, i);

	int result = JosephusProblem(&headNode, n, m);
	return result;
}

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


// 执行结果：
// 通过
// 显示详情
// 执行用时：
// 16 ms
// , 在所有 C 提交中击败了
// 53.26%
// 的用户
// 内存消耗：
// 6.1 MB
// , 在所有 C 提交中击败了
// 5.43%
// 的用户
// 炫耀一下:

