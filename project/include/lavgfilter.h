/******************************************************************/
/* Average filter image application function                      */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 20th November 2016                                             */
/******************************************************************/

/*
 *  INPUT: a grey scale image to make to apply a filter introduced too.
 *  REQUISITES: the size and the filter must be correlated.
 *  OUTPUT: an image with the filter introduced applied.
 */
int lavgfilter(
               const struct xvimage* im,
               const int size,
               struct xvimage** newim
);
