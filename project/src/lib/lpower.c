/******************************************************************/
/* Power transformation image function                            */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 30th September 2016                                            */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <mcimage.h>
#include <tools.h>
#include <lpower.h>

/*
 *  INPUT: an grey scale image to make its power transformation.
 *  REQUISITES: none.
 *  OUTPUT: an image that is the power transformation of the original image.
 */
int lpower(struct xvimage* im, const double c, const double p){
    
    int i;
    int N;
    unsigned char *pim;

    // Inicialization of image parameters
    N = im->col_size * im->row_size;
		
    // Power tranformation
    pim = (unsigned char*)(im->image_data);
    for (i=0; i<N; i++)
        pim[i] = (unsigned char) min(c * pow((double) pim[i], p), 255.0);
    
    return 0;
}
