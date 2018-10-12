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
#include <cmath>
#include <algorithm>
#include "Headers.h"

using namespace std;

void ReadFile(const char* FileName, unsigned char* Imagedata, int ImgHeight, int ImgWidth, int BytesPerPixel)
{
	FILE* file;

	if (!(file=fopen(FileName,"rb")))
    {
        cout << "Cannot open file: " << FileName <<endl;
		exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), ImgHeight*ImgWidth*BytesPerPixel, file);
    fclose(file);
	cout << "File " << FileName << " has been read successfully! " << endl;
}

void WriteFile(const char* FileName, unsigned char* Imagedata, int ImgHeight, int ImgWidth, int BytesPerPixel)
{
	FILE* file;

	if (!(file=fopen(FileName,"wb"))) {
		cout << "Cannot open file: " << FileName << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), ImgHeight*ImgWidth*BytesPerPixel, file);
	fclose(file);
	cout << "\nFile " << FileName << " has been written successfully!" << endl;
}

unsigned char** Allocate2d(unsigned char** Imagedata, int ImgHeight, int ImgWidth)
{
	Imagedata = new unsigned char *[ImgHeight]();
	for (int i = 0;i < ImgHeight;i++)
	{
		Imagedata[i] = new unsigned char[ImgWidth]();
		for (int j = 0;j < ImgWidth;j++)
		{
			Imagedata[i][j] = 0;
		}
	}
	return Imagedata;
}

void Delete2d(unsigned char** Imagedata, int ImgHeight)
{
	for (int i = 0; i < ImgHeight; i++)
	{
		delete[] Imagedata[i];
	}
	delete[] Imagedata;
}

void Delete3d(unsigned char*** Imagedata, int ImgHeight, int ImgWidth)
{
	for (int i = 0; i < ImgHeight; i++)
	{
		for (int j = 0; j < ImgWidth; j++)
			delete[] Imagedata[i][j];
		delete[] Imagedata[i];
	}
	delete[] Imagedata;
}

unsigned char** Convert1dTo2d(unsigned char* Imagedata, int ImgHeight, int ImgWidth)
{
	unsigned char** Img2d = new unsigned char *[ImgHeight]();
	for (int i = 0;i < ImgHeight;i++)
	{
		Img2d[i] = new unsigned char [ImgWidth]();
		for (int j = 0;j < ImgWidth;j++)
		{
			Img2d[i][j] = 0;
		}
	}

	for (int i = 0; i < ImgHeight; i++)
	{
		for (int j = 0; j < ImgWidth; j++)
		{
			Img2d[i][j] = Imagedata[i * ImgWidth + j];
		}
	}
	return(Img2d);
}

unsigned char* Convert2dTo1d(unsigned char** Imagedata, int ImgHeight, int ImgWidth)
{
	unsigned char* Img1d = new unsigned char[ImgHeight*ImgWidth]();
	for (int i = 0; i < ImgHeight; i++)
	{
		for (int j = 0; j < ImgWidth; j++)
		{
			Img1d[i * ImgWidth + j] = Imagedata[i][j];
		}
	}
	return(Img1d);
}



unsigned char*** Convert1dto3d(unsigned char* Imagedata, int ImgHeight, int ImgWidth, int BytesPerPixel)
{
	unsigned char*** Imagedata3d =  new unsigned char **[ImgHeight]();
	for (int i = 0; i < ImgHeight; i++)
	{
		Imagedata3d[i] = new unsigned char *[ImgWidth]();
		for (int j = 0; j < ImgWidth; j++)
		{
			Imagedata3d[i][j] = new unsigned char[BytesPerPixel]();
			for (int k = 0; k < BytesPerPixel; k++)
			{
				Imagedata3d[i][j][k] = 0;
			}
		}
	}

    //int m = 0 ;
	for (int i = 0; i < ImgHeight; i++)
	{
		for (int j = 0; j < ImgWidth; j++)
		{
			for (int k = 0; k < BytesPerPixel; k++)
			{
				Imagedata3d[i][j][k] = Imagedata[i * ImgWidth * BytesPerPixel + j * BytesPerPixel + k];
				//Imagedata3d[i][j][k] = Imagedata[m];
				//m = m+1;
			}
		}
	}
	return(Imagedata3d);
}


unsigned char* Convert3dTo1d(unsigned char*** Imagedata3d, int ImgHeight, int ImgWidth, int BytesPerPixel)
{
	unsigned char* Imagedata = new unsigned char[ImgHeight*ImgWidth*BytesPerPixel]();
	int m = 0;
	for (int i = 0; i < ImgHeight; i++)
	{
		for (int j = 0; j < ImgWidth; j++)
		{
			Imagedata [m] = Imagedata3d[i][j][0];
			Imagedata [m + 1] = Imagedata3d[i][j][1];
			Imagedata [m + 2] = Imagedata3d[i][j][2];
			m = m + 3;
		}
	}
	return(Imagedata);
}

int* GetHistogram(unsigned char *ImageData,int ImgHeight, int ImgWidth)
{
    int* histogram = new int [256]; // Initialize it into 0
    for(int i = 0 ; i < ImgHeight ; i++)
    {
        for(int j = 0 ; j < ImgWidth ; j++)
        {
            histogram[ImageData[i * ImgWidth + j]] ++;
        }
    }
    cout << "Histogram has been calculated successfully!" << endl;
    return histogram;
}

unsigned char* ConvertGreyToBinary (unsigned char*ImageData, int ImgHeight, int ImgWidth)
{
    unsigned char * TempOp = new unsigned char [ImgHeight*ImgWidth];
    for(int i = 0 ; i < ImgHeight*ImgWidth ; i++)
    {
        if(ImageData[i] < 127)
            TempOp[i] = 255 ;
        else
            TempOp[i] = 0 ;
    }
    WriteFile("Jigsaw_grey.raw",TempOp,ImgHeight, ImgWidth, 1);
    return TempOp;
}


