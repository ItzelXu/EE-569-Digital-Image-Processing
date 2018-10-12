// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #3 Prob 2 Sobel Detector
// Date: March 16, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------

#include "ImageBasics.h"


// ------------------------------------------------------------------------------------
//constructor
ImageBasics::ImageBasics(){
}

// ------------------------------------------------------------------------------------
//destructor
ImageBasics::~ImageBasics(){
}

// ------------------------------------------------------------------------------------
void ImageBasics::setParameters(int ImageHeight, int ImageWidth, int Planes)
{
    ImgHeight = ImageHeight;
    ImgWidth = ImageWidth;
    BytesPerPixel = Planes;
}

// ------------------------------------------------------------------------------------
void ImageBasics::readFile(const char* FileName, unsigned char* Imagedata)
{
    FILE* file;

	if (!(file=fopen(FileName,"rb")))
    {
        cout << "Cannot open file: " << FileName <<endl;
		exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), ImgHeight*ImgWidth*BytesPerPixel, file);
    fclose(file);
	cout << "File " << FileName << " has been read successfully! " << endl;
}

// ------------------------------------------------------------------------------------
void ImageBasics::writeFile(const char* FileName, unsigned char* Imagedata)
{
    FILE* file;

	if (!(file=fopen(FileName,"wb"))) {
		cout << "Cannot open file: " << FileName << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), ImgHeight*ImgWidth*BytesPerPixel, file);
	fclose(file);
	cout << "File " << FileName << " has been written successfully!" << endl;
}

// ------------------------------------------------------------------------------------
void ImageBasics::delete2d(unsigned char** Imagedata)
{
	for (int i = 0; i < ImgHeight; i++)
	{
		delete[] Imagedata[i];
	}
	delete[] Imagedata;
}

// ------------------------------------------------------------------------------------
void ImageBasics::delete3d(unsigned char*** Imagedata)
{
	for (int i = 0; i < ImgHeight; i++)
	{
		for (int j = 0; j < ImgWidth; j++)
			delete[] Imagedata[i][j];
		delete[] Imagedata[i];
	}
	delete[] Imagedata;
}

// ------------------------------------------------------------------------------------
unsigned char** ImageBasics::allocate2d(unsigned char** Imagedata)
{
    Imagedata = new unsigned char *[ImgHeight]();
	for (int i = 0;i < ImgHeight;i++)
	{
		Imagedata[i] = new unsigned char[ImgWidth]();
		for (int j = 0;j < ImgWidth;j++)
		{
			Imagedata[i][j] = 0;
		}
	}
	return Imagedata;
}

// ------------------------------------------------------------------------------------
unsigned char** ImageBasics::convert1dTo2d(unsigned char* Imagedata)
{
    unsigned char** Img2d = new unsigned char *[ImgHeight]();
	for (int i = 0;i < ImgHeight;i++)
	{
		Img2d[i] = new unsigned char [ImgWidth]();
		for (int j = 0;j < ImgWidth;j++)
		{
			Img2d[i][j] = 0;
		}
	}

	for (int i = 0; i < ImgHeight; i++)
	{
		for (int j = 0; j < ImgWidth; j++)
		{
			Img2d[i][j] = Imagedata[i * ImgWidth + j];
		}
	}
	return(Img2d);
}

// ------------------------------------------------------------------------------------
unsigned char* ImageBasics::convert2dTo1d(unsigned char** Imagedata)
{
    unsigned char* Img1d = new unsigned char[ImgHeight*ImgWidth]();
	for (int i = 0; i < ImgHeight; i++)
	{
		for (int j = 0; j < ImgWidth; j++)
		{
			Img1d[i * ImgWidth + j] = Imagedata[i][j];
		}
	}
	return(Img1d);
}

