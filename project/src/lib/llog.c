/******************************************************************/
/* Log transformation image function                              */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 29th September 2016                                            */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <mcimage.h>
#include <tools.h>
#include <llog.h>

/*
 *  INPUT: a grey scale image to make it log transformation.
 *  REQUISITES: none.
 *  OUTPUT: an image that is the log transformation of the original image.
 */
int llog(struct xvimage* im, const double c){
#undef F_NAME
#define F_NAME "llog"
    
    int i;
    int rs, cs, N;
    unsigned char *pim;

    // Inicialization of image parameters
    rs = im->row_size;
    cs = im->col_size;
    N = rs*cs;
		
    // Log transformation
    pim = (unsigned char*)(im->image_data);
    for (i=0; i<N; i++)
        pim[i] = (unsigned char) 255.0 * (c * log(1.0 + pim[i]/255.0));
    
    return 0;
}
