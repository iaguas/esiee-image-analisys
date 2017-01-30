/******************************************************************/
/* Pixelwise implementation filter color image function           */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 29th January 2017                                              */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <mcimage.h>
#include <tools.h>
#include <lpixelwisefilter_color.h>

/*      
 *  INPUT: a color image to make to apply a filter witch sigma is introduced too.
 *  REQUISITES: 
 *  OUTPUT: an image with filter applied.
 */
int lpixelwisefilter_color(const struct xvimage* imr, const struct xvimage* img, const struct xvimage* imb, const double sigma, 
                     struct xvimage** newr, struct xvimage** newg, struct xvimage** newb){

    int i, j, ii, jj;
    int rs, cs, N;
    int f, r;
    int pixindex, newpixindex;
    double sqdist, h, w, const_dist;
    double sum_w, sum_uwr, sum_uwg, sum_uwb, sum_distr, sum_distg, sum_distb;
    unsigned char *pimr, *pimg, *pimb, *pnewr, *pnewg, *pnewb;
    struct cgaparam params;
    params.sigma = sigma;

    // Inicialization of image parameters
    if(genCGAParameters(&params, 0)) {   
        fprintf(stderr,"lpixelwisefilter_color: parameters creation problem. Sigma value not valid.\n");
        return 2;
    }
    f = params.winsize/2; 
    r = params.rewinsize/2;
    h = params.h;
    const_dist = 1.0 / (3*(2*f+1)*(2*f+1));
    rs = rowsize(imr);
    cs = colsize(imr);
    N = rs*cs;

    // Creation of a new image
    *newr = allocimage(NULL, rs, cs, 1, VFF_TYP_1_BYTE);
    *newg = allocimage(NULL, rs, cs, 1, VFF_TYP_1_BYTE);
    *newb = allocimage(NULL, rs, cs, 1, VFF_TYP_1_BYTE);
    if ((*newr == NULL) || (*newg == NULL) || (*newb == NULL)) {   
        fprintf(stderr,"lpixelwisefilter_color: at least one chanel of image alloc failed\n");
        return 1;
    }

    // Pointers of images
    pimr = (UCHARDATA(imr));
    pimg = (UCHARDATA(img));
    pimb = (UCHARDATA(imb));
    pnewr = (UCHARDATA(*newr));
    pnewg = (UCHARDATA(*newg));    
    pnewb = (UCHARDATA(*newb));

    // CGA algorithm
    for (pixindex=0; pixindex < rs*cs; pixindex++) {
    
        // Normal pixels
        if(! isBorder(pixindex, r, rs, cs)) { // There isn't problem with other windows inside because all will have all the pixels that it needs.

            sum_w = 0.0;
            sum_uwr = 0.0;
            sum_uwg = 0.0;
            sum_uwb = 0.0;

            for (i = -r; i <= r; i++) {
                for (j = -r; j <= r; j++) {

                    newpixindex = pixindex + (i*rs) + j;

                    // Calculate of distance
                    sum_distr = 0.0;
                    sum_distg = 0.0;
                    sum_distb = 0.0;
                    for (ii = -f; ii <= f; ii++)
                        for (jj = -f; jj <= f; jj++) {
                            sum_distr += sqeuclideandist(pimr[pixindex + (ii*rs) + jj], pimr[newpixindex + (ii*rs) + jj]);
                            sum_distg += sqeuclideandist(pimg[pixindex + (ii*rs) + jj], pimg[newpixindex + (ii*rs) + jj]);
                            sum_distb += sqeuclideandist(pimb[pixindex + (ii*rs) + jj], pimb[newpixindex + (ii*rs) + jj]);
                        }
                    sqdist = const_dist * sum_distr + const_dist * sum_distg + const_dist * sum_distb;

                    // Calculate weight and sums
                    w = exp(- max(sqdist-2*sigma*sigma, 0.0) / (h*h));
                    sum_w += w;
                    sum_uwr += pimr[newpixindex] * w;
                    sum_uwg += pimg[newpixindex] * w;
                    sum_uwb += pimb[newpixindex] * w;
                }
            }
            pnewr[pixindex] = (char) roundf(1/sum_w * sum_uwr);
            pnewg[pixindex] = (char) roundf(1/sum_w * sum_uwg);
            pnewb[pixindex] = (char) roundf(1/sum_w * sum_uwb);
        }
        else {
            pnewr[pixindex] = 0; // It could be tryed something similar of average filter.
            pnewg[pixindex] = 0;
            pnewb[pixindex] = 0;
        }
    }
    return 0;
}
