// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #2 Prob1a
// Date: February 7, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include "Headers.h"

using namespace std;

int main(int argc, char* argv[])
{
    FILE *file;
    int ImgWidth = atoi(argv[4]);
	int ImgHeight = atoi(argv[5]);
	int BytesPerPixel = atoi(argv[6]);
	//int Size = ImgHeight;

	unsigned char* ImageData = new unsigned char [ ImgHeight*ImgWidth*BytesPerPixel ];
	unsigned char* ImageDataOp = new unsigned char [ ImgHeight*ImgWidth*BytesPerPixel ];
	unsigned char* ImageDataOpNew = new unsigned char [ ImgHeight*ImgWidth*BytesPerPixel ];

	//unsigned char ImageDataOp3D [ImgHeight][ImgWidth][BytesPerPixel];

	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(ImageData, sizeof(unsigned char),  ImgHeight*ImgWidth*BytesPerPixel ,  file);
	fclose(file);

    unsigned char *** ImageData3D = NULL;
    ImageData3D = Convert1dto3d(ImageData, ImgHeight, ImgWidth, BytesPerPixel);

    unsigned char *** ImageDataOp3D = NULL;
    ImageDataOp3D = Convert1dto3d(ImageDataOp, ImgHeight, ImgWidth, BytesPerPixel);

    unsigned char *** ImageDataOp3DNew = NULL;
    ImageDataOp3DNew = Convert1dto3d(ImageDataOpNew, ImgHeight, ImgWidth, BytesPerPixel);
    cout<< "Flag 1"<<endl;

    int NewHeight = 0 ;
    int NewWidth = 0;
    for (int i = 0 ; i < ImgHeight  ; i++)
    {
        for (int j = 0 ; j < ImgWidth  ; j++)
        {
            for (int k = 0 ; k < BytesPerPixel ; k++)
            {
                double u = double(i)/256;
                double v = double(j)/256;
                u = u-1;
                v = v-1;
                double x = 0 ;
                double y = 0 ;
                if (sqrt(u*u + v*v) <= 1)
                {
                    x = ((0.5 * (sqrt(2 + (u * u) - (v * v) + 2 * sqrt(2) * u))) - (0.5 * (sqrt(2 + (u * u) - (v * v) - 2 * sqrt (2) * u))) + 1)*256;
                    y = ((0.5 * (sqrt(2 - (u * u) + (v * v) + 2 * sqrt(2) * v))) - (0.5 * (sqrt(2 - (u * u) + (v * v) - 2 * sqrt (2) * v))) + 1)*256;
                    if(x >= 511 )
                        NewHeight = floor(x) - 1;
                    else
                        NewHeight = floor(x);
                    if (y >= 511)
                        NewWidth = floor(y) - 1 ;
                    else
                        NewWidth = floor(y) ;
                    float DeltaHeight = x - NewHeight;
                    float DeltaWidth = y - NewWidth;
                    ImageDataOp3D[i][j][k] = ((1 - DeltaHeight) * (1 - DeltaWidth) * ImageData3D[NewHeight][NewWidth][k] +
                                            (DeltaHeight * (1 - DeltaWidth)) * ImageData3D[NewHeight +1][NewWidth ][k] +
                                            ((1 - DeltaHeight) * DeltaWidth) * ImageData3D[NewHeight ][NewWidth + 1 ][k] +
                                            (DeltaHeight * DeltaWidth) * ImageData3D[NewHeight + 1][NewWidth + 1][k]);
                }
            }
        }
    }
    ImageDataOp = Convert3dTo1d(ImageDataOp3D, ImgHeight, ImgWidth, BytesPerPixel);

    NewHeight = 0 ;
    NewWidth = 0;
    for (int i = 0 ; i < ImgHeight  ; i++)
    {
        for (int j = 0 ; j < ImgWidth  ; j++)
        {
            for (int k = 0 ; k < BytesPerPixel ; k++)
            {
                double x = double (i) / 256;
                x = x - 1 ;
                double y = double (j) / 256;
                y = y - 1 ;
                //cout<<x<<"  "<<y<<endl;
                double a = 0 ;
                double b = 0 ;
                    a = (x * (sqrt(1 - (y * y)/2))+1)*256;
                    b = (y * (sqrt(1 - (x * x)/2))+1)*256;
                    if(a >= 511 )
                        NewHeight = floor(a) - 1;
                    else
                        NewHeight = floor(a);
                    float DeltaHeight = a - NewHeight;
                    if(b >= 511 )
                        NewWidth = floor(b) - 1;
                    else
                        NewWidth = floor(b);
                    float DeltaWidth = b - NewWidth;
                    ImageDataOp3DNew[i][j][k] = ((1 - DeltaHeight) * (1 - DeltaWidth) * ImageDataOp3D[NewHeight][NewWidth][k] +
                                            (DeltaHeight * (1 - DeltaWidth)) * ImageDataOp3D[NewHeight +1][NewWidth ][k] +
                                            ((1 - DeltaHeight) * DeltaWidth) * ImageDataOp3D[NewHeight ][NewWidth + 1 ][k] +
                                            (DeltaHeight * DeltaWidth) * ImageDataOp3D[NewHeight + 1][NewWidth + 1][k]);

            }
        }
    }
    ImageDataOpNew = Convert3dTo1d(ImageDataOp3DNew, ImgHeight, ImgWidth, BytesPerPixel);

    if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(ImageDataOp, sizeof(unsigned char), ImgWidth*ImgHeight*BytesPerPixel , file);
	fclose(file);

	if (!(file=fopen(argv[3],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(ImageDataOpNew, sizeof(unsigned char), ImgWidth*ImgHeight*BytesPerPixel , file);
	fclose(file);
    delete [] ImageData;
    delete [] ImageDataOp;

	return 0 ;
}
