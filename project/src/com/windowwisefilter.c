/******************************************************************/
/* CGA window-wise implementation filter image function           */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 30th January 2017                                              */
/******************************************************************/

#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h> 
#include <mcimage.h>
#include <tools.h>
#include <lwindowwisefilter.h>

/*      
 *  INPUT: a grey scale image to make to apply a filter witch size is introduced too.
 *  REQUISITES: 
 *  OUTPUT: an image with filter applied.
 */
int main(int argc, char **argv) {
	
    double sigma;
    struct xvimage *im, *outim;
 
    // Checking inputs
    if (argc < 4) {
        fprintf(stderr, "usage: %s in.pgm out.pgm\n sigma", argv[0]);
        exit(1);
    }
 
    // Reading image
    im = readimage(argv[1]);
    if (im == NULL) {
        fprintf(stderr, "%s: read image failed\n", argv[0]);
        exit(2);
    }

    // Calculating filter & image processing
    sigma = atof(argv[3]);
    if (lwindowwisefilter(im, sigma, &outim)) {
        fprintf(stderr, "%s: function lwindowwisefilter failed\n", argv[0]);
        exit(3);
    }
 
    // Writing result and finishing
    writeimage(outim, argv[2]);
    freeimage(outim);
    freeimage(im);
 
    return 0;
}
