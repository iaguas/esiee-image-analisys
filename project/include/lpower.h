/******************************************************************/
/* Power transformation image function                            */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 30th September 2016                                            */
/******************************************************************/

/*
 *  INPUT: an grey scale image to make its power transformation.
 *  REQUISITES: none.
 *  OUTPUT: an image that is the power transformation of the original image.
 */
int lpower(
           struct xvimage* im,
           const double c,
           const double pow
);
