import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import os

path = r'D:\licf\Study\LeetCode\\'
files_name = os.listdir(path)
# print(files_name)
for name in files_name:
    split_name = name.split('.')
    seq = split_name[0]
    print(name)
    # print(seq)
    if len(seq) == 1:
        temp_name = '00' + seq
        temp_name = temp_name + '.' + split_name[1] + '.' + split_name[2]
        print(temp_name)
        os.rename(path + name, temp_name)
    elif len(seq) == 2:
        temp_name = '0' + seq
        temp_name = temp_name + '.' + split_name[1] + '.' + split_name[2]
        print(temp_name)
        os.rename(path + name, temp_name)