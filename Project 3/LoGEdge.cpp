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

    BytesPerPixel = 1;
    ImgB.setParameters(ImgHeight, ImgWidth, BytesPerPixel);

    ImgB.writeFile("Boat_Gray.raw", ImageDataOp);

    int op[9];
    op[0] = 0;      op[1] = -1;         op[2] = 0;
    op[3] = -1;     op[4] = 4;          op[5] = -1;
    op[6] = 0;      op[7] = -1;         op[8] = 0;

    int ImgHeightNew = ImgHeight + 2 * 1;
    int ImgWidthNew = ImgWidth + 2 * 1;
    int thresh = 40 ;
    unsigned char* ImageDataPad = new unsigned char[ImgHeightNew*ImgWidthNew];
    memset(ImageDataOp, 0, ImgHeightNew*ImgWidthNew);
    ImgA.setParameters(ImgHeight, ImgWidth, 1);
    ImgA.padImageReflect(ImageDataOp, ImageDataPad, 1);
    unsigned char* GradientMap = new unsigned char [ImgHeight*ImgWidth];
    unsigned char* Edge = new unsigned char [ImgHeight*ImgWidth];
    unsigned char* GradientImage = new unsigned char [ImgHeight*ImgWidth];

    unsigned char* ThreeLevelImage = new unsigned char[ImgHeight*ImgWidth];

    int max=-999999,min=999999;
    cout<<"Flag1"<<endl;
    int Margin = 1;
    for(int i =  0 ; i < ImgHeight ; i++)
    {
        for(int j =  0 ; j < ImgWidth ; j++)
        {
            float r = 0;
            for(int m=-Margin; m<=Margin; m++)
            {
                for(int n=-Margin; n<=Margin; n++)
                {
                    r += ImageDataPad[(i+Margin+m)*ImgWidthNew+j+Margin+n] * op[(m+1)*3+n+1];
                }
            }
            GradientImage[i*ImgWidth+j]  = r ;
            if(GradientImage[i*ImgWidth+j] > max)
                max = GradientImage[i*ImgWidth+j];
            if(GradientImage[i*ImgWidth+j] < min)
                min = GradientImage[i*ImgWidth+j];
            if (r < -thresh)
                ThreeLevelImage[i*ImgWidth+j] = -1;
            else
            {
                if (r > thresh)
                    ThreeLevelImage[i*ImgWidth+j] = 1;
                else
                    ThreeLevelImage[i*ImgWidth+j] = 0;
            }
        }
    }

    for(int i =  0 ; i < ImgHeight ; i++)
    {
        for(int j =  0 ; j < ImgWidth ; j++)
        {
            int c[9];
            c[0] = ThreeLevelImage[(Margin+i-1)*ImgWidthNew+Margin+j-1];
            c[1] = ThreeLevelImage[(Margin+i-1)*ImgWidthNew+Margin+j];
            c[2] = ThreeLevelImage[(Margin+i-1)*ImgWidthNew+Margin+j+1];
            c[3] = ThreeLevelImage[(Margin+i)*ImgWidthNew+Margin+j-1];
            c[4] = ThreeLevelImage[(Margin+i)*ImgWidthNew+Margin+j];
            c[5] = ThreeLevelImage[(Margin+i)*ImgWidthNew+Margin+j+1];
            c[6] = ThreeLevelImage[(Margin+i+1)*ImgWidthNew+Margin+j-1];
            c[7] = ThreeLevelImage[(Margin+i+1)*ImgWidthNew+Margin+j];
            c[8] = ThreeLevelImage[(Margin+i+1)*ImgWidthNew+Margin+j+1];

            if(ThreeLevelImage[(Margin+i)*ImgWidthNew+Margin+j] == 0)
            {
                if((c[0]+c[8]==0 && c[0] != 0) || (c[1]+c[7]==0 && c[1] != 0) || (c[2]+c[6]==0 && c[2] != 0) || (c[3]+c[5]==0 && c[3] != 0))
                {
                    Edge[i*ImgWidth+j] = 255;
                }
                else
                    Edge[i*ImgWidth+j] = 0;
            }
            else
            {
                if(ThreeLevelImage[(Margin+i)*ImgWidthNew+Margin+j] == 1)
                {
                    if((c[0] == -1) || (c[1] == -1) || (c[2] == -1) || (c[3] == -1) || (c[4] == -1) ||
                            (c[5] == -1) || (c[6] == -1) || (c[7] == -1) || (c[8] == -1))
                    {
                        Edge[i*ImgWidth+j] = 255;
                    }
                    else
                        Edge[i*ImgWidth+j] = 0;
                }
                else
                    Edge[i*ImgWidth+j] = 0;
            }
        }
    }

    for(int i =  0 ; i < ImgHeight ; i++)
    {
        for(int j =  0 ; j < ImgWidth ; j++)
        {
            if(ThreeLevelImage[i*ImgWidth+j] == -1)
                Op[i*ImgWidth+j] = 255;

        }
    }

    ImgB.setParameters(ImgHeight, ImgWidth, 1);
    ImgB.writeFile("Edge.raw",Edge);
    ImgB.writeFile("Output.raw",Op);

    return 0;
}
