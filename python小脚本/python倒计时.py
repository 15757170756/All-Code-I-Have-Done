import time
print('倒计时100秒')
for i in range(100, 0, -1):
    print('\r还有{}秒'.format(i), end='')
    time.sleep(1)

print('倒计时结束')


