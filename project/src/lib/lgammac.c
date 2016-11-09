/******************************************************************/
/* Gamma correction image function                                */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 28th September 2016                                            */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <mcimage.h>
#include <tools.h>
#include <lgammac.h>

/*
 *  INPUT: a grey scale image to make it gamma correction.
 *  REQUISITES: none.
 *  OUTPUT: an image that is the gamma correction of the original image.
 */
int lgammac(struct xvimage* im, const double c, const double gamma){
#undef F_NAME
#define F_NAME "lgammac"
    
    int i;
    int rs, cs, N;
    unsigned char *pim;

    // Inicialization of image parameters
    rs = im->row_size;
    cs = im->col_size;
    N = rs*cs;
		
    // Gamma correction
    pim = (unsigned char*)(im->image_data);
    for (i=0; i<N; i++)
        pim[i] = (unsigned char) 255.0 * pow((double)pim[i]/255.0, gamma);
    
    return 0;
}
