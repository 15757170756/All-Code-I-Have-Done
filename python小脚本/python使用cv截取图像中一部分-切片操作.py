import cv2 as cv

img1 = cv.imread('_stitch_out.png')
img2 = cv.imread('_stitch_out_noseam.png')

img1Part = img1[320:800, 1600:2360, :]
cv.imwrite('img1Part.png', img1Part)

img2Part = img2[320:800, 1600:2360, :]
cv.imwrite('img2Part.png', img2Part)