/******************************************************************/
/* Laplacian filter image function                                */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 1st November 2016                                              */
/******************************************************************/
 
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h> 
#include <mcimage.h>
#include <tools.h>
#include <lfilter.h>

/*
 *  INPUT: a grey scale image to calculate its laplacian filter.
 *  REQUISITES: none.
 *  OUTPUT: an image that is the laplacian filter image in the route indicated.
 */
int main(int argc, char **argv) {
	
    double fi[] = {0.0, 1.0, 0.0, 1.0, -4.0, 1.0, 0.0, 1.0, 0.0};
    int size = 3;
    struct xvimage *im, *endim, *outim = NULL;
 
    // Checking inputs
    if ((argc < 3) && (argc > 4)) {
        fprintf(stderr, "usage: %s in.pgm out.pgm [check.pgm]\n", argv[0]);
        exit(1);
    }
 
    // Reading image
    im = readimage(argv[1]);
    if (im == NULL) {
        fprintf(stderr, "%s: read image failed\n", argv[0]);
        exit(2);
    }
    
    // Calculating filter & image processing
    if (lfilter(im, fi, size, &outim)) {
        fprintf(stderr, "%s: function lfilter failed\n", argv[0]);
        exit(3);
    }
 
    // Checking result
    if (argc == 4) {
        endim = readimage(argv[3]);
        if (checkEquals(im, endim))
            printf("Great! Both images are the same.\n");
        else
            printf("Ups! You should review your code, as both images shoul be equal.\n");
        freeimage(endim);
    }
 
    // Writing result and finishing
    writeimage(outim, argv[2]);
    freeimage(outim);
    freeimage(im);
 
    return 0;
}
