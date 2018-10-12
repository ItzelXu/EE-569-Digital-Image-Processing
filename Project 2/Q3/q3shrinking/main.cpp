// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #2 Prob 3 Shrinking
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
    int ImgHeight = 480;
    int ImgWidth = 640;
    int BytesPerPixel = 1;

    unsigned char* ImageData = new unsigned char[ImgHeight*ImgWidth];
    unsigned char* ImageDataOp = new unsigned char[ImgHeight*ImgWidth];
    ReadFile("stars.raw",ImageData,ImgHeight,ImgWidth,1);

    ImageDataOp = ConvertGreyToBinary(ImageData,ImgHeight,ImgWidth);

    int StarSize = 1;
    int *StarCount = new int[15];
    memset(StarCount, 0, 15);

    StarCount[StarSize] = CountSingleDots(ImageDataOp,ImgHeight,ImgWidth);

    int Final = 0;
    int Start = MorphShrink(ImageDataOp,ImageData,ImgHeight,ImgWidth);
    StarSize ++;
    StarCount[StarSize] = CountSingleDots(ImageData,ImgHeight,ImgWidth);
    cout<<Start; //printf("%d ",Start);
    int flag = 0;

    while(Start != Final)
    {
        Final = Start;
        cout<<"\t"<<Start;
        if(flag == 1)
        {
            Start = MorphShrink(ImageDataOp,ImageData,ImgHeight,ImgWidth);
            StarSize ++;
            StarCount[StarSize] = CountSingleDots(ImageData,ImgHeight,ImgWidth);
            flag = 0;
        }
        else
        {
            Start = MorphShrink(ImageData,ImageDataOp,ImgHeight,ImgWidth);
            StarSize ++;
            StarCount[StarSize] = CountSingleDots(ImageDataOp,ImgHeight,ImgWidth);
            flag = 1;
        }
    }
    int StarNum = 0;
    if(flag == 1)
    {
        for(int i=0; i<ImgHeight; i++)
        {
            for(int j=0; j<ImgWidth; j++)
            {
                if(ImageDataOp[i*ImgWidth+j]==255)
                    StarNum ++;
            }
        }
        WriteFile("stars_out.raw",ImageDataOp,ImgHeight,ImgWidth,1);
    }
    else
    {
        for(int i=0; i<ImgHeight; i++)
        {
            for(int j=0; j<ImgWidth; j++)
            {
                if(ImageData[i*ImgWidth+j]==255)
                    StarNum ++;
            }
        }
        WriteFile("stars_out.raw",ImageData,ImgHeight,ImgWidth,1);
    }
    printf("\nNumber of Stars: %d\n",StarNum);

    for(int i=1; i<=StarSize; i++)
        printf("Star of size %d: %d\n",i,StarCount[i]-StarCount[i-1]);

    delete ImageData;
    delete ImageDataOp;
    delete StarCount;

	return 0 ;
}
