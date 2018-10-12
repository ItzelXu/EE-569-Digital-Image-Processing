// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #3 Prob 2 Sobel Detector
// Date: March 16, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------

#include "ImageBasics.h"
#include "ImageAlgo.h"

// ------------------------------------------------------------------------------------
void ImageAlgo::padImageReflect(unsigned char* ImageData, unsigned char* ImageDataOp, int n)
{
    int ImgHeightNew = ImgHeight + 2 * n;
	int ImgWidthNew = ImgWidth + 2 * n;

	for(int k = 0 ; k < BytesPerPixel ; k++)
    {
        for (int i = 0 ; i < ImgHeight ; i++)
        {
            for (int j = 0 ; j < ImgWidth ; j++)
            {
                ImageDataOp[BytesPerPixel*((i+n)*ImgWidthNew+j+n)+k] = ImageData[BytesPerPixel*(i*ImgWidth+j)+ k]; //center
            }
        }

        for (int p = 0 ; p < n ; p++)
        {
            for (int j = 0 ; j < ImgWidth ; j++)
            {
                ImageDataOp[BytesPerPixel*(p*ImgWidthNew+j+n)+k] = ImageData[BytesPerPixel*((n-p-1)*ImgWidth+j)+ k];
                ImageDataOp[BytesPerPixel*((ImgHeightNew - p - 1)*ImgWidthNew+j+n)+k] = ImageData[BytesPerPixel*((ImgHeight-1-n+p+1)*ImgWidth+j)+ k]; //top and bottom
            }
        }

        for ( int p = 0 ; p < n ; p++)
        {
            for (int i = 0 ; i < ImgHeightNew ; i++)
            {
                ImageDataOp[BytesPerPixel*((i)*ImgWidthNew+p)+k] = ImageDataOp[BytesPerPixel*(i*ImgWidthNew+2*n-p-1)+ k];
                ImageDataOp[BytesPerPixel*((i)*ImgWidthNew+(ImgWidthNew-p-1))+k] = ImageDataOp[BytesPerPixel*(i*ImgWidthNew+(ImgWidthNew-1-2*n+p))+ k]; //left and right
            }
        }
    }
    cout<<"File has been padded successfully!"<<endl;
}

// ------------------------------------------------------------------------------------
void ImageAlgo::filter(unsigned char* ImageData, double* temp, int n, int index)
{

    int ImgHeightNew = ImgHeight + 2 * n;
	int ImgWidthNew = ImgWidth + 2 * n;
	ImageAlgo ImgA;
    ImgA.setParameters(ImgHeight, ImgWidth, BytesPerPixel);
    unsigned char* ImageDataPad = new unsigned char[ImgHeightNew*ImgWidthNew*BytesPerPixel];

    ImgA.padImageReflect(ImageData, ImageDataPad, n);

    float f[3][3] = {{1.0/4,2.0/4,1.0/4},
                    {-1.0/2,0,1.0/2},
                    {1.0/4,-2.0/4,1.0/4}
                    };

    float l[9][9]; // 9 laws filter
    for(int i = 0 ; i < 3 ; i++)
    {
        for(int j = 0 ; j < 3 ; j++)
        {
            for(int p = 0 ; p < 3 ; p++)
            {
                for(int q = 0 ; q < 3 ; q++)
                {
                    l[i*3+j][p*3+q] = f[i][p]*f[j][q];
                }
            }
        }
    }
    for(int k = 0 ; k < BytesPerPixel; k++)
    {
        for(int i = 0 ; i < ImgHeight ; i++)
        {
            for(int j = 0 ; j < ImgWidth ; j++)
            {
                //cout<<i<<" "<<j<<endl;
                double sum = 0;
                for(int p = -n ; p <= n ; p++)
                {
                    for(int q = -n ; q <= n ; q++)
                    {
                        int x = n + p;
                        int y = n + q;
                        sum += ImageDataPad[BytesPerPixel*((i+x)*ImgWidthNew+j+y)+k] * l[index][x*5+y];
                    }
                }
                temp[BytesPerPixel*(i*ImgWidth+j)+k] = sum;
            }
        }
    }

}

// ------------------------------------------------------------------------------------
int ImageAlgo::minDist(double d1, double d2, double d3, double d4)
{
    if(d1 < d2 && d1 < d3 && d1 < d4)
      {
        return 0 ;
      }
    if(d2 < d1 && d2 < d3 && d2 < d4)
      {
        return 1 ;
      }
    if(d3 < d1 && d3 < d2 && d3 < d4)
      {
        return 2 ;
      }
    if(d4 < d1 && d4 < d2 && d4 < d3)
      {
        return 3 ;
      }
      return 0;
}

// ------------------------------------------------------------------------------------
void ImageAlgo::convertColortoGray(unsigned char* ImageData, unsigned char* ImageDataOp)
{
    for (int i = 0 ; i < ImgHeight ; i++)
    {
        for (int j = 0 ; j < ImgWidth ; j++)
        {
            ImageDataOp[i*ImgWidth+j] = 0.21*ImageData[BytesPerPixel*(i*ImgWidth+j)] + 0.72*ImageData[BytesPerPixel*(i*ImgWidth+j)+1] + 0.07*ImageData[BytesPerPixel*(i*ImgWidth+j)+2];
        }
    }
}

