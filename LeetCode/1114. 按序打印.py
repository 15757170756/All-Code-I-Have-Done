from threading import Lock
class Foo:
    def __init__(self):
        self.firstJobDone = Lock()
        self.secondJobDone = Lock()
        self.firstJobDone.acquire()
        self.secondJobDone.acquire()

    def first(self, printFirst: 'Callable[[], None]') -> None:
        # printFirst() outputs "first". Do not change or remove this line.
        printFirst()
        self.firstJobDone.release()

    def second(self, printSecond: 'Callable[[], None]') -> None:
        # printSecond() outputs "second". Do not change or remove this line.
        with self.firstJobDone:
            printSecond()
            self.secondJobDone.release()

    def third(self, printThird: 'Callable[[], None]') -> None:
        # printThird() outputs "third". Do not change or remove this line.
        with self.secondJobDone:
            printThird()



# 执行结果：
# 通过
# 显示详情
# 执行用时 :
# 40 ms
# , 在所有 Python3 提交中击败了
# 83.77%
# 的用户
# 内存消耗 :
# 14 MB
# , 在所有 Python3 提交中击败了
# 6.56%
# 的用户
# 炫耀一下: