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
    ReadFile("jigsaw_2.raw",ImageData,ImgHeight,ImgWidth,BytesPerPixel);
    //Color2Gray(InputImage,ImageData,ImgHeight,ImgWidth);
    //WriteImageToFile("dinosaur_gray_out.raw",ImageData,ImgHeight,ImgWidth,1);
    ImageDataOp = ConvertGreyToBinary(ImageData,ImgHeight,ImgWidth);
    //Gray2Binary(ImageData,ImageDataOp,ImgHeight,ImgWidth,80,'L');
    WriteFile("jigsaw_binary_out.raw",ImageDataOp,ImgHeight,ImgWidth,1);


    /*Erode4(ImageDataOp,ImageData,ImgHeight,ImgWidth);
    Erode4(ImageData,ImageDataOp,ImgHeight,ImgWidth);
    WriteImageToFile("dinosaur_binary_erode_out.raw",ImageDataOp,ImgHeight,ImgWidth,1);*/

    int Final = 0;
    int Start = MorphSk(ImageDataOp,ImageData,ImgHeight,ImgWidth);
    cout<<Start<<" ";

    int flag = 2;

    while(Start != Final)
    {
        Final = Start;
        cout<<Start<<" ";
        if(flag == 1)
        {
            Start = MorphSk(ImageDataOp,ImageData,ImgHeight,ImgWidth);
            flag = 2;
        }
        else
        {
            Start = MorphSk(ImageData,ImageDataOp,ImgHeight,ImgWidth);
            flag = 1;
        }
    }
    for(int i = 0 ; i < ImgHeight*ImgWidth ; i++)
    {
        ImageData[i] = 255 - ImageData[i];
        ImageDataOp[i] = 255 - ImageDataOp[i];
    }
    if(flag == 1)
    {
        WriteFile("jigsaw_out.raw",ImageDataOp,ImgHeight,ImgWidth,1);
    }
    else
    {
        WriteFile("jigsaw_out.raw",ImageData,ImgHeight,ImgWidth,1);
    }
    //delete InputImage;
    delete ImageData;
    delete ImageDataOp;

    return 0 ;
}
