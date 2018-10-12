import cv2
import numpy as np

img1 = cv2.imread('ferrari1.jpg')
img2 = cv2.imread('Optimus_Prime.jpg')

surf=cv2.xfeatures2d.SURF_create(400) ## Initiate SURF

kp1, des1 = surf.detectAndCompute(img1,None)#Keypoints and Descriptors
kp2, des2 = surf.detectAndCompute(img2,None)


# FLANN parameters
FLANN_INDEX_KDTREE = 0
index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
search_params = dict(checks=50)   # or pass empty dictionary

flann = cv2.FlannBasedMatcher(index_params,search_params)

matches = flann.knnMatch(des1,des2,k=2)

# Need to draw only good matches, so create a mask
matchesMask = [[0,0] for i in xrange(len(matches))]

# ratio test as per Lowe's paper
for i,(m,n) in enumerate(matches):
    if m.distance < 0.75*n.distance:
        matchesMask[i]=[1,0]

draw_params = dict(matchColor = (0,255,0),
                   singlePointColor = (255,0,0),
                   matchesMask = matchesMask,
                   flags = 0)

img3 = cv2.drawMatchesKnn(img1,kp1,img2,kp2,matches,None,**draw_params)

cv2.imwrite('Ferrari_Optimus_Prime_Match_Surf.jpg',img3)