/******************************************************************/
/* Average filter image application function                      */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 20th November 2016                                             */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mcimage.h>
#include <tools.h>
#include <lavgfilter.h>

//#define VERBOSE

/*      
 *  INPUT: a grey scale image to make to apply a filter introduced too.
 *  REQUISITES: the size and the filter must be correlated. Windows must be smaller than images.
 *  OUTPUT: an image with the filter introduced applied.
 */
int lavgfilter(const struct xvimage* im, const int fsize, struct xvimage** newim){

    int i, j, pixindex;
    int a, sqfsize, specialfsize;
    int rs, cs, N;
    int ilimup, ilimdw, jlimup, jlimdw;
    long int sumpix;
    unsigned char *pim, *pnewim;

    // Inicialization of image parameters
    rs = rowsize(im);
    cs = colsize(im);
    N = rs*cs;
    a = fsize / 2;
    sqfsize = fsize * fsize;

    // Inicialitazion of a new image
    *newim = allocimage(NULL, rs, cs, 1, VFF_TYP_1_BYTE);
    if (*newim == NULL) {   
        fprintf(stderr,"lavgfilter: image alloc failed\n");
        return 2;
    }

    // Pointers of images
    pim = (UCHARDATA(im));
    pnewim = (UCHARDATA(*newim));

    // Trataiment of each pixel of image
    for (pixindex=0; pixindex<N; pixindex++) {
        sumpix=0;

        // Normal pixels
        if(! isBorder(pixindex, a, rs, cs)) {
            for (i=-a; i<=a; i++)
                for (j=-a; j<=a; j++)
                    sumpix += pim[pixindex + (i*rs) + j];
            pnewim[pixindex] =  sumpix / sqfsize;
        }

        // Corner pixels
        else {
            // Rows
            if (pixindex < rs*a) {
                ilimdw = pixindex % rs ? -pixindex/(rs*a)-1 : -pixindex/(rs*a);
                ilimup = a; // This could be dangerous if the windows is greater than the image. That is stupid.
            }
            else if (pixindex > N-a*rs) {
                ilimdw = -a;
                ilimup = pixindex % rs ? pixindex/(rs*a)+1 : pixindex/(rs*a);
            }
            else {
                ilimdw = -a;
                ilimup = a;
            }

            // Colums
            if (pixindex % rs < a) {
                jlimdw = pixindex % rs ? -pixindex/(rs*a)-1 : -pixindex/(rs*a);
                jlimup = a;
            }
            else if (pixindex % rs >= rs-a) {
                jlimdw = -a;
                jlimup = pixindex % rs ? pixindex/(rs*a)+1 : pixindex/(rs*a);
            }
            else {
                jlimdw = -a;
                jlimup = a;
            }

            specialfsize = 0;
            for (i=ilimdw; i<=ilimup; i++)
                for (j=jlimdw; j<=jlimup; j++){
                    #ifdef VERBOSE
                        printf("%d · %d · %d · %d · %d · %d · %d\n", pixindex, i, j, ilimdw, ilimup, jlimdw, jlimup);
                    #endif
                    sumpix += pim[pixindex + i*rs + j];
                    specialfsize++;
                }
            pnewim[pixindex] =  sumpix / specialfsize;
        }
    }
    return 0;
}
