
// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #2 Prob 3 Thinning
// Date: February 16, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------

#ifndef __MYIMGFUNCTIONS_H__
#define __MYIMGFUNCTIONS_H__

unsigned char * PadImage(unsigned char*, int, int, int);

int CheckCondPattern(int , char );

int CheckUncondPattern(int , char );

int CountSingleDots(unsigned char *, int , int );

int MorphThin(unsigned char *, unsigned char *, int , int);

#endif
