/*********************************************************/
/* Differencie image function				 */
/* Iñigo Aguas Ardaiz					 */
/* 14th September 2016					 */
/*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mcimage.h>
#include <ldiffimage.h>

/* Input: 2 images to make its difference.
   Output: The diference of this 2 images */
int ldiffimage(struct xvimage* im1, struct xvimage* im2){
	
	int index;
	unsigned char *pim1;
	unsigned char *pim2;
	int rs, cs, N;

	// TODO: We have to checked that both images have the same size?

	rs = im1->row_size;
	cs = im2->col_size;
	N = rs*cs;

	pim1 = (unsigned char*)(im1->image_data);
	pim2 = (unsigned char*)(im2->image_data);
	for (index=0; index<N; index++){
		pim1 = abs(pim1[index]-pim2[index]);
	}

	return 0;
}
