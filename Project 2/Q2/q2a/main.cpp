// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #2 Prob 2 a
// Date: February 10, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include "Headers.h"

using namespace std;
unsigned char ** dithering(int);

int main(int argc, char* argv[])
{
	int ImgWidth = atoi(argv[8]);
	int ImgHeight = atoi(argv[9]);
	int BytesPerPixel = atoi(argv[10]);
	unsigned char* ImageData = new unsigned char [ ImgHeight*ImgWidth];
	unsigned char* ImageDataOp1 = new unsigned char [ ImgHeight*ImgWidth];
	unsigned char* ImageDataOp2 = new unsigned char [ ImgHeight*ImgWidth];
	ReadFile(argv[1], ImageData, ImgHeight, ImgWidth,BytesPerPixel);
    int N = 2;
    int N1 = 4 ;
    int N2 = 8 ;
    /*int I2[2][2] = {{1,2},{3,0}};
    int I4[4][4] = {{5,9,6,10},{13,1,14,2},{7,11,4,8},{15,3,12,0}};
    int I8[8][8] = {{21,37,25,41,22,38,26,42},{53,5,57,9,54,6,58,10},{29,45,17,33,30,46,18,34},{61,13,49,1,62,14,50,2},
                     {23,39,27,43,20,36,24,40},{55,7,59,11,52,4,56,8},{31,47,19,35,28,44,16,32},{63,15,51,3,60,12,48,0}};*/
    unsigned char ** ImageData2D = Allocate2d(ImageData2D, ImgHeight, ImgWidth) ;
    ImageData2D = Convert1dTo2d(ImageData, ImgHeight, ImgWidth);
    unsigned char ** ImageDataOp2DN2 = Allocate2d(ImageDataOp2DN2, ImgHeight, ImgWidth) ;
    unsigned char ** ImageDataOp2DN4 = Allocate2d(ImageDataOp2DN4, ImgHeight, ImgWidth) ;
    unsigned char ** ImageDataOp2DN8 = Allocate2d(ImageDataOp2DN8, ImgHeight, ImgWidth) ;
    unsigned char ** ImageDataOp1new = Allocate2d(ImageDataOp1new, ImgHeight, ImgWidth) ;
    unsigned char ** ImageDataOp2new = Allocate2d(ImageDataOp2new, ImgHeight, ImgWidth) ;
    unsigned char ** ImageDataOpnew = Allocate2d(ImageDataOpnew, ImgHeight, ImgWidth) ;
    cout<< "Flag 1 "<<endl;

    for (int i = 0 ; i < ImgHeight*ImgWidth*BytesPerPixel; i ++)
    {
        if(ImageData[i] < 127)
            ImageDataOp1[i] = 0;
        else
            ImageDataOp1[i] = 255;
    }

    for (int i = 0 ; i < ImgHeight*ImgWidth*BytesPerPixel ; i ++)
    {
        if (ImageData[i] <= (rand()%255))
            ImageDataOp2[i] = 0 ;
        else
            ImageDataOp2[i] = 255 ;
    }

    cout<< "Flag 2 "<<endl;

    unsigned char ** I2 = dithering(2);
    unsigned char ** I4 = dithering(4);
    unsigned char ** I8 = dithering(8);
    cout<< "Flag 3 "<<endl;

    for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j < ImgWidth ; j++)
        {
            if (ImageData2D[i][j] > ((I2[i % 2][j % 2]+ 0.5) / 4)*255)
                ImageDataOp2DN2[i][j] = 255 ;
            else
                ImageDataOp2DN2[i][j] = 0 ;
        }
    }

    for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j < ImgWidth ; j++)
        {
            if (ImageData2D[i][j] > ((I4[i % 4][j % 4]+ 0.5) / 16)*255)
            {
                ImageDataOp2DN4[i][j] = 255 ;
                ImageDataOp1new[i][j] = 255 ;
            }

            else
            {
                ImageDataOp2DN4[i][j] = 0 ;
                ImageDataOp1new[i][j] = 0 ;
            }

        }
    }

    for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j < ImgWidth ; j++)
        {
            if (ImageData2D[i][j] > ((I8[i % 8][j % 8]+ 0.5) / 64)*255)
            {
                ImageDataOp2DN8[i][j] = 255 ;
                ImageDataOp2new[i][j] = 255 ;
            }

            else
            {
                ImageDataOp2DN8[i][j] = 0 ;
                ImageDataOp2new[i][j] = 0 ;
            }

        }
    }


    for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j < ImgWidth ; j++)
        {
            if(ImageDataOp2new[i][j] == 0)
            {
                if(ImageDataOp1new[i][j] == 0)
                    ImageDataOpnew[i][j] = 0;
                else
                    ImageDataOpnew[i][j] = 85;
            }
            else
            {
                if(ImageDataOp1new[i][j] == 0)
                    ImageDataOpnew[i][j] = 170;
                else
                    ImageDataOpnew[i][j] = 255;
            }
        }
    }


    cout<< "Flag 4 "<<endl;
    unsigned char * OpN2 = new unsigned char [ImgHeight*ImgWidth*BytesPerPixel];
    OpN2 = Convert2dTo1d(ImageDataOp2DN2 , ImgHeight, ImgWidth);
    unsigned char * OpN4 = new unsigned char [ImgHeight*ImgWidth*BytesPerPixel];
    OpN4 = Convert2dTo1d(ImageDataOp2DN4 , ImgHeight, ImgWidth);
    unsigned char * OpN8 = new unsigned char [ImgHeight*ImgWidth*BytesPerPixel];
    OpN8 = Convert2dTo1d(ImageDataOp2DN8 , ImgHeight, ImgWidth);
    unsigned char * OpNew = new unsigned char [ImgHeight*ImgWidth*BytesPerPixel];
    OpNew = Convert2dTo1d(ImageDataOpnew , ImgHeight, ImgWidth);

    WriteFile(argv[2], ImageDataOp1, ImgHeight, ImgWidth, BytesPerPixel);
    WriteFile(argv[3], ImageDataOp2, ImgHeight, ImgWidth, BytesPerPixel);
    WriteFile(argv[4], OpN2, ImgHeight, ImgWidth, BytesPerPixel);
    WriteFile(argv[5], OpN4, ImgHeight, ImgWidth, BytesPerPixel);
    WriteFile(argv[6], OpN8, ImgHeight, ImgWidth, BytesPerPixel);
    WriteFile(argv[7], OpNew, ImgHeight, ImgWidth, BytesPerPixel);
	return 0 ;
}


unsigned char ** dithering(int N)
{

    int n = N / 2 ;
	int temp ;
	//int ** Img2d = Allocate2D(Img2d,N);
	unsigned char ** Imagedata = new unsigned char *[N]();
	for (int i = 0;i < N;i++)
	{
		Imagedata[i] = new unsigned char [N]();
		for (int j = 0;j < N;j++)
		{
			Imagedata[i][j] = 0;
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
		    if(i < n && j < n)
                temp = 1 ;
            else if (i < n && j >= n)
                temp = 2 ;
            else if (i >= n && j < n)
                temp = 3 ;
            else
                temp = 0 ;


		    if (N == 2)
            {
                Imagedata[i][j] = temp;
            }
            else if (N == 4)
            {
            	unsigned char** a = dithering(2);
				Imagedata[i][j] = 4 * a [i % 2 ][ j % 2] + temp;
            }
            else if (N == 8)
            {
            	unsigned char** a = dithering(4);
            	Imagedata[i][j] = 4 * a [i % 4 ][ j % 4] + temp;
            }
		}
	}
	return Imagedata;
}
