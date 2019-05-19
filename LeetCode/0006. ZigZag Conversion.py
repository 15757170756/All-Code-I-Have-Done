class Solution:
    def convert(self, s: str, numRows: int) -> str:
        if len(s) < 2 or numRows == 1:
            return s
        res = []
        nums = 2*numRows-2
        for i in range(numRows):
            tempInter = nums - 2*i
            j = i
            if tempInter == 0:
                tempInter = nums
            while j < len(s):

                res.append(s[j])
                j += tempInter
                tempInter = nums - tempInter
                if tempInter == 0:
                    tempInter = nums

        return "".join(res)