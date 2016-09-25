/******************************************************************/
/* Normalize image function                                       */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 21th September 2016                                            */
/******************************************************************/
 
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h> 
#include <mcimage.h>
#include <tools.h>
#include <lnormalize.h>  

/*
 *  INPUT: an grey scale image to make it normalization and two integer values.
 *  REQUISITES: both values must be between 0 and 255.
 *  OUTPUT: an image that is the normalization of the original image.
 */
int main(int argc, char **argv) {  
	
    int lowt, higt;
    struct xvimage *im, *endim;
 
    // Checking inputs
    if ((argc < 5) && (argc > 6)) {
        fprintf(stderr, "usage: %s in.pgm low_extrem hig_extrem out.pgm [check.pgm]\n", argv[0]);
        exit(1);
    }
 
    // Reading image
    im = readimage(argv[1]);
    if (im == NULL){
        fprintf(stderr, "%s: read image failed\n", argv[0]);
        exit(2);
    }
 
    // Calculating image processing
    lowt = atoi(argv[2]);
    higt = atoi(argv[3]);
    if (lnormalize(im,lowt,higt)) {
        fprintf(stderr, "%s: function lnormalize failed\n", argv[0]);
        exit(3);
    }
 
    // Checking result
    if (argc == 6) {
        endim = readimage(argv[5]);
        if (checkEquals(im, endim))
            printf("Great! Both images are the same.\n");
        else
            printf("Ups! You should review your code, as both images shoul be equal.\n");
        freeimage(endim);
    }
 
    // Writing result and finishing
    writeimage(im, argv[4]);
    freeimage(im);
 
    return 0;
}
