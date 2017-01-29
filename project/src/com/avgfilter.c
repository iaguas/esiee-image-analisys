/******************************************************************/
/* Average filter image application function                      */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 20th November 2016                                             */
/******************************************************************/
 
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h> 
#include <mcimage.h>
#include <tools.h>
#include <lavgfilter.h>

/*
 *  INPUT: a grey scale image to calculate its average filter.
 *  REQUISITES: the size of filter must be odd.
 *  OUTPUT: an image that is the average filter image.
 */
int main(int argc, char **argv) {
	
  //  double *fi;
    int fsize;
    struct xvimage *im, *outim = NULL;
 
    // Checking inputs
    if (argc < 4) {
        fprintf(stderr, "usage: %s in.pgm out.pgm\n filter_size", argv[0]);
        exit(1);
    }
 
    // Reading image
    im = readimage(argv[1]);
    if (im == NULL) {
        fprintf(stderr, "%s: read image failed\n", argv[0]);
        exit(2);
    }

    // Calculating filter & image processing
    fsize = atoi(argv[3]);
    if (lavgfilter(im, fsize, &outim)) {
        fprintf(stderr, "%s: function lavgfilter failed\n", argv[0]);
        exit(3);
    }
 
    // Writing result and finishing
    writeimage(outim, argv[2]);
    freeimage(outim);
    freeimage(im);
 
    return 0;
}
