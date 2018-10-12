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
#include <cmath>
#include <algorithm>
#include "math.h"
#include "string.h"
#include <stdlib.h>
#include "MyImgfunctions.h"
#include "Headers.h"

using namespace std;


unsigned char * PadImage(unsigned char* Imagedata, int ImgHeight, int ImgWidth, int n)
{
    //int n = m ;
    int ImgHeightNew = ImgHeight + 2 * n ;
    int ImgWidthNew = ImgWidth + 2 * n ;

    unsigned char ** ImageData = NULL;
    ImageData = Allocate2d(ImageData, ImgHeight, ImgWidth);
    ImageData = Convert1dTo2d(Imagedata, ImgHeight, ImgWidth);

    unsigned char ** ImageDataNew = NULL;
    ImageDataNew = Allocate2d(ImageDataNew, ImgHeightNew, ImgWidthNew);

    for (int j = 0 ; j < ImgWidth ; j++)
    {
        ImageDataNew[0][j+n] = 0;
        ImageDataNew[ImgHeightNew - 1][j+n] = 0;//ImageData[ImgHeight - 1][j];
    }

    for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j < ImgWidth ; j++)
        {
			ImageDataNew[i+n][j+n] = ImageData[i][j];
        }
    }

    for (int i = 0 ; i < ImgHeightNew ; i++)
    {
        ImageDataNew[i][0] = 0;//ImageDataNew[i][n];
        ImageDataNew[i][ImgWidthNew - 1] = 0;//ImageDataNew[i][ImgWidth-1];
    }

    unsigned char * ImagedataNew = new unsigned char [ImgHeightNew * ImgWidthNew];
    ImagedataNew = Convert2dTo1d(ImageDataNew, ImgHeightNew, ImgWidthNew);
    //cout<<"Image has been padded successfully!"<<endl;
    return ImagedataNew;
}


int CountDots(unsigned char *ImageData, int ImgHeight, int ImgWidth)
{
	int cntr = 0  ;
	int n  = 1 ;
	int ImgHeightNew = ImgHeight + 2 * n ;
	int ImgWidthNew = ImgWidth + 2 * n ;
	unsigned char* PaddedImage = new unsigned char [ImgHeightNew * ImgWidthNew] ;
	PaddedImage = PadImage( ImageData, ImgHeight, ImgWidth, 1) ;

	int n1[]={-1,-1,-1,0,0,1,1,1};
    int n2[]={-1,0,1,-1,1,-1,0,1};

    for ( int i = 0 ; i < ImgHeight ; i++)
    {
    	for(int j = 0 ; j < ImgWidth ; j++)
    	{
    		if (ImageData[i*ImgWidth + j] == 255)
    		{
    			int f = 0 ;
    			for(int  k = 0 ; k < 8 ; k++)
    			{
    				if(PaddedImage[(i + n + n1[k])*ImgWidthNew + (j + n + n2[k])] == 255)
    					f = 1 ;
    			}
    			if(f == 0)
    				cntr ++ ;
    		}
    	}
    }

    delete [] PaddedImage ;
    return cntr ;
}


int CheckCondPattern(int pattern, char type)
{
    int Sb = 0, Se = 57;
    int Tb = 16, Te = 61;
    int Kb = 26, Ke = 65;
    int CPatterns[]={0b001010000,0b100010000,0b000010100,0b000010001, //S
                         0b000011000,0b010010000,0b000110000,0b000010010, //S
                         0b001011000,0b011010000,0b110010000,0b100110000, //S
                         0b000110100,0b000010110,0b000010011,0b000011001, //S
                         0b110011000,0b010011001,0b011110000,0b001011010, //ST
                         0b011011000,0b110110000,0b000110110,0b000011011, //ST
                         0b110011001,0b011110100, //ST

                         0b011011011,0b111111000,0b110110110,0b000111111, //STK
                         0b111011011,0b011011111,0b111111100,0b111111001, //STK
                         0b111110110,0b110110111,0b100111111,0b001111111, //STK
                         0b111011111,0b111111101,0b111110111,0b101111111, //STK
                         0b001011001,0b111010000,0b100110100,0b000010111, //STK
                         0b111011000,0b011011001,0b111110000,0b110110100, //STK
                         0b100110110,0b000110111,0b000011111,0b001011011, //STK
                         0b111011001,0b111110100,0b100110111,0b001011111, //STK
                         0b010011000,0b010110000,0b000110010,0b000011010, //TK
                         0b111111011,0b111111110,0b110111111,0b011111111};// K
    switch (type)
    {
    case 'S':
        for(int i=Sb;i<=Se;i++)
        {
            if(pattern == CPatterns[i])
            return 1;
        }
        break;
    case 'T':
        for(int i=Tb;i<=Te;i++)
        {
            if(pattern == CPatterns[i])
            return 1;
        }
        break;
    case 'K':
        for(int i=Kb;i<=Ke;i++)
        {
            if(pattern == CPatterns[i])
            return 1;
        }
        break;
    }

    return 0;
}

