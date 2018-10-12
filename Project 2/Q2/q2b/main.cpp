// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #2 Prob 2 b
// Date: February 11, 2018
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

int main(int argc, char* argv[])
{

	int ImgWidth = 512;
	int ImgHeight = 512;
	int BytesPerPixel = 1;
	unsigned char* ImageData = new unsigned char [ ImgHeight*ImgWidth];
	//unsigned char* ImageDataOp1 = new unsigned char [ ImgHeight*ImgWidth];
	ReadFile(argv[1], ImageData, ImgHeight, ImgWidth,BytesPerPixel);

    /*for (int i = 0 ; i < ImgHeight*ImgWidth*BytesPerPixel; i ++)
    {
        ImageDataOp1[i] = ImageData[i];
    }*/
    unsigned char ** ImageData2D = Allocate2d(ImageData2D, ImgHeight, ImgWidth) ;
    ImageData2D = Convert1dTo2d(ImageData, ImgHeight, ImgWidth);

    unsigned char ** ImageDataOp12D = Allocate2d(ImageDataOp12D, ImgHeight, ImgWidth) ;
    ImageDataOp12D = Convert1dTo2d(ImageData, ImgHeight, ImgWidth);

    unsigned char ** ImageDataOp22D = Allocate2d(ImageDataOp12D, ImgHeight, ImgWidth) ;
    ImageDataOp22D = Convert1dTo2d(ImageData, ImgHeight, ImgWidth);

    unsigned char ** ImageDataOp32D = Allocate2d(ImageDataOp12D, ImgHeight, ImgWidth) ;
    ImageDataOp32D = Convert1dTo2d(ImageData, ImgHeight, ImgWidth);

    double e = 0;
    cout<< "Flag 1 "<<endl;
    //float temp1 [ImgHeight*ImgWidth];
    double * temp1 = new double [ImgHeight*ImgWidth];
    double * temp2 = new double [ImgHeight*ImgWidth];
    double * temp3 = new double [ImgHeight*ImgWidth];
    //float temp2 [ImgHeight*ImgWidth];
    //float temp3 [ImgHeight*ImgWidth];
    cout<< "Flag 2 "<<endl;

    for(int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j < ImgWidth ; j++)
        {
            temp1 [i*ImgWidth+j] = 1 - (double) ImageData2D[i][j] / 255;
            temp2 [i*ImgWidth+j] = 1 - (double) ImageData2D[i][j] / 255;
            temp3 [i*ImgWidth+j] = 1 - (double) ImageData2D[i][j] / 255;
        }
    }
    //cout<< "Flag 3 "<<endl;

    for (int i = 0 ; i < ImgHeight ; i++)
    {
       if (i % 2 == 0)
       {
           for (int j = 0 ; j < ImgWidth ; j++)
            {
            if(temp1 [i*ImgWidth+j] >= 0.5)
            {
                e = temp1 [i*ImgWidth+j] - 1 ;
                ImageDataOp12D[i][j] = 0;
            }
            else
            {
                e = temp1 [i*ImgWidth+j] - 0 ;
                ImageDataOp12D[i][j] = 255;
            }
            if (j + 1 < ImgWidth)
        		temp1 [i*ImgWidth+j+1] += e*(0.4375);
        	if (j > 0 && i + 1 < ImgHeight)
        		temp1 [(i+1)*ImgWidth+j-1] += e*(0.1875);
        	if (i + 1 < ImgHeight)
        		temp1 [(i+1)*ImgWidth+j] += e*(0.3125);
        	if (i + 1 < ImgHeight && j + 1 < ImgWidth)
        		temp1 [(i+1)*ImgWidth+j+1] += e*(0.0625);
            }
       }
       else
       {
           for (int j = ImgWidth - 1 ; j >= 0 ; j--)
        {
            if(temp1 [i*ImgWidth+j] >= 0.5)
            {
                e = temp1 [i*ImgWidth+j] - 1 ;
                ImageDataOp12D[i][j] = 0;
            }
            else
            {
                e = temp1 [i*ImgWidth+j] - 0 ;
                ImageDataOp12D[i][j] = 255;
            }
            if (j + 1 < ImgWidth)
        		temp1 [i*ImgWidth+j-1] += e*(0.4375);
        	if (j > 0 && i + 1 < ImgHeight)
        		temp1 [(i+1)*ImgWidth+j-1] += e*(0.0625);
        	if (i + 1 < ImgHeight)
        		temp1 [(i+1)*ImgWidth+j] += e*(0.3125);
        	if (i + 1 < ImgHeight && j + 1 < ImgWidth)
        		temp1 [(i+1)*ImgWidth+j+1] += e*(0.1875);
        }
       }

    }
    cout<< "Flag 2 "<<endl;
    //e = 0 ;


    for (int i = 0 ; i < ImgHeight ; i++)
    {
       for (int j = 0 ; j < ImgWidth ; j++)
        {
            e = 0 ;
            if(temp2 [i*ImgWidth+j] >= 0.5)
            {
                e = temp2 [i*ImgWidth+j] - 1 ;
                ImageDataOp22D[i][j] = 0;
            }
            else
            {
                e = temp2 [i*ImgWidth+j] - 0 ;
                ImageDataOp22D[i][j] = 255;
            }
            if (j + 1 < ImgWidth)
                temp2[i*ImgWidth+j+1] += e*(0.1458);
            if (j + 1 < ImgWidth && i + 1 < ImgHeight)
                temp2[(i+1)*ImgWidth+j+1] += e*(0.1041);
            if (j + 1 < ImgWidth && i + 2 < ImgHeight)
                temp2[(i+2)*ImgWidth+j+1] += e*(0.0625);
            if (j + 2 < ImgWidth)
                temp2[i*ImgWidth+j+2] += e*(0.1041);
            if (j + 2 < ImgWidth && i + 1 < ImgHeight)
                temp2[(i+1)*ImgWidth+j+2] += e*(0.0625);
            if (j + 2 < ImgWidth && i + 2 < ImgHeight)
                temp2[(i+2)*ImgWidth+j+2] += e*(0.0208);
            if (i + 1 < ImgHeight)
                temp2[(i+1)*ImgWidth+j] += e*(0.1458);
            if (i + 2 < ImgHeight)
                temp2[(i+2)*ImgWidth+j] += e*(0.1041);
            if (j > 0 && i + 1 < ImgHeight)
                temp2[(i+1)*ImgWidth+j-1] += e*(0.1041);
            if (j > 0 && i + 2 < ImgHeight)
                temp2[(i+2)*ImgWidth+j-1] += e*(0.0625);
            if (j - 1 > 0 && i + 1 < ImgHeight)
                temp2[(i+1)*ImgWidth+j-2] += e*(0.0625);
            if (j - 1 > 0 && i + 2 < ImgHeight)
                temp2[(i+2)*ImgWidth+j-2] += e*(0.0208);
        }
    }


    for (int i = 0 ; i < ImgHeight ; i++)
    {
       for (int j = 0 ; j < ImgWidth ; j++)
        {
            e = 0 ;
            if(temp3 [i*ImgWidth+j] >= 0.5)
            {
                e = temp3 [i*ImgWidth+j] - 1 ;
                ImageDataOp32D[i][j] = 0;
            }
            else
            {
                e = temp3 [i*ImgWidth+j] - 0 ;
                ImageDataOp32D[i][j] = 255;
            }
            if (j + 1 < ImgWidth)
                temp3[i*ImgWidth+j+1] += e*(0.1904);
            if (j + 1 < ImgWidth && i + 1 < ImgHeight)
                temp3[(i+1)*ImgWidth+j+1] += e*(0.0952);
            if (j + 1 < ImgWidth && i + 2 < ImgHeight)
                temp3[(i+2)*ImgWidth+j+1] += e*(0.0476);
            if (j + 2 < ImgWidth)
                temp3[i*ImgWidth+j+2] += e*(0.0952);
            if (j + 2 < ImgWidth && i + 1 < ImgHeight)
                temp3[(i+1)*ImgWidth+j+2] += e*(0.0476);
            if (j + 2 < ImgWidth && i + 2 < ImgHeight)
                temp3[(i+2)*ImgWidth+j+2] += e*(0.0238);
            if (i + 1 < ImgHeight)
                temp3[(i+1)*ImgWidth+j] += e*(0.1904);
            if (i + 2 < ImgHeight)
                temp3[(i+2)*ImgWidth+j] += e*(0.0952);
            if (j > 0 && i + 1 < ImgHeight)
                temp3[(i+1)*ImgWidth+j-1] += e*(0.0952);
            if (j > 0 && i + 2 < ImgHeight)
                temp3[(i+2)*ImgWidth+j-1] += e*(0.0476);
            if (j - 1 > 0 && i + 1 < ImgHeight)
                temp3[(i+1)*ImgWidth+j-2] += e*(0.0476);
            if (j - 1 > 0 && i + 2 < ImgHeight)
                temp3[(i+2)*ImgWidth+j-2] += e*(0.0238);
        }
    }




    /*for (int i = 0 ; i < ImgHeight - 1 ; i++)
    {
        for (int j = 1 ; j < ImgWidth - 1 ; j++)
        {
        	e = 0 ;
        	ov = ImageDataOp12D[i][j];
        	if (ImageDataOp12D[i][j] <=127)
                ImageDataOp12D[i][j] = 0;
            else
                ImageDataOp12D[i][j] = 255;
        	e = ov - ImageDataOp12D[i][j];
        	cout<<e<<endl;
        	//if (j + 1 < ImgWidth)
        		ImageDataOp12D[i][j+1] += e*(0.4375);
        	//if (j > 0 && i + 1 < ImgHeight)
        		ImageDataOp12D[i+1]unsigned char * Op1 = new unsigned char [ImgHeight*ImgWidth*BytesPerPixel];
    Op1 = Convert2dTo1d(ImageDataOp12D , ImgHeight, ImgWidth);[j-1] += e*(0.1875);
        	//if (i + 1 < ImgHeight)
        		ImageDataOp12D[i+1][j] += e*(0.3125);
        	//if (i + 1 < ImgHeight && j + 1 < ImgWidth)
        		ImageDataOp12D[i+1][j+1] += e*(0.0625);
        }
    }*/

    cout<< "Flag 3 "<<endl;
    unsigned char * Op1 = new unsigned char [ImgHeight*ImgWidth*BytesPerPixel];
    Op1 = Convert2dTo1d(ImageDataOp12D , ImgHeight, ImgWidth);
    unsigned char * Op2 = new unsigned char [ImgHeight*ImgWidth*BytesPerPixel];
    Op2 = Convert2dTo1d(ImageDataOp22D , ImgHeight, ImgWidth);
    unsigned char * Op3 = new unsigned char [ImgHeight*ImgWidth*BytesPerPixel];
    Op3 = Convert2dTo1d(ImageDataOp32D , ImgHeight, ImgWidth);
    WriteFile(argv[2], Op1, ImgHeight, ImgWidth, BytesPerPixel);
    WriteFile(argv[3], Op2, ImgHeight, ImgWidth, BytesPerPixel);
    WriteFile(argv[4], Op3, ImgHeight, ImgWidth, BytesPerPixel);

    int Max = 255;
	double Sum = 0;
	long double Mse = 0;
	double Psnr;
	for (int i = 0;i < ImgHeight;i++)
	{
		for (int j = 0;j < ImgWidth;j++)
		{
			Sum = Sum + (pow((ImageDataOp32D[i][j] - ImageData2D[i][j]), 2));
			//cout<<Sum<<endl;
		}
	}
	Mse = (1 / (1.0 * ImgHeight * ImgWidth)) * Sum;
	Psnr = 10 * log10((pow(Max, 2)) / (1.0 * Mse));

	cout<< "PSNR :"<<Psnr<<endl;

	return 0 ;
}
