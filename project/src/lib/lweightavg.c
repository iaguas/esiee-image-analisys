/******************************************************************/
/* Power transformation image function                            */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 30th September 2016                                            */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <mcimage.h>
#include <tools.h>
#include <lweightavg.h>

/*       MODIFICAR     MODIFICAR     MODIFICAR     MODIFICAR     MODIFICAR     MODIFICAR     MODIFICAR
 *  INPUT: an grey scale image to make its power transformation.
 *  REQUISITES: none.
 *  OUTPUT: an image that is the power transformation of the original image.
 */
int lweightavg(const struct xvimage* im, const double* filter3, struct xvimage* newim){
    
    int i, j, k, l;
    int size = 3, a;
    int rs, cs, N;
    double np;
    unsigned char *pim, *pnewim;

    // Inicialization of image parameters
    rs = im->row_size;
    cs = im->col_size;
    N = rs*cs;
    a = size / 2;
		
    // Inicializar una nueva imagen
    newim = allocimage(NULL, rs, cs, 1, VFF_TYP_1_BYTE);
    pnewim = (unsigned char*)(newim->image_data);
    
    //
    pim = (unsigned char*)(im->image_data);
    // Dejo fuera la primera y última fila
    for (i=rs; i<N-rs; i++)
        if (i%rs != 0 && i%rs != rs-1){
            l = 0;
            np = 0;
            for (j=-a; j<a; j++)
                for (k=-a; k<a; k++)
                    np += pim[i+j*rs+k] * filter3[l++];
            pnewim[i] = (unsigned char) np;
        }
    
    return 0;
}
