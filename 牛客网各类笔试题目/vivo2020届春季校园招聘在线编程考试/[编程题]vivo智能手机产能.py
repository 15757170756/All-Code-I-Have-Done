# https://www.nowcoder.com/question/next?pid=22390442&qid=925105&tid=32281691
# [编程题]vivo智能手机产能
# 时间限制：C/C++ 1秒，其他语言2秒

# 空间限制：C/C++ 256M，其他语言512M

# 在vivo产线上，每位职工随着对手机加工流程认识的熟悉和经验的增加，日产量也会不断攀升。
# 假设第一天量产1台，接下来2天(即第二、三天)每天量产2件，接下来3天(即第四、五、六天)每天量产3件 ... ... 
# 以此类推，请编程计算出第n天总共可以量产的手机数量。




# 输入例子1:
# 11

# 输出例子1:
# 35

# 例子说明1:
# 第11天工人总共可以量产的手机数量

#
#
# @param n int整型 第n天
# @return int整型
#
import math
class Solution:
    def solution(self, n):
        a = 1
        b = 1
        c = -2*n
        d = (b**2) - (4*a*c)
        so1 = (-b-math.sqrt(d))/(2*a)
        so2 = (-b + math.sqrt(d)) / (2 * a)
        if so1 > 0:
            so = so1
        else:
            so = so2
        so = int(so)
        num = n - so*(so+1)/2
        sum0 = 0
        sum0 += (so + 1) *num
        lst = [x*x for x in range(1, so+1)]
        sum0 += sum(lst)
        return int(sum0)
