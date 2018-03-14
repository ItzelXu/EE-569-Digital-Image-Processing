// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #1 Problem 1b
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
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[])
{
    FILE *file;
    int Size = atoi(argv[3]);
    int SizeNew = atoi(argv[4]);
    //int ImgWidth = 512;	//int ImgHeight = 512;
	int BytesPerPixel = atoi(argv[5]);;
	unsigned char ImagedataNew[Size][Size][BytesPerPixel];

	unsigned char ResizeImage650by650 [SizeNew][SizeNew][BytesPerPixel];

    if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(ImagedataNew, sizeof(unsigned char), Size*Size*BytesPerPixel, file);	fclose(file);
	float a = (float)(Size - 1) / (SizeNew - 1);
	cout<<"Ratio of original to resized image: "<<a<<endl;

	for ( int i = 0; i < SizeNew ; i++)
    {

		for ( int j = 0; j < SizeNew ; j++)
        {

            float TranslatedHeight = 0.787365 * i;

            int NewHeight = floor(TranslatedHeight);

            float DeltaHeight = TranslatedHeight - NewHeight;

            float TranslatedWidth = 0.787365 * j;

            int NewWidth = floor(TranslatedWidth);

            float DeltaWidth = TranslatedWidth - NewWidth;

            for(int k = 0 ; k < BytesPerPixel ; k++)
            {
                ResizeImage650by650[i][j][k] =  ((1 - DeltaHeight) * (1 - DeltaWidth) * ImagedataNew[(int)NewHeight][(int)NewWidth][k] +
                                                                        DeltaHeight * (1 - DeltaWidth) * ImagedataNew[(int)NewHeight+1 ][(int)NewWidth ][k] +
                                                                        (1 - DeltaHeight) * DeltaWidth * ImagedataNew[(int)NewHeight ][(int)NewWidth + 1 ][k] +
                                                                        DeltaHeight * DeltaWidth * ImagedataNew[(int)NewHeight + 1][(int)NewWidth + 1][k]);

            }

        }
    }
	cout << "Conversion successfully done!!"<< endl;


    if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}
	fwrite(ResizeImage650by650, sizeof(unsigned char), SizeNew*SizeNew*BytesPerPixel, file);	fclose(file);

    return 0;
}
