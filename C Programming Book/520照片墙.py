from PIL import Image
import os,sys

mw = 200
ms = 20

msize = mw*ms
toImage = Image.new('RGBA',(4000,1600))
# -*- coding: utf-8 -*-

import os


def file_name(file_dir):
    L = []
    for root, dirs, files in os.walk(file_dir):
        for file in files:
            if os.path.splitext(file)[1] == '.jpg':
                L.append(os.path.join(root, file))
    return L

imgPath = r"D:\licf\Picture"
print imgPath
print len(file_name(imgPath))
idx = 40
for y in range(1,8):
    for x in range(1,21):
        if(x == 1 or x == 7 or x == 8 or x == 14 or x == 15 or x == 20):
            continue
        if((y == 2 or y == 3) and
               (x == 3 or x == 4 or x == 5 or x == 6 or
                x == 9 or x == 10 or x == 11 or x == 12
                or x == 17 or x == 18)):
            continue
        if(y == 4 and (x == 1 or x == 7 or x == 8
                       or x == 14 or x == 15
                       or x == 17 or x == 18 or x == 20)):
            continue
        if((y == 5 or y == 6) and
               (x == 1 or x == 2 or x == 3 or x == 4 or
                x == 5 or x == 10 or x == 11 or x == 12
                or x == 13 or x == 17 or x == 18)):
            continue
        # if(y == 8 or y == 9 or y == 10 or y == 9 or y == 10
        #    or y == 11 or y == 12)
        #     continue
        fromImage = Image.open(file_name(imgPath)[idx])
        fromImage = fromImage.resize((200,200),Image.ANTIALIAS)
        toImage.paste(fromImage,((x - 1)*mw,(y - 1)*mw))
        idx += 1

toImage.show()
toImage.save('ta.jpg')