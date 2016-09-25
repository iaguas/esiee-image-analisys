/******************************************************************/
/* Difference image library                                       */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 14th September 2016                                            */
/******************************************************************/

/*
 *  INPUT: 2 images to make it difference.
 *  REQUISITES: both images must have same size.
 *  OUTPUT: an image that is difference of this 2 original images
 */
int ldiffimage(
               struct xvimage* im1,
               struct xvimage* im2
);
