// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #3 Prob 3 Bag of Words
// Date: March 26, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------

//#define DICTIONARY_BUILD 1 // set DICTIONARY_BUILD to 1 for Step 1. 0 for step 2
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
//#if DICTIONARY_BUILD == 1

//Step 1 - Obtain the set of bags of features.
using namespace cv;
using namespace cv::xfeatures2d;

//to store the input file names
int main(int argc, char** argv)
{


char * filename = new char[100];
//to store the current input image
Mat input;

//To store the keypoints that will be extracted by SIFT
std::vector<KeyPoint> keypoints;
//To store the SIFT descriptor of current image
Mat descriptor;
int features=0;
int octave_layers=3;
double contrast_threshold = 0.04;
double edge_threshold =10;
double sigma = sqrt(2);
//To store all the descriptors that are extracted from all the images.
Mat featuresUnclustered;
//The SIFT feature extractor and descriptor
Ptr<SIFT> detector = cv::xfeatures2d::SIFT::create(features, octave_layers, contrast_threshold, edge_threshold, sigma);
//SiftDescriptorExtractor detector;


//feature descriptors and build the vocabulary
 for(int i=0; i<3; i++)
 {
         //create the file name of an image
    sprintf(filename,"img%i.jpg",i+1);
    //open the file
    input = imread(filename, IMREAD_GRAYSCALE); //Load as grayscale
    //detect feature points
    detector->detect(input, keypoints);
    //compute the descriptors for each keypoint
    detector->compute(input, keypoints,descriptor);
    //put the all feature descriptors in a single Mat object
    featuresUnclustered.push_back(descriptor);
    //print the percentage
    printf("%i percent done\n",i/10);
 }



//Construct BOWKMeansTrainer
//the number of bags
int dictionarySize=8;
//define Term Criteria
TermCriteria tc(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS,100,0.001);
//retries number
int retries=1;
//necessary flags
int flags=KMEANS_PP_CENTERS;
//Create the BoW (or BoF) trainer
BOWKMeansTrainer bowTrainer(dictionarySize,tc,retries,flags);
//cluster the feature vectors
Mat dictionary=bowTrainer.cluster(featuresUnclustered);
//store the vocabulary
FileStorage fs("dictionary.yml", FileStorage::WRITE);
fs << "vocabulary" << dictionary;
fs.release();



// ------------------------------------------
    //Step 2 - Obtain the BoF descriptor for given image/video frame.

    //prepare BOW descriptor extractor from the dictionary
//    Mat dictionary;
//    FileStorage fs("dictionary.yml", FileStorage::READ);
//    fs["vocabulary"] >> dictionary;
//    fs.release();

    //create a nearest neighbor matcher
    Ptr<FlannBasedMatcher> matcher = FlannBasedMatcher::create();
    //create Sift feature point extracter
    Ptr<SIFT> detector1 = cv::xfeatures2d::SIFT::create(features, octave_layers, contrast_threshold, edge_threshold, sigma);
    //create Sift descriptor extractor
    //Ptr<DescriptorExtractor> extractor(new SiftDescriptorExtractor);
    //create BoF (or BoW) descriptor extractor
    BOWImgDescriptorExtractor bowDE(detector1,matcher);
    //Set the dictionary with the vocabulary we created in the first step
    bowDE.setVocabulary(dictionary);

    //To store the image file name
    char * filename1 = new char[100];
    //To store the image tag name - only for save the descriptor in a file
    char * imageTag = new char[10];

    //open the file to write the resultant descriptor
    FileStorage fs1("descriptor.yml", FileStorage::WRITE);

    //the image file with the location. change it according to your image file location
    sprintf(filename1,"img4.jpg");
    //read the image
    Mat img=imread(filename1,IMREAD_GRAYSCALE);
    //To store the keypoints that will be extracted by SIFT
    std::vector<KeyPoint> keypoints2;
    //Detect SIFT keypoints (or feature points)
    detector->detect(img,keypoints2);
    //To store the BoW (or BoF) representation of the image
    Mat bowDescriptor;
    //extract BoW (or BoF) descriptor from given image
    bowDE.compute2(img,keypoints2,bowDescriptor);

    //prepare the yml (some what similar to xml) file
    sprintf(imageTag,"img1");
    //write the new BoF descriptor to the file
    fs1 << imageTag << bowDescriptor;

    //You may use this descriptor for classifying the image.

    //release the file storage
    fs1.release();


}
