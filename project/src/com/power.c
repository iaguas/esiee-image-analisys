/******************************************************************/
/* Power transformation image function                            */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 30th September 2016                                            */
/******************************************************************/
 
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h> 
#include <mcimage.h>
#include <tools.h>
#include <lpower.h>  

/*
 *  INPUT: a grey scale image to make its power transformation.
 *  REQUISITES: none.
 *  OUTPUT: an image that is the power transformation of the original image.
 */
int main(int argc, char **argv) {
	
    double c, p;
    struct xvimage *im, *endim;
 
    // Checking inputs
    if ((argc < 5) && (argc > 6)) {
        fprintf(stderr, "usage: %s in.pgm constant power out.pgm [check.pgm]\n", argv[0]);
        exit(1);
    }
 
    // Reading image
    im = readimage(argv[1]);
    if (im == NULL) {
        fprintf(stderr, "%s: read image failed\n", argv[0]);
        exit(2);
    }
 
    // Reading configuration values
    c = atof(argv[2]);
    p = atof(argv[3]);
    
    // Calculating image processing    
    if (lpower(im,c,p)) {
        fprintf(stderr, "%s: function lpower failed\n", argv[0]);
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
