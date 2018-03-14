// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #1 Problem 1a
// Date: February 4, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------


// This sample code reads in image data from a RAW image file and
#include <math.h>

int maximum( int a, int b, int c )
{
    //return max(a,max(b,c));
    int max = ( a < b ) ? b : a;
    return ( ( max < c ) ? c : max );
}

{
  //return min(a,min(b,c));
    int min = ( a > b ) ? b : a;
    return ( ( min > c ) ? c : min );
}
int main(int argc, char *argv[])

	unsigned char TiffanyAvgOp[Size][Size];
	unsigned char TiffanyLigOp[Size][Size];
	unsigned char TiffanyLumOp[Size][Size];
	//unsigned char Imagedata[Size][Size][BytesPerPixel];
	for (int i=0;i<Size;i++)
    {
        for (int j=0;j<Size;j++)
        {
            TiffanyAvgOp[i][j] = (Imagedata[i][j][0] + Imagedata[i][j][1] + Imagedata[i][j][2])/3;
        }
    }
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

    fclose(file);
    if (!(file=fopen(argv[3],"wb"))) {
	fwrite(TiffanyLigOp, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);
	if (!(file=fopen(argv[4],"wb"))) {
	fwrite(TiffanyLumOp, sizeof(unsigned char), Size*Size*BytesPerPixel, file);