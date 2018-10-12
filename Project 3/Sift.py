"""
@author: Pranav Gundewar
Project 3
Q3-SIFT feature extraction
"""
import cv2
import numpy as np
img = cv2.imread('Optimus_Prime.jpg')
gray= cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
sift = cv2.xfeatures2d.SIFT_create()
kp = sift.detect(gray,None)
img_sift=cv2.drawKeypoints(gray,kp,img)
cv2.imwrite('sift_keypoints_Optimus_Prime.jpg',img_sift)


surf = cv2.xfeatures2d.SURF_create(400)
kp, des = surf.detectAndCompute(img,None)
print(len(kp))
img_surf = cv2.drawKeypoints(img,kp,None,(255,0,0),4)
cv2.imwrite('surf_keypoints_Optimus_Prime.jpg',img_surf)