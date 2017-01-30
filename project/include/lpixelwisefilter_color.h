/******************************************************************/
/* Pixelwise implementation filter image function                 */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 29th January 2017                                              */
/******************************************************************/

/*      
 *  INPUT: a color image to make to apply a filter witch sigma is introduced too.
 *  REQUISITES: 
 *  OUTPUT: an image with filter applied.
 */
int lpixelwisefilter_color(
                           const struct xvimage* r,
                           const struct xvimage* g,
                           const struct xvimage* b, 
                           const double size, 
                           struct xvimage** newr,
                           struct xvimage** newg,
                           struct xvimage** newb
);
