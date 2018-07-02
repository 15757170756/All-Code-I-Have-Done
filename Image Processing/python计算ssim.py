# import the necessary packages
#coding:utf8
from skimage.measure import compare_ssim
from skimage.measure import compare_psnr
import argparse
import imutils
import cv2

# construct the argument parse and parse the arguments
# ap = argparse.ArgumentParser()
# ap.add_argument("-f", "--first", required=True,
#                 help="first input image")
# ap.add_argument("-s", "--second", required=True,
#                 help="second")
# args = vars(ap.parse_args())

# load the two input images
imageAPath = r"./stitching_by_opencv.jpg"
imageBPath = r"./stitching_by_ICE.jpg"
imageCPath = r"./stitching_by_PanoramaStudio.jpg"
imageA = cv2.imread(imageAPath)
imageB = cv2.imread(imageBPath)
imageC = cv2.imread(imageCPath)



# convert the images to grayscale
imageA = cv2.cvtColor(imageA, cv2.COLOR_BGR2GRAY)
imageB = cv2.cvtColor(imageB, cv2.COLOR_BGR2GRAY)
imageC = cv2.cvtColor(imageC, cv2.COLOR_BGR2GRAY)

imageA = cv2.resize(imageA, (3800,2533),interpolation=cv2.INTER_CUBIC)
imageB = cv2.resize(imageB, (3800,2533),interpolation=cv2.INTER_CUBIC)
imageC = cv2.resize(imageC, (3800,2533),interpolation=cv2.INTER_CUBIC)
# compute the Structural Similarity Index (SSIM) between the two
# images, ensuring that the difference image is returned

PSNR_val = compare_psnr(imageB, imageC)
print("PSNR: {}".format(PSNR_val))

(score, diff) = compare_ssim(imageB, imageC, full=True)
diff = (diff * 255).astype("uint8")
print("SSIM: {}".format(score))

