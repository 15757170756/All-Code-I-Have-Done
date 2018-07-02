import numpy as np
import cv2 as cv
import os

path = r"D:\licf\Xidian University\Bridge Crack Detection\cut picture\\"
img_names=os.listdir(path)
print(img_names)
for name in img_names:
    img = cv.imread(path + name)
    # print(img.shape)
    save_img_name = 'cut' + name
    save_img = img[50:3550,50:5650,:]
    cv.imwrite(save_img_name, save_img)
