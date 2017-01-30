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
#include <math.h>
#include <mcimage.h>  
#include <tools.h>

// Some interesting macros for min, max and another math operations in .h file.

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

/* ====================================
 *  INPUT: a position of the image an the dimension of it and of the filter.
 *  REQUISITES: none.
 *  OUTPUT: a boolean value that true means that not should be applied the filter.
 */
int isBorder(
             const int position,
             const int a,
             const int rs,
             const int cs)
/* ==================================== */
#undef F_NAME
#define F_NAME "isBorder"
{
// TODO: Not only for square images.
//      0    to   a-1     left border
//    rs-1   to   rs-a    rigth border
    int i, isBorder=0, N=rs*cs;
    
    if((position < rs*a) || (position > N-a*rs))
       isBorder=1;
    i=0;
    while (i<a && !isBorder) {
        isBorder += (position % rs == i);
        i++;
    }
    i=rs-1;
    while (i>=rs-a && !isBorder) {
        isBorder += (position % rs == i);
        i--;
    }
    
    return isBorder;
} // END isBorder

/* ====================================
 *  INPUT: a filter pointer and its size.
 *  REQUISITES: the filter and the size must be correlated.
 *  OUTPUT: the filter for a concret size to make the average filter.
 */
void generateAvgFilter(
                       double **filter,
                       const int size)
/* ==================================== */
#undef F_NAME
#define F_NAME "generateAvgFilter"
{
    double *f;
    int i, len = size*size;
    double weight = 1.0/len;
    
    f = (double *)malloc(len * sizeof(double));
    
    for (i=0; i<len; i++)
        f[i] = weight;
    
    *filter = f;
} // END generateAvgFilter

/* ====================================
 *  INPUT: value of sigma and if image is grayscale (1) or not (0).
 *  REQUISITES: none.
 *  OUTPUT: structure with params adjusted to project. 1 if all fails.
 */
int genCGAParameters(
                     struct cgaparam* params,
                     const char grayscale)
/* ==================================== */
#undef F_NAME
#define F_NAME "genCGAParameters"
{
    if (grayscale) 
        if ((params->sigma>0.0) && (params->sigma<=15.0)){
            params->winsize = 3;
            params->rewinsize = 21;
            params->h = 0.4 * params->sigma;
        }
        else if ((params->sigma>15.0) && (params->sigma<=30.0)){
            params->winsize = 5;
            params->rewinsize = 21;
            params->h = 0.4 * params->sigma;
        }
        else if ((params->sigma>30.0) && (params->sigma<=45.0)){
            params->winsize = 7;
            params->rewinsize = 35;
            params->h = 0.35 * params->sigma;
        }
        else if ((params->sigma>45.0) && (params->sigma<=75.0)){
            params->winsize = 9;
            params->rewinsize = 35;
            params->h = 0.35 * params->sigma;
        } 
        else if ((params->sigma>75.0) && (params->sigma<=100.0)){
            params->winsize = 11;
            params->rewinsize = 35;
            params->h = 0.35 * params->sigma;
        }
        else // Sigma is not correct.
            return 1; 
    else
        if ((params->sigma>0.0) && (params->sigma<=25.0)){
            params->winsize = 3;
            params->rewinsize = 21;
            params->h = 0.55 * params->sigma;
        }
        else if ((params->sigma>25.0) && (params->sigma<=55.0)){
            params->winsize = 5;
            params->rewinsize = 35;
            params->h = 0.4 * params->sigma;
        }
        else if ((params->sigma>55.0) && (params->sigma<=100.0)){
            params->winsize = 7;
            params->rewinsize = 35;
            params->h = 0.35 * params->sigma;
        }
        else // Sigma is not correct
            return 1;

    return 0;
} // END genCGAParameters

/* ====================================
 *  INPUT: clean and filtered images and padding (if is needed, else 0).
 *  REQUISITES: none.
 *  OUTPUT: Its PSNR value.
 */
double psnr(
            struct xvimage *imorig, 
            struct xvimage *imfilt, 
            const int a)
/* ==================================== */
#undef F_NAME
#define F_NAME "psnr"
{
    int i, j;
    const int rs = rowsize(imorig), cs = colsize(imorig);
    const int pixelstreated = (rs - 2*a) * (cs - 2*a);
    double mxpeak = -1.0;
    double mse = 0.0;

    const unsigned char *pimorig = UCHARDATA(imorig);
    const unsigned char *pimfilt = UCHARDATA(imfilt);

    for (i=a; i<(rs-a); i++) {
        for (j=a; j<(cs-a); j++) {
            mse += pow((pimorig[i*rs + j] - pimfilt[i*rs + j]), 2.0);
            if (mxpeak < pimorig[i*rs + j]) { // Peak value
                mxpeak = pimorig[i*rs + j];
            }
        }
    }

    mse = (1.0 / pixelstreated) * mse;
    return 10.0 * log10((mxpeak*mxpeak) / mse);
} // END psnr

/* ====================================
 *  INPUT: clean and filtered color images and padding (if is needed, else 0).
 *  REQUISITES: none.
 *  OUTPUT: Its PSNR value.
 */
double psnr_color(
                  struct xvimage *imorigr, 
                  struct xvimage *imorigg, 
                  struct xvimage *imorigb, 
                  struct xvimage *imfiltr, 
                  struct xvimage *imfiltg, 
                  struct xvimage *imfiltb, 
                  const int a)
/* ==================================== */
#undef F_NAME
#define F_NAME "psnr_color"
{
    int i, j;
    const int rs = rowsize(imorigr), cs = colsize(imorigr);
    const int pixelstreated = (rs - 2*a) * (cs - 2*a);
    double mxpeak=-255.0;
    double mser=0.0, mseg=0.0, mseb=0.0, mse;

    const unsigned char *pimorigr = UCHARDATA(imorigr);
    const unsigned char *pimorigg = UCHARDATA(imorigg);
    const unsigned char *pimorigb = UCHARDATA(imorigb);
    const unsigned char *pimfiltr = UCHARDATA(imfiltr);
    const unsigned char *pimfiltg = UCHARDATA(imfiltg);
    const unsigned char *pimfiltb = UCHARDATA(imfiltb);

    for (i=a; i<(rs-a); i++) {
        for (j=a; j<(cs-a); j++) {
            mser += pow((pimorigr[i*rs + j] - pimfiltr[i*rs + j]), 2.0);
            mseg += pow((pimorigg[i*rs + j] - pimfiltg[i*rs + j]), 2.0);
            mseb += pow((pimorigb[i*rs + j] - pimfiltb[i*rs + j]), 2.0);
        }
    }

    mse = (1.0 / (3*pixelstreated)) * (mser + mseg + mseb);
    return 10.0 * log10((mxpeak*mxpeak) / mse);
} // END psnr_color
