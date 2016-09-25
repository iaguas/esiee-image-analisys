/******************************************************************/
/* Threshold image function                                       */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 20th September 2016                                            */
/******************************************************************/

#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h> 
#include <mcimage.h>  
#include <lthreshold.h>  

/*
 *  INPUT: an grey scale image to make it combinate threshold and two threshold values.
 *  REQUISITES: both values must be between 0 and 255.
 *  OUTPUT: an image that is the combinate threshold of the original image.
 */
int main(int argc, char **argv) {
    
    int lowt, higt;
    struct xvimage* im;
 
    // Checking inputs
    if (argc != 5){
        fprintf(stderr, "usage: %s in.pgm low_threshold hig_threshold out.pgm \n", argv[0]);
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
    if (lthreshold(im,lowt,higt)){
        fprintf(stderr, "%s: function lthreshold failed\n", argv[0]);
        exit(3);
    }
 
    // Writing result and finishing
    writeimage(im, argv[4]);
    freeimage(im);
 
    return 0;
}
