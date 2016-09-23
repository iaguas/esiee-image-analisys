/******************************************************************/
/* Difference image function                                      */
/* Project of Image analisys and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 14th September 2016                                            */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mcimage.h>
#include <ldiffimage.h>

/*
 *  INPUT: 2 images to make it difference.
 *  REQUISITES: both images must have same size.
 *  OUTPUT: an image that is difference of this 2 original images
 */
int ldiffimage(struct xvimage* im1, struct xvimage* im2) {
#undef F_NAME
#define F_NAME "ldiffimage"
    
	int index;
	unsigned char *pim1;
	unsigned char *pim2;
	int rs, cs, N;
	
	// Compare the dimensions of the images and make error if is needed.
    if ((im1->row_size != im2->row_size) || (im1->col_size != im2->col_size)) {
        fprintf(stderr,"%s : not equal image dimensions\n", F_NAME);
		return 1;
    }

	// Inicialization of basic variables.
    rs = im1->row_size;
	cs = im2->col_size;
    N = rs*cs;

    // Taking data of images and processing.
	pim1 = (unsigned char*)(im1->image_data);
	pim2 = (unsigned char*)(im2->image_data);
	for (index=0; index<N; index++) {
		pim1[index] = abs(pim1[index]-pim2[index]);
	}

	return 0;
}
