// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #1 Problem 1a
// Date: February 4, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------


// This sample code reads in image data from a RAW image file and// writes it into another file// NOTE:	The code assumes that the image is of size 256 x 256 and is in the//			RAW format. You will need to make corresponding changes to//			accommodate images of different sizes and/or types#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <math.h>#include <algorithm>
using namespace std;
int maximum( int a, int b, int c )
{
    //return max(a,max(b,c));
    int max = ( a < b ) ? b : a;
    return ( ( max < c ) ? c : max );
}
int minimum(int a, int b, int c)
{
  //return min(a,min(b,c));
    int min = ( a > b ) ? b : a;
    return ( ( min > c ) ? c : min );
}
int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size ;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image_avg.raw output_image_lig.raw output_image_lum.raw [BytesPerPixel = 3] [Size = 256]" << endl;		return 0;	}
	// Check if image is gray scale or color	if (argc < 4){		BytesPerPixel = 1; // default is gray image	}	else {		BytesPerPixel = atoi(argv[5]);		// Check if size is specified		if (argc >= 5){			Size = atoi(argv[6]);		}	}	// Allocate image data array	unsigned char Imagedata[Size][Size][BytesPerPixel];
	unsigned char TiffanyAvgOp[Size][Size];
	unsigned char TiffanyLigOp[Size][Size];
	unsigned char TiffanyLumOp[Size][Size];
	//unsigned char Imagedata[Size][Size][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);	fclose(file);	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	for (int i=0;i<Size;i++)
    {
        for (int j=0;j<Size;j++)
        {
            TiffanyAvgOp[i][j] = (Imagedata[i][j][0] + Imagedata[i][j][1] + Imagedata[i][j][2])/3;
        }
    }    for (int i=0;i<Size;i++)
    {
        for (int j=0;j<Size;j++)
        {
            TiffanyLigOp[i][j] = (maximum(Imagedata[i][j][0],Imagedata[i][j][1],Imagedata[i][j][2]) + minimum(Imagedata[i][j][0],Imagedata[i][j][1],Imagedata[i][j][2]))/2;
        }
    }
    for (int i=0;i<Size;i++)
    {
        for (int j=0;j<Size;j++)
        {
            TiffanyLumOp[i][j] = (0.21*Imagedata[i][j][0] + 0.72*Imagedata[i][j][1] + 0.07*Imagedata[i][j][2]);
        }
    }
	// Write image data (filename specified by second argument) from image data matrix	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}    fwrite(TiffanyAvgOp, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);
    if (!(file=fopen(argv[3],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}
	fwrite(TiffanyLigOp, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);
	if (!(file=fopen(argv[4],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}
	fwrite(TiffanyLumOp, sizeof(unsigned char), Size*Size*BytesPerPixel, file);	fclose(file);	return 0;}