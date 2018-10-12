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


unsigned char * PadImage(unsigned char*, int, int, int);
unsigned char* MorphShrink (unsigned char*, int, int);
int CheckCondPattern(int , char );
int CheckUnCondPattern(int , char );

