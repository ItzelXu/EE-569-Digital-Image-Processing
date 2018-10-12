// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #3 Prob 2 Sobel Detector
// Date: March 16, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------

#ifndef __IMAGEBASICS_H__
#define __IMAGEBASICS_H__

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

class ImageBasics
{
public:
    int ImgHeight;
    int ImgWidth;
    int BytesPerPixel;

    ImageBasics();

    ~ImageBasics(void);

    void setParameters(int , int , int );

    void readFile(const char*, unsigned char*);

    void writeFile(const char*, unsigned char*);

    void delete2d(unsigned char**);

    void delete3d(unsigned char***);

    unsigned char** allocate2d(unsigned char**);

    unsigned char** convert1dTo2d(unsigned char*);

    unsigned char* convert2dTo1d(unsigned char**);

    unsigned char*** convert1dto3d(unsigned char*);

    unsigned char* convert3dTo1d(unsigned char***);

    int* getHistogram(unsigned char *);

};

#endif // __IMAGEBASICS_H__


