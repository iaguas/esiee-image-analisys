/******************************************************************/
/* Log transformation image function                              */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 29th September 2016                                            */
/******************************************************************/
 
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h> 
#include <mcimage.h>
#include <tools.h>
#include <llog.h>  

/*
 *  INPUT: an grey scale image to make it log transformation.
 *  REQUISITES: none.
 *  OUTPUT: an image that is the log transformation of the original image.
 */
int main(int argc, char **argv) {
	
    double c;
    struct xvimage *im, *endim;
 
    // Checking inputs
    if ((argc < 4) && (argc > 5)) {
        fprintf(stderr, "usage: %s in.pgm constant out.pgm [check.pgm]\n", argv[0]);
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
    
    // Calculating image processing    
    if (llog(im,c)) {
        fprintf(stderr, "%s: function llog failed\n", argv[0]);
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
    writeimage(im, argv[3]);
    freeimage(im);
 
    return 0;
}
