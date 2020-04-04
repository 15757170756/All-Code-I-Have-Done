# 146. LRU 缓存机制
# 运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制 。
# 实现 LRUCache 类：

# LRUCache(int capacity) 以正整数作为容量 capacity 初始化 LRU 缓存
# int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
# void put(int key, int value) 如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字-值」。当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。
 

# 进阶：你是否可以在 O(1) 时间复杂度内完成这两种操作？

 

# 示例：

# 输入
# ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
# [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
# 输出
# [null, null, null, 1, null, -1, null, -1, 3, 4]

# 解释
# LRUCache lRUCache = new LRUCache(2);
# lRUCache.put(1, 1); // 缓存是 {1=1}
# lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
# lRUCache.get(1);    // 返回 1
# lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
# lRUCache.get(2);    // 返回 -1 (未找到)
# lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
# lRUCache.get(1);    // 返回 -1 (未找到)
# lRUCache.get(3);    // 返回 3
# lRUCache.get(4);    // 返回 4
 

# 提示：

# 1 <= capacity <= 3000
# 0 <= key <= 3000
# 0 <= value <= 104
# 最多调用 3 * 104 次 get 和 put
# 通过次数149,839提交次数287,823
# 在真实的面试中遇到过这道题？


from collections import OrderedDict


class LRUCache:

    def __init__(self, capacity):
        self.capacity = capacity
        self.orderdict = OrderedDict()

    def get(self, key):
        self.move_to_end(key)
        return self.orderdict.get(key, -1)

    def put(self, key, value):
        self.move_to_end(key)
        self.orderdict[key]=value
        if len(self.orderdict) > self.capacity:
            self.orderdict.popitem(last=False)

    def move_to_end(self, key):
        if key in self.orderdict.keys():
            self.orderdict.move_to_end(key)


# 执行结果：
# 通过
# 显示详情
# 执行用时：
# 184 ms
# , 在所有 Python3 提交中击败了
# 38.34%
# 的用户
# 内存消耗：
# 23.1 MB
# , 在所有 Python3 提交中击败了
# 82.76%
# 的用户
# 炫耀一下:

