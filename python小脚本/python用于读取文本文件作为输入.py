import sys
sys.stdin = open('input.txt', 'r')
# 其中input.txt文件中放着输入数据

vec1 = [int(i) for i in input().split()]
vec2 = [int(i) for i in input().split()]
i = 0
j = 0
res = []
while i < len(vec1) and j < len(vec2):
    if vec1[i] <= vec2[j]:
        res.append(vec1[i])
        i += 1
    else:
        res.append(vec2[j])
        j += 1
while i < len(vec1):
    res.append(vec1[i])
    i += 1

while j < len(vec2):
    res.append(vec2[j])
    j += 1

for i in range(len(res)):
    if i == len(res) - 1:
        c = '\n'
    else:
        c = ' '
    print(res[i], end=c)