int CheckUncondPattern(int pattern, char type)
{
    int UCPatternsSTWithoutD[]={0b001010000,0b100010000, // Spur
                      0b000010010,0b000011000, // Single 4-connection
                      0b001011000,0b011010000,0b110010000,0b100110000, //LCluster
                      0b000110100,0b000010110,0b000010011,0b000011001,
                      0b011110000,0b110011000,0b010011001,0b001011010, // 4-connected offset
                      0b011011100,0b001011100,0b011010100, // Spur corner Cluster
                      0b110110001,0b100110001,0b110010001,
                      0b001110110,0b001110100,0b001010110,
                      0b100011011,0b100011001,0b100010011
                      };
    int UCPatternsSTWithD[]={0b110110000,// Corner Cluster
                      0b010111000,// TeeBranch
                      0b010111000,
                      0b000111010,
                      0b000111010,
                      0b010110010,
                      0b010110010,
                      0b010011010,
                      0b010011010,
                      0b101010001,0b101010010,0b101010011,0b101010100,0b101010101,0b101010110,0b101010111,// VeeBranch
                      0b100010101,0b100011100,0b100011101,0b101010100,0b101010101,0b101011100,0b101011101,
                      0b001010101,0b010010101,0b011010101,0b100010101,0b101010101,0b110010101,0b111010101,
                      0b001010101,0b001110001,0b001110101,0b101010001,0b101010101,0b101110001,0b101110101,
                      0b010011100,// DiagonalBranch
                      0b010110001,
                      0b001110010,
                      0b100011010
                      };
    int UCPatternsSTDMask[]={0b110110000,// Corner Cluster
                      0b011111011,// TeeBranch
                      0b110111110,
                      0b110111110,
                      0b011111011,
                      0b010111111,
                      0b111111010,
                      0b111111010,
                      0b010111111,
                      0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,// VeeBranch
                      0b101011111,0b101011111,0b101011111,0b101011111,0b101011111,0b101011111,0b101011111,
                      0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,
                      0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,
                      0b011111110,// DiagonalBranch
                      0b110111011,
                      0b011111110,
                      0b110111011
                      };
    int UCPatternsKWithoutD[]={0b000010001,0b000010100,0b001010000,0b100010000, // Spur
                      0b000010010,0b000011000,0b000110000,0b010010000, // Single 4-connection
                      0b010011000,0b010110000,0b000011010,0b000110010// LCorner
                      };
    int UCPatternsKWithD[]={
                      0b110110000,// Corner Cluster
                      0b000011011,
                      0b010111000,// TeeBranch
                      0b010110010,
                      0b000111010,
                      0b010011010,
                      0b101010001,0b101010010,0b101010011,0b101010100,0b101010101,0b101010110,0b101010111,// VeeBranch
                      0b100010101,0b100011100,0b100011101,0b101010100,0b101010101,0b101011100,0b101011101,
                      0b001010101,0b010010101,0b011010101,0b100010101,0b101010101,0b110010101,0b111010101,
                      0b001010101,0b001110001,0b001110101,0b101010001,0b101010101,0b101110001,0b101110101,
                      0b010011100,// DiagonalBranch
                      0b010110001,
                      0b001110010,
                      0b100011010,
                      };
    int UCPatternsKDMask[]={0b110110000,// Corner Cluster
                      0b000011011,
                      0b010111000,// TeeBranch
                      0b010110010,
                      0b000111010,
                      0b010011010,
                      0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,0b101010111,// VeeBranch
                      0b101011111,0b101011111,0b101011111,0b101011111,0b101011111,0b101011111,0b101011111,
                      0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,0b111010101,
                      0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,0b101110101,
                      0b011111110,// DiagonalBranch
                      0b110111011,
                      0b011111110,
                      0b110111011
                      };
    int LenSTWithoutD = sizeof(UCPatternsSTWithoutD)/sizeof(int);
    int LenSTWithD = sizeof(UCPatternsSTWithD)/sizeof(int);
    int LenKWithoutD = sizeof(UCPatternsKWithoutD)/sizeof(int);
    int LenKWithD = sizeof(UCPatternsKWithD)/sizeof(int);
    switch (type)
    {
    case 'S':
    case 'T':
        for(int i=0;i<LenSTWithoutD;i++)
        {
            if(pattern == UCPatternsSTWithoutD[i])
                return 1;
        }
        for(int i=0;i<LenSTWithD;i++)
        {
            int tmp = pattern & UCPatternsSTDMask[i];
            if(tmp == UCPatternsSTWithD[i])
                return 1;
        }
        break;
    case 'K':
        for(int i=0;i<LenKWithoutD;i++)
        {
            if(pattern == UCPatternsKWithoutD[i])
                return 1;
        }
        for(int i=0;i<LenKWithD;i++)
        {
            int tmp = pattern & UCPatternsKDMask[i];
            if(tmp == UCPatternsKWithD[i])
                return 1;
        }
        break;
    }
    return 0;
}


