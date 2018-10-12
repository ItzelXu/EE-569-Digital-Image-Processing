
// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #2 Prob 2 Error Difussion
// Date: February 21, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
#include <algorithm>


void ReadFile(char*, unsigned char*, int, int, int);
void WriteFile(char*, unsigned char*, int, int, int);
void Delete2d(unsigned char**, int);
void Delete3d(unsigned char*** , int , int );
unsigned char** Allocate2d(unsigned char**, int, int);
unsigned char** Convert1dTo2d(unsigned char*, int, int);
unsigned char* Convert2dTo1d(unsigned char**, int, int);
double*** Convert1dto3d(double*, int, int, int);
double* Convert3dTo1d(double***, int, int, int);
unsigned char*** Convert1dto3dus(unsigned char*, int, int, int);
unsigned char* Convert3dTo1dus(unsigned char***, int, int, int);
int* GetHistogram(unsigned char *,int, int);
unsigned char* ConvertGreyToBinary (unsigned char*, int, int);

//unsigned char** Img1dTo2d(unsigned char*, int, int);
//unsigned char* Img2dTo1d(unsigned char**, int, int);


