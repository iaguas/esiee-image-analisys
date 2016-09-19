/*********************************************************/
/* Differencie image function				 */
/* Iñigo Aguas Ardaiz					 */
/* 14th September 2016					 */
/*********************************************************/
 
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h> 
#include <mcimage.h>  
#include <ldiffimage.h>  

int f_diffimage(struct xvimage* im1, struct xvimage* im2);

/* Input: 2 images to make its difference. */
/* Output: The diference of this 2 images  */
int main(int argc, char **argv) {  
	struct xvimage* im1;
	struct xvimage* im2;
 
	if (argc != 4){
		fprintf(stderr, "usage: %s in1.pgm in2.pgm out.pgm \n", argv[0]);  
	exit(1);  
	}  
 
	im1 = readimage(argv[1]);  
	im2 = readimage(argv[2]);  
	if (im1 == NULL || im2 == NULL){  
    fprintf(stderr, "diffimage: read image failed\n");  
    exit(2);  
  }  
 
	if (ldiffimage(im1, im2)){  
		fprintf(stderr, "diffimage: function f_diffimage failed\n");  
		exit(3);  
	}  
 
	writeimage(im1, argv[3]);  
	freeimage(im1);
	freeimage(im2);
 
	return 0;
}
