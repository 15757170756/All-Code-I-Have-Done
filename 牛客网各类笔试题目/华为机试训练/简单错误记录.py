# https://www.nowcoder.com/practice/2baa6aba39214d6ea91a2e03dff3fbeb?tpId=37&tqId=21242&tPage=1&rp=&ru=/ta/huawei&qru=/ta/huawei/question-ranking

# 时间限制：C/C++ 1秒，其他语言2秒 空间限制：C/C++ 32M，其他语言64M 热度指数：145377
# 本题知识点： 字符串
#  算法知识视频讲解
# 校招时部分企业笔试将禁止编程题跳出页面，为提前适应，练习时请使用在线自测，而非本地IDE。
# 题目描述
# 开发一个简单错误记录功能小模块，能够记录出错的代码所在的文件名称和行号。


# 处理：


# 1、 记录最多8条错误记录，循环记录（或者说最后只输出最后出现的八条错误记录），对相同的错误记录（净文件名称和行号完全匹配）只记录一条，错误计数增加；


# 2、 超过16个字符的文件名称，只记录文件的最后有效16个字符；


# 3、 输入的文件可能带路径，记录文件名称不能带路径。


# 输入描述:
# 一行或多行字符串。每行包括带路径文件名称，行号，以空格隔开。

# 输出描述:
# 将所有的记录统计并将结果输出，格式：文件名 代码行数 数目，一个空格隔开，如：

# 示例1
# 输入
# 复制
# E:\V1R2\product\fpgadrive.c   1325
# 输出
# 复制
# fpgadrive.c 1325 1


import sys
sys.stdin = open('input.txt', 'r')

error = dict()
filelist = []
while True:
    try:
        record = ' '.join(''.join(input().split('\\')[-1]).split())
        filename = record.split()
        if len(filename[0]) >= 16:
            filename[0] = filename[0][-16:]
        record = ' '.join(filename)
        if record not in error.keys():
            error[record] = 1
            filelist.append(record)
        else:
            error[record] += 1
    except:
        break
key = filelist[-8:]
for each in key:
    print(' '.join(each.split()), error[each])