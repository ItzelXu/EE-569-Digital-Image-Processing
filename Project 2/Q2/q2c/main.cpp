// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #2 Prob 2 Error Difussion
// Date: February 21, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------

#include <iostream>
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include "string.h"
#include <stdlib.h>
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
	unsigned char*** ImageDataOp3D = NULL;
	ImageDataOp3D = Convert1dto3dus(ImageDataOp, ImgHeight, ImgWidth, BytesPerPixel);
	double* Temp = new double [ImgHeight*ImgWidth*BytesPerPixel];
	ReadFile(argv[1], ImageData, ImgHeight, ImgWidth,BytesPerPixel);
	cout<<"Flag 1"<<endl;
	double e = 0 ;
    memset(ImageDataOp,0, ImgHeight*ImgWidth*BytesPerPixel);

	for(int i = 0 ; i < ImgHeight*ImgWidth*BytesPerPixel ; i++)
		Temp[i] = 1 - (double) ImageData[i] / 255 ;
	double*** Temp3D = NULL;
	Temp3D = Convert1dto3d(Temp, ImgHeight, ImgWidth, BytesPerPixel);
	cout<<"Flag 2"<<endl;

	for (int k = 0 ; k < BytesPerPixel ; k++)
	{
		for (int i = 0 ; i < ImgHeight ; i++)
		{
			if (i % 2 == 0)
			{
				for (int j = 0 ; j < ImgWidth ; j++)
				{
				    //cout<<i<<" "<<j<<endl;
					if(Temp3D[i][j][k] >= 0.5)
					{
						e = Temp3D[i][j][k] - 1 ;
                		ImageDataOp3D[i][j][k] = 0;
					}
					else
					{
						e = Temp3D[i][j][k] - 0 ;
                		ImageDataOp3D[i][j][k] = 255;
					}
					//cout<<e<<endl;
					if (j + 1 < ImgWidth)
						Temp3D[i][j+1][k] += e*(0.4375) ;
        				//temp1 [i*ImgWidth+j+1] += e*(0.4375);
		        	if (j > 0 && i + 1 < ImgHeight)
		        		Temp3D[i+1][j-1][k] += e*(0.1875) ;
		        		//temp1 [(i+1)*ImgWidth+j-1] += e*(0.1875);
		        	if (i + 1 < ImgHeight)
		        		Temp3D[i+1][j][k] += e*(0.3125) ;
		        		//temp1 [(i+1)*ImgWidth+j] += e*(0.3125);
		        	if (i + 1 < ImgHeight && j + 1 < ImgWidth)
		        		Temp3D[i+1][j+1][k] += e*(0.0625) ;
		        		//temp1 [(i+1)*ImgWidth+j+1] += e*(0.0625);
		        }
			}
			else
			{
				for (int j = ImgWidth - 1 ; j > 0 ; j--)
				{
				    //cout<<i<<" "<<j<<endl;
					if(Temp3D[i][j][k] >= 0.5)
					{
						e = Temp3D[i][j][k] - 1 ;
                		ImageDataOp3D[i][j][k] = 0;
					}
					else
					{
						e = Temp3D[i][j][k] - 0 ;
                		ImageDataOp3D[i][j][k] = 255;
					}
					//cout<<e<<endl;
					if (j + 1 < ImgWidth)
						Temp3D[i][j-1][k] += e*(0.4375) ;
        				//temp1 [i*ImgWidth+j+1] += e*(0.4375);
		        	if (j > 0 && i + 1 < ImgHeight)
		        		Temp3D[i+1][j-1][k] += e*(0.0625) ;
		        		//temp1 [(i+1)*ImgWidth+j-1] += e*(0.1875);
		        	if (i + 1 < ImgHeight)
		        		Temp3D[i+1][j][k] += e*(0.3125) ;
		        		//temp1 [(i+1)*ImgWidth+j] += e*(0.3125);
		        	if (i + 1 < ImgHeight && j + 1 < ImgWidth)
		        		Temp3D[i+1][j+1][k] += e*(0.1875) ;
		        		//temp1 [(i+1)*ImgWidth+j+1] += e*(0.0625);
				}
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
            		    Sum = Sum + (pow((ImageDataOp3D[i][j][k] - ImageData[i * ImgWidth * BytesPerPixel + j * BytesPerPixel + k]), 2));
            		}
		}
	}
	Mse = (1 / (1.0 * ImgHeight * ImgWidth)) * Sum;
	Psnr = 10 * log10((pow(Max, 2)) / (1.0 * Mse));
	cout<<"PSNR: "<<Psnr<<endl; //2.7514
    cout<<"Flag 3"<<endl;
	ImageDataOp = Convert3dTo1dus(ImageDataOp3D, ImgHeight,ImgWidth, BytesPerPixel);




    WriteFile(argv[2], ImageDataOp, ImgHeight, ImgWidth, BytesPerPixel);
    return 0 ;
}
