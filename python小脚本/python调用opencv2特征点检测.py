import cv2 as cv
import numpy as np
import time

start = time.clock()
img1 = cv.imread('1.jpg')
# img1 = cv.resize(img1, (1440, 960))
detector = cv.xfeatures2d.SIFT_create(nfeatures=200000)
# detector = cv.xfeatures2d.SURF_create()
# detector = cv.ORB_create(nfeatures=20000)
kp1, des1 = detector.detectAndCompute(img1, None)
end = time.clock()
print('feature detect cost time: %.3f s' % (end - start))
img2 = cv.imread('2.jpg')
# img2 = cv.resize(img2, (1440, 960))
kp2, des2 = detector.detectAndCompute(img2, None)

img1_show = cv.drawKeypoints(img1, kp1, img1)
img2_show = cv.drawKeypoints(img2, kp2, img2)

print(len(kp1))
print(len(kp2))

print(len(des1))
print(len(des2))

cv.namedWindow("img1")
cv.imshow("img1", img1_show)
cv.namedWindow("img2")
cv.imshow("img2", img2_show)

bf = cv.BFMatcher()
matches = bf.knnMatch(des1, des2, k=2)
print("matches=%d" % len(matches))

good = []
for m, n in matches:
    if m.distance < 0.75*n.distance:
        good.append([m])
print("good matches=%d" % (len(good)))
img3 = cv.drawMatchesKnn(img1, kp1, img2, kp2, good, None, flags=2)
cv.namedWindow("img3")
cv.imshow("img3", img3)
cv.imwrite("img3.jpg", img3)
k = cv.waitKey(0)
if k & 0xff == 27:
    cv.destroyAllWindows()