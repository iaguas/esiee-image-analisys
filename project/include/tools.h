/******************************************************************/
/* Project tools library                                          */
/* Project of Image analysis and processing - ESIEE               */
/* Iñigo Aguas Ardaiz                                             */
/* 21th September 2016                                            */
/******************************************************************/

// CONSTANTS
#define L 256

// BASICAL OPERATIONS
// MAX
#define max(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a > _b ? _a : _b; })
// MIN
#define min(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a < _b ? _a : _b; })

// EUCLIDEAN DISTANCE
#define sqeuclideandist(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
(_a-_b)*(_a-_b); })

/*
 * Struct for parameters of cga.
 */
struct cgaparam {
    int winsize;
    int rewinsize;
    double sigma;
    double h;
};

/*
 *  INPUT: a matrix with the pixeles of an image and the number of pixeles.
 *  REQUISITES: the number of pixeles must be real.
 *  OUTPUT: the maximum pixel value of the image.
 */
int impixmax(
    const unsigned char* pix,
    const int numelem
);

/*
 *  INPUT: a matrix with the pixeles of an image and the number of pixeles.
 *  REQUISITES: the number of pixeles must be real.
 *  OUTPUT: the minimum pixel value of the image.
 */
int impixmin(
    const unsigned char* pix,
    const int numelem
);

/*
 *  INPUT: 2 images.
 *  REQUISITES: none.
 *  OUTPUT: a boolean that says if both images are equal or not.
 */
int checkEquals(
    const struct xvimage* im1,
    const struct xvimage* im2
);

/*
 *  INPUT: an image and the pointer of the exit.
 *  REQUISITES: the image must be defined in the interval [0, 255]
 *  OUTPUT: a vector of 256 positions with the frequency of each grey level.
 *          Also an integer that says if the process is correctly done or not.
 */
int histogram(
    const struct xvimage* im,
    int** histp
);

/*
 *  INPUT: a position of the image an the dimension of it and of the filter.
 *  REQUISITES: none.
 *  OUTPUT: a boolean value that true means that not should be applied the filter.
 */
int isBorder(
    const int position,
    const int a,
    const int rs,
    const int cs
);

/*
 *  INPUT: a filter and its size.
 *  REQUISITES: the filter and the size must be correlated.
 *  OUTPUT: the filter for a concret size to make the average filter.
 */
void generateAvgFilter(
    double **filter,
    const int size
);

/*
 *  INPUT: value of sigma and if image is grayscale (1) or not (0).
 *  REQUISITES: none.
 *  OUTPUT: structure with params adjusted to project. 1 if all fails.
 */
int genCGAParameters(
    struct cgaparam *params,
    const char grayscale
);

/* 
 *  INPUT: clean and filtered images and padding (if is needed, else 0).
 *  REQUISITES: none.
 *  OUTPUT: Its PSNR value.
 */
double psnr(
    struct xvimage *imorig, 
    struct xvimage *imfilt, 
    const int a
);

/* 
 *  INPUT: clean and filtered color images and padding (if is needed, else 0).
 *  REQUISITES: none.
 *  OUTPUT: Its PSNR value.
 */
double psnr_color(
    struct xvimage *imorigr, 
    struct xvimage *imorigg, 
    struct xvimage *imorigb, 
    struct xvimage *imfiltr, 
    struct xvimage *imfiltg, 
    struct xvimage *imfiltb, 
    const int a
);