/******************************************************************/
/* Equalize image function                                        */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 25th September 2016                                            */
/******************************************************************/
 
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h> 
#include <mcimage.h>
#include <tools.h>
#include <lequalize.h>  

/*
 *  INPUT: a grey scale image to make it normalization and two integer values.
 *  REQUISITES: both values must be between 0 and 255.
 *  OUTPUT: an image that is the normalization of the original image.
 */
int main(int argc, char **argv) {  
	
    struct xvimage *im, *endim;
 
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
 
    // Calculating image processing    
    if (lequalize(im)) {
        fprintf(stderr, "%s: function lequalize failed\n", argv[0]);
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
    writeimage(im, argv[2]);
    freeimage(im);
 
    return 0;
}
