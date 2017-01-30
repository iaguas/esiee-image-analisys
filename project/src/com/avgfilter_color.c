/******************************************************************/
/* Weight filter image function                                   */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 28th January 2017                                              */
/******************************************************************/

#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h> 
#include <mcimage.h>
#include <tools.h>
#include <lavgfilter.h>

/*
 *  INPUT: a color image to calculate its average filter.
 *  REQUISITES: an odd number as size.
 *  OUTPUT: another image that is the average filter of it.
 */
int main(int argc, char **argv) {
	
    int fsize;
    struct xvimage *r, *g, *b, *outr, *outg, *outb;
 
    // Checking inputs
    if (argc < 4) {
        fprintf(stderr, "usage: %s in.ppm out.ppm filter_size\n", argv[0]);
        exit(1);
    }
 
    // Reading image
    readrgbimage(argv[1], &r, &g, &b);
    if (r == NULL || g == NULL || b == NULL) {
        fprintf(stderr, "%s: read image failed\n", argv[0]);
        exit(2);
    }

    // Calculating filter & image processing
    fsize = atoi(argv[3]);
    if (lavgfilter(r, fsize, &outr) || lavgfilter(g, fsize, &outg) || lavgfilter(b, fsize, &outb)) {
        fprintf(stderr, "%s: function lavgfilter failed in at least one of channels\n", argv[0]);
        exit(3);
    }
 
    // Writing result and finishing
    writergbimage(outr, outg, outb, argv[2]);
    freeimage(r);
    freeimage(g);
    freeimage(b);
    freeimage(outr);
    freeimage(outg);
    freeimage(outb);

    return 0;
}
