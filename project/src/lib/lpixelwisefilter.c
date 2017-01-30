/******************************************************************/
/* Pixelwise implementation filter image function                 */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 28th January 2017                                              */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <mcimage.h>
#include <tools.h>
#include <lpixelwisefilter.h>

/*      
 *  INPUT: a grey scale image to make to apply a filter witch size is introduced too.
 *  REQUISITES: 
 *  OUTPUT: an image with filter applied.
 */
int lpixelwisefilter(const struct xvimage* im, const double sigma, struct xvimage** newim){

    int i, j, ii, jj;
    int rs, cs, N;
    int f, r;
    int pixindex, newpixindex;
    double sqdist, h, w, const_dist;
    double sum_w, sum_uw, sum_dist;
    unsigned char *pim, *pnewim;
    struct cgaparam params;
    params.sigma = sigma;

    // Inicialization of image parameters
    if(genCGAParameters(&params, 1)) {   
        fprintf(stderr,"lpixelwisefilter: parameters creation problem. Sigma value not valid.\n");
       // return 2;
    }
    f = params.winsize/2; 
    r = params.rewinsize/2;
    h = params.h;
    //printf("f: %d, r: %d, \n", );
    const_dist = 1.0 / (3*(2*f+1)*(2*f+1));
    rs = rowsize(im);
    cs = colsize(im);
    N = rs*cs;

    // Inicialitazion of a new image
    *newim = allocimage(NULL, rs, cs, 1, VFF_TYP_1_BYTE);
    if (*newim == NULL) {   
        fprintf(stderr,"lpixelwisefilter: image alloc failed\n");
        return 1;
    }

    // Pointers of images
    pim = (UCHARDATA(im));
    pnewim = (UCHARDATA(*newim));

    // CGA algorithm
    for (pixindex=0; pixindex < rs*cs; pixindex++) {
    
        // Normal pixels
        if(! isBorder(pixindex, r+f, rs, cs)) { // There isn't problem with other windows inside because all will have all the pixels that it needs.

            sum_w = 0.0;
            sum_uw = 0.0;

            for (i = -r; i <= r; i++) {
                for (j = -r; j <= r; j++) {

                    newpixindex = pixindex + (i*rs) + j;

                    // Calculate of distance
                    sum_dist = 0.0;
                    for (ii = -f; ii <= f; ii++)
                        for (jj = -f; jj <= f; jj++)
                            sum_dist += sqeuclideandist(pim[pixindex + (ii*rs) + jj], pim[newpixindex + (ii*rs) + jj]);
                    sqdist = const_dist * sum_dist;

                    // Calculate weight and sums
                    w = exp(- max(sqdist-2*sigma*sigma, 0.0) / (h*h));
                    sum_w += w;
                    sum_uw += pim[newpixindex] * w;
                }
            }
            pnewim[pixindex] = (char) 1/sum_w * sum_uw; // REVISAR
        }
        else {
            pnewim[pixindex] = 0; // It could be tryed something similar of average filter.
        }
    }
    return 0;
}
