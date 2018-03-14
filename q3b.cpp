// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #1 Problem 3b
// Date: February 4, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    FILE *file;
	int BytesPerPixel = atoi(argv[3]);
	int ImgHeight = atoi(argv[4]);
	int ImgWidth = atoi(argv[5]);
	int N = atoi(argv[6]);
	int n = (N-1) / 2 ;
	int ImgHeightNew = ImgHeight + 2 * n;
	int ImgWidthNew = ImgWidth + 2 * n;
    //int x = 0 , y = 0 ;
	unsigned char* ImagedataOp = new unsigned char[ImgHeight*ImgWidth*BytesPerPixel];
	unsigned char* Imagedata = new unsigned char[ImgWidth*ImgHeight*BytesPerPixel];
	unsigned char* ImagedataOriginal = new unsigned char[ImgWidth*ImgHeight*BytesPerPixel];
	unsigned char* red = new unsigned char[ImgWidth*ImgHeight];

	unsigned char* redOriginal = new unsigned char[ImgWidth*ImgHeight];

	unsigned char ** red2dOriginal = new unsigned char *[ImgHeight];
    for(int i = 0; i < ImgHeight; i++)
    red2dOriginal[i] = new unsigned char [ImgWidth];


    unsigned char ** red2d = new unsigned char *[ImgHeight];
    for(int i = 0; i < ImgHeight; i++)
    red2d[i] = new unsigned char [ImgWidth];


	unsigned char ** red2dNew = new unsigned char *[ImgHeight+(2*n)];
    for(int i = 0; i < ImgHeight+(2*n); i++)
    red2dNew[i] = new unsigned char [ImgWidth+(2*n)];


	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), ImgWidth*ImgHeight*BytesPerPixel, file);
	fclose(file);
	if (!(file=fopen(argv[7],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(ImagedataOriginal, sizeof(unsigned char), ImgWidth*ImgHeight*BytesPerPixel, file);
	fclose(file);

    cout<<"Flag 1"<<endl;

    int b = 0;
    for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j <ImgWidth ; j++)
        {
            red2d[i][j] = Imagedata[b];
            b = b + 1 ;
        }
    }
    b = 0;
    for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j <ImgWidth ; j++)
        {
            red2dOriginal[i][j] = ImagedataOriginal[b];
            b = b + 1 ;
        }
    }

    for ( int p = 0 ; p < n+1 ; p++)
    {
        for (int j = 0 ; j < ImgWidth ; j++)
        {
            red2dNew[p][j+n] = red2d[0][j];
            //green2dNew[p][j+n] = green2d[0][j];
            //blue2dNew[p][j+n] = blue2d[0][j];
            red2dNew[ImgHeightNew-p-1][j+n] = red2d[ImgHeight - 1][j];
            //green2dNew[ImgHeightNew-p-1][j+n] = green2d[ImgHeight - 1][j];
            //blue2dNew[ImgHeightNew-p-1][j+n] = blue2d[ImgHeight - 1][j];
        }
    }


    for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j < ImgWidth ; j++)
        {

			red2dNew[i+n][j+n] = red2d[i][j];
            //green2dNew[i+n][j+n] = green2d[i][j];
            //blue2dNew[i+n][j+n] = blue2d[i][j];

        }
    }

    for ( int p = 0 ; p < n ; p++)
    {
        for (int i = 0 ; i < ImgHeightNew ; i++)
        {
            red2dNew[i][p] = red2dNew[i][n];
            //green2dNew[i][p] = green2dNew[i][n];
            //blue2dNew[p][p] = blue2dNew[i][n];
            red2dNew[i][ImgWidthNew -p-1] = red2dNew[i][ImgWidth-1];
            //green2dNew[i][ImgWidthNew -p-1] = green2dNew[i][ImgWidth-1];
            //blue2dNew[i][ImgWidthNew -p-1] = blue2dNew[i][ImgWidth-1];
        }
    }

    cout<<"Flag 3"<<endl;

    int Nd = N*N;
    double histred[Nd] = {0};
    int index=0;
    cout<<"Flag 4"<<endl;

    for (int i = n ; i < ImgHeight + n ; i++)
        {
            for (int j = n ; j < ImgWidth + n ; j++)
            {
                int r = 0 ; int s = 0 ; int x = 0 ; int y = 0;
                for (int p = 0 ; p < N ; p++ )
                {
                    for (int q = 0 ; q < N ; q++)
                    {
                        x = i - p + n ;
                        y = j - q + n;
                        histred[r] = red2dNew[x][y];
                        //histgreen[r] = green2dNew[x][y];
                        //histblue[r] = blue2dNew[x][y];
                        r = r + 1 ;
                    }
                }
                int s1 = sizeof(histred)/sizeof(histred[0]);
                //cout << s1 << endl;
                sort(histred , histred + s1);
                //int s2 = sizeof(histblue)/sizeof(histblue[0]);
                //cout << s2 << endl;
                //sort(histblue , histblue + s2);
                //int s3 = sizeof(histgreen)/sizeof(histgreen[0]);
                //cout << s3 << endl;
                //sort(histgreen , histgreen + s3);
                red2dNew[i - n][j - n] = histred[(Nd + 1)/2];
                //green2dNew[i - n][j - n] = histgreen[(Nd + 1)/2];
                //blue2dNew[i - n][j - n] = histblue[(Nd + 1)/2];
            }
        }

    cout<<"Flag 5"<<endl;
    histred[Nd] = {0};
    int sum = 0;

    for (int i = n ; i < ImgHeight + n ; i++)
        {
            for (int j = n ; j < ImgWidth + n ; j++)
            {
                int r = 0 ; int x = 0 ; int y = 0;
                for (int p = 0 ; p < N ; p++ )
                {
                    for (int q = 0 ; q < N ; q++)
                    {
                        x = i - p + n ;
                        y = j - q + n;
                        histred[r] = red2dNew[x][y];
                        //histgreen[r] = green2dNew[x][y];
                        //histblue[r] = blue2dNew[x][y];
                        r = r + 1 ;
                    }
                }
                sum = 0;
                //int s1 = sizeof(histred)/sizeof(histred[0]);
                for (int s = 0 ; s < Nd ; s++)
                {
                    sum = sum + histred[s];
                }
                sum = sum / Nd;
                red2dNew[i - n][j - n] = sum;
                //red2dNew[i - n][j - n] = histred[(Nd + 1)/2];
                //green2dNew[i - n][j - n] = histgreen[(Nd + 1)/2];
                //blue2dNew[i - n][j - n] = histblue[(Nd + 1)/2];
            }
        }


    int a = 0 ;
    for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j <ImgWidth ; j++)
        {
            ImagedataOp[a] = red2dNew[i][j];
            a = a + 1 ;
        }
    }

    int Max = 255;
	int Sum = 0;
	double mse = 0;
	double psnr;
	for (int i = 0;i < ImgHeight;i++)
	{
		for (int j = 0;j < ImgWidth;j++)
		{
			Sum = Sum + (pow((red2dNew[i][j] - red2dOriginal[i][j]), 2));
		}
	}
	mse = (1 / (1.0 * ImgHeight * ImgWidth)) * Sum;
	psnr = 10 * log10((pow(Max, 2)) / (1.0 * mse));

	cout<< "PSNR for red channel:"<<psnr<<endl;


    if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(ImagedataOp, sizeof(unsigned char), (ImgWidth)*(ImgHeight)*BytesPerPixel , file);
	fclose(file);



    return 0 ;
}
