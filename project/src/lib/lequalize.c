/******************************************************************/
/* Equalize image function                                        */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 25th September 2016                                            */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mcimage.h>
#include <tools.h>
#include <lequalize.h>

/*
 *  INPUT: an grey scale image to make it equalization.
 *  REQUISITES: none.
 *  OUTPUT: an image that is the histogram equalization of the original image.
 */
int lequalize(struct xvimage* im){
#undef F_NAME
#define F_NAME "lequalize"
    
    int i;
    int *hist = NULL;
    int rs, cs, N;
    double prob[L], acum[L], equalizer[L];
    unsigned char *pim;

    // Inicialization of image parameters
    rs = im->row_size;
    cs = im->col_size;
    N = rs*cs;

    // Calculating the histogram and probabilities
	if(histogram(im, &hist)) {
		fprintf(stderr, "%s: problem calculating the histogram\n", F_NAME);
		return 1;
	}
		
	for (i=0; i<L; i++)
		prob[i] = hist[i]/(double)N;
			
	acum[0] = prob[0];
	for (i=1; i<L; i++)
		acum[i] = acum[i-1] + prob[i];
	
	// Creating and using equalizer
	for (i=0; i<L; i++)
		equalizer[i] = acum[i] * L;
		
    pim = (unsigned char*)(im->image_data);	
	for (i=0; i<L; i++)
		pim[i] = (unsigned char) equalizer[pim[i]];
    
    return 0;
}
