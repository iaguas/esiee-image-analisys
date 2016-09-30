/******************************************************************/
/* Project tools library                                          */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 21th September 2016                                            */
/******************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <mcimage.h>  
#include <tools.h>

/* ====================================
 *  INPUT: a matrix with the pixeles of an image and the number of pixeles.
 *  REQUISITES: the number of pixeles must be real.
 *  OUTPUT: the maximum pixel value of the image.
 */
int impixmax(
             const unsigned char* pix,
             const int numelem)
/* ==================================== */
{
    int i, max = pix[0];
   
    for (i=1; i<numelem; i++) {
        if (pix[i] > max)
            max = pix[i];
    }
	
    return max;
} // END impixmax

/* ====================================
 *  INPUT: a matrix with the pixeles of an image and the number of pixeles.
 *  REQUISITES: the number of pixeles must be real.
 *  OUTPUT: the minimum pixel value of the image.
 */

int impixmin(
             const unsigned char* pix,
             const int numelem)
/* ==================================== */
{
    int i, min = pix[0];
   
    for (i=1; i<numelem; i++) {
        if (pix[i] < min)
            min = pix[i];
    }

    return min;
} // END impixmin

/* ====================================
 *  INPUT: 2 images.
 *  REQUISITES: none.
 *  OUTPUT: a boolean that says if both images are equal or not.
 */
int checkEquals(
                const struct xvimage* im1,
                const struct xvimage* im2)
/* ==================================== */
#undef F_NAME
#define F_NAME "checkEquals"
{
	int i = 0;
	int N, eq = 1;
	unsigned char *pim1, *pim2;
	
    // Compare size of both images.
    if ((im1->row_size != im2->row_size) || (im1->col_size != im2->col_size)){
        fprintf(stderr, "%s: images of diferent sizes\n", F_NAME);
        return 1;
    }
	
    // Compare pixel by pixel
    pim1 = (unsigned char*)(im1->image_data);
    pim2 = (unsigned char*)(im2->image_data);
    N = im1->row_size * im1->col_size;
    do {
        eq = eq && (pim1[i]==pim2[i]);
    } while ((eq != 0) && (i++ > N));
    
    return eq;
} // END checkEquals

/* ====================================
 *  INPUT: an image and the pointer of the exit.
 *  REQUISITES: the image must be defined in the interval [0, 255]
 *  OUTPUT: a vector of 256 positions with the frequency of each grey level.
 *          Also an integer that says if the process is correctly done or not.
 */
int histogram(
              const struct xvimage* im,
              int** histp)
/* ==================================== */
#undef F_NAME
#define F_NAME "histogram"
{
    int i;
    int *hist;
    const unsigned char *pim;
    
    const int N = im->row_size * im->col_size;
    
    // Crear el histograma a cero ES
    hist = (int *) malloc(sizeof(int)*L);
    for (i=0; i<L; i++) {
        hist[i] = 0;
    }
    
    // Guardamos el número de píxeles ES
    pim = (unsigned char*)(im->image_data);
    for (i=1; i<N; i++) {
        hist[pim[i]] += 1;
    }
    *histp = hist;
    
    return 0;
} // END histogram
