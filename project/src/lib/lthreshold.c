/******************************************************************/
/* Threshold image function                                       */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 20th September 2016                                            */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mcimage.h>
#include <lthreshold.h>

/*
 *  INPUT: an grey scale image to make it combinate threshold and two threshold values.
 *  REQUISITES: both values must be between 0 and 255.
 *  OUTPUT: an image that is the combinate threshold of the original image.
 */
int lthreshold(struct xvimage* im, int lowt, int higt){
#undef F_NAME
#define F_NAME "lthreshold"
    
    int index;
    unsigned char *pim;
    int rs, cs, N;

    // Inicialization of image parameters
    rs = im->row_size;
    cs = im->col_size;
    N = rs*cs;
	
    // Checking thresholds
    if ((lowt<0 || lowt>255) || (higt<0 || higt>255)){
        fprintf(stderr, "%s: threshold values out of range\n", F_NAME);
        return 1;
    }
    
    // Swaping if it is need
    if (lowt>higt){
        higt ^= lowt;
        lowt ^= higt;
        higt ^= lowt;
    }
    
    // Creating new image with tresholds.
    pim = (unsigned char*)(im->image_data);
    for (index=0; index<N; index++){
        if ((pim[index]>=lowt) && (pim[index]<=higt)) {
            pim[index] = 255;
		}
        else {
            pim[index] = 0;
        }
    }

    return 0;
}
