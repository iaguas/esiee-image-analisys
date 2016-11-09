/******************************************************************/
/* Filter image application function                              */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 30th September 2016                                            */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mcimage.h>
#include <tools.h>
#include <lfilter.h>

/*      
 *  INPUT: a grey scale image to make to apply a filter introduced too.
 *  REQUISITES: the size and the filter must be correlated.
 *  OUTPUT: an image with the filter introduced applied.
 */
int lfilter(const struct xvimage* im, const double* filter, const int size, struct xvimage** newim){

    int i, j, k, l;
    int a;
    int rs, cs, N;
    double np;
    unsigned char *pim, *pnewim;
    
    // Inicialization of image parameters
    rs = im->row_size;
    cs = im->col_size;
    N = rs*cs;
    a = size / 2;
    pim = (unsigned char*)(im->image_data);

    // Inicialitazion of a new image
    *newim = allocimage(NULL, rs, cs, 1, VFF_TYP_1_BYTE);
    pnewim = (unsigned char*)((*newim)->image_data);
    
    // Trataiment of the image
    for (i=a*rs; i<N-a*rs; i++)
        // Normal Pixeles
        if(! isBorder(i, a, rs)) {
            l = 0;
            np = 0;
            for (j=-a; j<a; j++)
                for (k=-a; k<a; k++)
                    np += pim[i+j*rs+k] * filter[l++];
            pnewim[i] = (unsigned char) np;
        }
        // Especial rows pixeles
        else
            pnewim[i]=pim[i];
    // Especial left columns pixeles
    for (i=0; i<rs*a; i++)
        pnewim[i]=pim[i];
    // Espacial right columns pixeles
    for (i=N-a*rs; i<N; i++)
        pnewim[i]=pim[i];
    
    return 0;
}
