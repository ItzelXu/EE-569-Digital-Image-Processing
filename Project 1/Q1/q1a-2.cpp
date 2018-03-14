
// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #1 Problem 1a-2
// Date: February 4, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------


#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <math.h>#include <algorithm>

using namespace std;

int main(int argc, char* argv[])
{
    FILE *file;
    int ImgWidth = atoi(argv[6]);	int ImgHeight = atoi(argv[7]);
	int BytesPerPixel = atoi(argv[8]);
    unsigned char* Imagedata = new unsigned char[ImgWidth*ImgHeight*BytesPerPixel];
    unsigned char* BearOp = new unsigned char[ImgWidth*ImgHeight*BytesPerPixel];
    unsigned char* BearCyanOp = new unsigned char[ImgWidth*ImgHeight];
    unsigned char* BearMagOp = new unsigned char[ImgWidth*ImgHeight];
    unsigned char* BearYlOp = new unsigned char[ImgWidth*ImgHeight];

	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), ImgWidth*ImgHeight*BytesPerPixel, file);	fclose(file);

	for (int i=0;i<(ImgWidth*ImgHeight*BytesPerPixel);i++)
    {
        BearOp[i]= 255 - Imagedata[i];
    }
    for (int j=0;j<(ImgWidth*ImgHeight*BytesPerPixel);j=j+3)
    {
        BearCyanOp[j/3]= BearOp[j];
    }
    for (int j=1;j<(ImgWidth*ImgHeight*BytesPerPixel);j=j+3)
    {
        BearMagOp[j/3]= BearOp[j];
    }
    for (int j=2;j<(ImgWidth*ImgHeight*BytesPerPixel);j=j+3)
    {
        BearYlOp[j/3]= BearOp[j];
    }
	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}
	fwrite(BearOp, sizeof(unsigned char), ImgWidth*ImgHeight*BytesPerPixel, file);
	fclose(file);
	if (!(file=fopen(argv[3],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}
	fwrite(BearCyanOp, sizeof(unsigned char), ImgWidth*ImgHeight, file);
	fclose(file);
	if (!(file=fopen(argv[4],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}
	fwrite(BearMagOp, sizeof(unsigned char), ImgWidth*ImgHeight, file);
	fclose(file);
	if (!(file=fopen(argv[5],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}
	fwrite(BearYlOp, sizeof(unsigned char), ImgWidth*ImgHeight, file);	fclose(file);    delete [] Imagedata;
    delete [] BearOp;
    delete [] BearCyanOp;
    delete [] BearMagOp;
    delete [] BearYlOp;	return 0;
}
