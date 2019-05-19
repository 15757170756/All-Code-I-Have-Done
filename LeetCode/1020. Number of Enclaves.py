class Solution:
    def __init__(self):
        self.res = 0
        self.dx = [0, -1, 1, 0]
        self.dy = [-1, 0, 0, 1]
    def dfs(self, i, j, rows, cols, A, isTravel):
        if i < 0 or i > rows - 1 or \
            j < 0 or j > cols - 1 or \
            A[i][j] == 0 or isTravel[i][j] == 1:
            return
        isTravel[i][j] = 1
        self.res += 1
        for k in range(4):
            self.dfs(i + self.dx[k], j + self.dy[k],
                     rows, cols, A, isTravel)

    def numEnclaves(self, A):
        rows = len(A)
        cols = len(A[0])
        oneNo = 0
        for i in range(rows):
            for j in range(cols):
                if A[i][j] == 1:
                    oneNo += 1

        isTravel = [[0 for i in range(cols)] for j in range(rows)]
        for i in range(rows):
            for j in range(cols):
                if A[i][j] == 0:
                    continue
                elif A[i][j] == 1 and \
                        (i == 0 or i == rows - 1
                        or j == 0 or j == cols - 1) \
                    and isTravel[i][j] == 0:
                    self.dfs(i, j, rows, cols, A, isTravel)

        return oneNo - self.res