/******************************************************************/
/* Normalize image function                                       */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 21th September 2016                                            */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mcimage.h>
#include <lnormalize.h>
#include <tools.h>

/*
 *  INPUT: a grey scale image to make it normalization and two integer values.
 *  REQUISITES: both values must be between 0 and 255.
 *  OUTPUT: an image that is the normalization of the original image.
 */
int lnormalize(struct xvimage* im, int lowt, int higt){
#undef F_NAME
#define F_NAME "lnormalize"
    
    int index;
    unsigned char *pim;
    int rs, cs, N, min, max, weight;

    // Inicialization of image parameters
    rs = im->row_size;
    cs = im->col_size;
    N = rs*cs;
	
    // Checking thresholds values
    if ((lowt<0 || lowt>L-1) || (higt<0 || higt>L-1)){
        fprintf(stderr, "%s: extreme values out of range\n", F_NAME);
        return 1;
    }
	
    // Swaping if it is need
    if (lowt>higt){
        higt ^= lowt;
        lowt ^= higt;
        higt ^= lowt;
    }
    
    // Normalization of the image
    pim = (unsigned char*)(im->image_data);
    max = impixmax(pim, N);
    min = impixmin(pim, N);
    weight = (higt-lowt)/(max-min);
    for (index=0; index<N; index++){
        pim[index] = (pim[index] - min) * weight + lowt;
    }
    
    return 0;
}