// ------------------------------------------------------------------------------------
void ImageAlgo::edgeDetectionSobel(unsigned char* ImageData, unsigned char* ImageDataOp, float thresh)
{
    int N = 1;
    int ImgHeightNew = ImgHeight + 2 * N;
	int ImgWidthNew = ImgWidth + 2 * N;
	BytesPerPixel = 1;
	ImageAlgo ImgA;
    ImgA.setParameters(ImgHeight, ImgWidth, BytesPerPixel);
    unsigned char* ImageDataPad = new unsigned char[ImgHeightNew*ImgWidthNew];

    ImgA.padImageReflect(ImageData, ImageDataPad, 1);
    ImageBasics ImgB;
    ImgB.setParameters(ImgHeightNew, ImgWidthNew, BytesPerPixel);
    ImgB.writeFile("Boat_Gray_padded.raw", ImageDataPad);

    ImageBasics i;
    i.setParameters(ImgHeight, ImgWidth,1);

    int row[9];
    int col[9];

    row[0] = -1; row[1] = 0; row[2] = 1;
    row[3] = -2; row[4] = 0; row[5] = 2;
    row[6] = -1; row[7] = 0; row[8] = 1;

    col[0] = -1; col[1] = -2; col[2] = -1;
    col[3] = 0; col[4] = 0; col[5] = 0;
    col[6] = 1; col[7] = 2; col[8] = 1;

    unsigned char** ImageDataPad2D = ImgB.convert1dTo2d(ImageDataPad);
    unsigned char** GradientMap = i.allocate2d(GradientMap);
    unsigned char* Edge = new unsigned char [ImgHeight* ImgWidth];
    unsigned char* FinalOp = new unsigned char [ImgHeight* ImgWidth];
    memset(FinalOp, 0,ImgHeight* ImgWidth);
    unsigned char* GradientX = new unsigned char [ImgHeight* ImgWidth];
    unsigned char* GradientY = new unsigned char [ImgHeight* ImgWidth];

    int max = -999999; int min = 999999;

    for(int i=0; i<ImgHeight; i++)
    {
        for(int j=0; j<ImgWidth; j++)
        {
            float gx = 0;
            for(int m=-N; m<=N; m++)
            {
                for(int n=-N; n<=N; n++)
                {
                    gx += ImageDataPad[(i+N+m)*ImgWidthNew+j+N+n] * row[(m+1)*3+n+1];
                }
            }
            float gy = 0;
            for(int m=-N; m<=N; m++)
            {
                for(int n=-N; n<=N; n++)
                {
                    gy += ImageDataPad[(i+N+m)*ImgWidthNew+j+N+n] * col[(m+1)*3+n+1];
                }
            }
            GradientX[i*ImgWidth+j] = gx;
            GradientY[i*ImgWidth+j] = gy;
            GradientMap[i][j] = sqrt(gx*gx + gy*gy);
            //cout<<int(GradientMap[i][j])<<endl;
            if(GradientMap[i][j]>max)
                max = GradientMap[i][j];
            if(GradientMap[i][j]<min)
                min = GradientMap[i][j];
            if(GradientMap[i][j] > 100)
                Edge[i*ImgWidth+j] = 0;
            else
                Edge[i*ImgWidth+j] = 255;
        }
    }

    i.writeFile("trial.raw",Edge);

    /*for(int i=0; i<ImgHeight; i++)
    {
        for(int j=0; j<ImgWidth; j++)
        {
            if (GradientX[i*ImgWidth+j]>200)
            FinalOp[i*ImgWidth+j] = 255.0;//*(GradientX[i*ImgWidth+j]-min)/(max-min);
        }
    }*/
    i.writeFile("final.raw", FinalOp);

    double cntr[int(max)] = {0};
    int val;

    for (int i = 0; i < ImgHeight; i++)
    {
        for (int j = 0; j < ImgWidth; j++)
        {
            val = GradientMap[i][j];
            int index = val;
            cntr[index]++;
        }
    }

    for (int i = 1; i < int(max); i++)
    {
        cntr[i] = cntr[i-1] + cntr[i];
    }

    ofstream tf("cdf.csv");
    for (int i =0; i < int(max); i++)
    {
        tf << i << "," << cntr[i] << endl;
    }
    tf.close();

    int threshold;
    for (int i = 0; i < int(max); i++)
    {
        if (cntr[i] <= 0.90*(ImgHeight* ImgWidth))
            threshold = i;
    }
    cout<<threshold<<endl;
    for (int i = 0; i < ImgHeight; i++)
    {
        for (int j = 0; j < ImgWidth; j++)
        {
            if (GradientMap[i][j] > threshold)
                ImageDataOp[i*ImgWidth+j] = 255;
            else
                ImageDataOp[i*ImgWidth+j] = 0;
        }
    }
    i.writeFile("FinalOpNorm.raw", ImageDataOp);
    cout<<"Sobel Filtering done!"<<endl;
}

// ------------------------------------------------------------------------------------
/*double ImageAlgo::feature(unsigned char** ImageData, int** filter, int i, int j, int N)
{
    double sum = 0;
    for (int i = 0; i < window; i++)
    {
        for (int j = 0; j < window; j++)
        {
            sum = sum + (image[x + i - (window/2)][y + j - (window/2)])*(filter[i][j]);
        }
    }
    return (sum*sum);
}*/
