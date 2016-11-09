/******************************************************************/
/* Log transformation image function                              */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 28th September 2016                                            */
/******************************************************************/

/*
 *  INPUT: a grey scale image to make it log transformation.
 *  REQUISITES: none.
 *  OUTPUT: an image that is the log transformation of the original image.
 */
int llog(
            struct xvimage* im,
            const double c
);
