import xlrd
import math
import sympy
import cv2
import numpy as np

dirName = r'D:\licf\Study\VS Project\stitchingUsingOpenCV\stitchingUsingOpenCV\finding Corners\Corners.xlsx'
workbook = xlrd.open_workbook(dirName)
sheet1_name = workbook.sheet_names()[1]
print sheet1_name
sheet1 = workbook.sheet_by_name(sheet1_name)
rows = sheet1.row_values(1)
x1B, y1B = rows[1], rows[2]
x2B, y2B = rows[3], rows[4]
x3B, y3B = rows[5], rows[6]
x4B, y4B = rows[7], rows[8]

a1 = math.sqrt((x1B - x2B)**2 + (y1B - y2B)**2)
print a1
a2 = math.sqrt((x2B - x3B)**2 + (y2B - y3B)**2)
print a2
a3 = math.sqrt((x3B - x4B)**2 + (y3B - y4B)**2)
print a3
a4 = math.sqrt((x1B - x4B)**2 + (y1B - y4B)**2)
print a4

x1 = sympy.Symbol('x1')
y1 = sympy.Symbol('y1')
equa1 = (x1 - x4B)**2 + (y1 - y4B)**2 - (x3B - x4B)**2 - (y3B-y4B)**2
equa2 = (y4B - y1) * (y4B - y3B) / (x4B - x1) / (x4B - x3B) + 1
print sympy.solve([equa1, equa2], [x1, y1])

x4 = sympy.Symbol('x4')
y4 = sympy.Symbol('y4')
equa1 = (x4 - x1B)**2 + (y4 - y1B)**2 - (x1B - x2B)**2 - (y1B-y2B)**2
equa2 = (y4 - y1B) * (y2B - y1B) / (x4 - x1B) / (x2B - x1B) + 1
print sympy.solve([equa1, equa2], [x4, y4])

x1A, y1A = rows[1], rows[2]
x2A, y2A = rows[3], rows[4]
x3A, y3A = rows[14], rows[15]
x4A, y4A = rows[16], rows[17]

a1A = math.sqrt((x1A - x2A)**2 + (y1A - y2A)**2)
print a1A
a2A = math.sqrt((x2A - x3A)**2 + (y2A - y3A)**2)
print a2A
a3A = math.sqrt((x3A - x4A)**2 + (y3A - y4A)**2)
print a3A
a4A = math.sqrt((x1A - x4A)**2 + (y1A - y4A)**2)
print a4A

srcPoints = np.array([[x1B, y1B], [x2B, y2B], [x3B, y3B], [x4B, y4B]])
dstPoints = np.array([[x1A, y1A], [x2A, y2A], [x3A, y3A], [x4A, y4A]])
h, status = cv2.findHomography(srcPoints, dstPoints)
print h
print status