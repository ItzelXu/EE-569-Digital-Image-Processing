// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #3 Prob 1 Texture Classification
// Date: February 16, 2018
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
    int ImgHeight = 128;
    int ImgWidth = 128;
    int BytesPerPixel = 1;
    int n = 2;
    int ImgHeightNew = ImgHeight + 2 * n;
	int ImgWidthNew = ImgWidth + 2 * n;

    unsigned char* ImageData = new unsigned char[ImgHeight*ImgWidth*BytesPerPixel];
    memset(ImageData, 0, ImgHeight*ImgWidth*BytesPerPixel);
    unsigned char* ImageDataOp = new unsigned char[ImgHeightNew*ImgWidthNew*BytesPerPixel];
    memset(ImageDataOp, 0, ImgHeightNew*ImgWidthNew*BytesPerPixel);
    float featureVector[12][9] = {0};
    double* temp = new double [ImgHeight*ImgWidth*BytesPerPixel];
    memset(temp, 0, ImgHeight*ImgWidth*BytesPerPixel);

    ImageBasics ImgB;
    ImgB.setParameters(ImgHeight, ImgWidth, BytesPerPixel);

    ImageAlgo ImgA;
    ImgA.setParameters(ImgHeight, ImgWidth, BytesPerPixel);

    for(int x = 0 ; x < 12 ; x++)
    {
        char file[20]={0};
        sprintf(file,"texture%d.raw",x+1);
        ImgB.readFile(file,ImageData);

        for (int y = 0 ; y < 9 ; y++)
        {
            ImgA.filter(ImageData, temp, n, y);
            double avg = 0;
            for(int i = 0 ; i < ImgHeight ; i++)
            {
                for(int j = 0 ; j < ImgWidth ; j++)
                {
                    //cout<<temp[i*ImgWidth+j];
                    avg += temp[i*ImgWidth+j]*temp[i*ImgWidth+j];
                }
            }
            avg /= ImgHeight*ImgWidth;
            featureVector[x][y] = avg;
        }
    }

    cout<<"Feature Vector:"<<endl;
    double Min = featureVector[0][0];
    double Max = featureVector[0][0];
    for(int i = 0 ; i < 12 ; i++)
    {
        for(int j = 0 ; j < 9 ; j++)
        {
            if(featureVector[i][j] > Max)
                Max = featureVector[i][j];
            if(featureVector[i][j] < Min)
                Min = featureVector[i][j];
                cout<<featureVector[i][j]<<" ";
        }
        cout<<endl;
    }

    int labels[12] = {0};
    //int oldLabels[12] = {0};
    double centers[4][9] = {0};
    double newCenters[4][9] = {0};
    srand (time(NULL));

    for(int y = 0 ; y < 9 ; y++)
    {
        centers[0][y] = featureVector[0][y];
        centers[1][y] = featureVector[1][y];
        centers[2][y] = featureVector[2][y];
        centers[3][y] = featureVector[7][y];
    }
    cout<<endl;

    for(int itr = 0 ; itr < 200 ; itr++)
    {
        cout<<"Iteration: "<<itr+1<<endl;
        int cnt[4] = {0} ;
        for(int i = 0 ; i < 12 ; i++)
        {
            double dist[4] = {0};
            for(int k = 0 ; k < 4 ; k++)
            {
                for(int j = 0 ; j < 9 ; j++)
                {
                    dist[k] += sqrt((centers[k][j] - featureVector[i][j])*(centers[k][j] - featureVector[i][j])) ;
                }
                //cout<<dist[k]<<endl;
            }

            double D = min(dist[0], min(dist[1], min(dist[2], dist[3])));

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
        }
        int cntr = 0;

        for(int x =  0 ; x < 4 ; x++)
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
        //cout<<"Counter: "<<cntr<<endl;
        if(cntr == 36)
            break;
    }

    cout<<"\nFinal Class Labels:"<<endl;

    cout<<"Images belong to Class Rock: ";
    for(int j = 0 ; j < 12 ; j++)
    {
        if(labels[j] == 0)
            cout<<j+1<<" ";
    }
    cout<<endl;
    cout<<"Images belong to Class Grass: ";
    for(int j = 0 ; j < 12 ; j++)
    {
        if(labels[j] == 1)
            cout<<j+1<<" ";
    }
    cout<<endl;
    cout<<"Images belong to Class Weave: ";
    for(int j = 0 ; j < 12 ; j++)
    {
        if(labels[j] == 2)
            cout<<j+1<<" ";
    }
    cout<<endl;
    cout<<"Images belong to Class Sand: ";
    for(int j = 0 ; j < 12 ; j++)
    {
        if(labels[j] == 3)
            cout<<j+1<<" ";
    }
    cout<<endl;

    delete temp;
    delete ImageDataOp;
    delete ImageData;
    return 0;
}