int CountSingleDots(unsigned char *ImageData, int ImgHeight, int ImgWidth)
{
    int count = 0;
    int N = 1;
    int ImgHeightNew = ImgHeight + 2*N;
    int ImgWidthNew = ImgWidth + 2*N;
    unsigned char *PaddedImage = new unsigned char[ImgHeightNew*ImgWidthNew];
    PaddedImage = PadImage(ImageData,ImgHeight,ImgWidth,1);

    int n1[]={-1,-1,-1,0,0,1,1,1};
    int n2[]={-1,0,1,-1,1,-1,0,1};

    for(int i=0;i<ImgHeight;i++)
    {
        for(int j=0;j<ImgWidth;j++)
        {
            if(ImageData[i*ImgWidth+j]==255)
            {
                int flag = 0;
                for(int k=0; k<8; k++)
                {
                    if(PaddedImage[(i+N+n1[k])*ImgWidthNew+j+N+n2[k]] == 255)
                        flag = 1;
                }
                if(flag == 0)
                    count ++;
            }
        }
    }

    delete PaddedImage;

    return count;
}


int MorphShrink(unsigned char *ImageData, unsigned char *ImageDataOp, int ImgHeight, int ImgWidth)
{
    // S: Shrinking, T: Thinning, K: Skeletonizing
    int remainPixel = 0;
    int N = 1;
    int ImgHeightNew = ImgHeight + 2*N;
    int ImgWidthNew = ImgWidth + 2*N;
    unsigned char *PaddedImage = new unsigned char[ImgHeightNew*ImgWidthNew];

    //ImageExpandBlack(N,ImageData,PaddedImage,ImgHeight,ImgWidth,1);
    PaddedImage = PadImage(ImageData,ImgHeight,ImgWidth,1);

    for(int i=0;i<ImgHeight;i++)
    {
        for(int j=0;j<ImgWidth;j++)
        {
            PaddedImage[(i+N)*ImgWidthNew+j+N] = ImageData[i*ImgWidth+j];
        }
    }
    unsigned char*Temp = new unsigned char[ImgHeight*ImgWidth];
    unsigned char *PaddedTemp = new unsigned char[ImgHeightNew*ImgWidthNew];
    unsigned char*FinalOp = new unsigned char[ImgHeight*ImgWidth];
    memset(Temp,0,ImgHeight*ImgWidth);
    memset(FinalOp,0,ImgHeight*ImgWidth);
    // Stage 1
    for(int i=0;i<ImgHeight;i++)
    {
        for(int j=0;j<ImgWidth;j++)
        {
            if(PaddedImage[(i+N)*ImgWidthNew+j+N] == 255)
            {
                int pattern = 0b00000000;
                for(int m=-1; m<=1; m++)
                {
                    for(int n=-1; n<=1; n++)
                    {
                        pattern = pattern<<1;
                        if(PaddedImage[(i+N+m)*ImgWidthNew+j+N+n]==255)
                            pattern += 1;
                    }
                }

                /*for(int m=i-1; m<=i+1; m++)
                {
                    for(int n=i-1; n<=i+1; n++)
                    {
                        pattern = pattern<<1;
                        if(PaddedImage[(N+m)*ImgWidthNew+N+n]==255)
                            pattern += 1;
                    }
                }*/
                int hit = CheckCondPattern(pattern,'S');
                if(hit==1)
                    Temp[i*ImgWidth+j] = 255;
                else
                    Temp[i*ImgWidth+j] = 0;
            }
        }
    }
    //WriteFile("Temp.raw",Temp,ImgHeight,ImgWidth,1);
    //ImageExpandBlack(N,Temp,PaddedTemp,ImgHeight,ImgWidth,1);
    PaddedTemp = PadImage(Temp,ImgHeight,ImgWidth,1);
    // Stage 2
    for(int i=0;i<ImgHeight;i++)
    {
        for(int j=0; j<ImgWidth; j++)
        {
            if(Temp[i*ImgWidth+j]==255)
            {
                int pattern = 0b00000000;
                for(int m=-1; m<=1; m++)
                {
                    for(int n=-1; n<=1; n++)
                    {
                        pattern = pattern<<1;
                        if(PaddedTemp[(i+N+m)*ImgWidthNew+j+N+n]==255)
                            pattern += 1;
                    }
                }
                int hit = CheckUncondPattern(pattern,'S');
                if(hit==1)
                    FinalOp[i*ImgWidth+j] = 0;
                else
                    FinalOp[i*ImgWidth+j] = 255;
            }
        }
    }
    //WriteImageToFile("FinalOp.raw",FinalOp,ImgHeight,ImgWidth,1);
    for(int i=0;i<ImgHeight;i++)
    {
        for(int j=0;j<ImgWidth;j++)
        {
            if(FinalOp[i*ImgWidth+j]==255)
                ImageDataOp[i*ImgWidth+j] = 0;
            else
                ImageDataOp[i*ImgWidth+j] = ImageData[i*ImgWidth+j];
            if(ImageDataOp[i*ImgWidth+j] == 255)
                remainPixel ++;
        }
    }

    delete PaddedImage;
    delete Temp;
    delete PaddedTemp;
    delete FinalOp;
    return remainPixel;
}
