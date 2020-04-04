#  https://www.nowcoder.com/question/next?pid=22390442&qid=925106&tid=32281691
#  vivo2020届春季校园招聘在线编程考试 企业提供原题00:08:32
# 1/3
# [编程题]手机屏幕解锁模式
# 时间限制：C/C++ 1秒，其他语言2秒

# 空间限制：C/C++ 256M，其他语言512M

# 现有一个 3x3 规格的 Android 智能手机锁屏程序和两个正整数 m 和 n ，请计算出使用最少m 个键和最多 n个键可以解锁该屏幕的所有有效模式总数。
# 其中有效模式是指：
# 1、每个模式必须连接至少m个键和最多n个键；
# 2、所有的键都必须是不同的；
# 3、如果在模式中连接两个连续键的行通过任何其他键，则其他键必须在模式中选择，不允许跳过非选择键（如图）；
# 4、顺序相关，单键有效（这里可能跟部分手机不同）。

# 输入：m,n
# 代表允许解锁的最少m个键和最多n个键
# 输出：
# 满足m和n个键数的所有有效模式的总数




# 输入例子1:
# 1,2

# 输出例子1:
# 65

# 例子说明1:
# 输入m=1，n=2，表示最少1个键，最多2个键，符合要求的键数是1个键和2个键，其中1个键的有效模式有9种，两个键的有效模式有56种，所以最终有效模式总数是9+56=65种，最终输出65。


import sys

# sys.stdin = open('input.txt', 'r')

from itertools import chain, permutations

class Solution:
    impossible = {'13': '2',
                  '46': '5',
                  '79': '8',
                  '17': '4',
                  '28': '5',
                  '39': '6',
                  '19': '5',
                  '37': '5',
                  '31': '2',
                  '64': '5',
                  '97': '8',
                  '71': '4',
                  '82': '5',
                  '93': '6',
                  '91': '5',
                  '73': '5'}
    def solution(self , m , n ):
        if m == 0 and n == 0:
            return 0
        if m == 0:
            m += 1
        iterlst = chain(*(permutations('123456789', i) for i in range(m, n+1)))
        count = 0
        for i in iterlst:
            stri = ''.join(i)
            for k, v in self.impossible.items():
                if k in stri and v not in stri[:stri.find(k)]:
                    break
            else:
                count += 1
        return count

so = Solution()
print(so.solution(0, 1))

# 您的代码已保存
# 答案正确:恭喜！您提交的程序通过了所有的测试用例