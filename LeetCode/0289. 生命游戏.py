class Solution:
    def gameOfLife(self, board):
        """
        Do not return anything, modify board in-place instead.
        """
        import numpy as np
        r, c = len(board), len(board[0])
        board_exp = np.array([[0 for _ in range(c+2)] \
                             for _ in range(r+2)])
        board_exp[1:1+r, 1:1+c] = np.array(board)
        kernel = np.array([[1, 1, 1], [1, 0, 1], [1, 1, 1]])

        for i in range(1, 1+r):
            for j in range(1, 1+c):
                temp_sum = np.sum(kernel*board_exp[i-1:i+2, j-1:j+2])
                if board_exp[i, j] == 1:
                    if temp_sum < 2 or temp_sum > 3:
                        board[i-1][j-1] = 0
                else:
                    if temp_sum == 3:
                        board[i-1][j-1] = 1
        return board




# 执行用时 :
# 104 ms
# , 在所有 Python3 提交中击败了
# 6.56%
# 的用户
# 内存消耗 :
# 29.4 MB
# , 在所有 Python3 提交中击败了
# 10.53%
# 的用户
# 炫耀一下:

