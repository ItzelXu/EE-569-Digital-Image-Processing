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

int CheckCondpat(int pat, char type)
{
    int Sb = 0, Se = 57;
    int Tb = 16, Te = 61;
    int Kb = 26, Ke = 65;
    int Cpats[]={0b001010000,0b100010000,0b000010100,0b000010001, //S
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
            if(pat == Cpats[i])
            return 1;
        }
        break;
    case 'T':
        for(int i=Tb;i<=Te;i++)
        {
            if(pat == Cpats[i])
            return 1;
        }
        break;
    case 'K':
        for(int i=Kb;i<=Ke;i++)
        {
            if(pat == Cpats[i])
            return 1;
        }
        break;
    }

    return 0;
}

int CheckUncondpat(int pat, char type)
{
    int UCpatsSTWithoutD[]={0b001010000,0b100010000, // Spur
                      0b000010010,0b000011000, // Single 4-connection
                      0b001011000,0b011010000,0b110010000,0b100110000, //LCluster
                      0b000110100,0b000010110,0b000010011,0b000011001,
                      0b011110000,0b110011000,0b010011001,0b001011010, // 4-connected offset
                      0b011011100,0b001011100,0b011010100, // Spur corner Cluster
                      0b110110001,0b100110001,0b110010001,
                      0b001110110,0b001110100,0b001010110,
                      0b100011011,0b100011001,0b100010011
                      };
    int UCpatsSTWithD[]={0b110110000,// Corner Cluster
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
    int UCpatsSTDMask[]={0b110110000,// Corner Cluster
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
    int UCpatsKWithoutD[]={0b000010001,0b000010100,0b001010000,0b100010000, // Spur
                      0b000010010,0b000011000,0b000110000,0b010010000, // Single 4-connection
                      0b010011000,0b010110000,0b000011010,0b000110010// LCorner
                      };
    int UCpatsKWithD[]={
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
    int UCpatsKDMask[]={0b110110000,// Corner Cluster
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
    int LenSTWithoutD = sizeof(UCpatsSTWithoutD)/sizeof(int);
    int LenSTWithD = sizeof(UCpatsSTWithD)/sizeof(int);
    int LenKWithoutD = sizeof(UCpatsKWithoutD)/sizeof(int);
    int LenKWithD = sizeof(UCpatsKWithD)/sizeof(int);
    switch (type)
    {
    case 'S':
    case 'T':
        for(int i=0;i<LenSTWithoutD;i++)
        {
            if(pat == UCpatsSTWithoutD[i])
                return 1;
        }
        for(int i=0;i<LenSTWithD;i++)
        {
            int tmp = pat & UCpatsSTDMask[i];
            if(tmp == UCpatsSTWithD[i])
                return 1;
        }
        break;
    case 'K':
        for(int i=0;i<LenKWithoutD;i++)
        {
            if(pat == UCpatsKWithoutD[i])
                return 1;
        }
        for(int i=0;i<LenKWithD;i++)
        {
            int tmp = pat & UCpatsKDMask[i];
            if(tmp == UCpatsKWithD[i])
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
                int pat = 0b00000000;
                for(int m=-1; m<=1; m++)
                {
                    for(int n=-1; n<=1; n++)
                    {
                        pat = pat<<1;
                        if(PaddedImage[(i+N+m)*ImgWidthNew+j+N+n]==255)
                            pat += 1;
                    }
                }

                /*for(int m=i-1; m<=i+1; m++)
                {
                    for(int n=i-1; n<=i+1; n++)
                    {
                        pat = pat<<1;
                        if(PaddedImage[(N+m)*ImgWidthNew+N+n]==255)
                            pat += 1;
                    }
                }*/
                int hit = CheckCondpat(pat,'S');
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
                int pat = 0b00000000;
                for(int m=-1; m<=1; m++)
                {
                    for(int n=-1; n<=1; n++)
                    {
                        pat = pat<<1;
                        if(PaddedTemp[(i+N+m)*ImgWidthNew+j+N+n]==255)
                            pat += 1;
                    }
                }
                int hit = CheckUncondpat(pat,'S');
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



void GetEdges(unsigned char* ImageData,int edgeh1[16], int edgew1[16],int edgeh2[16], int edgew2[16], int ImgHeight, int ImgWidth)
{
    int mask1 = 0b000011011;
    int mask2 = 0b000110110;
    int a = 0 ;
    int b = 0 ;
    int pat = 0b00000000;
    for(int i=0;i<ImgHeight;i++)
    {
        for(int j=0;j<ImgWidth;j++)
        {
            if(ImageData[i*ImgWidth+j]==255)
            {
                pat = 0;
                for(int m=-1; m<=1; m++)
                {
                    for(int n=-1; n<=1; n++)
                    {
                        pat = pat<<1;
                        if(ImageData[(i+m)*ImgWidth+j+n]==255)
                            pat += 1;
                    }
                }
                //cout<<pat<<" "<<i<<" "<<j<< endl;
                if (pat == mask1)
                {
                    edgeh1[a] = i;
                    edgew1[a] = j;
                    a ++;
                }
                if (pat == mask2)
                {
                    edgeh2[b] = i;
                    edgew2[b] = j;
                    b ++;
                }
            }

        }
    }
   /* unsigned char** ImageData2D = NULL;
    ImageData2D = Convert1dTo2d(ImageData,ImgHeight,ImgHeight);
    int com = 0b10000011;
    for (int i = 1 ; i < ImgHeight - 1 ; i++)
    {
        for (int j = 1 ; j < ImgWidth - 1; j++)
        {
            unsigned char ar[8] = {0};
            if ((int)ImageData2D[i][j] == 255)
            {
                ar[0] = ImageData2D[i][j+1];
                ar[1] = ImageData2D[i-1][j+1];
                ar[2] = ImageData2D[i-1][j];
                ar[3] = ImageData2D[i-1][j-1];
                ar[4] = ImageData2D[i][j-1];
                ar[5] = ImageData2D[i+1][j-1];
                ar[6] = ImageData2D[i+1][j];
                ar[7] = ImageData2D[i+1][j+1];
                unsigned char mask = 0b10000000;
                unsigned char pat = 0b00000000;
                for (int k = 0 ; k < 8 ; k++)
                {
                    if((int)ar[k] == 255)
                    {
                        pat = mask | pat ;
                        mask = mask >> 1;
                    }
                    else
                        mask = mask >> 1;
                }
                //cout<<pat<<endl;
                if (pat == com)
                {
                    edgeh[a] = i;
                    edgew[a] = j;
                    a ++;
                }
            }
        }
    }*/
}
