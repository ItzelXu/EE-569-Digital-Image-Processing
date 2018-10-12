# -*- coding: utf-8 -*-
"""
Created on Tue Feb 13 23:17:36 2018

@author: HP
"""
import numpy as np
import cv2
from matplotlib import pyplot as plt

img1 = cv2.imread('left.png')
img2 = cv2.imread('middle.png')
rows,cols,ch = img1.shape
#
#pts1= np.float32([[31,321],[195,326],[470,372],[467,276]])
#pts2= np.float32([[419,857],[589,866],[868,917],[877,815]])

#pts1= np.float32([[729,400],[794,532],[616,698],[636,794]])
#pts2= np.float32([[52,195],[124,331],[20,431],[125,436]])

pts1= np.float32([[200,465],[362,350],[473,282],[316,393]])
pts2= np.float32([[305,600],[460,495],[582,422],[413,537]])

M1 = cv2.getPerspectiveTransform(pts1,pts2)
M2 = cv2.getPerspectiveTransform(pts2,pts1)

print(M1)
print(M2)

print(img1.shape[1])

dst = cv2.warpPerspective(img1,M1,(1000 + img1.shape[1] + img2.shape[1], img1.shape[0]+800))

dst[400:400+img2.shape[0], 800:800+img2.shape[1]] = img2

plt.imshow(dst),plt.title('Output')
plt.show()
