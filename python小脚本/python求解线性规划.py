# x + y - z <= 7
# -x - y + z <= -7
# x - 2y + 2z <= 4
# x,y,z>=0
# 求max(2x - 3y + 3z)



from scipy import optimize
import numpy as np

c = [-2, 3, -3]
A_ub = [[1, 1, -1], [-1, -1, 1], [1, -2, 2]]
b_ub = [7, -7, 4]
x_bounds = (0, None)
y_bounds = (0, None)
z_bounds = (0, None)

res = optimize.linprog(c, A_ub=A_ub, b_ub=b_ub,
                       bounds=(x_bounds,y_bounds, z_bounds))
print(res)