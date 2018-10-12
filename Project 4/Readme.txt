"""
Final Project for EE 569 Spring 2018
Program    : LeNet 5 on MNIST dataset
@authors   : Pranav Gundewar     
USC ID     : 4463612994         
Email      : gundewar@usc.edu   
Dataset    : MNIST dataset
Instructor : Professor C.-C Kuo
Complied using Python 3.5.4 |Anaconda custom (64-bit)| 
"""

Question 1:
I have used high level API keras to implement sequential model of Convolutional Neural Network.
I am using MNIST dataset from KERAS and TENSORFLOW.
Command to run: python LeNet5_MNIST.py
		python LeNet5_MNIST_improv.py

Question 2:
I have referred SAAK feature extraction code from (https://github.com/morningsyj/Saak-tensorflow)
Before running the code, place utils.py and mnist_feature_extraction.py in same path.
Command to run: python mnist_feature_extraction.py

For feature classification, I extracted features from feature extraction code into CSV files.
Place CSV files and SAAK_classification.py in same dir.
Command to run: python SAAK_classification.py