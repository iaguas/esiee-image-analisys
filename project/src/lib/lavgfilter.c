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
#include <lavgfilter.h>

/*      
 *  INPUT: a grey scale image to make to apply a filter introduced too.
 *  REQUISITES: the size and the filter must be correlated.
 *  OUTPUT: an image with the filter introduced applied.
 */
int lavgfilter(const struct xvimage* im, const int size, struct xvimage** newim){

    int i, j, k;
    int a, sqrsize, specialsize;
    int rs, cs, N;
    int ilimup, ilimdw, jlimup, jlimdw;
    long int np;
    //unsigned char *pim;
    //struct xvimage * image;

    // Inicialization of image parameters
    rs = im->row_size;
    cs = im->col_size;
    N = rs*cs;
    a = size / 2;
    sqrsize = size * size;

  //  pim = (unsigned char*)(im->image_data);
        

    printf("Esto es a %d y por tanto sqrsize %d\n", a, sqrsize);
    // Inicialitazion of a new image
    *newim = allocimage(NULL, rs, cs, 1, VFF_TYP_1_BYTE);
    if (newim == NULL) {   
        fprintf(stderr,"lavgfilter: image alloc failed\n");
        return(1);
    }
   // pnewim = (unsigned char*)((image)->image_data);

    // Trataiment of each pixel of image
    for (k=0; k<N; k++) {
        np=0;

        // Normal Pixeles
        if(! isBorder(k, a, rs, cs)) {
            for (i=-a; i<=a; i++)
                for (j=-a; j<=a; j++) {
                    //printf("%d · %d · %d \n", i, j, k);
                    np += (UCHARDATA(im))[k+(i*rs)+j];
                }
            (UCHARDATA(*newim))[k] =  np / sqrsize;
            //printf("%d · %d\n",np / sqrsize, (UCHARDATA(*newim))[i]);
        }

        else {
            // Rows
            if (k < rs*a) {
                ilimdw = k%rs ? -k/(rs*a)-1 : -k/(rs*a);
                ilimup = a; // This could be dangerous if the windows is greater than the image. That is stupid.
            }
            else if (k > N-a*rs) {
                ilimdw = -a;
                ilimup = k%rs ? k/(rs*a)+1 : k/(rs*a);
            }
            // Colums
            if (k%rs < a) {
                jlimdw = k%rs ? -k/(rs*a)-1 : -k/(rs*a);
                jlimup = a;
            }
            else if (k%rs >= rs-a) {
                jlimdw = -a;
                jlimup = k%rs ? k/(rs*a)+1 : k/(rs*a);
            }

            specialsize = 0;
            for (i=ilimdw; i<=ilimup; i++)
                for (j=jlimdw; j<=jlimup; j++){
                    //printf("%d · %d · %d · %d · %d · %d · %d\n", k, i, j, ilimdw, ilimup, jlimdw, jlimup);

                    np += (UCHARDATA(im))[k+i*rs+j];
                    specialsize++;
                }
            (UCHARDATA(*newim))[k] =  np / specialsize;
        }

//        if(k>rs*(cs-20))
 //           break;
    }
    return 0;
}
