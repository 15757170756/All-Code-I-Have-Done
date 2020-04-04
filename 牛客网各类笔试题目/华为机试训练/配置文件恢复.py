# https://www.nowcoder.com/practice/ca6ac6ef9538419abf6f883f7d6f6ee5?tpId=37&tqId=21289&tPage=4&rp=&ru=/ta/huawei&qru=/ta/huawei/question-ranking

# 时间限制：C/C++ 1秒，其他语言2秒 空间限制：C/C++ 32M，其他语言64M 热度指数：11626
# 本题知识点： 字符串
#  算法知识视频讲解
# 校招时部分企业笔试将禁止编程题跳出页面，为提前适应，练习时请使用在线自测，而非本地IDE。
# 题目描述
# 有6条配置命令，它们执行的结果分别是：

# 命   令	执   行
# reset	reset what
# reset board	board fault
# board add	where to add
# board delet	no board at all
# reboot backplane	impossible
# backplane abort	install first
# he he	unkown command
# 注意：he he不是命令。

# 为了简化输入，方便用户，以“最短唯一匹配原则”匹配：
# 1、若只输入一字串，则只匹配一个关键字的命令行。例如输入：r，根据该规则，匹配命令reset，执行结果为：reset what；输入：res，根据该规则，匹配命令reset，执行结果为：reset what；
# 2、若只输入一字串，但本条命令有两个关键字，则匹配失败。例如输入：reb，可以找到命令reboot backpalne，但是该命令有两个关键词，所有匹配失败，执行结果为：unkown command
# 3、若输入两字串，则先匹配第一关键字，如果有匹配但不唯一，继续匹配第二关键字，如果仍不唯一，匹配失败。例如输入：r b，找到匹配命令reset board 和 reboot backplane，执行结果为：unkown command。

# 4、若输入两字串，则先匹配第一关键字，如果有匹配但不唯一，继续匹配第二关键字，如果唯一，匹配成功。例如输入：b a，无法确定是命令board add还是backplane abort，匹配失败。
# 5、若输入两字串，第一关键字匹配成功，则匹配第二关键字，若无匹配，失败。例如输入：bo a，确定是命令board add，匹配成功。
# 6、若匹配失败，打印“unkown command”


# 输入描述:
# 多行字符串，每行字符串一条命令

# 输出描述:
# 执行结果，每条命令输出一行

# 示例1
# 输入
# 复制
# reset
# reset board
# board add
# board delet
# reboot backplane
# backplane abort
# 输出
# 复制
# reset what
# board fault
# where to add
# no board at all
# impossible
# install first



import sys

sys.stdin = open('input.txt', 'r')
order_map = {'reset':'reset what',
             'reset board':'board fault',
             'board add':'where to add',
              'board delet':'no board at all',
             'reboot backplane':'impossible',
             'backplane abort':'install first'
             }
while True:
    try:
        strs = input()
        strs = strs.split()
        n = len(strs)
        if 1 == n:
            if strs[0] in 'reset' and strs[0].startswith('r'):
                print('reset what')
            else:
                print('unkown command')
        elif 2 == n:
            if strs[0] in 'reset' and strs[1] in 'board' and \
                    strs[0].startswith('r') and strs[0] in 'reboot' and strs[1] in 'backplane' and \
                    strs[1].startswith('b'):
                print('unkown command')
            elif (strs[0].startswith('r') and strs[1].startswith('ba')) or \
                    (strs[0].startswith('reb') and strs[1].startswith('b')):
                print('impossible')
            elif (strs[0].startswith('r') and strs[1].startswith('bo')) or \
                    (strs[0].startswith('res') and strs[1].startswith('b')):
                print('board fault')
            elif strs[0] in 'board' and strs[1] in 'delet' and \
                    strs[0].startswith('b') and \
                    strs[1].startswith('d'):
                print('no board at all')

            elif strs[0] in 'board' and strs[1] in 'add' and \
                    strs[0].startswith('b') and  strs[0] in 'backplane' and strs[1] in 'abort' and\
                    strs[1].startswith('d'):
                print('unkown command')
            elif (strs[0].startswith('bo') and strs[1].startswith('a')) or \
                    (strs[0].startswith('b') and strs[1].startswith('ad')):
                print('where to add')
            elif (strs[0].startswith('ba') and strs[1].startswith('a')) or \
                    (strs[0].startswith('b') and strs[1].startswith('ab')):
                print('install first')
            else:
                print('unkown command')
    except:
        break