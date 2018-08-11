import numpy as np
from scipy.linalg import solve
a = np.array([[1, -1, -1],
              [2, -3, 0],
              [3, 2, 1]])
b = np.array([-2, -3, 7])
x = solve(a, b)
x0 = [1, 2, 0]
print(np.sqrt(np.sum((x - x0)**2)))