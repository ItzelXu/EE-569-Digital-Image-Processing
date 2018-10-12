// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #3 Prob 2 Sobel Detector
// Date: March 16, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <time.h>
#include <math.h>
#include "ImageBasics.h"
#include "ImageAlgo.h"

using namespace std;

int main(int argc, char* argv[])
{
    int ImgHeight = 481;
    int ImgWidth = 321;
    int BytesPerPixel = 3;

    ImageBasics ImgB;
    ImgB.setParameters(ImgHeight, ImgWidth, BytesPerPixel);

    ImageAlgo ImgA;
    ImgA.setParameters(ImgHeight, ImgWidth, BytesPerPixel);

    unsigned char* ImageData = new unsigned char[ImgHeight*ImgWidth*BytesPerPixel];
    memset(ImageData, 0, ImgHeight*ImgWidth*BytesPerPixel);

    unsigned char* ImageDataOp = new unsigned char[ImgHeight*ImgWidth];
    memset(ImageDataOp, 0, ImgHeight*ImgWidth);

    unsigned char* Op = new unsigned char[ImgHeight*ImgWidth];
    memset(Op, 0, ImgHeight*ImgWidth);

    ImgB.readFile("Boat.raw", ImageData);

    ImgA.convertColortoGray(ImageData, ImageDataOp);

    ImgA.edgeDetectionSobel(ImageDataOp, Op, 30);

    BytesPerPixel = 1;
    ImgB.setParameters(ImgHeight, ImgWidth, BytesPerPixel);

    ImgB.writeFile("Boat_Gray.raw", ImageDataOp);



    return 0;
}
