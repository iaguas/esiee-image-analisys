/******************************************************************/
/* Equalize image function                                        */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 25th September 2016                                            */
/******************************************************************/

/*
 *  INPUT: an grey scale image to make it normalization and two integer values.
 *  REQUISITES: both values must be between 0 and 255.
 *  OUTPUT: an image that is the normalization of the original image.
 */
int lequalize(
              struct xvimage* im
);
