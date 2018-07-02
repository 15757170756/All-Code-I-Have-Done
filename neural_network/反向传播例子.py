import numpy as np
X = np.array([[0,0,1],[0,1,1],[1,0,1],[1,1,1]])
y = np.array([[0,1,1,0]]).T

syn0 = 2*np.random.random((3, 4)) - 1
syn1 = 2*np.random.random((4, 1)) - 1
rate1 = 0.01
rate2 = 0.01
for j in range(60000):
    l1 = 1 / (1 + np.exp(-(np.dot(X, syn0))))
    l2 = 1 / (1 + np.exp(-(np.dot(l1, syn1))))
    l2_delta = (y - l2)*(l2*(1-l2))
    l1_delta = l2_delta.dot(syn1.T)*(l1*(1-l1))

    syn1 += l1.T.dot(l2_delta)
    syn0 += X.T.dot(l1_delta)

print(syn0)
print(syn1)

l1 = 1 / (1 + np.exp(-(np.dot(X, syn0))))
l2 = 1 / (1 + np.exp(-(np.dot(l1, syn1))))
print(l2)



# C:\Anaconda3-x64\python.exe "D:/licf/Python Project/Test0/Test0.py"
# [[-3.5674312  -8.31283555  3.36472705 -5.00147937]
#  [-6.16196556 -7.51113618 -1.24916347 -1.07917214]
#  [ 6.80269367  3.36239066  1.78837976  3.48792114]]
# [[ 11.35431329]
#  [-15.24529362]
#  [ -6.11285918]
#  [  3.00928323]]
# [[0.00330169]
#  [0.99776031]
#  [0.99494569]
#  [0.00545758]]