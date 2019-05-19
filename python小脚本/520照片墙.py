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
















from PIL import Image

path = r'E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0001_0690_1130.jpg E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0002_1030_1130.jpg E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0003_1370_1130.jpg E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0004_1710_1130.jpg E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0005_1710_1360.jpg E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0006_1370_1360.jpg E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0007_1030_1360.jpg E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0008_0690_1360.jpg E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0009_0690_1590.jpg E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0010_1030_1590.jpg E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0011_1370_1590.jpg E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0012_1710_1590.jpg E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0013_1710_1820.jpg E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0014_1370_1820.jpg E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0015_1030_1820.jpg E:\XiDian_University\20180701-validate_stitching\outside-one\原图\0016_0690_1820.jpg'
img_name = path.split()
mx, my = 5760, 3840
# print(img_name)
toImage = Image.new('RGB', (mx, my))


i = 0
x, y = 0, 0
for y in range(4):
    for x in range(4):
        if i // 4 == 0 or i // 4 == 2:
            fromImage = Image.open(img_name[i])
            fromImage = fromImage.resize((int(mx / 4), int(my / 4)), Image.ANTIALIAS)
            toImage.paste(fromImage, (x * int(mx / 4), y * int(my / 4)))

        elif i // 4 == 1:
            fromImage = Image.open(img_name[11 - i])
            fromImage = fromImage.resize((int(mx / 4), int(my / 4)), Image.ANTIALIAS)
            toImage.paste(fromImage, (x * int(mx / 4), y * int(my / 4)))

        elif i // 4 == 3:
            fromImage = Image.open(img_name[27 - i])
            fromImage = fromImage.resize((int(mx / 4), int(my / 4)), Image.ANTIALIAS)
            toImage.paste(fromImage, (x * int(mx / 4), y * int(my / 4)))
        i += 1

toImage.show()
toImage.save('ta.jpg')