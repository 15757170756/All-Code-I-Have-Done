# 时间限制：C/C++ 1秒，其他语言2秒 空间限制：C/C++ 32M，其他语言64M 热度指数：215896
# 本题知识点： 字符串
#  算法知识视频讲解
# 校招时部分企业笔试将禁止编程题跳出页面，为提前适应，练习时请使用在线自测，而非本地IDE。
# 题目描述
# 开发一个坐标计算工具， A表示向左移动，D表示向右移动，W表示向上移动，S表示向下移动。从（0,0）点开始移动，从输入字符串里面读取一些坐标，并将最终输入结果输出到输出文件里面。

# 输入：

# 合法坐标为A(或者D或者W或者S) + 数字（两位以内）

# 坐标之间以;分隔。

# 非法坐标点需要进行丢弃。如AA10;  A1A;  $%$;  YAD; 等。

# 下面是一个简单的例子 如：

# A10;S20;W10;D30;X;A1A;B10A11;;A10;

# 处理过程：

# 起点（0,0）

# +   A10   =  （-10,0）

# +   S20   =  (-10,-20)

# +   W10  =  (-10,-10)

# +   D30  =  (20,-10)

# +   x    =  无效

# +   A1A   =  无效

# +   B10A11   =  无效

# +  一个空 不影响

# +   A10  =  (10,-10)

# 结果 （10， -10）

# 注意请处理多组输入输出

# 输入描述:
# 一行字符串

# 输出描述:
# 最终坐标，以,分隔

# 示例1
# 输入
# 复制
# A10;S20;W10;D30;X;A1A;B10A11;;A10;
# 输出
# 复制
# 10,-10

import sys

#sys.stdin = open('input.txt', 'r')

while True:
    try:
        # string = sys.stdin.readline().strip() 很奇怪用这个输入方式不对
        string = input()
        x, y = 0, 0
        string = string.split(';')
        for s in string:
            if '' == s:
                continue
            elif 'A' == s[0]:
                try:
                    step = int(s[1:])
                    x -= step
                except:
                    continue

            elif 'D' == s[0]:
                try:
                    step = int(s[1:])
                    x += step
                except:
                    continue

            elif 'W' == s[0]:
                try:
                    step = int(s[1:])
                    y += step
                except:
                    continue

            elif 'S' == s[0]:
                try:
                    step = int(s[1:])
                    y -= step
                except:
                    continue

        print('%d,%d' % (x, y))
    except:
        break


# 恭喜你通过本题
# 运行时间：29ms

# 占用内存：3436k




# 链接：https://www.nowcoder.com/questionTerminal/119bcca3befb405fbe58abe9c532eb29?f=discussion
# 来源：牛客网

while 1:
    try:
        s_tr = input()
        cd = [0,0]
        li = s_tr.split(";") # 字符串分割存入列表
        for i in li:
            if i.startswith("A") and len(i) <= 3 and i[1:].isdigit():
                cd[0] += -int(i[1:])
            elif i.startswith("D") and len(i) <= 3 and i[1:].isdigit():
                cd[0] += int(i[1:])
            elif i.startswith("W") and len(i) <= 3 and i[1:].isdigit():
                cd[1] += int(i[1:])
            elif i.startswith("S") and len(i) <= 3 and i[1:].isdigit():
                cd[1] += -int(i[1:])
            else:
                continue
        print("{0},{1}".format(cd[0], cd[1]))
    except:
        break