/******************************************************************/
/* Project tools library                                          */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 21th September 2016                                            */
/******************************************************************/

/*
 *  INPUT: a matrix with the pixeles of an image and the number of pixeles.
 *  REQUISITES: the number of pixeles must be real.
 *  OUTPUT: the maximum pixel value of the image.
 */
int impixmax(
    unsigned char* pix,
    int numelem
);

/*
 *  INPUT: a matrix with the pixeles of an image and the number of pixeles.
 *  REQUISITES: the number of pixeles must be real.
 *  OUTPUT: the minimum pixel value of the image.
 */
int impixmin(
    unsigned char* pix,
    int numelem
);

/*
 *  INPUT: 2 images.
 *  REQUISITES: none.
 *  OUTPUT: a boolean that says if both images are equal or not.
 */
int checkEquals(
    struct xvimage* im1,
    struct xvimage* im2
);
