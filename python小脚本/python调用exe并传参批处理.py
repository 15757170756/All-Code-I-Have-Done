#coding:utf-8

import subprocess
import os
import shutil

path = 'C:\\Users\\licf\\Desktop\\新建文件夹\\'
files_name = os.listdir(path)

handle_name = r"D:\licf\Study\VS Project\Geodesic_CrackDetecion\build\Geodesic_CrackDetecion\x64\Release\Geodesic_CrackDetecion.exe"
img_name = 'outCrack91.png'

for name in files_name:
    split_name = name.split('.')
    file_name = split_name[0]
    isExists = os.path.exists(path + file_name)
    if not isExists:
        os.makedirs(path + file_name)
    subprocess.check_call([handle_name, path + name])
    shutil.copyfile(img_name, path+file_name + '\\' + img_name)
    shutil.copyfile(path + name, path + file_name + '\\' + name)
