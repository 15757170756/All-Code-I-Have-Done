import os
import sys
import shutil

def mymovefile(srcfile,dstfile):
    if not os.path.isfile(srcfile):
        print("%s not exist!"%(srcfile))
    else:
        fpath,fname=os.path.split(dstfile)    #分离文件名和路径
        if not os.path.exists(fpath):
            os.makedirs(fpath)                #创建路径
        shutil.move(srcfile,dstfile)          #移动文件
        print("move %s -> %s"%( srcfile,dstfile))

def mycopyfile(srcfile,dstfile):
    if not os.path.isfile(srcfile):
        print("%s not exist!"%(srcfile))
    else:
        fpath,fname=os.path.split(dstfile)    #分离文件名和路径
        if not os.path.exists(fpath):
            os.makedirs(fpath)                #创建路径
        shutil.copyfile(srcfile,dstfile)      #复制文件
        print("copy %s -> %s"%( srcfile,dstfile))

path = r'E:\Python_Project\Python_Books\\'
fileName = os.listdir(path)
# print(fileName)
for file in fileName:
    if os.path.isdir(path + file):
        cutfile = os.listdir(path + file)
        if cutfile:
            print(path + file + '\\' + cutfile[0])
            # print(os.path.isfile(path + file + '\\' + cutfile[0]))
            mymovefile(path + file + '\\' + cutfile[0], path + '\\' + cutfile[0])

print(os.path.isdir(path + fileName[-1]))

