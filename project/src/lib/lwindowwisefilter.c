/******************************************************************/
/* Window-wise implementation filter image function               */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 30th January 2017                                              */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <mcimage.h>
#include <tools.h>
#include <lwindowwisefilter.h>

/*      
 *  INPUT: a grey scale image to make to apply a filter witch size is introduced too.
 *  REQUISITES: 
 *  OUTPUT: an image with filter applied.
 */
int lwindowwisefilter(const struct xvimage* im, const double sigma, struct xvimage** newim){

    int i, j, iwin, jwin, ii, jj;
    int rs, cs, N;
    int f, r;
    int pixindex, winpixindex, newpixindex;
    double sqdist, h, w, const_dist, const_norm;
    double sum_w, sum_uw, sum_dist;//, *sum_dist;
    double *previm;//, *prevwin;
    unsigned char *pim, *pnewim;
    struct cgaparam params;
    params.sigma = sigma;

    // Inicialization of image parameters
    if(genCGAParameters(&params, 1)) {   
        fprintf(stderr,"lwindowwisefilter: parameters creation problem. Sigma value not valid.\n");
        return 2;
    }
    f = params.winsize/2;
    r = params.rewinsize/2;
    h = params.h;
    const_dist = 1.0 / (3*(2*f+1)*(2*f+1)); // 1/(3*params.winsize^2)
    const_norm = 1.0 / ((2*f+1) * (2*f+1)); // 1/params.winsize^2
    rs = rowsize(im);
    cs = colsize(im);
    N = rs*cs;

    // Creation and inicialitation of a new image
    *newim = allocimage(NULL, rs, cs, 1, VFF_TYP_1_BYTE);
    if (*newim == NULL) {   
        fprintf(stderr,"lwindowwisefilter: image alloc failed\n");
        return 1;
    }

    // Allocating space for auxiliar variables
    previm = (double *) malloc(sizeof(double)*N);
    //prevwin = (double *) malloc(sizeof(double)*r*r);
    //sum_w = (double *) malloc(sizeof(double)*params.winsize);
    //sum_uw = (double *) malloc(sizeof(double)*params.winsize);
//    sum_dist = (double *) malloc(sizeof(double)*r*r);
    if ((previm==NULL) ){//|| (prevwin==NULL)){
        fprintf(stderr,"lwindowwisefilter: variables alloc failed\n");
        return 1;
    }

    for (i = 0; i < N; ++i) {
        previm[i] = 0.0;
    }

  /*  for (i = 0; i < r*r; ++i) {
        prevwin[i] = 0.0;
    }
*/
    // Pointers of images
    pim = (UCHARDATA(im));
    pnewim = (UCHARDATA(*newim));

    // CGA algorithm
    for (pixindex=0; pixindex < rs*cs; pixindex++) { // HAY QUE HACER EL ACCESO A UNA VENTANA, NO A UN PÍXEL
        
        // Normal pixels
        if (! isBorder(pixindex, r+2*f, rs, cs)) { // There isn't problem with other windows inside because all will have all the pixels that it needs.

            for (iwin=-f; iwin<=f; iwin++) {
                for (jwin=-f; jwin<=f; jwin++) {

                    winpixindex = pixindex + (iwin*rs) + jwin;

                    sum_w = 0.0;
                    sum_uw = 0.0;

                    for (i = -r; i <= r; i++) {
                        for (j = -r; j <= r; j++) {
                            
                            newpixindex = winpixindex + (i*rs) + j;

                            // Calculate of distance
                            sum_dist = 0.0;
                            for (ii = -f; ii <= f; ii++)
                                for (jj = -f; jj <= f; jj++)
                                    sum_dist += sqeuclideandist(pim[winpixindex + (ii*rs) + jj], pim[newpixindex + (ii*rs) + jj]);
                            sqdist = const_dist * sum_dist;

                            // Calculate weight and sums
                            w = exp(- max(sqdist-2*sigma*sigma, 0.0) / (h*h));
                            sum_w += w;
                            sum_uw += pim[newpixindex] * w;
                        }
                    }

                    previm[winpixindex] += 1/(sum_w * sum_uw);
                }
            }
        }
        else {
            previm[winpixindex] += 0.0; // It could be tryed something similar of average filter.
        }
    }

    printf("Llega hasta aquí\n");

    // Normalize the results
    for (i = r; i < N-r; i++) {
        pnewim[i] = (char) roundf(const_norm * previm[i]);
        printf("orig: %d, norm: %d\n",previm[i],pnewim[i]);
        
/*        double estimated_value = (1.0 / size) * estimated_pixels[j * rows + i]; // size: N^2 = (2*f+1)^2
        if (estimated_value > 255.0) {
            estimated_value = 255.0;
        }
        outputImageData[j * rows + i] = estimated_value;
        */
    }

    return 0;
}
