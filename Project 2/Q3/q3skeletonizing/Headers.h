
// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #2 Prob 3 Skeletonizing
// Date: February 16, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------

#ifndef __HEADERS_H__
#define __HEADERS_H__

void ReadFile(const char*, unsigned char*, int, int, int);
void WriteFile(const char*, unsigned char*, int, int, int);
void Delete2d(unsigned char**, int);
void Delete3d(unsigned char*** , int , int );
unsigned char** Allocate2d(unsigned char**, int, int);
unsigned char** Convert1dTo2d(unsigned char*, int, int);
unsigned char* Convert2dTo1d(unsigned char**, int, int);
unsigned char*** Convert1dto3d(unsigned char*, int, int, int);
unsigned char* Convert3dTo1d(unsigned char***, int, int, int);
int* GetHistogram(unsigned char *,int, int);
unsigned char* ConvertGreyToBinary (unsigned char*, int, int);

#endif

