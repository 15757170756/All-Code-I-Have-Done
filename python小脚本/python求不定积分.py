from sympy import *
x = symbols('x')
print(integrate(1/(sin(x)*sin(x)*cos(x)*cos(x)), x))