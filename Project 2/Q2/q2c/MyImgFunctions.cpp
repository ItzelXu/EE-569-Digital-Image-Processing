//
//// ------------------------------------------------------------------------------------
//// EE569 Homework Assignment #2 Prob 3 Shrinking
//// Date: February 16, 2018
//// Name : Pranav Gundewar
//// USC-ID : 4463612994
//// email : gundewar@usc.edu
//// ------------------------------------------------------------------------------------
//
//#include <iostream>
//#include <fstream>
//#include <math.h>
//#include <algorithm>
//#include <cstdlib>
//#include "string.h"
//#include <stdlib.h>
//#include "Headers.h"
//#include "MyImgFunctions.h"
//
//using namespace std;
//
//unsigned char * PadImage(unsigned char* Imagedata, int ImgHeight, int ImgWidth, int n)
//{
//    //int n = m ;
//    int ImgHeightNew = ImgHeight + 2 * n ;
//    int ImgWidthNew = ImgWidth + 2 * n ;
//
//    unsigned char ** ImageData = NULL;
//    ImageData = Allocate2d(ImageData, ImgHeight, ImgWidth);
//    ImageData = Convert1dTo2d(Imagedata, ImgHeight, ImgWidth);
//
//    unsigned char ** ImageDataNew = NULL;
//    ImageDataNew = Allocate2d(ImageDataNew, ImgHeightNew, ImgWidthNew);
//
//    for ( int p = 0 ; p < n+1 ; p++)
//    {
//        for (int j = 0 ; j < ImgWidth ; j++)
//        {
//            ImageDataNew[p][j+n] = 0;//ImageData[0][j];
//            ImageDataNew[ImgHeightNew-p-1][j+n] = 0;//ImageData[ImgHeight - 1][j];
//        }
//    }
//
//    for (int i = 0 ; i < ImgHeight ; i++)
//    {
//        for (int j = 0 ; j < ImgWidth ; j++)
//        {
//			ImageDataNew[i+n][j+n] = ImageData[i][j];
//        }
//    }
//
//    for ( int p = 0 ; p < n ; p++)
//    {
//        for (int i = 0 ; i < ImgHeightNew ; i++)
//        {
//            ImageDataNew[i][p] = 0;//ImageDataNew[i][n];
//            ImageDataNew[i][ImgWidthNew -p-1] = 0;//ImageDataNew[i][ImgWidth-1];
//        }
//    }
//    unsigned char * ImagedataNew = new unsigned char [ImgHeightNew * ImgWidthNew];
//    ImagedataNew = Convert2dTo1d(ImageDataNew, ImgHeightNew, ImgWidthNew);
//    std::cout<<"Image has been padded successfully!"<<std::endl;
//    return ImagedataNew;
//}
//
//int CheckCondPattern(int pat, char process)
//{
//    int ss = 0, se = 57;
//    int ts = 16, te = 61;
//    int ks = 26, ke = 65;
//    unsigned char CondPatterns[]=  { 0b01000000,0b00010000,0b00000100,0b00000001, //S
//                                     0b10000000,0b00100000,0b00001000,0b00000010,   //S
//                                     0b11000000,0b01100000,0b00110000,0b00011000,0b00001100,0b00000110,0b00000011,0b10000001, //S
//                                     0b10110000,0b10100001,0b01101000,0b11000010,   //ST
//                                     0b11100000,0b00111000,0b00001110,0b10000011,   //ST
//                                     0b10110001,0b01101100,                         //ST
//                                     0b11110000,0b11100001,0b01111000,0b00111100,0b00011110,0b00001111,0b10000111,0b11000011, //STK
//                                     0b11110001,0b01111100,0b00011111,0b11000111,   //STK
//                                     0b11100011,0b11111000,0b00111110,0b10001111,   //STK
//                                     0b11110011,0b11100111,0b11111100,0b11111001,0b01111110,0b00111111,0b10011111,0b11001111, //STK
//                                     0b11110111,0b11111101,0b01111111,0b11011111,   //STK
//                                     0b11000001,0b01110000,0b00011100,0b00000111,   //STK
//                                     0b10100000,0b00101000,0b00001010,0b10000010,   //TK
//                                     0b11111011,0b11111110,0b10111111,0b11101111};// K
//    switch (process)
//    {
//    case 'S':
//        for(int i=ss;i<=se;i++)
//        {
//            if(pat == CondPatterns[i])
//            return 1;
//        }
//        break;
//    case 'T':
//        for(int i=ts;i<=te;i++)
//        {
//            if(pat == CondPatterns[i])
//            return 1;
//        }
//        break;
//    case 'K':
//        for(int i=ks;i<=ke;i++)
//        {
//            if(pat == CondPatterns[i])
//            return 1;
//        }
//        break;
//    }
//
//    return 0;
//}
//
//int CheckUnCondPattern(int pat, char process)
//{
//
//    unsigned char UnCondPatternsST[]=  {0b01000000,0b00010000, //spur
//                                        0b00000010,0b10000000, //single 4 connection
//                                        0b11000000,0b01100000,0b00110000,0b00011000,0b00001100,0b00000110,0b00000011,0b10000001, //L cluster
//                                        0b01101000,0b10110000,0b10100001,0b11000010,    //4-connected offset
//                                        0b11000100,0b00110001,0b01000110,0b10010001,    //spur corner cluster A = 0 B = 1
//                                        0b01100100,0b00011001,0b01001100,0b00010011,    //spur corner cluster A = 1 B = 0
//                                        0b11100100,0b00111001,0b01001110,0b10010011,    //spur corner cluster A = 1 B = 1
//                                        };
//
//    unsigned char UnCondPatternsSTWithD1[]=   { 0b11111111, //corner cluster
//                                                0b10111100,0b11101001,0b11001011,0b10011110,0b01111010,0b00101111,0b10100111,0b11110010, //Tee Branch
//                                                0b11111010,0b10111110,0b10101111,0b11101011,    //Vee Branch 0 1 0
//                                                0b11111011,0b11111110,0b10111111,0b11101111,    //Vee Branch 0 1 1
//                                                0b11111100,0b00111111,0b11001111,0b11110011,    //Vee Branch 1 0 0
//                                                0b11111110,0b01111111,0b11011111,0b11110111,    //Vee Branch 1 0 1
//                                                0b11111110,0b10111111,0b11101111,0b11111011,    //Vee Branch 1 1 0
//                                                0b11111111,0b11111111,0b11111111,0b11111111,    //Vee Branch 1 1 1
//                                                0b10110101,0b01101101,0b01011011,0b11010110,    //Diagonal Branch
//                                                };
//
//    unsigned char UnCondPatternsSTWithD0[]=   { 0b00111000, //corner cluster
//                                                0b10101000,0b10101000,0b10001010,0b10001010,0b00101010,0b00101010,0b10100010,0b10100010, //Tee Branch
//                                                0b01010010,0b10010100,0b00100101,0b01001001,    //Vee Branch 0 1 0
//                                                0b01010011,0b11010100,0b00110101,0b01001101,    //Vee Branch 0 1 1
//                                                0b01010100,0b00010101,0b01000101,0b01010001,    //Vee Branch 1 0 0
//                                                0b01010110,0b01010101,0b01010101,0b01010101,    //Vee Branch 1 0 1
//                                                0b01010110,0b10010101,0b01100101,0b01011001,    //Vee Branch 1 1 0
//                                                0b01010111,0b11010101,0b01110101,0b01011101,    //Vee Branch 1 1 1
//                                                0b10100100,0b00101001,0b01001010,0b10010010,    //Diagonal Branch
//                                                };
//
//    int LenSTWithoutD = sizeof(UnCondPatternsST)/sizeof(unsigned char);
//    int LenSTWithD1 = sizeof(UnCondPatternsSTWithD1)/sizeof(unsigned char);
//    int LenSTWithD0 = sizeof(UnCondPatternsSTWithD0)/sizeof(unsigned char);
//    //int LenKWithoutD = sizeof(UCPatternsKWithoutD)/sizeof(int);
//    //int LenKWithD = sizeof(UCPatternsKWithD)/sizeof(int);
//    switch (process)
//    {
//    case 'S':
//    case 'T':
//        for(int i = 0 ; i < LenSTWithoutD ; i++)
//        {
//            if(pat == UnCondPatternsST[i])
//                return 1;
//        }
//        for(int i = 0 ; i < LenSTWithD1 ; i++)
//        {
//            if(pat == UnCondPatternsSTWithD1[i])
//                return 1;
//        }
//        for(int i = 0 ; i < LenSTWithD0 ; i++)
//        {
//            if(pat == UnCondPatternsSTWithD0[i])
//                return 1;
//        }
//        break;
//    /*case 'K':
//        for(int i=0;i<LenKWithoutD;i++)
//        {
//            if(pattern == UCPatternsKWithoutD[i])
//                return 1;
//        }
//        for(int i=0;i<LenKWithD;i++)
//        {
//            int tmp = pattern & UCPatternsKDMask[i];
//            if(tmp == UCPatternsKWithD[i])
//                return 1;
//        }
//        break;*/
//    }
//    return 0;
//}
//
//unsigned char* MorphShrink (unsigned char*Imagedata, int ImgHeight, int ImgWidth)
//{
//    int cntr = 0;
//    int n = 1;
//    int ImgHeightNew = ImgHeight + 2 * n ;
//    int ImgWidthNew = ImgWidth + 2 * n ;
//    unsigned char *ImageData = new unsigned char[ImgHeightNew * ImgWidthNew];
//    ImageData = PadImage(Imagedata, ImgHeight, ImgWidth, n);
//    // shrink conditional mark patterns
//
//    unsigned char CondPattern[58] = { 0b01000000,0b00010000,0b00000100,0b00000001,
//                                    0b10000000,0b00100000,0b00001000,0b00000010,
//                                    0b11000000,0b01100000,0b00110000,0b00011000,0b00001100,0b00000110,0b00000011,0b10000001,
//                                    0b11000001,0b01110000,0b00011100,0b00000111,
//                                    0b10110000,0b10100001,0b01101000,0b11000010,
//                                    0b11100000,0b00111000,0b00001110,0b10000011,
//                                    0b10110001,0b01101100,
//                                    0b11110000,0b11100001,0b01111000,0b00111100,0b00011110,0b00001111,0b10000111,0b11000011,
//                                    0b11110001,0b01111100,0b00011111,0b11000111,
//                                    0b11100011,0b11111000,0b00111110,0b10001111,
//                                    0b11110011,0b11100111,0b11111100,0b11111001,0b01111110,0b00111111,0b10011111,0b11001111,
//                                    0b11110111,0b11111101,0b01111111,0b11011111};
//
//    unsigned char UnCondPatternsST[28]=  {0b01000000,0b00010000, //spur
//                                        0b00000010,0b10000000, //single 4 connection
//                                        0b11000000,0b01100000,0b00110000,0b00011000,0b00001100,0b00000110,0b00000011,0b10000001, //L cluster
//                                        0b01101000,0b10110000,0b10100001,0b11000010,    //4-connected offset
//                                        0b11000100,0b00110001,0b01000110,0b10010001,    //spur corner cluster A = 0 B = 1
//                                        0b01100100,0b00011001,0b01001100,0b00010011,    //spur corner cluster A = 1 B = 0
//                                        0b11100100,0b00111001,0b01001110,0b10010011,    //spur corner cluster A = 1 B = 1
//                                        };
//
//    unsigned char uncon_em [41] = {0b00111000,                                        //corner cluster
//                                 0b11101011, 0b10111110, 0b10111110, 0b11101011, 0b10101111, 0b11111010, 0b11111010, 0b10101111,    //tee branch
//                                 0b01010111, 0b11010101, 0b01110101, 0b01011101,
//                                 0b01010111, 0b11010101, 0b01110101, 0b01011101,
//                                 0b01010111, 0b11010101, 0b01110101, 0b01011101,
//                                 0b01010111, 0b11010101, 0b01110101, 0b01011101,
//                                 0b01010111, 0b11010101, 0b01110101, 0b01011101,
//                                 0b01010111, 0b11010101, 0b01110101, 0b01011101,
//                                 0b01010111, 0b11010101, 0b01110101, 0b01011101,    //vee branch
//                                 0b11101110, 0b10111011, 0b11101110, 0b10111011};
//
//    unsigned char uncon_dc [41] = {  0b00111000,
//                                    0b10101000, 0b10101000, 0b10001010, 0b10001010, 0b00101010, 0b00101010, 0b10100010, 0b10100010,
//                                    0b01010001, 0b00010101, 0b00010101, 0b01000101,
//                                    0b01010010, 0b01010100, 0b00100101, 0b01001001,
//                                    0b01010011, 0b01010101, 0b00110101, 0b01001101,
//                                    0b01010100, 0b10010100, 0b01000101, 0b01010001,
//                                    0b01010101, 0b10010101, 0b01010101, 0b01010101,
//                                    0b01010110, 0b11010100, 0b01100101, 0b01011001,
//                                    0b01010111, 0b11010101, 0b01110101, 0b01011101,
//                                    0b10100100, 0b00101001, 0b01001010, 0b10010010,
//                                    };
//
//    unsigned char ** ImageData2D = NULL;
//    ImageData2D = Allocate2d(ImageData2D, ImgHeightNew, ImgWidthNew);
//    ImageData2D = Convert1dTo2d(ImageData, ImgHeightNew, ImgWidthNew);
//    unsigned char*Temp = new unsigned char[ImgHeightNew*ImgWidthNew];
//    //unsigned char *PadTemp = new unsigned char[ImgHeightNew*ImgWidthNew];
//    unsigned char*FinalOp = new unsigned char[ImgHeight*ImgWidth];
//    memset(FinalOp,0,ImgHeight*ImgWidth);
//    memset(Temp,0,ImgHeightNew*ImgWidthNew);
//
//    for ( int l = 0 ; l < 25 ; l++){
//    // Stage 1
//    cntr = 0;
//    memset(Temp,0,ImgHeightNew*ImgWidthNew);
//    for (int i = 1 ; i < ImgHeightNew - 1 ; i++)
//    {
//        for (int j = 1 ; j < ImgWidthNew - 1; j++)
//        {
//            unsigned char ar[8] = {0};
//            if (ImageData2D[i][j] == 1)
//            {
//                ar[0] = ImageData2D[i][j+1];
//                ar[1] = ImageData2D[i-1][j+1];
//                ar[2] = ImageData2D[i-1][j];
//                ar[3] = ImageData2D[i-1][j-1];
//                ar[4] = ImageData2D[i][j-1];
//                ar[5] = ImageData2D[i+1][j-1];
//                ar[6] = ImageData2D[i+1][j];
//                ar[7] = ImageData2D[i+1][j+1];
//                unsigned char mask = 0b10000000;
//                unsigned char pat = 0b00000000;
//                for (int k = 0 ; k < 8 ; k++)
//                {
//                    //cout<< (int)ar[k]<<endl;
//                    if((int)ar[k] == 1)
//                    {
//                        pat = mask | pat ;
//                        mask = mask >> 1;
//                    }
//                    else
//                        mask = mask >> 1;
//                }
//                //cout<<"Pattern: "<<(int)pat<<endl;
//                //int hit = CheckCondPattern(pat,'S');
//                for(int k = 0 ; k < 58 ; k++)
//                {
//                    if(pat==CondPattern[k])
//                    {
//                        Temp[i*ImgWidthNew + j] = 1;
//                        cntr ++;
//                        break ;
//                    }
//                    else
//                        Temp[i*ImgWidthNew + j] = 0;
//                }
//            }
//        }
//    }
//    cout<<l<<"  "<<cntr<<endl;
//    /*for(int o = 0 ; o < ImgHeightNew*ImgWidthNew ; o++)
//    {
//        Temp[o] = 255 * Temp[o];
//    }*/
//    WriteFile("Temp.raw", Temp, ImgHeightNew, ImgWidthNew, 1);
//    //PadTemp = PadImage(Temp, ImgHeight, ImgWidth, 1);
//    unsigned char ** PadTemp2D = NULL;
//    PadTemp2D = Allocate2d(PadTemp2D, ImgHeightNew, ImgWidthNew);
//    PadTemp2D = Convert1dTo2d(Temp,ImgHeightNew, ImgWidthNew);
//    // Stage 2
//    int cntr2 = 0;
//    //memset(FinalOp,0,ImgHeight*ImgWidth);
//    for (int i = 1 ; i < ImgHeightNew - 1 ; i++)
//    {
//        for (int j = 1 ; j < ImgWidthNew - 1; j++)
//        {
//            //FinalOp [(i-1) * ImgWidth + j - 1] = Imagedata [(i-1) * ImgWidth + j - 1];
//
//            int tp = 0;
//            unsigned char ar[8] = {0};
//            if (PadTemp2D[i][j] == 1)
//            {
//                ar[0] = PadTemp2D[i][j+1];
//                ar[1] = PadTemp2D[i-1][j+1];
//                ar[2] = PadTemp2D[i-1][j];
//                ar[3] = PadTemp2D[i-1][j-1];
//                ar[4] = PadTemp2D[i][j-1];
//                ar[5] = PadTemp2D[i+1][j-1];
//                ar[6] = PadTemp2D[i+1][j];
//                ar[7] = PadTemp2D[i+1][j+1];
//                unsigned char mask = 0b10000000;
//                unsigned char pat = 0b00000000;
//                for (int k = 0 ; k < 8 ; k++)
//                {
//                    //cout<<(int)ar[k]<<endl;
//                    if((int)ar[k] == 1)
//                    {
//                        pat = mask | pat ;
//                        mask = mask >> 1;
//                    }
//                    else
//                        mask = mask >> 1;
//                }
//                //cout<<"Pattern: "<<(int)pat<<endl;
//                //int hit = CheckUnCondPattern(pat,'S');
//
//                for(int p = 0 ; p < 28 ; p++)
//                {
//                    if(pat == UnCondPatternsST[p])
//                        tp = 1;
//                }
//
//                for (int q = 0 ; q < 41 ; q++)
//                {
//                    unsigned char test = pat & uncon_em[q];
//                    if(test == uncon_dc[q])
//                        tp = 1;
//                }
//
//                if(tp == 1 )
//                {
//                    FinalOp[(i-1)*ImgWidth + j - 1] = 1;
//                }
//                else
//                {
//                    FinalOp[(i-1)*ImgWidth + j - 1] = 0;
//                    cntr2 ++;
//                }
//
//            }
//            /*else
//            {
//                FinalOp[(i-1)*ImgWidth + j - 1] = 0;
//            }*/
//        }
//    }
//    //cout<<"Hits: "<<cntr2<<endl;
//    /*for (int y = 0 ; y < ImgHeight * ImgWidth ; y++)
//    {
//        Imagedata [y] = FinalOp[y];
//    }*/
//    ImageData = PadImage(FinalOp, ImgHeight, ImgWidth,1);
//    ImageData2D = Convert1dTo2d(ImageData, ImgHeightNew, ImgWidthNew);
//    cout<<"Remaining Pixels: "<<cntr2<<endl;
//
//    }
//
//    return FinalOp;
//
//}
//
