#ifdef _CH_  
#pragma package <opencv>  
#endif  

#ifndef _EiC  
#include <stdio.h>  

#include "stdlib.h"  
#include "string.h"   
#include "malloc.h"   
#include "math.h"   
#include <assert.h>  
#include <ctype.h>  
#include <time.h>  
#include <cv.h>  
#include <cxcore.h>  
#include <highgui.h>  
#include <vector>  

#define NUMSIZE 2  
#define GAUSSKERN 3.5  
#define PI 3.14159265358979323846  

//Sigma of base image -- See D.L.'s paper.  
#define INITSIGMA 0.5  
//Sigma of each octave -- See D.L.'s paper.  
#define SIGMA sqrt(3)//1.6//  

//Number of scales per octave.  See D.L.'s paper.  
#define SCALESPEROCTAVE 2  
#define MAXOCTAVES 4  
int     numoctaves;

#define CONTRAST_THRESHOLD   0.02  
#define CURVATURE_THRESHOLD  10.0  
#define DOUBLE_BASE_IMAGE_SIZE 1  
#define peakRelThresh 0.8  
#define LEN 128  

// temporary storage  
CvMemStorage* storage = 0;

#endif  

#ifdef _EiC  
#define WIN32  
#endif 