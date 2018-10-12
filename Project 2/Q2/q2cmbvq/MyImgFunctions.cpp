// ------------------------------------------------------------------------------------
// EE569 Homework Assignment #2 Prob 2 Error Diffusion
// Date: February 16, 2018
// Name : Pranav Gundewar
// USC-ID : 4463612994
// email : gundewar@usc.edu
// ------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
#include <algorithm>
#include "Headers.h"
#include "MyImgFunctions.h"

using namespace std;

int getMBVQquad(unsigned char r, unsigned char g, unsigned char b)
{
   if ((r + g) > 255)
   {
       if ((g + b) > 255)
       {
           if ((r + g + b) > 510)
               return 1 ;   //CMYW
           else
            return 2 ;  //MYGC
       }
        else
            return 3 ;  //RGMY
   }
   else
   {
       if ((g + b) <= 255)
       {
           if ((r + g + b) <= 255)
            return 4 ;  //KRGB
           else
            return 5 ;  //RGBM
       }
       else
        return 6 ;  //CMGB
   }
}

int mindist(double x, double y, double z, double q1[][3])
{
  double d1 = 0 ; double d2 = 0 ; double d3 = 0 ; double d4 = 0 ;
  d1 = (x-q1[0][0])*(x-q1[0][0])+(y-q1[0][1])*(y-q1[0][1])+(z-q1[0][2])*(z-q1[0][2]);
  d2 = (x-q1[1][0])*(x-q1[1][0])+(y-q1[1][1])*(y-q1[1][1])+(z-q1[1][2])*(z-q1[1][2]);
  d3 = (x-q1[2][0])*(x-q1[2][0])+(y-q1[2][1])*(y-q1[2][1])+(z-q1[2][2])*(z-q1[2][2]);
  d4 = (x-q1[3][0])*(x-q1[3][0])+(y-q1[3][1])*(y-q1[3][1])+(z-q1[3][2])*(z-q1[3][2]);
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
  return 0 ;
}
