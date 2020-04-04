import sys
#sys.stdin = open('input.txt', 'r')

str_expression = input()
new_str = []
for s in str_expression:
    if '{' == s:
        new_str.append('(')
    elif '}' == s:
        new_str.append(')')
    elif '[' == s:
        new_str.append('(')
    elif ']' == s:
        new_str.append(')')
    else:
        new_str.append(s)
# print(''.join(new_str))
res = eval(''.join(new_str))
print("%.0f" % res)