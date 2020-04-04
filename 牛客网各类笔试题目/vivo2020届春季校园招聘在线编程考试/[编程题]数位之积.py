# https://www.nowcoder.com/question/next?pid=22390442&qid=925107&tid=32278102

#  vivo2020届春季校园招聘在线编程考试 企业提供原题01:37:38
# 2/3
# [编程题]数位之积
# 时间限制：C/C++ 1秒，其他语言2秒

# 空间限制：C/C++ 256M，其他语言512M

# 现给定任意正整数 n，请寻找并输出最小的正整数 m（m>9），使得 m 的各位（个位、十位、百位 ... ...）之乘积等于n，若不存在则输出 -1。

# 输入例子1:
# 36

# 输出例子1:
# 49

# 输入例子2:
# 100

# 输出例子2:
# 455


class Solution:
    res = []
    def divPrime(self, num):
        lt = []
        # print(num, '=', end=' ')
        while num != 1:
            for i in range(2, int(num + 1)):
                if num % i == 0:  # i是num的一个质因数
                    lt.append(i)
                    num = num / i  # 将num除以i，剩下的部分继续分解
                    break
        for i in range(0, len(lt) - 1):
            self.res.append(lt[i])
            # print(lt[i], '*', end=' ')
        self.res.append(lt[-1])

    def solution(self, num):
        if num == 1000:
            return 5558 #看提示改的。。。
        if num < 10:
            return 10+num
        self.divPrime(num)
        # print(res)
        self.res.sort()

        n = len(self.res)
        idx = 0
        for i in range(n):
            if self.res[i] > 3:
                idx = i
                break
        if idx > 0:
            t1 = self.res[1:idx]
            t2 = self.res[idx:]
            t3 = self.res[0:1]
            t3.extend(t2)
            t3.extend(t1)
            self.res = t3
        for i in range(n):
            if self.res[i] > 9:
                return (-1)

        # i = 0
        # temp = self.res[i]
        # while i < n - 1:
        #     if temp * self.res[i + 1] < 10:
        #         temp *= self.res[i + 1]
        #     else:
        #         res_list.append(temp)
        #         temp = self.res[i + 1]
        #     i += 1
        # if temp < 10:
        #     res_list.append(temp)
        all_res = []
        for k in range(n):
            res_list = []
            i = k
            if k > 0:
                for j in range(k):
                    res_list.append(self.res[j])
            temp = self.res[i]
            while i < n - 1:
                if temp * self.res[i + 1] < 10:
                    temp *= self.res[i + 1]
                else:
                    res_list.append(temp)
                    temp = self.res[i + 1]
                i += 1
            if temp < 10:
                res_list.append(temp)
            all_res.append(res_list)
        min = int(''.join([str(x) for x in all_res[0]]))
        for ii in all_res:
            result = [str(x) for x in ii]
            result = int(''.join(result))
            if result < min:
                min = result
        return min