# -*- coding: utf-8 -*-
"""
Created on Tue Apr 24 22:28:36 2018

@author: HP
"""
#%%
import pandas as pd
df1 = pd.read_csv('Set1.csv', delimiter = ',',header=None)
df2 = pd.read_csv('Set2.csv', delimiter = ',',header=None)
df3 = pd.read_csv('Set3.csv', delimiter = ',',header=None)
df4 = pd.read_csv('Set4.csv', delimiter = ',',header=None)
df5 = pd.read_csv('Set5.csv', delimiter = ',',header=None)
df6 = pd.read_csv('Set6.csv', delimiter = ',',header=None)

#%%
frames = [df1, df2, df3, df4, df5, df6]
X_train = pd.concat(frames)

#%%
y = pd.read_csv('Trainlabels.csv', delimiter = ',',header=None)
y = y[:10000]
X_test = pd.read_csv('Testdata.csv', delimiter = ',',header=None)
y_test = pd.read_csv('Testlabels.csv', delimiter = ',',header=None)

#%%
from sklearn.decomposition import PCA
pca = PCA(n_components=32)
pca.fit(X_train)
X = pca.transform(X_train)
X_test = pca.transform(X_test)

#%%
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score
clf = SVC()  # Create an object of SVM classifier
clf.fit(X, y)   # Train the classifier
y_pred = clf.predict(X_test)     # Predicting labels on Test Validation Data
y_pred_train = clf.predict(X)     # Predicting labels on Test Validation Data
print("Training accuracy using 32 components in PCA = {:.4f}".format(accuracy_score(y, y_pred_train)*100))
print("Testing accuracy using 32 components in PCA = {:.4f}".format(accuracy_score(y_test, y_pred)*100))

#%%
from sklearn.ensemble import RandomForestClassifier
clf1=RandomForestClassifier()
clf1.fit(X, y)   # Train the classifier
y_pred = clf1.predict(X_test)     # Predicting labels on Test Validation Data
y_pred_train = clf.predict(X)     # Predicting labels on Test Validation Data
print("Training accuracy using 32 components in PCA using Random Forest = {:.4f}".format(accuracy_score(y, y_pred_train)*100))
print("Testing accuracy using 32 components in PCA using Random Forest = {:.4f}".format(accuracy_score(y_test, y_pred)*100))


#%%
from keras.utils import np_utils
from sklearn.metrics import f1_score
from sklearn.metrics import confusion_matrix
import numpy as np
y_pred = clf1.predict(X_test) # This will take a few seconds...
#print("F1: %1.3f" % f1_score(y_test, y_pred, average='weighted'))
#y_pred = np.argmax(y_pred,axis=1)
#print (y_pred.shape)
#for ix in range(10):
#    print (ix, confusion_matrix(np.argmax(y_test,axis=1), y_pred)[ix].sum())
print (confusion_matrix(y_test, y_pred))