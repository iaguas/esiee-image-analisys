/******************************************************************/
/* Weight average filter image function                           */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 30th September 2016                                            */
/******************************************************************/
 
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h> 
#include <mcimage.h>
#include <tools.h>
#include <lfilter.h>
#include <lweightavg.h>

/*
 *  INPUT: a grey scale image to calculate its average filter.
 *  REQUISITES: the size of filter must be odd.
 *  OUTPUT: an image that is the average filter image.
 */
int main(int argc, char **argv) {
	
    double *fi;
    int size;
    struct xvimage *im, *endim, *outim = NULL;
 
    // Checking inputs
    if ((argc < 4) && (argc > 5)) {
        fprintf(stderr, "usage: %s in.pgm filter_size out.pgm [check.pgm]\n", argv[0]);
        exit(1);
    }
 
    // Reading image
    im = readimage(argv[1]);
    if (im == NULL) {
        fprintf(stderr, "%s: read image failed\n", argv[0]);
        exit(2);
    }
    
    // Calculating filter & image processing
    size = atoi(argv[2]);
    generateAvgFilter(&fi, size);
    if (lfilter(im, fi, size, &outim)) {
        fprintf(stderr, "%s: function lfilter failed\n", argv[0]);
        exit(3);
    }
 
    // Checking result
    if (argc == 5) {
        endim = readimage(argv[4]);
        if (checkEquals(im, endim))
            printf("Great! Both images are the same.\n");
        else
            printf("Ups! You should review your code, as both images shoul be equal.\n");
        freeimage(endim);
    }
 
    // Writing result and finishing
    writeimage(outim, argv[3]);
    freeimage(outim);
    freeimage(im);
 
    return 0;
}
