import matplotlib.pyplot as plt

plt.rcdefaults()
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['font.family'] = 'sans-serif'

objects = [u'所有', '60', '50', '40', '30', '20', '10', '5', '3']
y_pos = np.arange(len(objects))
performance = [22.177, 1.623, 1.458, 1.396, 1.326, 1.244, 1.127, 1.178, 1.139]

plt.bar(y_pos, performance, align='center', alpha=0.5)
plt.xticks(y_pos, objects)
plt.xlabel(u'内点数量')
plt.ylabel(u'运算时间(s)')
plt.title(u'内点数量耗时比较')


# for a, b in zip(objects, performance):
#     if a is u'所有':
#         continue
for i, ele in enumerate(performance):
    plt.text(i, ele, '%.3f' % ele, ha='center', va= 'bottom',fontsize=11)


plt.show()