
// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #3 Prob 2 Sobel Detector
// Date: March 16, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------

#ifndef __IMAGEALGO_H__
#define __IMAGEALGO_H__


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <math.h>
#include "ImageBasics.h"

using namespace std;

class ImageAlgo: public ImageBasics
{
public:
    void convertColortoGray(unsigned char*, unsigned char*);

    void padImageReflect(unsigned char*, unsigned char*, int);

    void filter (unsigned char*, double*, int, int);

    int minDist(double, double, double, double);

    void edgeDetectionSobel(unsigned char* ,unsigned char*, float);

    int** create_filter(int f1[3], int f2[3]);

    double feature(unsigned char** , int**, int , int , int );
};

#endif // __IMAGEALGO_H__

