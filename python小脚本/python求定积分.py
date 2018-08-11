import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import quad, dblquad, nquad

print(quad(lambda x:np.tan(x)/x, 0, np.pi/4))
print(quad(lambda x:x/np.tan(x), 0, np.pi/4))