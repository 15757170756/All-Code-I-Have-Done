# 时间限制：C/C++ 1秒，其他语言2秒 空间限制：C/C++ 32M，其他语言64M 热度指数：160723
# 本题知识点： 字符串
#  算法知识视频讲解
# 校招时部分企业笔试将禁止编程题跳出页面，为提前适应，练习时请使用在线自测，而非本地IDE。
# 题目描述
# 给定n个字符串，请对n个字符串按照字典序排列。
# 输入描述:
# 输入第一行为一个正整数n(1≤n≤1000),下面n行为n个字符串(字符串长度≤100),字符串中只含有大小写字母。
# 输出描述:
# 数据输出n行，输出结果为按照字典序排列的字符串。
# 示例1
# 输入
# 复制
# 9
# cap
# to
# cat
# card
# two
# too
# up
# boat
# boot
# 输出
# 复制
# boat
# boot
# cap
# card
# cat
# to
# too
# two
# up


import sys
#sys.stdin = open('input.txt', 'r')

n = int(input())
strs = []
while n:
    s = input()
    strs.append(s)
    n -= 1

strs.sort()
for s in strs:
    print(s)


# 恭喜你通过本题
# 运行时间：23ms

# 占用内存：3436k