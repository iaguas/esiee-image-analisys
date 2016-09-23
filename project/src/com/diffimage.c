/******************************************************************/
/* Difference image function                                      */
/* Project of Image analisys and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 14th September 2016                                            */
/******************************************************************/
 
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h> 
#include <mcimage.h>  
#include <ldiffimage.h>  

/*
 *  INPUT: 2 images to make it difference.
 *  REQUISITES: both images must have same size.
 *  OUTPUT: an image that is difference of this 2 original images
 */
int main(int argc, char **argv) {
#undef F_NAME
#define F_NAME "diffimage"
    
	struct xvimage* im1;
	struct xvimage* im2;
 
	if (argc != 4){
		fprintf(stderr, "usage: %s in1.pgm in2.pgm out.pgm\n", argv[0]);
		exit(1);  
	}  
 
	im1 = readimage(argv[1]);  
	im2 = readimage(argv[2]);  
	if (im1 == NULL || im2 == NULL){  
		fprintf(stderr, "%s: read image failed\n", F_NAME);
		exit(2);  
	}  
 
	if (ldiffimage(im1, im2)){  
		fprintf(stderr, "%s: function ldiffimage failed\n", F_NAME);
		exit(3);  
	}  
 
	writeimage(im1, argv[3]);  
	freeimage(im1);
	freeimage(im2);
 
	return 0;
}