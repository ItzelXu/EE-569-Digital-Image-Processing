// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #1 Problem 2a
// Date: February 4, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------


#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[])
{
    FILE *file;
    int ImgWidth =atoi(argv[5]) ;
	int ImgHeight = atoi(argv[6]);
	int BytesPerPixel = atoi(argv[4]);
    unsigned char Imagedata[ImgHeight][ImgWidth][BytesPerPixel];
    unsigned char ImagedataNew[ImgHeight][ImgWidth][BytesPerPixel];
    unsigned char ImagedataBf [ImgHeight][ImgWidth][BytesPerPixel];
    //unsigned char* ImagedataOriginal = new unsigned char [ImgWidth*ImgHeight*BytesPerPixel];

    if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char),  ImgHeight*ImgWidth*BytesPerPixel ,  file);
	fclose(file);

	int histRed [256] = { 0 } ;
    float histRedNorm [256] = {0} ;
    float histGreenNorm [256] = {0} ;
    float histBlueNorm [256] = {0} ;
    int histGreen[ 256 ] = { 0 } ;
    int histBlue[ 256 ] = { 0 } ;
    int xloc [ImgHeight*ImgWidth];
    int yloc [ImgHeight*ImgWidth];
    int x,y,z;

    for (int k = 0 ; k < 256 ; k ++)
     {
        //int countr=0,countg=0,countb=0;
        for (int i = 0 ; i < ImgHeight ; i++)
        {
            for (int j = 0 ; j < ImgWidth ; j++)
            {
                x = (int)Imagedata [i][j][0] ;
                y = (int)Imagedata [i][j][1] ;
                z = (int)Imagedata [i][j][2] ;
                //x++;y++;z++;
                if (k == x)
                    histRed[x] = histRed[x] + 1;
                if (k == y)
                    histGreen[y] = histGreen[y] + 1;
                if (k == z)
                    histBlue[z] = histBlue[z] + 1;
            }
        }
     }

    for (int i = 0 ; i < 256 ; i++)
     {
            histRedNorm[i] =(float) histRed[i] / (ImgHeight*ImgWidth);
            histGreenNorm[i] = (float) histGreen[i] / (ImgHeight*ImgWidth);
            histBlueNorm[i] = (float) histBlue[i] / (ImgHeight*ImgWidth);
     }
    float temp[256][3] = {0};
    float tf [256][3];
    for (int i = 0 ; i < 256 ; i++)
        {
            if(i == 0)
            {
                temp[i][0] = histRedNorm[i];
                temp[i][1] = histGreenNorm[i];
                temp[i][2] = histBlueNorm[i];
            }
            else
            {
                temp [i][0] = histRedNorm[i] + temp[i-1][0] ;
                temp [i][1] = histGreenNorm[i] + temp[i-1][1]  ;
                temp [i][2] = histBlueNorm[i] + temp[i-1][2] ;
                    //cout<< temp[i][0]<<"  "endl;
            }

        }
    for (int i = 0 ; i < 256 ; i++)
    {
        for (int k = 0 ; k < BytesPerPixel ; k++)
        {
            tf[i][k] = 255 * temp[i][k];
        }

    }

    for(int k=0;k<BytesPerPixel;k++)
        {
            for(int i=0;i<ImgHeight;i++)
            {
                for(int j=0;j<ImgWidth;j++)
                {
                    for(int g = 0 ; g < 256; g++)
                    {
                        if(g == int(Imagedata[i][j][k]))
                        {
                            ImagedataNew[i][j][k]=(unsigned char)(floor(tf[g][k]));
                            break;
                        }
                    }

                }
            }

        }


////////////////////////////////////////////////////////////////////////////////////

  for( int k = 0 ; k < BytesPerPixel ; k++ )
        {
            int m = 0;
            int n = 0;
            for (int g = 0; g < 256; g++)
            {
                for (int i = 0 ; i < ImgHeight ; i++)
                {
                    for (int j = 0 ; j < ImgWidth ; j++)
                    {
                        if (g == (int)Imagedata[i][j][k])
                        {
                            xloc[m] = i;
                            yloc[n] = j;
                            m = m + 1;
                            n = n + 1;
                        }
                    }
                }
            }
            int g = 0 ; int cntr = 1;
            for (int p = 0 ; p < ImgHeight*ImgWidth ; p++)
            {
                if(cntr % 470 == 0 )
                {
                    cntr = 1 ;
                    g = g + 1 ;
                    ImagedataBf[xloc[p]][yloc[p]][k] = (unsigned char) g;
                }
                else
                {
                    ImagedataBf[xloc[p]][yloc[p]][k] = (unsigned char) g;
                    cntr = cntr + 1;
                }
                //ImagedataBf[xloc[p]][yloc[p]][k] = (unsigned char) g;
            }
                //q = q + 468;

        }



	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(ImagedataNew, sizeof(unsigned char), ImgWidth*ImgHeight*BytesPerPixel , file);
	fclose(file);
	if (!(file=fopen(argv[3],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(ImagedataBf, sizeof(unsigned char), ImgWidth*ImgHeight*BytesPerPixel , file);
	fclose(file);

    return 0;
}
