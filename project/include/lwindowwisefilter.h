/******************************************************************/
/* Window-wise implementation filter image function                 */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 30th January 2017                                              */
/******************************************************************/

/*      
 *  INPUT: a grey scale image to make to apply a filter witch size is introduced too.
 *  REQUISITES: 
 *  OUTPUT: an image with filter applied.
 */
int lwindowwisefilter(
                      const struct xvimage* im, 
                      const double size, 
                      struct xvimage** newim
);
