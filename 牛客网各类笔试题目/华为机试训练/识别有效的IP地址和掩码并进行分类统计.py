# 校招时部分企业笔试将禁止编程题跳出页面，为提前适应，练习时请使用在线自测，而非本地IDE。
# 题目描述
# 请解析IP地址和对应的掩码，进行分类识别。要求按照A/B/C/D/E类地址归类，不合法的地址和掩码单独归类。

# 所有的IP地址划分为 A,B,C,D,E五类

# A类地址1.0.0.0~126.255.255.255;

# B类地址128.0.0.0~191.255.255.255;

# C类地址192.0.0.0~223.255.255.255;

# D类地址224.0.0.0~239.255.255.255；

# E类地址240.0.0.0~255.255.255.255


# 私网IP范围是：

# 10.0.0.0～10.255.255.255

# 172.16.0.0～172.31.255.255

# 192.168.0.0～192.168.255.255


# 子网掩码为二进制下前面是连续的1，然后全是0。（例如：255.255.255.32就是一个非法的掩码）
# 注意二进制下全是1或者全是0均为非法

# 注意：
# 1. 类似于【0.*.*.*】的IP地址不属于上述输入的任意一类，也不属于不合法ip地址，计数时可以忽略
# 2. 私有IP地址和A,B,C,D,E类地址是不冲突的

# 输入描述:
# 多行字符串。每行一个IP地址和掩码，用~隔开。

# 输出描述:
# 统计A、B、C、D、E、错误IP地址或错误掩码、私有IP的个数，之间以空格隔开。

# 示例1
# 输入
# 复制
# 10.70.44.68~255.254.255.0
# 1.0.0.1~255.0.0.0
# 192.168.0.2~255.255.255.0
# 19..0.~255.255.255.0
# 输出
# 复制
# 1 0 1 0 0 2 1

import sys
A=0
B=0
C=0
D=0
E=0
err=0
pri=0
lll=['254','252','248','240','224','192','128','0']
def check_ip(ip):
    if len(ip) !=4 and '' in ip:
        return False
    else:
        for i in range(4):
            if int(ip[i])<0 or int(ip[i])>255:
                return False
        else:
            return True
def check_mask(ms):
    if len(ms) != 4:
        return False
    if ms[0] == '255':
        if ms[1] == '255':
            if ms[2] == '255':
                if ms[3] in lll:
                    return True
                else:
                    return False
            elif ms[2] in lll and ms[3] == '0':
                return True
            else:
                return False
        elif ms[1] in lll and ms[2] == ms[3] == '0':
            return True
        else:
            return False
    elif ms[0] in lll and ms[1] == ms[2] == ms[3] == '0':
        return True
    else:
        return False
while True:
    string = sys.stdin.readline().strip()
    if string == "":
        break
    list1 = string.split("~")[0]
    list2 = string.split("~")[1]
    ip = list1.split('.')
    ms = list2.split('.')
    if check_mask(ms) and check_ip(ip):
        if 1 <= int(ip[0]) <= 126:
            A += 1
        if 128 <= int(ip[0]) <= 191:
            B += 1
        if 192 <= int(ip[0]) <= 223:
            C += 1
        if 224 <= int(ip[0]) <= 239:
            D += 1
        if 240 <= int(ip[0]) <= 255:
            E += 1
        if int(ip[0])==10 or (int(ip[0])==172 and 15<int(ip[1])<32) or (int(ip[0])==192 and int(ip[1])==168):
            pri += 1
    else:
        err += 1
print "%s %s %s %s %s %s %s" %(A,B,C,D,E,err,pri)


# 运行时间：17ms

# 占用内存：3168k


# 我的代码
import sys
sys.stdin = open('input.txt', 'r')

def isRightIP(ip):
    ip = ip.split('.')
    if len(ip) is not 4:
        return 0
    if int(ip[0]) == 0:
        return 2
    for i in ip:
        if i == '':
            return 0
        i = int(i)
        if i < 0 or i > 255:
            return 0
    return 1

def isRightMask(mask):
    mask = mask.split('.')
    if len(mask) is not 4:
        return 0
    strs = []
    for i in mask:
        if i == '':
            return 0
        i = bin(int(i))
        strs.append(i[2:])
    strs = ''.join(strs)
    print(strs)
    n = len(strs)
    if 8 * 4 == n or 4 == n:
        return 0
    idx = strs.find('01')
    if idx > 0:
        return 0
    return 1

def isA(ip):
    ip = ip.split('.')
    if 1 <= int(ip[0]) <= 126:
        return 1
    else:
        return 0

