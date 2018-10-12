// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #2 Prob 1 b
// Date: February 10, 2018
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
    //FILE *file;
    int ImgWidth = atoi(argv[5]);
	int ImgHeight = atoi(argv[6]);
	int BytesPerPixel = atoi(argv[7]);
	int ImgHeightNew = 1600;//ImgHeight + 600 ;
	int ImgWidthNew = 2000;//ImgWidth + 1000 ;

	unsigned char* ImageDatal = new unsigned char [ ImgHeight*ImgWidth*BytesPerPixel ];
	unsigned char* ImageDatam = new unsigned char [ ImgHeight*ImgWidth*BytesPerPixel ];
	unsigned char* ImageDatar = new unsigned char [ ImgHeight*ImgWidth*BytesPerPixel ];
	unsigned char* ImageDataOp = new unsigned char [ ImgHeightNew*ImgWidthNew*BytesPerPixel ];
	ReadFile(argv[1], ImageDatal, ImgHeight, ImgWidth, BytesPerPixel);
	ReadFile(argv[2], ImageDatam, ImgHeight, ImgWidth, BytesPerPixel);
	ReadFile(argv[3], ImageDatar, ImgHeight, ImgWidth, BytesPerPixel);

	unsigned char *** ImageData3Dl = NULL;
    ImageData3Dl = Convert1dto3d(ImageDatal, ImgHeight, ImgWidth, BytesPerPixel);

    unsigned char *** ImageData3Dm = NULL;
    ImageData3Dm = Convert1dto3d(ImageDatam, ImgHeight, ImgWidth, BytesPerPixel);

    unsigned char *** ImageData3Dr = NULL;
    ImageData3Dr = Convert1dto3d(ImageDatar, ImgHeight, ImgWidth, BytesPerPixel);

    unsigned char *** ImageDataOp3D = NULL;
    ImageDataOp3D = Convert1dto3d(ImageDataOp, ImgHeightNew, ImgWidthNew, BytesPerPixel);

	/*double Mask1[1][3] = {0.3722, -0.0096, 141.2700};
	double Mask2[1][3] = {-0.0067, 0.8299, 20.1573};
	double Mask3[1][3] = {-0.0001, 0, 0.9423};*/

	/*double Mask1[1][3] = {0.880723, -0.00707328, 21.392};
	double Mask2[1][3] = {-0.0102191, 0.394997, 149.923};
	double Mask3[1][3] = {-2.73489e-05, -0.000159115, 1};*/

	/*double Mask1[1][3] = {0.419449, -0.275449, 73.3546};
	double Mask2[1][3] = {0.00113844,0.178761, -18.6054};
	double Mask3[1][3] = {3.11472e-05, -0.000691099, 1};*/

	/*double Mask1[1][3] = {0.525034, -0.344785, 93.3907};
	double Mask2[1][3] = {0.00142501,0.223759, 44.124};
	double Mask3[1][3] = {3.89876e-05, -0.000865064, 1};*/ //final

	long double Mask1[1][3] = {0.5240058692077,	-0.0115748061743, -207.6811251316429};
	long double Mask2[1][3] = {-0.1590200780123, 0.7110449886249, 6.2856980157611};
	long double Mask3[1][3] = {-0.0005379881325, -0.0000154118279, 1.2154116788525};

	//cout<<Mask3[0][0]<<" "<<Mask3[0][1]<<" "<<Mask3[0][2]<<endl;
	int NewHeight = 0 ;
    int NewWidth = 0 ;
    float DeltaHeight = 0 ;
    float DeltaWidth = 0 ;

    cout<< "Flag 1"<<endl;



    for (int i = 0 ; i < ImgHeightNew  ; i++)
    {
        for (int j = 0 ; j < ImgWidthNew  ; j++)
        {
            for (int k = 0 ; k < BytesPerPixel ; k++)
            {
                double x = 0 , y = 0;
            	x = (Mask1[0][0]*i + Mask1[0][1]*j +  Mask1[0][2]*1) / (Mask3[0][0]*i +  Mask3[0][1]*j +  Mask3[0][2] * 1) ;
            	y = (Mask2[0][0]*i + Mask2[0][1]*j +  Mask2[0][2]*1) / (Mask3[0][0]*i +  Mask3[0][1]*j +  Mask3[0][2] * 1) ;
            	//cout<<x<<"    "<<y<<endl;
            	/*if(x > 0 && x < 639 && y > 0 && y < 479)
                {
                    //cout<< "Bilinear Interpolation: "<<x<<"  "<<y<<endl;
					NewHeight = floor(x);
            		NewWidth = floor(y);
            		DeltaHeight = x - NewHeight;
            		DeltaWidth = y - NewWidth;
            		ImageDataOp3D[i][j][k] = ((1 - DeltaHeight) * (1 - DeltaWidth) * ImageData3Dl[NewHeight][NewWidth][k] +
                                            (DeltaHeight * (1 - DeltaWidth)) * ImageData3Dl[NewHeight +1][NewWidth ][k] +
                                            ((1 - DeltaHeight) * DeltaWidth) * ImageData3Dl[NewHeight ][NewWidth + 1 ][k] +
                                            (DeltaHeight * DeltaWidth) * ImageData3Dl[NewHeight + 1][NewWidth + 1][k]);
                }*/
                if(x > 0 && x < 479 && y > 0 && y < 639)
                ImageDataOp3D[j][i][k] = ImageData3Dl[int(y)][int(x)][k];
            }
        }
    }


    cout<<"Flag 2"<<endl;

    long double Mask11[1][3] = {1.168142525442,   0.009061898202,  -1179.894859973706};
	long double Mask21[1][3] = {0.176676986862,   1.092133279563,  -422.727997963135};
	long double Mask31[1][3] = {0.000582924847,   0.000029862938,   0.405535493772};

    /*double Mask1[1][3] = {-0.167234, -0.468756, 393.851};
	double Mask2[1][3] = {-0.0637066,-0.197984, 165.875};
	double Mask3[1][3] = {-0.000329222, -0.00129497, 1};*/
	for (int i = 0 ; i < ImgHeightNew  ; i++)
    {
        for (int j = 0 ; j < ImgWidthNew  ; j++)
        {
            for (int k = 0 ; k < BytesPerPixel ; k++)
            {
            	double x = 0 , y = 0;
            	x = (Mask11[0][0]*i + Mask11[0][1]*j +  Mask11[0][2]*1) / (Mask31[0][0]*i +  Mask31[0][1]*j +  Mask31[0][2] * 1) ;
            	y = (Mask21[0][0]*i + Mask21[0][1]*j +  Mask21[0][2]*1) / (Mask31[0][0]*i +  Mask31[0][1]*j +  Mask31[0][2] * 1) ;
            	//cout<<x<<"    "<<y<<endl;
            	if(x>0 && x<479 && y>0 && y <639)
            	{
					//cout<< "Bilinear Interpolation: "<<x<<"  "<<y<<endl;
					//cout<<"Bilinear: "<<i<<" "<<j<<endl;
					NewHeight = floor(x);
            		NewWidth = floor(y);
            		DeltaHeight = x - NewHeight;
            		DeltaWidth = y - NewWidth;
            		ImageDataOp3D[i][j][k] = ((1 - DeltaHeight) * (1 - DeltaWidth) * ImageData3Dr[NewHeight][NewWidth][k] +
                                            (DeltaHeight * (1 - DeltaWidth)) * ImageData3Dr[NewHeight +1][NewWidth ][k] +
                                            ((1 - DeltaHeight) * DeltaWidth) * ImageData3Dr[NewHeight ][NewWidth + 1 ][k] +
                                            (DeltaHeight * DeltaWidth) * ImageData3Dr[NewHeight + 1][NewWidth + 1][k]);
            	}
                /*if(x > 0 && x < 479 && y > 0 && y < 639)
                ImageDataOp3D[j][i][k] = ImageData3Dr[int(y)][int(x)][k];*/
            }
        }
    }
    cout<< "Flag 2"<<endl;
    for (int i = 0 ; i < ImgHeight  ; i++)
    {
        for (int j = 0 ; j < ImgWidth  ; j++)
        {
            for (int k = 0 ; k < BytesPerPixel ; k++)
            {
                ImageDataOp3D[i+200][j+800][k] = ImageData3Dm[i][j][k];
            }
        }
    }
    for (int i = 0 ; i < ImgHeight  ; i++)
    {
        for (int j = 0 ; j < ImgWidth  ; j++)
        {
            for (int k = 0 ; k < BytesPerPixel ; k++)
            {
                ImageDataOp3D[i+200][j+800][k] = ImageData3Dm[i][j][k];
            }
        }
    }
    //double temp = 0  ;
    /*for (int i = 0 ; i < ImgHeightNew  ; i++)
    {
        for (int j = 270 ; j < ImgWidthNew  ; j++)
        {
            for (int k = 0 ; k < BytesPerPixel ; k++)
            {

                temp = i * 0.6037;
                NewHeight = floor(temp);
                NewWidth = j - 270;
                DeltaWidth = 1  ;
                DeltaHeight = temp - NewHeight;
                if(NewHeight>0 && NewHeight<639 && NewWidth>0 && NewWidth <479)
                {
                    if (ImageDataOp3D[i][j][k] >0)
                    {
                        int a = ((1 - DeltaHeight) * (1 - DeltaWidth) * ImageData3Dm[NewHeight][NewWidth][k] +
                                        (DeltaHeight * (1 - DeltaWidth)) * ImageData3Dm[NewHeight +1][NewWidth ][k] +
                                        ((1 - DeltaHeight) * DeltaWidth) * ImageData3Dm[NewHeight ][NewWidth + 1 ][k] +
                                        (DeltaHeight * DeltaWidth) * ImageData3Dm[NewHeight + 1][NewWidth + 1][k]);

                        ImageDataOp3D[i][j][k] = (ImageDataOp3D[i][j][k] + a) / 2 ;

                    }
                    else
                    ImageDataOp3D[i][j][k] = ((1 - DeltaHeight) * (1 - DeltaWidth) * ImageData3Dm[NewHeight][NewWidth][k] +
                                        (DeltaHeight * (1 - DeltaWidth)) * ImageData3Dm[NewHeight +1][NewWidth ][k] +
                                        ((1 - DeltaHeight) * DeltaWidth) * ImageData3Dm[NewHeight ][NewWidth + 1 ][k] +
                                        (DeltaHeight * DeltaWidth) * ImageData3Dm[NewHeight + 1][NewWidth + 1][k]);
                }
                //cout<< "Bilinear Interpolation: "<<i<<"  "<<j<<endl;

            }
        }
    }*/

    ImageDataOp = Convert3dTo1d(ImageDataOp3D, ImgHeightNew, ImgWidthNew, BytesPerPixel);
    //ImageData = Convert3dTo1d(ImageData3D, ImgHeight, ImgWidth, BytesPerPixel);

	WriteFile(argv[4], ImageDataOp, ImgHeightNew, ImgWidthNew, BytesPerPixel);

	return 0 ;
}
