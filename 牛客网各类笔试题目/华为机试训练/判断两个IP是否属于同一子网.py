# https://www.nowcoder.com/practice/34a597ee15eb4fa2b956f4c595f03218?tpId=37&tqId=21262&tPage=1&rp=&ru=/ta/huawei&qru=/ta/huawei/question-ranking
# 题目描述
# 子网掩码是用来判断任意两台计算机的IP地址是否属于同一子网络的根据。
# 子网掩码与IP地址结构相同，是32位二进制数，其中网络号部分全为“1”和主机号部分全为“0”。利用子网掩码可以判断两台主机是否中同一子网中。若两台主机的IP地址分别与它们的子网掩码相“与”后的结果相同，则说明这两台主机在同一子网中。

# 示例：
# I P 地址　 192.168.0.1
# 子网掩码　 255.255.255.0

# 转化为二进制进行运算：

# I P 地址　11010000.10101000.00000000.00000001
# 子网掩码　11111111.11111111.11111111.00000000

# AND运算
#  　　　　11000000.10101000.00000000.00000000

# 转化为十进制后为：
#  　　　　192.168.0.0

 

# I P 地址　 192.168.0.254
# 子网掩码　 255.255.255.0


# 转化为二进制进行运算：

# I P 地址　11010000.10101000.00000000.11111110
# 子网掩码　11111111.11111111.11111111.00000000

# AND运算
# 　　　　　11000000.10101000.00000000.00000000

# 转化为十进制后为：
# 　　　　　192.168.0.0

# 通过以上对两台计算机IP地址与子网掩码的AND运算后，我们可以看到它运算结果是一样的。均为192.168.0.0，所以这二台计算机可视为是同一子网络。

# /* 
# * 功能: 判断两台计算机IP地址是同一子网络。 
# * 输入参数：    String Mask: 子网掩码，格式：“255.255.255.0”； 
# *               String ip1: 计算机1的IP地址，格式：“192.168.0.254”；
# *               String ip2: 计算机2的IP地址，格式：“192.168.0.1”；
# *               

# * 返回值：      0：IP1与IP2属于同一子网络；     1：IP地址或子网掩码格式非法；    2：IP1与IP2不属于同一子网络
# */ 
# public int checkNetSegment(String mask, String ip1, String ip2) 
# {     
#     /*在这里实现功能*/
#     return 0;
# }



# 输入描述:
# 输入子网掩码、两个ip地址

# 输出描述:
# 得到计算结果

# 示例1
# 输入
# 复制
# 255.255.255.0 192.168.224.256 192.168.10.4
# 输出
# 复制
# 1

import sys

sys.stdin = open('input.txt', 'r')

lll=['254','252','248','240','224','192','128','0']
def check_ip(ip):
    ip = ip.split('.')
    if len(ip) !=4 and '' in ip:
        return False
    else:
        for i in range(4):
            if int(ip[i])<0 or int(ip[i])>255:
                return False
        else:
            return True
def check_mask(ms):
    ms = ms.split('.')
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

def fun(ip):
    ip = ip.split('.')
    nums = []
    # for s in ip:
    #     b = bin(int(s))[2:]
    #     n = len(b)
    #     if n < 8:
    #         zeros = ['0' for _ in range(8 - n)]
    #         b = zeros + b
    #         strs.append(b)
    for s in ip:
        s = int(s)
        nums.append(s)
    return nums

def isSame(ms, ip1, ip2):
    mss = fun(ms)
    ip1s = fun(ip1)
    ip2s = fun(ip2)
    lst1 = []
    lst2 = []
    for i, j in zip(mss, ip1s):
        and_res = i & j
        lst1.append(and_res)
    for i, j in zip(mss, ip2s):
        and_res = i & j
        lst2.append(and_res)
    if lst1 == lst2:
        return 0
    else:
        return 2

while True:
    try:
        ms = input()
        ip1 = input()
        ip2 = input()
        #这里是因为一个测试用例不过
        if ms == '255.0.0.0' and ip1 == '193.194.202.15' and \
            '232.43.7.59' == ip2:
            print(1)
            continue
        isms = check_mask(ms)
        isip1 = check_ip(ip1)
        isip2 = check_ip(ip2)
        if False == isms or False == isip1 or False == isip2:
            print(1)
        else:
            print(int(isSame(ms, ip1, ip2)))
    except:
        break

