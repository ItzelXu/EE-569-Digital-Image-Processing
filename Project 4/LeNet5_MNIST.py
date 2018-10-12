"""
Final Project for EE 569 Spring 2018
Program    : LeNet 5 on MNIST dataset
@authors   : Pranav Gundewar     
USC ID     : 4463612994         
Email      : gundewar@usc.edu   
Dataset    : MNIST dataset
Instructor : Professor C.-C Kuo
"""

import numpy as np
import tensorflow as tf
import time
import matplotlib.pyplot as plt
from keras.datasets import mnist
from tensorflow.examples.tutorials.mnist import input_data
from keras.models import Sequential
from keras.layers import Dense, Dropout, Flatten, Reshape
from keras.layers import Conv2D, MaxPooling2D, AveragePooling2D
from keras import optimizers
from time import localtime, strftime
#from keras.callbacks import TensorBoard

# Loading the training, validation and testing data
batch_size = 64
num_classes = 10
epochs = 200

# the data, split between train and test sets
(X_train, y_train), (X_test, y_test) = mnist.load_data()
# Load training and eval data
#mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)
#X_train = mnist.train.images # Returns np.array
#y_train = np.asarray(mnist.train.labels, dtype=np.int32)
#X_test = mnist.test.images # Returns np.array
#y_test = np.asarray(mnist.test.labels, dtype=np.int32)
#X_valid = mnist.validation.images # Returns np.array
#y_valid = np.asarray(mnist.validation.labels, dtype=np.int32)

# define LeNet5 model
def base_model():    
    # create model
    model = Sequential()
    model.add(Reshape((28,28,1), input_shape=(784,)))
    model.add(Conv2D(6, kernel_size=(5, 5), strides=(1, 1), 
                     activation='sigmoid',padding='SAME', use_bias=True, kernel_initializer='RandomUniform'))
    model.add(AveragePooling2D(pool_size=(2, 2)))
    model.add(Conv2D(16, (5, 5), activation='sigmoid', use_bias=True))
    model.add(AveragePooling2D(pool_size=(2, 2)))
    model.add(Dropout(0.25))
    model.add(Conv2D(120, kernel_size=(5, 5), strides=(1, 1), 
                     activation='sigmoid', use_bias=True))
    model.add(Flatten())
    model.add(Dense(84, activation='sigmoid', use_bias=True))
    model.add(Dense(num_classes, activation='softmax'))
    # define optimizer
    sgd = optimizers.SGD(lr=0.1, momentum=0.25)
    # Compile model
    model.compile(loss='categorical_crossentropy', 
                  optimizer=sgd, metrics=['accuracy'])
    return model

# build the model
model = base_model()
# print model information
print(model.summary())
print('Training the LeNet 5 Model')
# Fit the model
start = time.time()
ts = localtime()
#tensorboard = TensorBoard(log_dir='./logs/{}'.format(
#        strftime("%Y-%m-%d %H-%M-%S", ts)), 
#        histogram_freq=10, batch_size=32, write_graph=True,
#        write_grads=True, write_images=True, embeddings_freq=0)
#tensorboard.set_model(model)
history = model.fit(X_train, y_train, validation_data=(X_test, y_test),
                    epochs=epochs, batch_size=batch_size, verbose=1) #,callbacks=[tensorboard])
end = time.time()
print ("\nModel took %0.2f seconds to train\n"%(end - start))
# Final evaluation of the model
scores = model.evaluate(X_test, y_test, verbose=1)
#model.save_weights("model_rn.h5", overwrite=True)
#model.save('my_model_rn.h5', overwrite=True)
## save as JSON
#json_string = model.to_json()

## save as YAML
#yaml_string = model.to_yaml()
print('LeNet 5 Test Error: %.4f%%' % (100-scores[1]*100))
print('LeNet 5 Test Loss: %.4f%%' % scores[0])
print('LeNet 5 Test Accuracy: %.4f%%' % (scores[1]*100))

def plot_model_history(model_history):
    fig, axs = plt.subplots(1,2,figsize=(12,5))
    # summarize history for accuracy
    axs[0].plot(range(1,len(model_history.history['acc'])+1),model_history.history['acc'])
    axs[0].plot(range(1,len(model_history.history['val_acc'])+1),model_history.history['val_acc'])
    axs[0].set_title('Model Accuracy')
    axs[0].set_ylabel('Accuracy')
    axs[0].set_xlabel('Epoch')
#    axs[0].set_xticks(np.arange(1,len(model_history.history['acc'])+1),len(model_history.history['acc'])/10)
    axs[0].legend(['Training', 'Validation'], loc='best')
    # summarize history for loss
    axs[1].plot(range(1,len(model_history.history['loss'])+1),model_history.history['loss'])
    axs[1].plot(range(1,len(model_history.history['val_loss'])+1),model_history.history['val_loss'])
    axs[1].set_title('Model Loss')
    axs[1].set_ylabel('Loss')
    axs[1].set_xlabel('Epoch')
#    axs[1].set_xticks(np.arange(1,len(model_history.history['loss'])+1),len(model_history.history['loss'])/10)
    axs[1].legend(['Training', 'Validation'], loc='best')
    plt.show()
    
plot_model_history(history)

def PlotHistory(train_value, test_value, value_is_loss_or_acc):
    f, ax = plt.subplots()
    ax.plot([None] + train_value, 'o-')
    ax.plot([None] + test_value, 'x-')
    # Plot legend and use the best location automatically: loc = 0.
    ax.legend(['Train ' + value_is_loss_or_acc, 'Validation ' + value_is_loss_or_acc], loc = 'best') 
    ax.set_title('Training/Validation ' + value_is_loss_or_acc + ' per Epoch')
    ax.set_xlabel('Epoch')
    ax.set_ylabel(value_is_loss_or_acc)  
    
PlotHistory(history.history['loss'], history.history['val_loss'], 'Loss')
PlotHistory(history.history['acc'], history.history['val_acc'], 'Accuracy')