// ------------------------------------------------------------------------------------
unsigned char*** ImageBasics::convert1dto3d(unsigned char* Imagedata)
{
    unsigned char*** Imagedata3d =  new unsigned char **[ImgHeight]();
	for (int i = 0; i < ImgHeight; i++)
	{
		Imagedata3d[i] = new unsigned char *[ImgWidth]();
		for (int j = 0; j < ImgWidth; j++)
		{
			Imagedata3d[i][j] = new unsigned char[BytesPerPixel]();
			for (int k = 0; k < BytesPerPixel; k++)
			{
				Imagedata3d[i][j][k] = 0;
			}
		}
	}

	for (int i = 0; i < ImgHeight; i++)
	{
		for (int j = 0; j < ImgWidth; j++)
		{
			for (int k = 0; k < BytesPerPixel; k++)
			{
				Imagedata3d[i][j][k] = Imagedata[i * ImgWidth * BytesPerPixel + j * BytesPerPixel + k];
			}
		}
	}
	return(Imagedata3d);
}

// ------------------------------------------------------------------------------------
unsigned char* ImageBasics::convert3dTo1d(unsigned char*** Imagedata3d)
{
    unsigned char* Imagedata = new unsigned char[ImgHeight*ImgWidth*BytesPerPixel]();
    cout<<ImgHeight<<" "<<ImgWidth<<" "<<BytesPerPixel<<endl;
	int m = 0;
	for (int i = 0; i < ImgHeight; i++)
	{
		for (int j = 0; j < ImgWidth; j++)
		{
			Imagedata [m] = Imagedata3d[i][j][0];
			Imagedata [m + 1] = Imagedata3d[i][j][1];
			Imagedata [m + 2] = Imagedata3d[i][j][2];
			m = m + 3;
			cout<<i<<" "<<j<<endl;
		}
	}
	return(Imagedata);
}

// ------------------------------------------------------------------------------------
int* ImageBasics::getHistogram(unsigned char* Imagedata)
{
    int* histogram = new int [256]; // Initialize it into 0
    for(int i = 0 ; i < ImgHeight ; i++)
    {
        for(int j = 0 ; j < ImgWidth ; j++)
        {
            histogram[Imagedata[i * ImgWidth + j]] ++;
        }
    }
    cout << "Histogram has been calculated successfully!" << endl;
    return histogram;
}

// ------------------------------------------------------------------------------------
/*void ImageBasics::padImageReflect(unsigned char* ImageData, unsigned char* ImageDataOp, int n)
{
    int ImgHeightNew = ImgHeight + 2 * n;
	int ImgWidthNew = ImgWidth + 2 * n;

	for(int k = 0 ; k < BytesPerPixel ; k++)
    {
        for (int i = 0 ; i < ImgHeight ; i++)
        {
            for (int j = 0 ; j < ImgWidth ; j++)
            {
                ImageDataOp[BytesPerPixel*((i+n)*ImgWidthNew+j+n)+k] = ImageData[BytesPerPixel*(i*ImgWidth+j)+ k];
            }
        }

        for (int p = 0 ; p < n ; p++)
        {
            for (int j = 0 ; j < ImgWidth ; j++)
            {
                ImageDataOp[BytesPerPixel*(p*ImgWidthNew+j+n)+k] = ImageData[BytesPerPixel*j+ k];
                ImageDataOp[BytesPerPixel*((ImgHeightNew - p - 1)*ImgWidthNew+j+n)+k] = ImageData[BytesPerPixel*((ImgHeight-1)*ImgWidth+j)+ k];
            }
        }

        for ( int p = 0 ; p < n ; p++)
        {
            for (int i = 0 ; i < ImgHeightNew ; i++)
            {
                ImageDataOp[BytesPerPixel*((i)*ImgWidthNew+p)+k] = ImageDataOp[BytesPerPixel*(i*ImgWidthNew+n)+ k];
                ImageDataOp[BytesPerPixel*((i)*ImgWidthNew+(ImgWidthNew -p - 1))+k] = ImageDataOp[BytesPerPixel*(i*ImgWidthNew+(ImgWidth - 1))+ k];
            }
        }
    }

    cout<<"File has been padded successfully!"<<endl;
}*/


