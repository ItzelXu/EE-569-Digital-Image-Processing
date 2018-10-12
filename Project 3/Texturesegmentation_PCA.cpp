// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #3 Prob 1 Texture Segmentation
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
    int ImgHeight = 450;
    int ImgWidth = 600;
    int BytesPerPixel = 1;
    int W = 15;

	int data = ImgHeight*ImgWidth;
    int dataDim = 9;
    int clusters = 6;
    int n = 1;

	ImageBasics ImgB;
    ImgB.setParameters(ImgHeight, ImgWidth, BytesPerPixel);

    ImageAlgo ImgA;
    ImgA.setParameters(ImgHeight, ImgWidth, BytesPerPixel);

	unsigned char* ImageData = new unsigned char[ImgHeight*ImgWidth*BytesPerPixel];
    memset(ImageData, 0, ImgHeight*ImgWidth*BytesPerPixel);

    unsigned char* ImageDataOp = new unsigned char[ImgHeight*ImgWidth*BytesPerPixel];
    memset(ImageDataOp, 0, ImgHeight*ImgWidth*BytesPerPixel);

    double** featureVector = new double*[data];
    for(int i = 0; i < data ; i++)
        featureVector[i] = new double [dataDim];
    double** temp = new double*[dataDim];
    for(int i = 0 ; i < dataDim ; i++)
        temp[i] = new double [ImgHeight*ImgWidth];
    ImgB.readFile("comb.raw", ImageData);

    int ImgHeightNew = ImgHeight + 2 * W/2;
	int ImgWidthNew = ImgWidth + 2 * W/2;

    double** tempPad = new double* [dataDim];
    for(int i = 0 ; i < dataDim ; i++)
        tempPad[i] = new double [ImgHeightNew*ImgWidthNew];

    cout<<"Flag"<<endl;
    for(int i = 0 ; i < 9 ; i++)
    {
        cout<<i+1<<endl;
        ImgA.filter(ImageData, temp[i], n, i);
        ImgA.padImageReflectDouble(temp[i], tempPad[i], W/2);
    }

    //unsigned char grayLevel[6] = {0, 51, 102, 153, 204, 255};
    cout<<"Now Segmenting!!"<<endl;

    for(int i = W/2 ; i < ImgHeight + W/2 ; i++)
    {
        for(int j = W/2 ; j < ImgWidth + W/2 ; j++)
        {
            for(int k = 0 ; k <9 ; k++)
            {
                cout<<i<<" "<<j<<" "<<k<<endl;
                featureVector[i*ImgWidth + j][k] = 0;
                double sum = 0;
                for(int x = -W/2 ; x <= W/2 ; x++)
                {
                    for(int y =  -W/2 ; y <= W/2 ; y++)
                    {
                        sum += tempPad[k][(i+x)*ImgWidthNew + (j+y)] * tempPad[k][(i+x)*ImgWidthNew + (j+y)];
                        //sum += temp[k][(i+x)*ImgWidth + (j+y)] * temp[k][(i+x)*ImgWidth + (j+y)] ;
                    }
                }
                sum /= W*W;
                featureVector[(i-W/2)*ImgWidth + j-W/2][k] += sum;
            }
            //cout<<featureVector[i*ImgWidth + j][8]<<" "<<endl;
        }
        //cout<<endl;
    }
    cout<<"Segmentation Done!!"<<endl;
    cout<<featureVector[8][0]<<endl;


    double centers[6][9] = {0};
    double newCenters[6][9] = {0};
    int labels [ImgHeight*ImgWidth] = {0};

    for(int y = 0 ; y < 9 ; y++)
    {
        centers[0][y] = featureVector[100][y];
        centers[1][y] = featureVector[300][y];
        centers[2][y] = featureVector[500][y];
        centers[3][y] = featureVector[138300][y];
        centers[4][y] = featureVector[269500][y];
        centers[5][y] = featureVector[269900][y];
    }

    for(int itr = 0 ; itr < 200 ; itr++)
    {
        cout<<"Iteration: "<<itr+1<<endl;
        int cnt[6] = {0} ;
        double dist[6] = {0};
        for(int i = 0 ; i < ImgHeight*ImgWidth ; i++)
        {
            for(int k = 0 ; k < 6 ; k++)
            {
                for(int j = 0 ; j < 9 ; j++)
                {
                    dist[k] += sqrt((centers[k][j] - featureVector[i][j])*(centers[k][j] - featureVector[i][j]));
                }
            }

        double D = min(dist[0], min(dist[1], min(dist[2], min(dist[3], min(dist[4], min(dist[5], dist[6]))))));

        if(D == dist[0])
            {
                for(int j = 0 ; j < 9 ; j++)
                    newCenters[0][j] += featureVector[i][j];
                cnt[0]++;
                labels[i] = 0;
            }
            if(D == dist[1])
            {
                for(int j = 0 ; j < 9 ; j++)
                    newCenters[1][j] += featureVector[i][j];
                cnt[1]++;
                labels[i] = 1;
            }
            if(D == dist[2])
            {
                for(int j = 0 ; j < 9 ; j++)
                    newCenters[2][j] += featureVector[i][j];
                cnt[2]++;
                labels[i] = 2;
            }
            if(D == dist[3])
            {
                for(int j = 0 ; j < 9 ; j++)
                    newCenters[3][j] += featureVector[i][j];
                cnt[3]++;
                labels[i] = 3;
            }
            if(D == dist[4])
            {
                for(int j = 0 ; j < 9 ; j++)
                    newCenters[4][j] += featureVector[i][j];
                cnt[4]++;
                labels[i] = 4;
            }
            if(D == dist[5])
            {
                for(int j = 0 ; j < 9 ; j++)
                    newCenters[5][j] += featureVector[i][j];
                cnt[5]++;
                labels[i] = 5;
            }
            if(D == dist[6])
            {
                for(int j = 0 ; j < 9 ; j++)
                    newCenters[6][j] += featureVector[i][j];
                cnt[6]++;
                labels[i] = 6;
            }
        }
        int cntr = 0 ;
        for(int x =  0 ; x < 6 ; x++)
        {
            for(int y = 0 ; y < 9 ; y++)
            {
                newCenters[x][y] /= cnt[x];
                cout<<newCenters[x][y]<<" "<<centers[x][y]<<endl;
                if(newCenters[x][y] == centers[x][y])
                    cntr++;
                centers[x][y] = newCenters[x][y];
                newCenters[x][y] = 0 ;
            }
        }

        if(cntr == 54)
            break;
    }
    unsigned char* output = new unsigned char[ImgHeight*ImgWidth];
    for(int i=0; i<ImgHeight*ImgWidth; i++)
    {
        output[i] = graylevel[labels(i)];
    }

    ImgB.writeFile("FinalOp.raw", output);
    delete ImageData;
    delete ImageDataOp;
    return 0 ;
}
