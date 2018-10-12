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
#include <vector>
#include <algorithm>
#include "Headers.h"
#include "MyImgFunctions.h"

using namespace std;

int main(int argc, char* argv[])
{
    int ImgHeight = 372;
    int ImgWidth = 372;
    int BytesPerPixel = 1;

    unsigned char* ImageData = new unsigned char[ImgHeight*ImgWidth];
    unsigned char* ImageData1 = new unsigned char[ImgHeight*ImgWidth];
    unsigned char* ImageDataOp = new unsigned char[ImgHeight*ImgWidth];
    ReadFile("board.raw",ImageData,ImgHeight,ImgWidth,1);
    //ReadFile("board.raw",ImageDataNew,ImgHeight,ImgWidth,1);

    ImageDataOp = ConvertGreyToBinary(ImageData,ImgHeight,ImgWidth);
    ImageData1 = ConvertGreyToBinary(ImageData,ImgHeight,ImgWidth);
    for(int i = 0 ; i < ImgHeight*ImgWidth ; i++)
    {
        if(ImageData[i] <= 127)
            ImageData1[i] = 255 ;
        else
            ImageData1[i] = 0 ;
    }
    int Final = 0;
    int Start = MorphShrink(ImageDataOp,ImageData,ImgHeight,ImgWidth);
    //cout<<Start; //printf("%d ",Start);
    int flag = 0;

    while(Start != Final)
    {
        Final = Start;
        //cout<<"\t"<<Start;
        if(flag == 1)
        {
            Start = MorphShrink(ImageDataOp,ImageData,ImgHeight,ImgWidth);
            flag = 0;
        }
        else
        {
            Start = MorphShrink(ImageData,ImageDataOp,ImgHeight,ImgWidth);
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
        WriteFile("board_out.raw",ImageDataOp,ImgHeight,ImgWidth,1);
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
        WriteFile("board_out.raw",ImageData,ImgHeight,ImgWidth,1);
    }
    cout<<"Number of Pieces: "<<StarNum<<endl;

    int edgeh1[16]= {0};
    int edgew1[16]= {0};
    int edgeh2[16]= {0};
    int edgew2[16]= {0};
    int ar[16][4] = {0};
    //memset(edges,0,50);
    GetEdges(ImageData1,edgeh1, edgew1,edgeh2, edgew2, ImgHeight, ImgWidth);
    int os = 22;
    int cntr = 16;
    unsigned char** ImageDataNew = NULL;
    ImageDataNew = Convert1dTo2d(ImageData1,ImgHeight, ImgWidth);
    for(int a = 0 ; a < 16; a++)
    {
        //cout<<edgeh1[a]<<" "<<edgew1[a]<<" "<<edgeh2[a]<<" "<<edgew2[a]<<endl;
        if (ImageDataNew[(int)edgeh1[a]-2][(int)edgew1[a]+os] == 255)
            ar[a][0] = 2;
        else if(ImageDataNew[(int)edgeh1[a]][(int)edgew1[a]+os] == 255)
            ar[a][0] = 1;
        else
             ar[a][0] = 0;

        if (ImageDataNew[(int)edgeh1[a]+os][(int)edgew2[a]+2] == 255)
            ar[a][1] = 2;
        else if (ImageDataNew[(int)edgeh1[a]+os][(int)edgew2[a]] == 255)
            ar[a][1] = 1;
        else
            ar[a][1] = 0;

        if (ImageDataNew[(int)edgeh1[a]+47][(int)edgew1[a]+os] == 255)
            ar[a][2] = 2;
        else if (ImageDataNew[(int)edgeh1[a]+45][(int)edgew1[a]+os] == 255)
            ar[a][2] = 1;
        else
            ar[a][2] = 0;

        if (ImageDataNew[(int)edgeh1[a]+os][(int)edgew1[a]-2] == 255)
            ar[a][3] = 2;
        else if (ImageDataNew[(int)edgeh1[a]+os][(int)edgew1[a]] == 255)
            ar[a][3] = 1;
        else
            ar[a][3] = 0;
    }
    cout<<"Pattern for all pieces:"<<endl;
    for(int a = 0 ; a < 16; a++)
    {
        cout<<ar[a][0]<<" "<<ar[a][1]<<" "<<ar[a][2]<<" "<<ar[a][3]<<endl;
    }
    int r[16] = {0};
    for(int i = 0 ; i < 15; i++)
    {
        for(int j = i+1 ; j < 16; j++)
        {
            vector<int> c;
            vector<int> d;
            for(int x = 0 ; x < 4 ; x ++)
            {
                c.push_back(ar[i][x]);
                d.push_back(ar[j][x]);
            }
            int p = c[2];
            c[2] = c[0];
            c[0] = p;

            if(c == d)
            {
                if(r[i]==1 and r[j]==1)
                    cntr = cntr;
                else
                {
                    r[i] = 1 ; r[j] = 1 ;
                    cout<<"Match: "<<i+1<<" "<<j+1<<endl;
                    cntr --;
                }
            }
            p = c[2];
            c[2] = c[0];
            c[0] = p;
            if(c == d)
            {
                if(r[i]==1 and r[j]==1)
                    cntr = cntr;
                else
                {
                    r[i] = 1 ; r[j] = 1 ;
                    cout<<"Match: "<<i+1<<" "<<j+1<<endl;
                    cntr --;
                }
            }

            rotate(c.begin(), c.begin()+1, c.end());
            if(c == d)
            {
                if(r[i]==1 and r[j]==1)
                    cntr = cntr;
                else
                {
                    r[i] = 1 ; r[j] = 1 ;
                    cout<<"Match: "<<i+1<<" "<<j+1<<endl;
                    cntr --;
                }
            }
            rotate(c.begin(), c.begin()+1, c.end());
            if(c == d)
            {
                if(r[i]==1 and r[j]==1)
                    cntr = cntr;
                else
                {
                    r[i] = 1 ; r[j] = 1 ;
                    cout<<"Match: "<<i+1<<" "<<j+1<<endl;
                    cntr --;
                }
            }
            rotate(c.begin(), c.begin()+1, c.end());
            if(c == d)
            {
                if(r[i]==1 and r[j]==1)
                    cntr = cntr;
                else
                {
                    r[i] = 1 ; r[j] = 1 ;
                    cout<<"Match: "<<i+1<<" "<<j+1<<endl;
                    cntr --;
                }
            }
        }
    }
    cout<<"Unique pieces: "<<cntr<<endl;

    delete ImageData;
    delete ImageDataOp;
   	return 0 ;
}
