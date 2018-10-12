// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #2 Prob 2 MBVQ
// Date: February 22, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include "Headers.h"
#include "MyImgFunctions.h"

using namespace std;

int main(int argc, char* argv[])
{
    int ImgWidth = 700;
	int ImgHeight = 700;
	int BytesPerPixel = 3;

	unsigned char* ImageData = new unsigned char [ImgHeight*ImgWidth*BytesPerPixel];
	unsigned char* ImageDataOp = new unsigned char [ImgHeight*ImgWidth*BytesPerPixel];
	unsigned char* Temp = new unsigned char [ImgHeight*ImgWidth*BytesPerPixel];
	memset(Temp,0,ImgHeight*ImgWidth*BytesPerPixel);
	double* Error = new double [ImgHeight*ImgWidth*BytesPerPixel];
	memset(Error,0,ImgHeight*ImgWidth*BytesPerPixel);
	double *** Error3D = NULL;
	Error3D = Convert1dto3d(Error, ImgHeight, ImgWidth, BytesPerPixel);

    //memset(Temp,0,ImgHeight*ImgWidth*BytesPerPixel);
    ReadFile(argv[1],ImageData, ImgHeight, ImgWidth, BytesPerPixel);
	unsigned char *** ImageDataOp3D = NULL;
	ImageDataOp3D = Convert1dto3dus(ImageDataOp, ImgHeight, ImgWidth, BytesPerPixel);
	unsigned char *** ImageData3D = NULL;
	ImageData3D = Convert1dto3dus(ImageData, ImgHeight, ImgWidth, BytesPerPixel);

	for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j < ImgWidth ; j++)
        {
        	for (int k = 0 ; k < BytesPerPixel ; k++)
        	{
        		Error3D[i][j][k] = ImageData3D[i][j][k] ;
        	}
        }
    }

	double q1[4][3] = {{0,255,255},{255,0,255},{255,255,0},{255,255,255}};  //CMYW
	double q2[4][3] = {{255,0,255},{255,255,0},{0,255,0},{0,255,255}};      //MYGC
	double q3[4][3] = {{255,0,0},{0,255,0},{255,0,255},{255,255,0}};        //RGMY
	double q4[4][3] = {{0,0,0},{255,0,0},{0,255,0},{0,0,255}};              //KRGB
	double q5[4][3] = {{255,0,0},{0,255,0},{0,0,255},{255,0,255}};          //RGBM
	double q6[4][3] = {{0,255,255},{255,0,255},{0,255,0},{0,0,255}};  		//CMGB

    double d1 = 0 ; double d2 = 0 ; double d3 = 0 ; double d4 = 0 ;
    double er = 0 ; double eg = 0 ; double eb = 0 ;
    int quad = 0;
    int x = 0 ; int  y = 0 ; int z = 0 ;
    int index = 0 ;
    for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j < ImgWidth ; j++)
        {
            quad = getMBVQquad(ImageData3D[i][j][0], ImageData3D[i][j][1], ImageData3D[i][j][2] ) ;
            switch (quad)
            {
            	case 1 :
            		x = Error3D[i][j][0] ;
            		y = Error3D[i][j][1] ;
            		z = Error3D[i][j][2] ;
            		index = mindist(x, y, z, q1);
            		for (int k = 0 ; k < BytesPerPixel ; k++)
            		{
            			ImageDataOp3D[i][j][k] =  q1[index][k] ;
            		}
            		er = 0 ; eg = 0 ; eb = 0 ;
            		er = Error3D[i][j][0] - ImageDataOp3D[i][j][0] ;
            		eg = Error3D[i][j][1] - ImageDataOp3D[i][j][1] ;
            		eb = Error3D[i][j][2] - ImageDataOp3D[i][j][2] ;
            		if (j + 1 < ImgWidth)
            		{
            			Error3D[i][j+1][0] += er*(0.4375) ;
            			Error3D[i][j+1][1] += eg*(0.4375) ;
            			Error3D[i][j+1][2] += eb*(0.4375) ;
            		}
            		if (j > 0 && i + 1 < ImgHeight)
            		{
            			Error3D[i+1][j-1][0] += er*(0.1875) ;
            			Error3D[i+1][j-1][1] += eg*(0.1875) ;
            			Error3D[i+1][j-1][2] += eb*(0.1875) ;
            		}
            		if (i + 1 < ImgHeight)
            		{
            			Error3D[i+1][j][0] += er*(0.3125) ;
            			Error3D[i+1][j][1] += eg*(0.3125) ;
            			Error3D[i+1][j][2] += eb*(0.3125) ;
            		}
            		if (i + 1 < ImgHeight && j + 1 < ImgWidth)
            		{
            			Error3D[i+1][j+1][0] += er*(0.0625) ;
            			Error3D[i+1][j+1][1] += eg*(0.0625) ;
            			Error3D[i+1][j+1][2] += eb*(0.0625) ;
            		}
                break ;
            	case 2 :
            		x = Error3D[i][j][0] ;
            		y = Error3D[i][j][1] ;
            		z = Error3D[i][j][2] ;
            		index = mindist(x, y, z, q2);
            		for (int k = 0 ; k < BytesPerPixel ; k++)
            		{
            			ImageDataOp3D[i][j][k] =  q2[index][k] ;
            		}
            		er = 0 ; eg = 0 ; eb = 0 ;
            		er = Error3D[i][j][0] - ImageDataOp3D[i][j][0] ;
            		eg = Error3D[i][j][1] - ImageDataOp3D[i][j][1] ;
            		eb = Error3D[i][j][2] - ImageDataOp3D[i][j][2] ;
            		if (j + 1 < ImgWidth)
            		{
            			Error3D[i][j+1][0] += er*(0.4375) ;
            			Error3D[i][j+1][1] += eg*(0.4375) ;
            			Error3D[i][j+1][2] += eb*(0.4375) ;
            		}
            		if (j > 0 && i + 1 < ImgHeight)
            		{
            			Error3D[i+1][j-1][0] += er*(0.1875) ;
            			Error3D[i+1][j-1][1] += eg*(0.1875) ;
            			Error3D[i+1][j-1][2] += eb*(0.1875) ;
            		}
            		if (i + 1 < ImgHeight)
            		{
            			Error3D[i+1][j][0] += er*(0.3125) ;
            			Error3D[i+1][j][1] += eg*(0.3125) ;
            			Error3D[i+1][j][2] += eb*(0.3125) ;
            		}
            		if (i + 1 < ImgHeight && j + 1 < ImgWidth)
            		{
            			Error3D[i+1][j+1][0] += er*(0.0625) ;
            			Error3D[i+1][j+1][1] += eg*(0.0625) ;
            			Error3D[i+1][j+1][2] += eb*(0.0625) ;
            		}
                break ;
            	case 3 :
            		x = Error3D[i][j][0] ;
            		y = Error3D[i][j][1] ;
            		z = Error3D[i][j][2] ;
            		index = mindist(x, y, z, q3);
            		for (int k = 0 ; k < BytesPerPixel ; k++)
            		{
            			ImageDataOp3D[i][j][k] =  q3[index][k] ;
            		}
            		er = 0 ; eg = 0 ; eb = 0 ;
            		er = Error3D[i][j][0] - ImageDataOp3D[i][j][0] ;
            		eg = Error3D[i][j][1] - ImageDataOp3D[i][j][1] ;
            		eb = Error3D[i][j][2] - ImageDataOp3D[i][j][2] ;
            		if (j + 1 < ImgWidth)
            		{
            			Error3D[i][j+1][0] += er*(0.4375) ;
            			Error3D[i][j+1][1] += eg*(0.4375) ;
            			Error3D[i][j+1][2] += eb*(0.4375) ;
            		}
            		if (j > 0 && i + 1 < ImgHeight)
            		{
            			Error3D[i+1][j-1][0] += er*(0.1875) ;
            			Error3D[i+1][j-1][1] += eg*(0.1875) ;
            			Error3D[i+1][j-1][2] += eb*(0.1875) ;
            		}
            		if (i + 1 < ImgHeight)
            		{
            			Error3D[i+1][j][0] += er*(0.3125) ;
            			Error3D[i+1][j][1] += eg*(0.3125) ;
            			Error3D[i+1][j][2] += eb*(0.3125) ;
            		}
            		if (i + 1 < ImgHeight && j + 1 < ImgWidth)
            		{
            			Error3D[i+1][j+1][0] += er*(0.0625) ;
            			Error3D[i+1][j+1][1] += eg*(0.0625) ;
            			Error3D[i+1][j+1][2] += eb*(0.0625) ;
            		}
                break ;
            	case 4 :
            		x = Error3D[i][j][0] ;
            		y = Error3D[i][j][1] ;
            		z = Error3D[i][j][2] ;
            		index = mindist(x, y, z, q4);
            		for (int k = 0 ; k < BytesPerPixel ; k++)
            		{
            			ImageDataOp3D[i][j][k] =  q4[index][k] ;
            		}
            		er = 0 ; eg = 0 ; eb = 0 ;
            		er = Error3D[i][j][0] - ImageDataOp3D[i][j][0] ;
            		eg = Error3D[i][j][1] - ImageDataOp3D[i][j][1] ;
            		eb = Error3D[i][j][2] - ImageDataOp3D[i][j][2] ;
            		if (j + 1 < ImgWidth)
            		{
            			Error3D[i][j+1][0] += er*(0.4375) ;
            			Error3D[i][j+1][1] += eg*(0.4375) ;
            			Error3D[i][j+1][2] += eb*(0.4375) ;
            		}
            		if (j > 0 && i + 1 < ImgHeight)
            		{
            			Error3D[i+1][j-1][0] += er*(0.1875) ;
            			Error3D[i+1][j-1][1] += eg*(0.1875) ;
            			Error3D[i+1][j-1][2] += eb*(0.1875) ;
            		}
            		if (i + 1 < ImgHeight)
            		{
            			Error3D[i+1][j][0] += er*(0.3125) ;
            			Error3D[i+1][j][1] += eg*(0.3125) ;
            			Error3D[i+1][j][2] += eb*(0.3125) ;
            		}
            		if (i + 1 < ImgHeight && j + 1 < ImgWidth)
            		{
            			Error3D[i+1][j+1][0] += er*(0.0625) ;
            			Error3D[i+1][j+1][1] += eg*(0.0625) ;
            			Error3D[i+1][j+1][2] += eb*(0.0625) ;
            		}
                break ;
            	case 5 :
            		x = Error3D[i][j][0] ;
            		y = Error3D[i][j][1] ;
            		z = Error3D[i][j][2] ;
            		index = mindist(x, y, z, q5);
            		for (int k = 0 ; k < BytesPerPixel ; k++)
            		{
            			ImageDataOp3D[i][j][k] =  q5[index][k] ;
            		}
            		er = 0 ; eg = 0 ; eb = 0 ;
            		er = Error3D[i][j][0] - ImageDataOp3D[i][j][0] ;
            		eg = Error3D[i][j][1] - ImageDataOp3D[i][j][1] ;
            		eb = Error3D[i][j][2] - ImageDataOp3D[i][j][2] ;
            		if (j + 1 < ImgWidth)
            		{
            			Error3D[i][j+1][0] += er*(0.4375) ;
            			Error3D[i][j+1][1] += eg*(0.4375) ;
            			Error3D[i][j+1][2] += eb*(0.4375) ;
            		}
            		if (j > 0 && i + 1 < ImgHeight)
            		{
            			Error3D[i+1][j-1][0] += er*(0.1875) ;
            			Error3D[i+1][j-1][1] += eg*(0.1875) ;
            			Error3D[i+1][j-1][2] += eb*(0.1875) ;
            		}
            		if (i + 1 < ImgHeight)
            		{
            			Error3D[i+1][j][0] += er*(0.3125) ;
            			Error3D[i+1][j][1] += eg*(0.3125) ;
            			Error3D[i+1][j][2] += eb*(0.3125) ;
            		}
            		if (i + 1 < ImgHeight && j + 1 < ImgWidth)
            		{
            			Error3D[i+1][j+1][0] += er*(0.0625) ;
            			Error3D[i+1][j+1][1] += eg*(0.0625) ;
            			Error3D[i+1][j+1][2] += eb*(0.0625) ;
            		}
                break ;
            	case 6 :
            		x = Error3D[i][j][0] ;
            		y = Error3D[i][j][1] ;
            		z = Error3D[i][j][2] ;
            		index = mindist(x, y, z, q6);
            		for (int k = 0 ; k < BytesPerPixel ; k++)
            		{
            			ImageDataOp3D[i][j][k] =  q6[index][k] ;
            		}
            		er = 0 ; eg = 0 ; eb = 0 ;
            		er = Error3D[i][j][0] - ImageDataOp3D[i][j][0] ;
            		eg = Error3D[i][j][1] - ImageDataOp3D[i][j][1] ;
            		eb = Error3D[i][j][2] - ImageDataOp3D[i][j][2] ;
            		if (j + 1 < ImgWidth)
            		{
            			Error3D[i][j+1][0] += er*(0.4375) ;
            			Error3D[i][j+1][1] += eg*(0.4375) ;
            			Error3D[i][j+1][2] += eb*(0.4375) ;
            		}
            		if (j > 0 && i + 1 < ImgHeight)
            		{
            			Error3D[i+1][j-1][0] += er*(0.1875) ;
            			Error3D[i+1][j-1][1] += eg*(0.1875) ;
            			Error3D[i+1][j-1][2] += eb*(0.1875) ;
            		}
            		if (i + 1 < ImgHeight)
            		{
            			Error3D[i+1][j][0] += er*(0.3125) ;
            			Error3D[i+1][j][1] += eg*(0.3125) ;
            			Error3D[i+1][j][2] += eb*(0.3125) ;
            		}
            		if (i + 1 < ImgHeight && j + 1 < ImgWidth)
            		{
            			Error3D[i+1][j+1][0] += er*(0.0625) ;
            			Error3D[i+1][j+1][1] += eg*(0.0625) ;
            			Error3D[i+1][j+1][2] += eb*(0.0625) ;
            		}
                break ;
            }
        }
    }


    int Max = 255;
	double Sum = 0;
	double Mse = 0;
	double Psnr = 0;
	for (int i = 0;i < ImgHeight;i++)
	{
		for (int j = 0;j < ImgWidth;j++)
		{

			for (int k = 0 ; k < BytesPerPixel ; k++)
            		{
            		    Sum = Sum + (pow((ImageDataOp3D[i][j][k] - ImageData3D[i][j][k]), 2));
            		}
		}
	}
	Mse = (1 / (1.0 * ImgHeight * ImgWidth)) * Sum;
	Psnr = 10 * log10((pow(Max, 2)) / (1.0 * Mse));

	cout<< "PSNR:"<<Psnr<<endl;     //2.7616
    ImageDataOp = Convert3dTo1dus(ImageDataOp3D, ImgHeight, ImgWidth, BytesPerPixel);
    WriteFile(argv[2],ImageDataOp, ImgHeight, ImgWidth, BytesPerPixel);
    Delete3d(ImageData3D, ImgHeight, ImgWidth) ;
	Delete3d(ImageDataOp3D, ImgHeight, ImgWidth);
	delete [] ImageData;
	delete [] ImageDataOp;

    return 0 ;
}
