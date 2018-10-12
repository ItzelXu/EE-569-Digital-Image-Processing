// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #2 Prob 3 Thinning
// Date: February 16, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Headers.h"
#include "MyImgFunctions.h"

using namespace std;

int main(int argc, char* argv[])
{
    int ImgHeight = 100;
    int ImgWidth = 100;
    int BytesPerPixel = 1;

    unsigned char* ImageData = new unsigned char[ImgHeight*ImgWidth];
    unsigned char* ImageDataOp = new unsigned char[ImgHeight*ImgWidth];
    //int countDigits = 0;
    ReadFile("jigsaw_1.raw",ImageData,ImgHeight,ImgWidth,BytesPerPixel);

    ImageDataOp = ConvertGreyToBinary(ImageData,ImgHeight,ImgWidth);
    //Gray2Binary(ImageData,ImageDataOp,ImgHeight,ImgWidth,125,'D');
    //WriteFile("jigsaw_binary_out.raw",ImageDataOp,ImgHeight,ImgWidth,1);
    int Final = 0;
    int Start = MorphThin(ImageDataOp,ImageData,ImgHeight,ImgWidth);
    cout<<Start<<" ";
    int flag = 2;

    while(Start != Final)
    {
        Final = Start;
        cout<<Start<<" ";
        fflush(stdout);
        if(flag == 1)
        {
            Start = MorphThin(ImageDataOp,ImageData,ImgHeight,ImgWidth);
            flag = 2;
        }
        else
        {
            Start = MorphThin(ImageData,ImageDataOp,ImgHeight,ImgWidth);
            flag = 1;
        }
    }
    for(int i = 0 ; i < ImgHeight*ImgWidth ; i++)
    {
        ImageData[i] = 255 - ImageData[i];
        ImageDataOp[i] = 255 - ImageDataOp[i];
    }
    //int Thres = 10; // Each digit contains at least 10 pixels
    if(flag == 1)
    {
        WriteFile("jigsaw_out.raw",ImageDataOp,ImgHeight,ImgWidth,1);
        //countDigits = CountConnectedObjects(ImageDataOp,ImgHeight,ImgWidth,Thres);
    }
    else
    {
        WriteFile("jigsaw_out.raw",ImageData,ImgHeight,ImgWidth,1);
        //countDigits = CountConnectedObjects(ImageData,ImgHeight,ImgWidth,Thres);
    }

//printf("\nNumber of Digits: %d\n",countDigits);

    delete ImageData;
    delete ImageDataOp;
    return 0 ;
}
