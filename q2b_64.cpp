// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #1 Problem 2b
// Date: February 4, 2017
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------


#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

unsigned char*** Allocate_3D(int x, int y, int z)
{
    unsigned char*** the_array = NULL;
    the_array = new unsigned char**[x];
    for(int i(0); i < x; i++)
    {
        the_array[i] = new unsigned char*[y];

        for(int j(0); j < y; j++)
        {
            the_array[i][j] = new unsigned char[z];

            for(int k(0); k < z; k++ )
            {
                the_array[i][j][k]= 0.;
            }
        }
    }
    return the_array;
}

void release(unsigned char*** the_array, int x, int y, int z)
{
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            delete [] the_array[i][j];
        }
        delete [] the_array[i];
    }
    delete [] the_array;
}




int main(int argc, char *argv[])

{
    FILE *file;
	int bytesPerPixel = atoi(argv[3]);
	int ImgHeight = atoi(argv[4]);//338;
	int ImgWidth = atoi(argv[5]);//600;
	int x,y,z;
    int hist[256][3] = {0} ;
    int cntr = 0;
    int M = 4;
    int N = atoi(argv[6]) ;
    int n = (N-1)/2;
    int ImgHeightNew = ImgHeight+2*n;
    int ImgWidthNew = ImgWidth+2*n;
    unsigned char*** Imagedata = Allocate_3D(ImgHeight, ImgWidth, bytesPerPixel);
    unsigned char*** ImagedataOp = Allocate_3D(ImgHeight, ImgWidth, bytesPerPixel);
    unsigned char*** Imagedata1 = Allocate_3D(ImgHeightNew, ImgWidthNew, bytesPerPixel);

    //unsigned char Imagedata[ImgHeight][ImgWidth][bytesPerPixel];
    //unsigned char Imagedata1[ImgHeight+2*n][ImgWidth+2*n][bytesPerPixel];
    //unsigned char ImagedataOp[ImgHeight][ImgWidth][bytesPerPixel];
    cout<<"flag1"<<endl;
    if (!(file=fopen(argv[1],"rb"))) {
	cout << "Cannot open file: " << argv[1] <<endl;
	exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), ImgHeight*ImgWidth*bytesPerPixel, file);
	fclose(file);
    cout<<"flag2"<<endl;
    for (int k = 0 ; k < 256 ; k ++)
     {
        for (int i = 0 ; i < ImgHeight ; i++)
        {
            for (int j = 0 ; j < ImgWidth ; j++)
            {
                x = (int)Imagedata [i][j][0] ;
                y = (int)Imagedata [i][j][1] ;
                z = (int)Imagedata [i][j][2] ;
                if (k == x)
                    hist[x][0] = hist[x][0] + 1;
                if (k == y)
                    hist[y][1] = hist[y][1] + 1;
                if (k == z)
                    hist[z][2] = hist[z][2] + 1;
            }
        }
     }
     cout<<"flag3"<<endl;
     for(int i = 0 ; i <256 ; i++)
     {
         cout<<hist[i][0]<<endl;
     }
     int bin = ImgHeight*ImgWidth/4;
     int p[M+1][3] = {0}; p[M][0] = 256; p[M][1] = 256; p[M][2] = 256;
     int numpixel[M+1][3] = {0};
     int e = 1;
     int sum[3] = {0} ;
     for (int k = 0 ; k < bytesPerPixel ; k++)
     {
         cntr = 0; e = 1;
         for (int i = 0 ; i < 256 ; i++)
         {
             cntr = cntr + hist[i][k];
             if (cntr > bin)
             {
                p[e][k] = i;
                numpixel[e][k] = cntr ;
                cntr = 0;
                e = e + 1;
             }
         }
    }
    cout<<"flag3"<<endl;
    for (int i = 0 ;i < M+1 ; i++)
    {
        cout<< p[i][0]<<"     "<<numpixel[i][0]<<endl;
    }
     for (int k = 0 ; k < bytesPerPixel ; k++)
     {
         for (int i = 0 ; i < M ; i++)
         {
             sum[k] = sum[k] +numpixel[i][k];
         }
         numpixel[M][k] = (ImgHeight*ImgWidth) - sum[k];
     }

     for (int k = 0 ; k < bytesPerPixel ; k++)
     {
         for (int i = 0 ; i < M+1 ; i++)
        {
            cout << p[i][k]<<"  "<<numpixel[i][k]<<endl;
            //cout<< numpixel[i][k]<<endl;
        }
     }
    cout<<"flag3"<<endl;
    int wmean[M+1][3] = {0};
    for (int k = 0 ; k < bytesPerPixel ; k++)
    {
        for (int a = 0 ; a < M ; a++)
        {
            for (int  i = (p[a][k])+1 ; i < p[a+1][k] ; i++)
                {
                    wmean[a][k] = wmean[a][k] + i*hist[i][k];
                }
                wmean[a][k] = wmean[a][k] / numpixel[a+1][k];
        }
    }
    cout<<"flag3"<<endl;
    /*for (int k = 0 ; k < bytesPerPixel ; k++)
     {
         for (int i = 0 ; i < M+1 ; i++)
        {
            cout << wmean[i][k]<<endl;
            //cout<< numpixel[i][k]<<endl;
        }
     }*/
    for (int k = 0 ; k < bytesPerPixel; k ++)
     {
        for (int i = 0 ; i < ImgHeight ; i++)
        {
            for (int j = 0 ; j < ImgWidth ; j++)
            {
                if (Imagedata[i][j][k] <= p[1][k])
                 {
                     ImagedataOp[i][j][k] = wmean[0][k] ;
                 }
                 else if  (Imagedata[i][j][k] <= p[2][k])
                 {
                     ImagedataOp[i][j][k] =  wmean[1][k] ;
                 }
                 else if (Imagedata[i][j][k] <= p[3][k])
                 {
                     ImagedataOp[i][j][k] = wmean[2][k] ;
                 }
                 else if (Imagedata[i][j][k] <= p[4][k])
                 {
                     ImagedataOp[i][j][k] =  wmean[3][k] ;
                 }
            }
        }
     }

    cout<<"flag3"<<endl;
    /*for (int k = 0 ; k < bytesPerPixel ; k++)
    {
        for (int i = 0 ; i < ImgHeight ; i++)
        {
            for (int j = 0 ; j < ImgWidth ; j++)
            {

                    Imagedata1[0][j+1][k] = ImagedataOp[0][j][k];
                    Imagedata1[ImgHeight+1][j+1][k] = ImagedataOp[ImgHeight-1][j][k];
                    Imagedata1[i+1][j+1][k] = ImagedataOp [i][j][k];
                    Imagedata1[i+1][0][k] = ImagedataOp[i][0][k];
                    Imagedata1[i+1][ImgWidth+1][k] = ImagedataOp[i][ImgWidth-1][k] ;
                    Imagedata1[0][0][k] = ImagedataOp [0][0][k];
                    Imagedata1[0][ImgWidth+1][k] = ImagedataOp [0][ImgWidth-1][k];
                    Imagedata1[ImgHeight+1][0][k] = ImagedataOp [ImgHeight-1][0][k];
                    Imagedata1[ImgHeight+1][ImgWidth+1][k] = ImagedataOp[ImgHeight-1][ImgWidth-1][k];
            }
        }
    }*/


    for (int k = 0 ; k < bytesPerPixel ; k++)
    {
        for ( int p = 0 ; p < n+1 ; p++)
        {
            for (int j = 0 ; j < ImgWidth ; j++)
            {
                Imagedata1[p][j+n][k] = ImagedataOp[0][j][k];
                Imagedata1[ImgHeightNew-p-1][j+n][k] = ImagedataOp[ImgHeight - 1][j][k];
            }
        }
    }

    for (int k = 0 ; k < bytesPerPixel ; k++)
    {
        for (int i = 0 ; i < ImgHeight ; i++)
        {
            for (int j = 0 ; j < ImgWidth ; j++)
            {
                Imagedata1[i+n][j+n][k] = ImagedataOp[i][j][k];
            }
        }
    }

    for (int k = 0 ; k < bytesPerPixel ; k++)
    {
        for ( int p = 0 ; p < n ; p++)
        {
            for (int i = 0 ; i < ImgHeightNew ; i++)
            {
                Imagedata1[i][p][k] = ImagedataOp[i][n][k];
                Imagedata1[i][ImgWidthNew - p - 1][k] = ImagedataOp[i][ImgWidth-1][k];
            }
        }
    }


    cout<< "flag 3 "<<endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    int Nd = N * N ;
    int histNew[Nd] = {0};
    x=0;y=0;
    int index=0;

    for (int k = 0 ; k < bytesPerPixel ; k++)
    {
        for (int i = n ; i < ImgHeight + n ; i++)
        {
            for (int j = n ; j < ImgWidth + n ; j++)
            {
                int a = 0;
                for (int p = 0 ; p < N ; p++ )
                {
                    for (int q = 0 ; q < N ; q++)
                    {
                        x = i - p + 1 ;
                        y = j - q + 1;
                        histNew[a] = Imagedata1[x][y][k];
                        a=a+1;
                        //cout<< x<<"  "<<y;
                    }
                }
                    int maximum = 0;
                    int frequency[4] = {0};
                    for (int r = 0 ; r < Nd ; r++)
                        {
                            //cout<<histNew[r]<<endl;
                            if (histNew[r] == wmean[0][k])
                                frequency[0]+=1;
                            else if (histNew[r] == wmean[1][k])
                                frequency[1]+=1;
                            else if (histNew[r] == wmean[2][k])
                                frequency[2]+=1;
                            else if (histNew[r] == wmean[3][k])
                                frequency[3]+=1;
                            //cout<< "hist: "<<hist[i]<<endl;
                        }
                    maximum = frequency[0];
                    index = 0;
                    for (int s = 1 ; s < 4 ; s++)
                        {
                                //cout<< "frequency"<<frequency[i]<<endl;
                            if(maximum < frequency[s])
                            {
                                maximum = frequency[s];
                                index = s;
                            }
                            else
                                index = index;
                        }
                        if(index == 0)
                            ImagedataOp[i-n][j-n][k] = wmean[0][k];
                        else if (index == 1)
                            ImagedataOp[i-n][j-n][k] = wmean[1][k];
                        else if (index == 2)
                            ImagedataOp[i-n][j-n][k] = wmean[2][k];
                        else if (index == 3)
                            ImagedataOp[i-n][j-n][k] = wmean[3][k];

            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////

    if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(ImagedataOp, sizeof(unsigned char), (ImgWidth)*(ImgHeight)*bytesPerPixel , file);
	fclose(file);

	release(ImagedataOp, ImgHeight, ImgWidth, bytesPerPixel);
	release(Imagedata, ImgHeight, ImgWidth, bytesPerPixel);
	release(Imagedata1, ImgHeightNew, ImgWidthNew, bytesPerPixel);

    return 0;
}
