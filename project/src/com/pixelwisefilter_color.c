/******************************************************************/
/* CGA pixel wise implementation filter color image function      */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 29th January 2017                                              */
/******************************************************************/
 
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h> 
#include <mcimage.h>
#include <tools.h>
#include <lpixelwisefilter_color.h>

/*
 *  INPUT: a color image to make to apply a filter witch size is introduced too.
 *  REQUISITES: an odd number for filter.
 *  OUTPUT: an image with filter applied.
 */
int main(int argc, char **argv) {
	
    int sigma;
    struct xvimage *r, *g, *b, *outr, *outg, *outb;
    
    // Checking inputs
    if (argc < 4) {
        fprintf(stderr, "usage: %s in.pgm out.pgm\n sigma", argv[0]);
        exit(1);
    }
 
    // Reading image
    readrgbimage(argv[1], &r, &g, &b);
    if (r == NULL || g == NULL || b == NULL) {
        fprintf(stderr, "%s: read image failed\n", argv[0]);
        exit(2);
    }

    // Calculating filter & image processing
    sigma = atof(argv[3]);
    if (lpixelwisefilter_color(r,g,b, sigma, &outr,&outg,&outb)) {
        fprintf(stderr, "%s: function lpixelwisefilter_color failed\n", argv[0]);
        exit(3);
    }
 
    // Writing result and finishing
    writergbimage(outr, outg, outb, argv[2]);
    freeimage(r);
    freeimage(g);
    freeimage(b);
    freeimage(outr);
    freeimage(outg);
    freeimage(outb);

    return 0;
}