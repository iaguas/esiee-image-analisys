/******************************************************************/
/* Gamma correction image function                                */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 28th September 2016                                            */
/******************************************************************/

/*
 *  INPUT: an grey scale image to make it gamma correction.
 *  REQUISITES: none.
 *  OUTPUT: an image that is the gamma correction of the original image.
 */
int lgammac(
            struct xvimage* im,
            const double c,
            const double gamma
);
