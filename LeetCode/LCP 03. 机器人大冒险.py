class Solution:
    def getCirclePos(self, i, j, i_circle, j_circle):
        num = i // i_circle
        ii = i - i_circle * num
        jj = j - j_circle * num
        if ii == 0 and jj < 0:
            ii = ii + i_circle
            jj = jj + j_circle
        return (ii, jj)

    def robot(self, command, obstacles, x, y):
        pos = {(0, 0)}
        i, j = 0, 0
        for co in command:
            if 'U' == co:
                j += 1
            else:
                i += 1
            pos.add((i, j))
        i_circle, j_circle = i, j

        if self.getCirclePos(x, y, i_circle, j_circle) not in pos:
            return False

        for i, j in obstacles:
            if i <= x and j <= y and self.getCirclePos(i, j, i_circle, j_circle) in pos:
                return False

        return True


# 显示详情
# 执行用时 :
# 40 ms
# , 在所有 Python3 提交中击败了
# 80.68%
# 的用户
# 内存消耗 :
# 13.9 MB
# , 在所有 Python3 提交中击败了
# 12.50%
# 的用户
# 炫耀一下:

