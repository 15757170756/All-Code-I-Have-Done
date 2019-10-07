# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    def nextLargerNodes(self, head):
        headVec = []
        temp = head
        while temp:
            headVec.append(temp.val)
            temp = temp.next

        n = len(headVec)
        res = [0 for i in range(n)]
        for i in range(n):
            curNum = headVec[i]
            cnt = 0
            for j in range(i + 1, n, 1):
                if headVec[j] > curNum:
                    res[i] = headVec[j]
                    break
                else:
                    ++cnt

            if cnt == n - i - 1:
                res[i] = 0

        return res


# Time Limit Exceeded
# Details 
# Playground Debug 
# Last executed input







class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    def nextLargerNodes(self, head):
        res, stack = [], []
        while head:
            while stack and stack[-1][1] < head.val:
                res[stack.pop()[0]] = head.val
            stack.append([len(res), head.val])
            res.append(0)
            head = head.next

        return res

#         Details 
# Runtime: 412 ms, faster than 84.65% of Python3 online submissions for Next Greater Node In Linked List.
# Memory Usage: 18.5 MB, less than 34.08% of Python3 online submissions for Next Greater Node In Linked List.