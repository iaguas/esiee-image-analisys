/******************************************************************/
/* Normalize image library                                        */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 21th September 2016                                            */
/******************************************************************/

/*
 *  INPUT: an grey scale image to make it normalization and two integer values.
 *  REQUISITES: both values must be between 0 and 255.
 *  OUTPUT: an image that is the normalization of the original image.
 */
int lnormalize(
               struct xvimage* im,
               int lowt,
               int higt
);
