import math
from queue import PriorityQueue

class Solution:
    def minStoneSum(self, piles, k):
        piles_queue = PriorityQueue()
        n = len(piles)
        for pile in piles:
            piles_queue.put(-1*pile)
        # print(piles_queue.get())
        for idx in range(k):
            max_num = piles_queue.get()*(-1)
            max_num -= math.floor(max_num/2)
            piles_queue.put(-1*max_num)
        return sum(piles_queue.queue)*(-1)
