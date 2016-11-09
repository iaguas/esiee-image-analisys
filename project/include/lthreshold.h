/******************************************************************/
/* Threshold image library                                        */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 20th September 2016                                            */
/******************************************************************/

/*
 *  INPUT: a grey scale image to make it combinate threshold and two threshold values.
 *  REQUISITES: both values must be between 0 and 255.
 *  OUTPUT: an image that is the combinate threshold of the original image.
 */
int lthreshold(
               struct xvimage* im,
               int lowt,
               int higt
);