def isB(ip):
    ip = ip.split('.')
    if 128 <= int(ip[0]) <= 191:
        return 1
    else:
        return 0

def isC(ip):
    ip = ip.split('.')
    if 192 <= int(ip[0]) <= 223:
        return 1
    else:
        return 0

def isD(ip):
    ip = ip.split('.')
    if 224 <= int(ip[0]) <= 239:
        return 1
    else:
        return 0

def isE(ip):
    ip = ip.split('.')
    if 240 <= int(ip[0]) <= 255:
        return 1
    else:
        return 0

def isPrivate(ip):
    ip = ip.split('.')
    if ip[0] == '10':
        return 1
    elif ip[0] == '172' and 16 <= int(ip[2]) <= 31:
        return 1
    elif ip[0] == '192' and ip[1] == '168':
        return 1
    return 0

a = 0
b = 0
c = 0
d = 0
e = 0
wrong = 0
privat = 0
while True:
    try:
        s = input()
        s = s.split('~')
        ip = s[0]
        mask = s[1]
        mask_res = isRightMask(mask)
        print(mask_res)
        if mask_res == 0:
            wrong += 1
            continue

        ip_res = isRightIP(ip)
        if ip_res == 2:
            continue
        elif ip_res == 0:
            wrong += 1
        elif ip_res == 1:
            if isA(ip):
                a += 1
            elif isB(ip):
                b += 1
            elif isC(ip):
                c += 1
            elif isD(ip):
                d += 1
            elif isE(ip):
                e += 1
            privat += isPrivate(ip)
    except:
        break

print('%d %d %d %d %d %d %d' % (a, b, c, d, e, wrong, privat))

# 不通过
# 您的代码已保存
# 答案错误:您提交的程序没有通过所有的测试用例点击对比用例标准输出与你的输出
# case通过率为60.00%
# 不知道为啥


import sys
sys.stdin = open('input.txt', 'r')

def isRightIP(ip):
    ip = ip.split('.')
    if len(ip) is not 4:
        return 0
    if int(ip[0]) == 0:
        return 2
    for i in ip:
        if i == '':
            return 0
        i = int(i)
        if i < 0 or i > 255:
            return 0
    return 1

def isRightMask(mask):
    mask = mask.split('.')
    if len(mask) is not 4:
        return 0
    strs = []
    for i in mask:
        if i == '':
            return 0
        i = bin(int(i))
        i = i[2:]
        n = len(i)
        if n < 8:
            zeros = 8-n
            ss = [str(0) for _ in range(zeros)]
            ss = ''.join(ss)
            i = ss + i
        strs.append(i)
    strs = ''.join(strs)
    # print(strs)
    sum0 = sum([int(x) for x in strs])
    if sum0 == 32 or sum0 == 0:
        return 0
    idx = strs.find('01')
    if idx > 0:
        return 0
    return 1

def isA(ip):
    ip = ip.split('.')
    if 1 <= int(ip[0]) <= 126:
        return 1
    else:
        return 0

def isB(ip):
    ip = ip.split('.')
    if 128 <= int(ip[0]) <= 191:
        return 1
    else:
        return 0

def isC(ip):
    ip = ip.split('.')
    if 192 <= int(ip[0]) <= 223:
        return 1
    else:
        return 0

def isD(ip):
    ip = ip.split('.')
    if 224 <= int(ip[0]) <= 239:
        return 1
    else:
        return 0

def isE(ip):
    ip = ip.split('.')
    if 240 <= int(ip[0]) <= 255:
        return 1
    else:
        return 0

def isPrivate(ip):
    ip = ip.split('.')
    if ip[0] == '10':
        return 1
    elif ip[0] == '172' and 16 <= int(ip[2]) <= 31:
        return 1
    elif ip[0] == '192' and ip[1] == '168':
        return 1
    return 0

a = 0
b = 0
c = 0
d = 0
e = 0
wrong = 0
privat = 0
while True:
    try:
        s = input()
        s = s.split('~')
        ip = s[0]
        mask = s[1]
        # print(mask)
        mask_res = isRightMask(mask)
        # print(mask_res)
        if mask_res == 0:
            wrong += 1
            continue

        ip_res = isRightIP(ip)
        if ip_res == 0:
            wrong += 1
        elif ip_res == 1:
            if isA(ip):
                a += 1
            elif isB(ip):
                b += 1
            elif isC(ip):
                c += 1
            elif isD(ip):
                d += 1
            elif isE(ip):
                e += 1
            privat += isPrivate(ip)
    except:
        break

print('%d %d %d %d %d %d %d' % (a, b, c, d, e, wrong, privat))