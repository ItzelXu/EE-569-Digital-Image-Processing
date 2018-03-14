// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #1 Problem 2c
// Date: February 4, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
    FILE *file;
	int BytesPerPixel = atoi(argv[3]);
	int ImgHeight = atoi(argv[4]);
	int ImgWidth = atoi(argv[5]);
	unsigned char* Imagedata = new unsigned char[ImgWidth*ImgHeight*BytesPerPixel];
	unsigned char* ImagedataOp = new unsigned char[ImgWidth*ImgHeight*BytesPerPixel];
	unsigned char* CyanOp = new unsigned char [ImgHeight*ImgWidth];
	unsigned char* MagOp = new unsigned char [ImgHeight*ImgWidth];
	unsigned char* YlOp = new unsigned char [ImgHeight*ImgWidth];
	//cout<<"flag1"<<endl;
	/*unsigned char cyan [ImgHeight][ImgWidth];
	unsigned char mag [ImgHeight][ImgWidth];
	unsigned char yellow [ImgHeight][ImgWidth];*/
	unsigned char ** cyan = new unsigned char *[ImgHeight];
    for(int i = 0; i < ImgHeight; ++i)
    cyan[i] = new unsigned char [ImgWidth];
    unsigned char ** mag = new unsigned char *[ImgHeight];
    for(int i = 0; i < ImgHeight; ++i)
    mag[i] = new unsigned char [ImgWidth];
    unsigned char ** yellow = new unsigned char *[ImgHeight];
    for(int i = 0; i < ImgHeight; ++i)
    yellow[i] = new unsigned char [ImgWidth];
	cout<<"flag1"<<endl;

	unsigned char ** cyanNew = new unsigned char *[ImgHeight];
    for(int i = 0; i < ImgHeight; ++i)
    cyanNew[i] = new unsigned char [ImgWidth];
    unsigned char ** magNew = new unsigned char *[ImgHeight];
    for(int i = 0; i < ImgHeight; ++i)
    magNew[i] = new unsigned char [ImgWidth];
    unsigned char ** yellowNew = new unsigned char *[ImgHeight];
    for(int i = 0; i < ImgHeight; ++i)
    yellowNew[i] = new unsigned char [ImgWidth];


	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), ImgWidth*ImgHeight*BytesPerPixel, file);	fclose(file);
    for (int i=0;i<(ImgWidth*ImgHeight*BytesPerPixel);i++)
    {
        ImagedataOp[i]= 255 - Imagedata[i];
    }

    for (int j=0;j<(ImgWidth*ImgHeight*BytesPerPixel);j=j+3)
    {
        CyanOp[j/3]= ImagedataOp[j];
    }
    for (int j=1;j<(ImgWidth*ImgHeight*BytesPerPixel);j=j+3)
    {
        MagOp[j/3]= ImagedataOp[j];
    }
    for (int j=2;j<(ImgWidth*ImgHeight*BytesPerPixel);j=j+3)
    {
        YlOp[j/3]= ImagedataOp[j];
    }
    cout<<"flag2"<<endl;
    int b = 0 ;
    for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j <ImgWidth ; j++)
        {
            cyan[i][j] = CyanOp[b];
            mag[i][j] = MagOp[b];
            yellow[i][j] = YlOp[b];
            b = b + 1 ;
        }
    }
    cout<<"flag3"<<endl;
    for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j <ImgWidth ; j++)
        {
            //int temp1 = cyan[i][j];
            //int temp2 = mag[i][j];
            //int temp3 = yellow[i][j];
            cyanNew[i][j] = cyan [i][ImgWidth-j-1];
            magNew[i][j] = mag [i][ImgWidth-j-1];
            yellowNew[i][j] = yellow [i][ImgWidth-j-1];
            //cyan [i][ImgWidth-j-1] = temp1;
            //mag [i][ImgWidth-j-1] = temp2;
            //yellow [i][ImgWidth-j-1] = temp3;
        }
    }
    cout<<"Flag 4"<<endl;
    int a = 0 ;
    /*for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j <ImgWidth ; j++)
        {
            ImagedataOp[a] = cyanNew[i][j];
            ImagedataOp[a+1] = magNew[i][j];
            ImagedataOp[a+2] = yellowNew[i][j];
            a = a + 3 ;
        }
    }*/
    cout<<"Flag 5"<<endl;
    double p , q , r;

    for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j <ImgWidth ; j++)
        {
            p = cyanNew[i][j];
            p = (p / 255*170) + 85 ;
            cyanNew[i][j] = p ;
            //cyanNew[i][j] = cyanNew[i][j] + 85
            q  = magNew[i][j];
            q = (q / 255*170) + 30;
            magNew[i][j] = q ;
            //magNew[i][j] = magNew[i][j] + 30
            r = yellowNew[i][j];
            r = (r / 255*150) + 20;
            yellowNew[i][j] = r;

        }
    }
    a = 0 ;
    for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j <ImgWidth ; j++)
        {
            ImagedataOp[a] = cyanNew[i][j];
            ImagedataOp[a+1] = magNew[i][j];
            ImagedataOp[a+2] = yellowNew[i][j];
            a = a + 3 ;
        }
    }

    cout<<"Flag 6"<<endl;
    if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(ImagedataOp, sizeof(unsigned char), (ImgWidth)*(ImgHeight)*BytesPerPixel , file);
	fclose(file);
	cout<<"Flag 7"<<endl;
	delete [] Imagedata;
    delete [] ImagedataOp;
    delete [] CyanOp;
    delete [] MagOp;
    delete [] YlOp;
    /*for(int i = 0; i < ImgHeight; ++i)
        {
            delete [] cyan[i];
        }
    delete [] cyan;
    for(int i = 0; i < ImgHeight; ++i)
        {
            delete [] mag[i];
        }
    delete [] mag;
    for(int i = 0; i < ImgHeight; ++i)
        {
            delete [] yellow[i];
        }
    delete [] yellow;*/
}
