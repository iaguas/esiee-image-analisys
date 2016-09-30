imorig = imread('../../img/blobs.pgm');
imend = imread('../../img/blobsNormalize.pgm');
imout = imread('../../img/out/outNormalize.pgm');

checkEqualImg(imend, imout)

imout2 = normalize(imorig,0,255);

checkEqualImg(imend, imout2)

checkEqualImg(imout2,imout)